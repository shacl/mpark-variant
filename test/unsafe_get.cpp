// MPark.Variant
//
// Copyright Michael Park, 2015-2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at
// http://boost.org/LICENSE_1_0.txt)

#include <mpark/variant.hpp>

#include <gtest/gtest.h>

#include "util.hpp"

namespace lib = mpark::lib;

TEST(Get, HoldsAlternative) {
  mpark::variant<int, std::string> v(42);
  EXPECT_TRUE(mpark::holds_alternative<0>(v));
  EXPECT_FALSE(mpark::holds_alternative<1>(v));
  EXPECT_TRUE(mpark::holds_alternative<int>(v));
  EXPECT_FALSE(mpark::holds_alternative<std::string>(v));

  /* constexpr */ {
    constexpr mpark::variant<int, const char *> cv(42);
    static_assert(mpark::holds_alternative<0>(cv), "");
    static_assert(!mpark::holds_alternative<1>(cv), "");
    static_assert(mpark::holds_alternative<int>(cv), "");
    static_assert(!mpark::holds_alternative<const char *>(cv), "");
  }
}

TEST(Get, MutVarMutType) {
  mpark::variant<int> v(42);
  EXPECT_EQ(42, mpark::unsafe::get<int>(v));
  // Check qualifier.
  EXPECT_EQ(LRef, get_qual(mpark::unsafe::get<int>(v)));
  EXPECT_EQ(RRef, get_qual(mpark::unsafe::get<int>(lib::move(v))));
}

TEST(Get, MutVarConstType) {
  mpark::variant<const int> v(42);
  EXPECT_EQ(42, mpark::unsafe::get<const int>(v));
  // Check qualifier.
  EXPECT_EQ(ConstLRef, get_qual(mpark::unsafe::get<const int>(v)));
  EXPECT_EQ(ConstRRef, get_qual(mpark::unsafe::get<const int>(lib::move(v))));
}

TEST(Get, ConstVarMutType) {
  const mpark::variant<int> v(42);
  EXPECT_EQ(42, mpark::unsafe::get<int>(v));
  // Check qualifier.
  EXPECT_EQ(ConstLRef, get_qual(mpark::unsafe::get<int>(v)));
  EXPECT_EQ(ConstRRef, get_qual(mpark::unsafe::get<int>(lib::move(v))));

  /* constexpr */ {
    constexpr mpark::variant<int> cv(42);
    static_assert(42 == mpark::unsafe::get<int>(cv), "");
    // Check qualifier.
    static_assert(ConstLRef == get_qual(mpark::unsafe::get<int>(cv)), "");
    static_assert(ConstRRef == get_qual(mpark::unsafe::get<int>(lib::move(cv))),
                  "");
  }
}

TEST(Get, ConstVarConstType) {
  const mpark::variant<const int> v(42);
  EXPECT_EQ(42, mpark::unsafe::get<const int>(v));
  // Check qualifier.
  EXPECT_EQ(ConstLRef, get_qual(mpark::unsafe::get<const int>(v)));
  EXPECT_EQ(ConstRRef, get_qual(mpark::unsafe::get<const int>(lib::move(v))));

  /* constexpr */ {
    constexpr mpark::variant<const int> cv(42);
    static_assert(42 == mpark::unsafe::get<const int>(cv), "");
    // Check qualifier.
    static_assert(ConstLRef == get_qual(mpark::unsafe::get<const int>(cv)), "");
    static_assert(
        ConstRRef == get_qual(mpark::unsafe::get<const int>(lib::move(cv))),
        "");
  }
}

TEST(GetIf, MutVarMutType) {
  mpark::variant<int> v(42);
  EXPECT_EQ(42, *mpark::unsafe::get_if<int>(&v));
  // Check qualifier.
  EXPECT_EQ(Ptr, get_qual(mpark::unsafe::get_if<int>(&v)));
}

TEST(GetIf, MutVarConstType) {
  mpark::variant<const int> v(42);
  EXPECT_EQ(42, *mpark::unsafe::get_if<const int>(&v));
  // Check qualifier.
  EXPECT_EQ(ConstPtr, get_qual(mpark::unsafe::get_if<const int>(&v)));
}

TEST(GetIf, ConstVarMutType) {
  const mpark::variant<int> v(42);
  EXPECT_EQ(42, *mpark::unsafe::get_if<int>(&v));
  // Check qualifier.
  EXPECT_EQ(ConstPtr, get_qual(mpark::unsafe::get_if<int>(&v)));

  /* constexpr */ {
    static constexpr mpark::variant<int> cv(42);
    static_assert(42 == *mpark::unsafe::get_if<int>(&cv), "");
    // Check qualifier.
    static_assert(ConstPtr == get_qual(mpark::unsafe::get_if<int>(&cv)), "");
  }
}

TEST(GetIf, ConstVarConstType) {
  const mpark::variant<const int> v(42);
  EXPECT_EQ(42, *mpark::unsafe::get_if<const int>(&v));
  // Check qualifier.
  EXPECT_EQ(ConstPtr, get_qual(mpark::unsafe::get_if<const int>(&v)));

  /* constexpr */ {
    static constexpr mpark::variant<const int> cv(42);
    static_assert(42 == *mpark::unsafe::get_if<const int>(&cv), "");
    // Check qualifier.
    static_assert(ConstPtr == get_qual(mpark::unsafe::get_if<const int>(&cv)),
                  "");
  }
}
