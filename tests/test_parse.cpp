#include <gtest/gtest.h>

#include "parse.h"

TEST(abacus, can_parse_variable_name)
{
    EXPECT_NO_THROW(abacus::detail::parse("xsdf"));
}

TEST(abacus, can_parse_variable_name_with_underscore)
{
    EXPECT_NO_THROW(abacus::detail::parse("xsdf_"));
}

TEST(abacus, can_parse_variable_name_with_digit)
{
    EXPECT_NO_THROW(abacus::detail::parse("xs112354df_"));
}

TEST(abacus, can_parse_variable_name_starting_with_underscore)
{
    EXPECT_NO_THROW(abacus::detail::parse("_xsdf_"));
}

TEST(abacus, cannot_parse_variable_name_starting_with_digit)
{
    EXPECT_THROW(abacus::detail::parse("1xsdf_"), std::runtime_error);
}

TEST(abacus, can_parse_variable_name_starting_with_function_name)
{
    EXPECT_NO_THROW(abacus::detail::parse("sin1xsdf_"));
}
