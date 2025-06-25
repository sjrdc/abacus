#include <gtest/gtest.h>

#include "abacus/parser.h"
#include "abacus/evaluate.h"

TEST(parser, can_create)
{
    auto parser = abacus::parser();
}

TEST(parser, can_evaluate_resulting_numeric_expression)
{
    auto parser = abacus::parser();
    const auto operand = parser.parse("7*8-43");
    EXPECT_EQ(13, abacus::evaluate(operand));
}

TEST(parser, throws_upon_evaluating_undefined_variable)
{
    auto parser = abacus::parser();
    const auto operand = parser.parse("7*x-43");
    EXPECT_THROW(abacus::evaluate(operand), std::runtime_error);
}

TEST(parser, can_evaluate_variable_expression)
{
    auto parser = abacus::parser();
    const auto operand = parser.parse("7*x-43");
    parser.parse("x = 3");
    EXPECT_EQ(7*3-43, abacus::evaluate(operand));
}
