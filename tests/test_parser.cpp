#include <gtest/gtest.h>

#include "abacus/parser.h"
#include "abacus/evaluate.h"

TEST(parser, can_create)
{
    auto parser = abacus::parser();
}

TEST(parser, can_parse_evaluate)
{
    auto parser = abacus::parser();
    const auto operand = parser.parse("7*8-43");
    EXPECT_EQ(13, abacus::evaluate(operand));
}
