#include <iostream>
#include <cmath>
#include "IntType.h"
#include "DoubleType.h"
#include "FloatType.h"

IntType::~IntType()
{
    delete value;
}

IntType& IntType::add (int rhs)
{
    *value += rhs;
    return *this;
}

IntType& IntType::divide (int rhs)
{
    if (rhs == 0)
    {
        std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
    }
    else
    {
        *value /= rhs;    
    }
    
    return *this;
}

IntType& IntType::multiply (int rhs)
{
    *value *= rhs;
    return *this;
}

IntType& IntType::pow (int exponent)
{
    return powInternal (exponent);
}

IntType& IntType::pow (const DoubleType& exponent)
{
    return pow (static_cast<int> (exponent));
}

IntType& IntType::pow (const FloatType& exponent)
{
    return pow (static_cast<int> (exponent));
}

IntType& IntType::pow (const IntType& exponent)
{
    return pow (static_cast<int> (exponent));
}

IntType& IntType::powInternal (int exponent)
{
    *value = static_cast<int> (std::pow (*value, exponent));
    
    return *this;
}

IntType& IntType::subtract (int rhs)
{
    *value -= rhs;
    return *this;
}

// Not sure why this definition produces an error, so I put the implementation in the header file (where it seems to work).
// error: out-of-line definition of 'toString' does not match any declaration in 'IntType'
// std::string IntType::toString() const
// {
//     return std::to_string (*value);
// }
