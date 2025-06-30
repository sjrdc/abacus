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

#include "printer.h"

#include "abacus.h"
#include "../ast.h"
#include "../parse.h"

namespace abacus::detail
{
    printer::printer(std::ostream& os) :
        ostream(os)
    {
    }
    printer::result_type printer::operator()(const detail::ast::unary_operation& f) const
    {
        ostream << f.op_name() << '(';
        f.rhs.apply_visitor(*this);
        ostream << ')';
    }
    printer::result_type printer::operator()(const detail::ast::ASTVariableType& v) const
    {
        if (!v)
        {
            throw std::runtime_error("Error printing variable null pointer.");
        }

        ostream << v->name;
        if (v->value)
        {
            ostream << " = ";
            v->value->apply_visitor(*this);
        }
    }

    printer::result_type printer::operator()(const detail::ast::binary_operation& f) const
    {
        f.lhs.apply_visitor(*this);
        ostream << ' ' << f.op_name() << ' ';
        f.rhs.apply_visitor(*this);
    }
    
    printer::result_type printer::operator()(double d) const
    {
        ostream << d;
    }

    printer::result_type printer::operator()(const detail::ast::expression& e) const
    {
        e.lhs.apply_visitor(*this);
        for (const auto& o : e.rhs)
        {
            ostream << ' ' << o.op_name() << ' ';
            o.rhs.apply_visitor(*this);
        }
    }
    
    printer::result_type printer::operator()(const detail::ast::nil&) const
    {
        throw std::runtime_error("operation not implemented");
    }

    printer::result_type printer::operator()(const detail::ast::operand& o) const
    {
        return o.apply_visitor(*this);
    }

    printer::result_type printer::operator()(const abacus::operand& o) const
    {
        return o.evaluate(*this);
    }
}
