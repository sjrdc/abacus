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

#include "abacus.h"
#include "../ast.h"
#include "../parse.h"

namespace abacus::detail
{
    result_type calculator::operator()(double d) const
    {
        return d;
    }

    result_type calculator::operator()(const detail::ast::nil&) const
    {
        throw std::runtime_error("operation not implemented");
    }

    result_type calculator::operator()(const detail::ast::expression& e) const
    {
        auto r = e.lhs.apply_visitor(*this);
        for (auto& o : e.rhs)
        {
            r = o.op(r, o.rhs.apply_visitor(*this));
        }
        
        return r;
    }

    result_type calculator::operator()(const detail::ast::binary_operation& f) const
    {
        return f.op(f.lhs.apply_visitor(*this), f.rhs.apply_visitor(*this));
    }
    
    result_type calculator::operator()(const detail::ast::unary_operation& f) const
    {
        return f.op(f.rhs.apply_visitor(*this));
    }

    result_type calculator::operator()(const detail::ast::operand& o) const
    {
        return o.apply_visitor(*this);
    }

    result_type calculator::operator()(const detail::ast::ASTVariableType& v) const
    {
        if (!v)
        {
            throw std::runtime_error("Error evaluating variable null pointer.");
        }

        if (v->value) return v->value->apply_visitor(*this);
        
        throw std::runtime_error("Error evaluating variable '"
            + v->name + "' with no assigned value.");
    }

    result_type calculator::operator()(const abacus::operand& o) const
    {
        return o.evaluate(*this);
    }
}
