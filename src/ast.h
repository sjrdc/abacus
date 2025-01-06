#pragma once
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

#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/variant.hpp>

#include <optional>
#include <string>

namespace abacus
{
	struct nil {};
	struct unary_function;
	struct binary_function;
	struct variable;
	
	namespace x3 = boost::spirit::x3;

	struct expression: public boost::variant<double,
		nil,
		x3::forward_ast<unary_function>,
		x3::forward_ast<binary_function>, 
		x3::forward_ast<variable>
	>
	{
	};

	struct unary_function
	{
		using function = std::function<double(double)>;
		function operation;
		expression arg;
	};

	struct binary_function
	{
		using function = std::function<double(double,double)>;
		function operation;
		expression arg1;
		expression arg2;
	};

	struct variable
	{
		std::string name;
		std::optional<double> value;
	};
}