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

#include <boost/spirit/home/x3/string/symbols.hpp>

#include <exception>
#include <functional>
#include <iostream>
#include <iomanip>
#include <numbers>


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
            unary_function_symbol()
            {
                add
                    ("sin", [](double x) { return std::sin(x); })
                    ("sinh", [](double x) { return std::sinh(x); })
                    ("asin", [](double x) { return std::asin(x); })
                    ("asinh", [](double x) { return std::asinh(x); })
                    ("cos", [](double x) { return std::cos(x); })
                    ("cosh", [](double x) { return std::cosh(x); })
                    ("acos", [](double x) { return std::acos(x); })
                    ("acosh", [](double x) { return std::acosh(x); })
                    ("tan", [](double x) { return std::tan(x); })
                    ("tanh", [](double x) { return std::tanh(x); })
                    ("atan", [](double x) { return std::atan(x); })
                    ("log10", [](double x) { return std::log10(x); })
                    ("log2", [](double x) { return std::log2(x); })
                    ("log", [](double x) { return std::log(x); })
                    ("abs", [](double x) { return std::abs(x); });
            }
        };

        struct binary_function_symbol : x3::symbols<ast::binary_operation::function>
        {
            binary_function_symbol()
            {
                add
                    ("atan2", [](double a, double b) { return std::atan2(a, b); })
                    ("min", [](double a, double b) { return std::min(a, b); })
                    ("max", [](double a, double b) { return std::max(a, b); });
            }
        };

        struct additive_symbol : x3::symbols<ast::binary_operation::function>
        {
            additive_symbol() 
            {
                add
                    ("+", std::plus<double>())
                    ("-", std::minus<double>());
            }
        };

        struct multiplicative_symbol : x3::symbols<ast::binary_operation::function>
        {
            multiplicative_symbol()
            {
                add
                    ("/", std::divides<double>())
                    ("*", std::multiplies<double>());
            }
        };

        struct power_symbol : x3::symbols<ast::binary_operation::function>
        {
            power_symbol()
            {
                add
                    ("^", [](double a, double b) { return std::pow(a, b); });

            }
        };

        struct numeric_constant_symbol : x3::symbols<double>
        {
            numeric_constant_symbol()
            {
                add
                    ("pi", std::numbers::pi)
                    ("e", std::numbers::e);
            }
        };

        struct expression_class : error_handler {};
        struct additive_class : error_handler {};
        struct multiplicative_class : error_handler {};
        struct factor_class : error_handler {};
        struct primary_class : error_handler {};
        struct unary_class : error_handler {};
        struct binary_class : error_handler {};
        struct variable_class : error_handler {};
        struct identifier_class : error_handler {};
        struct constant_class : error_handler {};

        // Rule declarations
        constexpr auto expression_rule = x3::rule<expression_class, ast::operand>{ "expression" };
        constexpr auto primary_rule = x3::rule<primary_class, ast::operand>{ "primary" };
        constexpr auto additive_rule = x3::rule<additive_class, ast::expression>{ "additive" };
        constexpr auto multiplicative_rule = x3::rule<multiplicative_class, ast::expression>{ "multiplicative" };
        constexpr auto factor_rule = x3::rule<factor_class, ast::expression>{ "factor" };
        constexpr auto unary_rule = x3::rule<unary_class, ast::unary_operation>{ "unary" };
        constexpr auto binary_rule = x3::rule<binary_class, ast::binary_operation>{ "binary" };
        constexpr auto variable_rule = x3::rule<variable_class, ast::ASTVariableType>{ "variable" };
        constexpr auto identifier_rule = x3::rule<identifier_class, std::string>{ "identifier" };
        constexpr auto constant_rule = x3::rule<constant_class, double>{ "constant" };

        // Rule definitions
        constexpr auto expression_rule_def = additive_rule;

        const auto constant_rule_def = numeric_constant_symbol();

        const auto additive_rule_def =
            multiplicative_rule >> *(additive_symbol() >> multiplicative_rule);

        const auto multiplicative_rule_def = 
            factor_rule >> *(multiplicative_symbol() >> factor_rule);

        const auto factor_rule_def = primary_rule >> *(power_symbol() >> factor_rule);

        const auto unary_rule_def =
            unary_function_symbol() >> '(' >> expression_rule >> ')';

        const auto binary_rule_def =
            binary_function_symbol() >> '(' >> expression_rule >> ',' >> expression_rule >> ')';

        constexpr auto make_variable = [](auto& context)
            {
                const auto variable = std::make_shared<ast::variable>();
                variable->name = x3::_attr(context);
                return variable;
            };

        constexpr auto underscore = x3::char_('_');
        constexpr auto identifier_rule_def = x3::lexeme[(x3::alpha | underscore) >> *(x3::alnum | underscore)];
        const auto variable_rule_def = (identifier_rule)[make_variable];

        const auto primary_rule_def =
            x3::double_
            | constant_rule
            | ('(' >> expression_rule >> ')')
            | binary_rule
            | unary_rule
            | variable_rule
            ;

        BOOST_SPIRIT_DEFINE(
            constant_rule,
            expression_rule,
            additive_rule,
            multiplicative_rule,
            factor_rule,
            unary_rule,
            binary_rule,
            identifier_rule,
            variable_rule,
            primary_rule
        )
    }

    namespace detail
    {
        abacus::detail::ast::operand parse(const std::string& input)
        {
            auto f = begin(input), l = end(input);
            abacus::detail::ast::operand out;
            if (phrase_parse(f, l, detail::grammar::expression_rule, boost::spirit::x3::space, out))
            {
                if (f != l)
                {
                    throw std::runtime_error(std::string("Unparsed: \"") + std::string(f, l) + "\"");
                }

                return out;
            }
            throw std::runtime_error("unknown error occurred on parsing " + input);
        }
    }
}