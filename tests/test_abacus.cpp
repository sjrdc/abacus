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


#define MAKE_TEST_VALUE(VAR) test_parameter(#VAR, std::VAR)

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
		test_parameter("1. + 1.", 2.),
		MAKE_TEST_VALUE(abs(1. + 1 + 1. + 2)),
		test_parameter("1. - 1.", 0.),
		test_parameter("2. * 3.", 6.),
		test_parameter("12. / 3.", 4.),
		test_parameter("2. ^ 5.", 32.),
		MAKE_TEST_VALUE(sin(1.)),
		MAKE_TEST_VALUE(sinh(2.)),
		MAKE_TEST_VALUE(asin(1.)),
		MAKE_TEST_VALUE(asinh(4.)),
		MAKE_TEST_VALUE(cos(5.)),
		MAKE_TEST_VALUE(cosh(6.)),
		MAKE_TEST_VALUE(acos(1.)),
		MAKE_TEST_VALUE(acosh(8.)),
		MAKE_TEST_VALUE(tan(1.)),
		MAKE_TEST_VALUE(tanh(1.)),
		MAKE_TEST_VALUE(atan(1.)),
		MAKE_TEST_VALUE(log10(1.)),
		MAKE_TEST_VALUE(log2(1.)),
		MAKE_TEST_VALUE(log(1.)),
		MAKE_TEST_VALUE(abs(-1.)),
		MAKE_TEST_VALUE(min(-1., 5.)),
		MAKE_TEST_VALUE(max(-1., 5.))
	);
}

void parse_and_check(const std::string& expression, double value)
{
	auto parsed = abacus::parse(expression);
	ASSERT_TRUE(parsed.has_value());

	abacus::calculator calculator;
	EXPECT_DOUBLE_EQ(calculator(parsed.value()), value);
}

TEST_P(ParseAndCheck, can_parse_and_calculate)
{
	auto& p = GetParam();
	parse_and_check(p.expression, p.value);
}

INSTANTIATE_TEST_SUITE_P(ArithmeticTest,ParseAndCheck, number_arithmetic_test_values);

TEST(abacus, can_parse_variable)
{
	auto parsed = abacus::parse("x_1");
	EXPECT_TRUE(parsed.has_value());

	parsed = abacus::parse("_x1");
	EXPECT_TRUE(parsed.has_value());

    parsed = abacus::parse("1_x");
	EXPECT_FALSE(parsed.has_value());
}
