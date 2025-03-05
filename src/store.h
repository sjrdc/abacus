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
#include <unordered_map>

namespace abacus
{
    class variable_store
    {
    public:
        using store_type = std::unordered_map<std::string, std::shared_ptr<detail::ast::variable>>;
        using value_type = store_type::mapped_type;
        using key_type = store_type::key_type;

        value_type get(const key_type&);

    private:
        std::unordered_map<std::string, value_type> variables;
    };
}
