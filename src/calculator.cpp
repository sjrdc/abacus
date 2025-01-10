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

namespace abacus
{
    calculator::result_type calculator::operator()(double d) const
    {
        return d;
    }

    calculator::result_type calculator::operator()(const detail::ast::nil&) const
    {
        throw std::runtime_error("operation not implemented");
    }

    calculator::result_type calculator::operator()(const detail::ast::expression& e) const
    {
        auto r = e.lhs.apply_visitor(*this);
        for (auto& o : e.rhs)
        {
            r = o.op(r, o.rhs.apply_visitor(*this));
        }
        return r;
    }

    calculator::result_type calculator::operator()(const detail::ast::binary_operation& f) const
    {
        return f.op(f.lhs.apply_visitor(*this), f.rhs.apply_visitor(*this));
    }
    
    calculator::result_type calculator::operator()(const detail::ast::unary_operation& f) const
    {
        return f.op(f.rhs.apply_visitor(*this));
    }

    calculator::result_type calculator::operator()(const detail::ast::operand& o) const
    {
        return o.apply_visitor(*this);
    }

    double calculator::operator()(const detail::ast::ASTVariableType& v) const
    {

        if (v->value) return v->value->apply_visitor(*this);
        throw std::runtime_error("Error evaluating variable '"
            + v->name + "' with no assigned value.");
    }
}
