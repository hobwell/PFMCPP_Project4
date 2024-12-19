#include <functional>
#include <iostream>
#include <cmath>
#include "IntType.h"
#include "DoubleType.h"
#include "FloatType.h"

DoubleType::DoubleType (double d) : 
    value {new double (d)} 
{}

DoubleType::~DoubleType()
{
    delete value;
}

DoubleType& DoubleType::operator+= (double rhs)
{
    *value += rhs;
    return *this;
}

DoubleType& DoubleType::operator-= (double rhs)
{
    *value -= rhs;
    return *this;
}

DoubleType& DoubleType::operator*= (double rhs)
{
    *value *= rhs;
    return *this;
}

DoubleType& DoubleType::operator/= (double rhs)
{
    if (rhs == 0.0)
    {
        std::cout << "warning: floating point division by zero!" << std::endl;
    }
    
    *value /= rhs;
    return *this;
}

DoubleType& DoubleType::apply(std::function<DoubleType& (double&)> func)
{
    if (func)
    {
        return func(*value);
    }

    return *this;
}

DoubleType& DoubleType::apply(void (*func) (double&))
{
    if (func)
    {
        func(*value);
    }

    return *this;
}

DoubleType& DoubleType::pow (double exponent)
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

DoubleType& DoubleType::powInternal (double exponent)
{
    *value = static_cast<double> (std::pow (*value, exponent));
    
    return *this;
}
