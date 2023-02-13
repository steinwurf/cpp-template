// Copyright (c) Steinwurf ApS 2020.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <{{cookiecutter.name}}/version.hpp>
#include <gtest/gtest.h>

TEST(test_some, return_value_of_some_method)
{
    auto version = {{cookiecutter.namespace}}::version();
    EXPECT_EQ(version, "0.0.0");
}
