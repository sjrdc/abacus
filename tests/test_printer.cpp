#include <gtest/gtest.h>

#include "abacus/parser.h"
#include "abacus/evaluate.h"

namespace
{
    class printer_test : public testing::Test
    {
    protected:
        printer_test()
        {
        }

        abacus::parser parser;
    };
}

TEST_F(printer_test, can_print_double)
{
    const auto o = parser.parse("3.14");
    
    std::ostringstream ostream;
    abacus::print(o, ostream);
    EXPECT_STREQ("3.14", ostream.str().c_str());
}
