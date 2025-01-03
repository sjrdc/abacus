#include <boost/spirit/home/x3.hpp>

#include <string>

namespace abacus
{
	struct operand
	{

	};

	struct unary_function
	{
		operand arg;
	};

	struct binary_function
	{
		operand arg1;
		operand arg2;
	};

	struct variable
	{
		std::string name;
	};
}