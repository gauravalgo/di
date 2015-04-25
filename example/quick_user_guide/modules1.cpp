//
// Copyright (c) 2012-2015 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/di.hpp>
#include <memory>
#include <cassert>

namespace di = boost::di;

struct i1 { virtual ~i1() noexcept = default; virtual void dummy1() = 0; };
struct i2 { virtual ~i2() noexcept = default; virtual void dummy2() = 0; };
struct impl1 : i1 { void dummy1() override { } };
struct impl2 : i2 { void dummy2() override { } };

struct c {
    c(std::unique_ptr<i1> i1
    , std::unique_ptr<i2> i2
    , int i)
        : i1_(std::move(i1))
        , i2_(std::move(i2))
        , i(i)
    { }

    std::unique_ptr<i1> i1_;
    std::unique_ptr<i2> i2_;
    int i = 0;
};

struct module1 {
    auto configure() const noexcept {
        return di::make_injector(
            di::bind<i1, impl1>
          , di::bind<int>.to(42)
        );
    }
};

struct module2 {
    auto configure() const noexcept {
        return di::make_injector(
            di::bind<i2, impl2>
        );
    };
};

int main() {
    auto injector = di::make_injector(
        module1{}, module2{}
    );

    auto object = injector.create<std::unique_ptr<c>>();
    assert(dynamic_cast<impl1*>(object->i1_.get()));
    assert(dynamic_cast<impl2*>(object->i2_.get()));
    assert(42 == object->i);

    auto up1 = injector.create<std::unique_ptr<i1>>();
    assert(dynamic_cast<impl1*>(up1.get()));

    auto up2 = injector.create<std::unique_ptr<i2>>();
    assert(dynamic_cast<impl2*>(up2.get()));
}

