/*
    This file is part of abacus
    Copyright(C) 2025 Sjoerd Crijns

    This program is free software : you can redistribute it and /or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see < https://www.gnu.org/licenses/>.
*/

#include "abacus.h"
#include "parse.h"
#include "calculator.h"

#include <gtest/gtest.h>

#include <numbers>

#define MAKE_TEST_VALUE(VAR) test_parameter(#VAR, VAR)
#define MAKE_TEST_VALUE_FROM_STD_FUNCTION(VAR) test_parameter(#VAR, std::VAR)

namespace
{
    struct test_parameter
    {
        std::string expression;
        double value;
    };

    class ParseAndCheck :
        public testing::TestWithParam<test_parameter>
    {
    };

    auto number_arithmetic_test_values = testing::Values<test_parameter>(
        MAKE_TEST_VALUE((1. + 1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(abs(1. + 1 + 1. + 2)),
        MAKE_TEST_VALUE((1. - 1.)),
        MAKE_TEST_VALUE((2. * 3.)),
        MAKE_TEST_VALUE((12. / 3.)),
        test_parameter("2. ^ 5.", 32.),
        test_parameter("e", std::numbers::e),
        test_parameter("pi", std::numbers::pi),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(sin(1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(sinh(2.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(asin(1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(asinh(4.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(cos(5.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(cosh(6.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(acos(1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(acosh(8.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(tan(1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(tanh(1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(atan(1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(log10(1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(log2(1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(log(1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(abs(-1.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(min(-1., 5.)),
        MAKE_TEST_VALUE_FROM_STD_FUNCTION(max(-1., 5.))
    );
}

void parse_and_check(const std::string& expression, double value)
{
    EXPECT_DOUBLE_EQ(abacus::evaluate(expression), value);
}

TEST_P(ParseAndCheck, can_parse_and_calculate)
{
    auto& p = GetParam();
    parse_and_check(p.expression, p.value);
}

INSTANTIATE_TEST_SUITE_P(ArithmeticTest,ParseAndCheck, number_arithmetic_test_values);
