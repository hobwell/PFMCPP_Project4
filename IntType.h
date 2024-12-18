#pragma once

#include "NumericType.h"

struct DoubleType;
struct FloatType;

struct IntType : NumericType
{
    IntType (int i);

    ~IntType() override;

    operator double() const { return static_cast<double> (*value); }
    operator float() const { return static_cast<float> (*value); }    
    operator int() const { return *value; }

    IntType& add (const int rhs);
    IntType& divide (const int rhs);
    IntType& multiply (const int rhs);
    IntType& pow (int exponent);
    IntType& pow (const DoubleType& exponent);
    IntType& pow (const FloatType& exponent);
    IntType& pow (const IntType& exponent);
    IntType& subtract (const int rhs);

    std::string toString() const override;

private:
    int* value;

    IntType& powInternal (const int exponent);
};
