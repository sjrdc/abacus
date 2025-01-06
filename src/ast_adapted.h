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

#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(abacus::unary_function, operation, arg)
BOOST_FUSION_ADAPT_STRUCT(abacus::binary_function, operation, arg1, arg2)
BOOST_FUSION_ADAPT_STRUCT(abacus::variable, name, value)
