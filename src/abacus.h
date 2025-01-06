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

#include "ast.h"
#include "ast_adapted.h"

#include <boost/spirit/home/x3.hpp>
#include <expected>

namespace abacus
{
    namespace detail
    {
        namespace x3 = boost::spirit::x3;
        
        struct unary_function_symbols : x3::symbols<unary_function::function>
        {
            unary_function_symbols();
        };

        struct binary_function_symbols : x3::symbols<binary_function::function>
        {
            binary_function_symbols();
        };
    }

	template <typename Iterator>
    std::expected<::abacus::expression, std::string> parse(Iterator begin, Iterator end)
	{
        if (false)
        {
            return ::abacus::expression();
        }
        else
        {
            return std::unexpected("Could not parse");
        }
	}
}