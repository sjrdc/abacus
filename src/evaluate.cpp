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

#include "calculator.h"
#include "is_evaluatable.h"
#include "parse.h"

namespace 
{
    const abacus::detail::calculator calculator;
    const abacus::detail::is_evaluatable is_evaluatable;
}

namespace abacus
{
    result_type evaluate(std::string expression)
    {
        const auto operand = abacus::detail::parse(expression);
        return ::calculator(operand);
    }

    result_type evaluate(const operand& o)
    {
        return ::calculator(o);
    }

    result_type evaluate(operand&& o)
    {
        return ::calculator(o);
    }
    void print(std::ostream& os)
    {
        os << "hello, world!";
    }

    bool can_evaluate(const operand& o)
    {
        return ::is_evaluatable(o);
    }

    bool can_evaluate(operand&& o)
    {
        return ::is_evaluatable(o);
    }
}
