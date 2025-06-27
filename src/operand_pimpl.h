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

#include "ast.h"
#include "abacus/datatypes.h"

namespace abacus
{
    namespace detail
    {
        class operand_pimpl
        {
        public:
            operand_pimpl(ast::operand);
            
            template <typename V>
            V::result_type evaluate(const V&) const;

        private:
            ast::operand operand;
        };
    }
}