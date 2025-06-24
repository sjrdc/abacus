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
#include "operand_pimpl.h"
#include "parse.h"

namespace abacus
{
    namespace detail
    {
        operand_pimpl::operand_pimpl(ast::operand operand) :
            operand(std::move(operand))
        {
        }

        template <>
        result_type operand_pimpl::evaluate(const calculator& calculator) const
        {
            return calculator(operand);
        }
    }


    operand::~operand() = default;

    operand::operand(std::unique_ptr<detail::operand_pimpl>&& pimpl) :
        pimpl(std::move(pimpl))
    {
    }

    template <>
    result_type operand::evaluate(const detail::calculator& calculator) const
    {
        return pimpl->evaluate(calculator);
    }
}
