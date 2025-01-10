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

#include "store.h"

namespace abacus
{
    variable_store::value_type variable_store::get(const store_type::key_type& name)
    {
        static_assert(std::is_same_v<value_type, std::shared_ptr<detail::ast::variable>>, 
            "this code is written with the assumption of storing shared ptrs in the store");


        auto iterator = variables.find(name);
        if (iterator == variables.cend())
        {
            const auto inserted = variables.insert(std::make_pair(name, std::make_shared<detail::ast::variable>()));
            if (inserted.second)
            {
                iterator = inserted.first;
                iterator->second->name = name;
            }
            else
                throw std::runtime_error("Failed to create variable with name '" + name + "' in store.");
        }
        return iterator->second;
    }
}
