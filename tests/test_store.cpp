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
#include "store.h"

#include <gtest/gtest.h>

using namespace abacus;

namespace
{
	const auto varname = std::string("variable");
}

TEST(store, can_store_variable)
{
	variable_store store;
	auto variable = store.get(varname);
}

TEST(store, retrieves_stored_variable)
{
	variable_store store;
	auto* raw_ptr = store.get(varname).get();
	EXPECT_EQ(raw_ptr, store.get(varname).get());
}

TEST(store, preserves_variable_values)
{
	// given a store containing a variable
	variable_store store;
	const auto value = std::numbers::pi;
	{
		// when the variable is given a value but it goes out of scope
		auto variable = store.get(varname);
		variable->value = value;
	}

	// the store retains the variable and its value
	calculator calc;
	EXPECT_EQ(calc(store.get(varname)), value);
}
