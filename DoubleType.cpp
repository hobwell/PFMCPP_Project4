#include <iostream>
#include <cmath>
#include "IntType.h"
#include "DoubleType.h"
#include "FloatType.h"

DoubleType::DoubleType (const double d) : 
    value {new double (d)} 
{}

DoubleType::~DoubleType()
{
    delete value;
}

DoubleType& DoubleType::add (const double rhs)
{
    *value += rhs;
    return *this;
}

DoubleType& DoubleType::divide (const double rhs)
{
    if (rhs == 0.0)
    {
        std::cout << "warning: floating point division by zero!" << std::endl;
    }
    
    *value /= rhs;
    return *this;
}

DoubleType& DoubleType::multiply (const double rhs)
{
    *value *= rhs;
    return *this;
}

DoubleType& DoubleType::pow (const double exponent)
{
    return powInternal (exponent);
}

DoubleType& DoubleType::pow (const DoubleType& exponent)
{
    return powInternal (exponent);
}

DoubleType& DoubleType::pow (const FloatType& exponent)
{
    return powInternal (exponent);
}

DoubleType& DoubleType::pow (const IntType& exponent)
{
    return powInternal (exponent);
}

DoubleType& DoubleType::powInternal (const double exponent)
{
    *value = static_cast<double> (std::pow (*value, exponent));
    
    return *this;
}

DoubleType& DoubleType::subtract (const double rhs)
{
    *value -= rhs;
    return *this;
}
