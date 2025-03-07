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

namespace abacus
{
    calculator::result_type calculator::operator()(double d) const
    {
        return d;
    }

    calculator::result_type calculator::operator()(const detail::ast::nil&) const
    {
        return std::unexpected("operation not implemented");
    }

    calculator::result_type calculator::operator()(const detail::ast::expression& e) const
    {
        auto r = e.lhs.apply_visitor(*this);
        if (r.has_value())
        {
            for (auto& o : e.rhs)
            {
                r = o.rhs.apply_visitor(*this).and_then(
                    [&r, &o](auto value)
                    {
                        return calculator::result_type(o.op(r.value(), value));
                    }
                );
            }
        }
        return r;
    }

    calculator::result_type calculator::operator()(const detail::ast::binary_operation& f) const
    {
        return f.lhs.apply_visitor(*this).and_then(
            [&f, this](double vlhs)
            {
                return f.rhs.apply_visitor(*this).and_then(
                    [&vlhs, &f](double val)
                    {
                        return calculator::result_type(f.op(vlhs, val));
                    }
                );
            }
        );
    }
    
    calculator::result_type calculator::operator()(const detail::ast::unary_operation& f) const
    {
        return f.rhs.apply_visitor(*this).and_then(
            [&f](auto value)
            {
                return calculator::result_type(f.op(value));
            }
        );
    }

    calculator::result_type calculator::operator()(const detail::ast::operand& o) const
    {
        return o.apply_visitor(*this);
    }

    calculator::result_type calculator::operator()(const detail::ast::ASTVariableType& v) const
    {
        if (v->value) return v->value->apply_visitor(*this);
        return std::unexpected("Error evaluating variable '"
            + v->name + "' with no assigned value.");
    }

    calculator::result_type calculator::evaluate(std::string expression)
    {
        return abacus::parse(expression).and_then(
            [](auto value)
            {
                const abacus::calculator calculator;
                return calculator(value);
            }
        );
    }
}
