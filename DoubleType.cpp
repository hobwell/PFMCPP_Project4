#include <iostream>
#include <cmath>
#include "IntType.h"
#include "DoubleType.h"
#include "FloatType.h"

DoubleType::~DoubleType()
{
    delete value;
}

DoubleType& DoubleType::add (double rhs)
{
    *value += rhs;
    return *this;
}

DoubleType& DoubleType::divide (double rhs)
{
    if (rhs == 0.0)
    {
        std::cout << "warning: floating point division by zero!" << std::endl;
    }
    
    *value /= rhs;
    return *this;
}

DoubleType& DoubleType::multiply (double rhs)
{
    *value *= rhs;
    return *this;
}


DoubleType& DoubleType::pow (double exponent)
{
    return powInternal (exponent);
}

DoubleType& DoubleType::pow (const DoubleType& exponent)
{
    return pow (static_cast<double> (exponent));
}

DoubleType& DoubleType::pow (const FloatType& exponent)
{
    return pow (static_cast<double> (exponent));
}

DoubleType& DoubleType::pow (const IntType& exponent)
{
    return pow (static_cast<double> (exponent));
}

DoubleType& DoubleType::powInternal (double exponent)
{
    *value = static_cast<double> (std::pow (*value, exponent));
    
    return *this;
}

DoubleType& DoubleType::subtract (double rhs)
{
    *value -= rhs;
    return *this;
}
