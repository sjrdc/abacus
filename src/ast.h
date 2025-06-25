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

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <functional>
#include <list>
#include <memory>
#include <optional>

namespace abacus
{
    namespace detail::ast
    {
        namespace x3 = ::boost::spirit::x3;
        struct nil {};
        struct unary_operation;
        struct binary_operation;
        struct expression;
        struct variable;

        using ASTVariableType = std::shared_ptr<variable>;
    
        struct operand : x3::variant<
            detail::ast::nil,
            double,
            x3::forward_ast<detail::ast::unary_operation>,
            x3::forward_ast<detail::ast::binary_operation>,
            x3::forward_ast<detail::ast::expression>,
            x3::forward_ast<detail::ast::ASTVariableType>>
        {
            using base_type::base_type;
            using base_type::operator=;
        };

        struct variable
        {
            std::string name;
            std::optional<operand> value;
        };

        struct unary_operation
        {
            using function = std::function<double(double)>;
            function op;
            operand rhs;
        };

        struct binary_operation
        {
            using function = std::function<double(double, double)>;
            function op;
            operand lhs;
            operand rhs;
        };

        struct operation
        {
            binary_operation::function op;
            operand rhs;
        };

        struct expression
        {
            operand lhs;
            std::list<operation> rhs;
        };
    }
}
