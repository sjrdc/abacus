# abacus

Abacus is a C++ library that supports parsing and evaluating basic mathematical expressions.
Expressions are composed of variables, functions and numbers.

### Functions
We distinguish
* unary functions; functions with a single argument
* binary functions; functions with two arguments
Functions are written as the function name, followed by their argument(s) in braces. In case of more than
one argument, arguments are separated by a comma. Arguments can be composed of other functions, variables or numbers.

Example
```
func(a, 5 * log(x))
```

The following functions are supported
| Function | Category | Meaning |
| -------- | ------- | ------- |
| sin| unary | sine |
| sinh| unary | hyperbolic sine |
| asin| unary | arcsine |
| asinh| unary | inverse hyperbolic sine |
| cos| unary | cosine |
| cosh| unary | hyperbolic cosine |
| acos| unary | arccosine |
| acosh| unary  | inverse hyperbolic cosine |
| tan| unary  | tangent |
| tanh| unary  | hyperbolic tangent |
| atan| unary  | arctangent |
| log10| unary  | base-10 logarithm |
| log2| unary  | base-2 logarithm |
| log| unary  | natural logarithm |
| abs| unary | absolute value of argument |
| atan2| binary | two argument arctangent |
| min| binary | minimum of arguments |
| max| binary | maximum of arguments |

### Variable naming rules
Similar to C++ variable naming rules,
* variable names may be composed of alphanumeric characters and underscores
* a variable name shall start with a non-numeric character (hence, with an underscore or a letter)

### Numbers
Numbers in expressions may be written as integers or floating points base-10 numbers. Internally 
they are *always* represented as double precision floating point numbers. 