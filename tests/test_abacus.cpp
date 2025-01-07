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
#include "calculator.h"

#include <gtest/gtest.h>

namespace
{
    struct arithmetic_parameter
    {
        std::string expression;
        double value;
    };

    class ArithmeticTest :
        public testing::TestWithParam<arithmetic_parameter>
    {
    };

    auto number_arithmetic_test_values = testing::Values<arithmetic_parameter>(
        arithmetic_parameter("1. + 1.", 2.),
        arithmetic_parameter("1. - 1.", 0.),
        arithmetic_parameter("2. * 3.", 6.),
        arithmetic_parameter("12. / 3.", 4.),
        arithmetic_parameter("2. ^ 5.", 32.)
    );
}

TEST_P(ArithmeticTest, can_perform_number_arithmetic)
{
    auto& p = GetParam();
    auto parsed = abacus::parse(p.expression);
    ASSERT_TRUE(parsed.has_value());

    abacus::calculator calculator;
    EXPECT_DOUBLE_EQ(calculator(parsed.value()), p.value);
}

INSTANTIATE_TEST_SUITE_P(ArithmeticTest, ArithmeticTest, number_arithmetic_test_values);
