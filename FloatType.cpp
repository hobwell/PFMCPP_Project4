#include <iostream>
#include <cmath>
#include "IntType.h"
#include "DoubleType.h"
#include "FloatType.h"
 
FloatType::~FloatType()
    {
        delete value;
    }

FloatType& FloatType::add (float rhs)
{
    *value += rhs;
    return *this;
}

FloatType& FloatType::divide (float rhs)
{
    if (rhs == 0.0f)
    {
        std::cout << "warning: floating point division by zero!" << std::endl;
    }
    
    *value /= rhs;
    return *this;
}

FloatType& FloatType::multiply (float rhs)
{
    *value *= rhs;
    return *this;
}

FloatType& FloatType::pow (float exponent)
{
    return powInternal (exponent);
}

FloatType& FloatType::pow (const DoubleType& exponent)
{
    return pow (static_cast<float> (exponent));
}

FloatType& FloatType::pow (const FloatType& exponent)
{
    return pow (static_cast<float> (exponent));
}

FloatType& FloatType::pow (const IntType& exponent)
{
    return pow (static_cast<float> (exponent));
}

FloatType& FloatType::powInternal (float exponent)
{
    *value = static_cast<float> (std::pow (*value, exponent));
    
    return *this;
}

FloatType& FloatType::subtract (float rhs)
{
    *value -= rhs;
    return *this;
}
