//
// Copyright (c) 2012-2015 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <memory>
#include "boost/di/scopes/singleton.hpp"
#include "common/fakes/fake_provider.hpp"

namespace boost { namespace di { inline namespace v1 { namespace scopes {

test create_singleton = [] {
    singleton::scope<int, int> singleton;
    std::shared_ptr<int> object1 = singleton.create<int>(fake_provider<int>{});
    std::shared_ptr<int> object2 = singleton.create<int>(fake_provider<int>{});
    expect_eq(object1, object2);
};

struct c { };
auto has_shared_ptr__(c&&) -> std::false_type;

test create_singleton_from_ptr_to_ptr = [] {
    singleton::scope<c, c> singleton;
    c& object1 = singleton.create<c>(fake_provider<c>{});
    c& object2 = singleton.create<c>(fake_provider<c>{});
    expect_eq(&object1, &object2);
};

test create_singleton_from_ptr_to_const_ptr = [] {
    singleton::scope<c, c> singleton;
    const c& object1 = singleton.create<c>(fake_provider<c>{});
    const c& object2 = singleton.create<c>(fake_provider<c>{});
    expect_eq(&object1, &object2);
};

}}}} // boost::di::v1::scopes

