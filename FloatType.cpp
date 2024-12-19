#include <functional>
#include <iostream>
#include <cmath>
#include "IntType.h"
#include "DoubleType.h"
#include "FloatType.h"

FloatType::FloatType (float f) : 
    value {new float (f)} 
{}

FloatType::~FloatType()
{
    delete value;
}

FloatType& FloatType::operator+= (float rhs)
{
    *value += rhs;
    return *this;
}

FloatType& FloatType::operator-= (float rhs)
{
    *value -= rhs;
    return *this;
}

FloatType& FloatType::operator*= (float rhs)
{
    *value *= rhs;
    return *this;
}

FloatType& FloatType::operator/= (float rhs)
{
    if (rhs == 0.0f)
    {
        std::cout << "warning: floating point division by zero!" << std::endl;
    }
    
    *value /= rhs;
    return *this;
}

FloatType& FloatType::apply(std::function<FloatType& (float&)> func)
{
    if (func)
    {
        return func(*value);
    }

    return *this;
}

FloatType& FloatType::apply(void (*func) (float&))
{
    if (func)
    {
        func(*value);
    }

    return *this;
}

FloatType& FloatType::pow (float exponent)
{
    return powInternal (exponent);
}

FloatType& FloatType::pow (const DoubleType& exponent)
{
    return powInternal (exponent);
}

FloatType& FloatType::pow (const FloatType& exponent)
{
    return powInternal (exponent);
}

FloatType& FloatType::pow (const IntType& exponent)
{
    return powInternal (exponent);
}

FloatType& FloatType::powInternal (float exponent)
{
    *value = static_cast<float> (std::pow (*value, exponent));
    
    return *this;
}
