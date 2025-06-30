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

#include "is_evaluatable.h"

#include "abacus.h"
#include "../ast.h"
#include "../parse.h"


namespace abacus::detail
{
    is_evaluatable::result_type is_evaluatable::operator()(double d) const
    {
        return true;
    }

    is_evaluatable::result_type is_evaluatable::operator()(const detail::ast::nil&) const
    {
        return false;
    }

    is_evaluatable::result_type is_evaluatable::operator()(const detail::ast::expression& e) const
    {
        auto r = e.lhs.apply_visitor(*this);
        for (auto& o : e.rhs)
        {
            r = (r && o.rhs.apply_visitor(*this));
        }
        
        return r;
    }

    is_evaluatable::result_type is_evaluatable::operator()(const detail::ast::binary_operation& f) const
    {
        return f.lhs.apply_visitor(*this) && f.rhs.apply_visitor(*this);
    }
    
    is_evaluatable::result_type is_evaluatable::operator()(const detail::ast::unary_operation& f) const
    {
        return f.rhs.apply_visitor(*this);
    }

    is_evaluatable::result_type is_evaluatable::operator()(const detail::ast::operand& o) const
    {
        return o.apply_visitor(*this);
    }

    is_evaluatable::result_type is_evaluatable::operator()(const detail::ast::ASTVariableType& v) const
    {
        return v && v->value.has_value() && v->value->apply_visitor(*this);
    }

    is_evaluatable::result_type is_evaluatable::operator()(const abacus::operand& o) const
    {
        return o.evaluate(*this);
    }
}
