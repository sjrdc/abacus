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
#include "ast.h"

#include <boost/spirit/home/x3/string/symbols.hpp>
#include <functional>

namespace abacus
{
    namespace detail::grammar
    {
        namespace x3 = boost::spirit::x3;

        unary_function_symbol::unary_function_symbol()
        {
            this->add("sin", [](double x) { return std::sin(x); });
            this->add("sinh", [](double x) { return std::sinh(x); });
            this->add("asin", [](double x) { return std::asin(x); });
            this->add("asinh", [](double x) { return std::asinh(x); });
            this->add("cos", [](double x) { return std::cos(x); });
            this->add("cosh", [](double x) { return std::cosh(x); });
            this->add("acos", [](double x) { return std::acos(x); });
            this->add("acosh", [](double x) { return std::acosh(x); });
            this->add("tan", [](double x) { return std::tan(x); });
            this->add("tanh", [](double x) { return std::tanh(x); });
            this->add("atan", [](double x) { return std::atan(x); });
            this->add("log10", [](double x) { return std::log10(x); });
            this->add("log2", [](double x) { return std::log2(x); });
            this->add("log", [](double x) { return std::log(x); });
            this->add("abs", [](double x) { return std::abs(x); });
        }

        binary_function_symbol::binary_function_symbol()
        {
            this->add("atan2", [](double a, double b) { return std::atan2(a, b); });
            this->add("min", [](double a, double b) { return std::min(a, b); });
            this->add("max", [](double a, double b) { return std::max(a, b); });
        }

        additive_symbol::additive_symbol()
        {
            this->add("+", std::plus<double>());
            this->add("-", std::minus<double>());
        }

        multiplicative_symbol::multiplicative_symbol()
        {
            this->add("/", std::divides<double>());
            this->add("*", std::multiplies<double>());
        }

        power_symbol::power_symbol()
        {
            this->add("^", [](double a, double b) { return std::pow(a, b);  });
        }


        struct expression_class : error_handler {};
        struct additive_class : error_handler {};
        struct multiplicative_class : error_handler {};
        struct factor_class : error_handler {};
        struct primary_class : error_handler {};
        struct unary_class : error_handler {};
        struct binary_class : error_handler {};

        // Rule declarations
        const auto expression_rule = x3::rule<expression_class, ast::operand       >{ "expression" };
        const auto primary_rule = x3::rule<primary_class, ast::operand          >{ "primary" };
        const auto additive_rule = x3::rule<additive_class, ast::expression      >{ "additive" };
        const auto multiplicative_rule = x3::rule<multiplicative_class, ast::expression>{ "multiplicative" };
        const auto factor_rule = x3::rule<factor_class, ast::expression        >{ "factor" };
        const auto unary_rule = x3::rule<unary_class, ast::unary_operation    >{ "unary" };
        const auto binary_rule = x3::rule<binary_class, ast::binary_operation  >{ "binary" };

        // Rule defintions
        const auto expression_rule_def = additive_rule;

        const auto additive_rule_def =
            multiplicative_rule >> *(additive_symbol() >> multiplicative_rule);

        const auto multiplicative_rule_def =
            factor_rule >> *(multiplicative_symbol() >> factor_rule);

        const auto factor_rule_def = primary_rule >> *(power_symbol() >> factor_rule);

        const auto unary_rule_def =
            unary_function_symbol() >> '(' >> expression_rule >> ')';

        const auto binary_rule_def =
            binary_function_symbol() >> '(' >> expression_rule >> ',' >> expression_rule >> ')';

        const auto primary_rule_def =
            x3::double_
            | ('(' >> expression_rule >> ')')
            | binary_rule
            | unary_rule
            ;

        BOOST_SPIRIT_DEFINE(
            expression_rule,
            additive_rule,
            multiplicative_rule,
            factor_rule,
            unary_rule,
            binary_rule,
            primary_rule
        )
    }

    std::expected<operand, std::string> parse(const std::string& input)
    {
        auto f = begin(input), l = end(input);
        operand out;
        if (phrase_parse(f, l, detail::grammar::expression_rule, boost::spirit::x3::space, out))
        {
            return out;
        }

        if (f != l)
        {
            auto error = std::string("Unparsed: \"") + std::string(f, l) + "\"";
            return std::unexpected(error);
        }
        return std::unexpected("");
    }
}