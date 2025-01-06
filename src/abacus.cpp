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

#include <functional>

namespace abacus
{
    namespace detail
    {
        unary_function_symbols::unary_function_symbols() : x3::symbols<unary_function::function>()
        {
            this->add("sin", [](double x) { return std::sin(x); });
            this->add("sinh", [](double x) { return std::sinh(x); });
            this->add("asin", [](double x) { return std::asin(x); });
            this->add("asinh", [](double x) { return std::asinh(x); });
            this->add("cos", [](double x) { return std::cos(x); });
            this->add("cosh", [](double x) { return std::cosh(x); });
            this->add("acos", [](double x) { return std::acos(x); });
            this->add("acosh", [](double x) { return std::acosh(x); });
            this->add("tan", [](double x) { return std::sin(x); });
            this->add("tanh", [](double x) { return std::tanh(x); });
            this->add("atan", [](double x) { return std::atan(x); });
            this->add("log10", [](double x) { return std::log10(x); });
            this->add("log2", [](double x) { return std::log2(x); });
            this->add("log", [](double x) { return std::log(x); });
        }

        binary_function_symbols::binary_function_symbols() : x3::symbols<binary_function::function>()
        {
            this->add("+", std::plus<double>());
            this->add("/", std::divides<double>());
            this->add("-", std::minus<double>());
            this->add("*", std::multiplies<double>());
            this->add("^", [](double a, double b) { return std::pow(a, b); });
        }
    }
}