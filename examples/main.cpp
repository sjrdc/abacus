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

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    std::string string_from_args(int argc, char **argv)
    {
        std::vector<std::string> strings(argv + 1, argv + argc);
        std::string concat;
        std::for_each(strings.cbegin(), strings.cend(),
                      [&concat](const auto &s)
                      {
                          concat += s;
                      });
        return concat;
    }
}

int main(int argc, char **argv)
{
    std::string expression;
    abacus::parser parser;
    do
    {
        std::cout << "> " << std::flush;
        std::getline(std::cin, expression);
        const auto op = parser.parse(expression);
        if (abacus::can_evaluate(op))
            std::cout << expression << " = " << abacus::evaluate(op) << std::endl;
    } while (true);
    return 0;
}
