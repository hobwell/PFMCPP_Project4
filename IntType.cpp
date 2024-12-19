#include <iostream>
#include <cmath>
#include "IntType.h"
#include "DoubleType.h"
#include "FloatType.h"

IntType::IntType (int i) : 
    value {new int (i)} 
{}

IntType::~IntType() 
{
    delete value;
}

IntType& IntType::add (const int rhs)
{
    *value += rhs;
    return *this;
}

IntType& IntType::divide (const int rhs)
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

IntType& IntType::multiply (const int rhs)
{
    *value *= rhs;
    return *this;
}

IntType& IntType::pow (const int exponent)
{
    return powInternal (exponent);
}

IntType& IntType::pow (const DoubleType& exponent)
{
    return powInternal (exponent);
}

IntType& IntType::pow (const FloatType& exponent)
{
    return powInternal (exponent);
}

IntType& IntType::pow (const IntType& exponent)
{
    return powInternal (exponent);
}

IntType& IntType::powInternal (const int exponent)
{
    *value = static_cast<int> (std::pow (*value, exponent));
    
    return *this;
}

IntType& IntType::subtract (const int rhs)
{
    *value -= rhs;
    return *this;
}
