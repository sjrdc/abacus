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

#include "ast_adapted.h"

#include <boost/spirit/home/x3.hpp>

#include <iomanip>
#include <iostream>
#include <string>

namespace abacus
{
	namespace detail::grammar
	{
		namespace x3 = boost::spirit::x3;
		struct error_handler
		{
			template <typename It, typename Ctx>
			x3::error_handler_result on_error(It f, It l, x3::expectation_failure<It> const& e, Ctx const& /*ctx*/) const {
				std::cout << std::string(f, l) << "\n"
					<< std::setw(1 + std::distance(f, e.where())) << "^"
					<< "-- expected: " << e.which() << "\n";
				return x3::error_handler_result::fail;
			}
		};

		struct unary_function_symbol : x3::symbols<ast::unary_operation::function>
		{
			unary_function_symbol();
		};

		struct binary_function_symbol : x3::symbols<ast::binary_operation::function>
		{
			binary_function_symbol();
		};

		struct additive_symbol : x3::symbols<ast::binary_operation::function>
		{
			additive_symbol();
		};

		struct multiplicative_symbol : x3::symbols<ast::binary_operation::function>
		{
			multiplicative_symbol();
		};

		struct power_symbol : x3::symbols<ast::binary_operation::function>
		{
			power_symbol();
		};
	}

	detail::ast::operand parse(const std::string& input);
}
