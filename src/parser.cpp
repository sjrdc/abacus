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

#include "abacus/parser.h"

#include "operand_pimpl.h"
#include "parse.h"
#include "store.h"

namespace 
{
    // trim from start (in place)
    void ltrim(std::string &s) 
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    void rtrim(std::string &s) 
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }
    // trim from both ends (in place)
    void trim(std::string &s) 
    {
        rtrim(s);
        ltrim(s);
    }
}
namespace abacus::detail
{

    class parser_pimpl
    {
    public:
        abacus::operand parse(const std::string& expression)
        {
            if (expression.empty())
            {
                throw std::runtime_error("Cannot parse empty expression.");
            }

            auto q = std::unique_ptr<detail::operand_pimpl>();
            if (const auto n = expression.find('='); n != std::string::npos)
            {
                // we're parsing an equation, not just an expression
                // get the variable
                auto name = expression.substr(0, n);
                trim(name);
                auto variable = store.get(name);
                // and assign it an expression 
                variable->value = detail::parse(expression.substr(n + 1), store);
                q = std::make_unique<detail::operand_pimpl>(ast::operand(variable));
            }
            else
            {
                q = std::make_unique<detail::operand_pimpl>(detail::parse(expression, store));
            }
            return operand(std::move(q));
        }

      private:
        variable_store store;
    };
}

namespace abacus
{
    parser::parser() :
        pimpl(std::make_unique<detail::parser_pimpl>())
    {
    }

    parser::~parser() = default;

    operand parser::parse(const std::string& expression)
    {
        return pimpl->parse(expression);
    }
}
