#pragma once

#include "NumericType.h"

struct FloatType;
struct IntType;

struct DoubleType : NumericType
{
    explicit DoubleType (double d);

    ~DoubleType() override;

    operator double() const { return *value; }
    operator float() const { return static_cast<float> (*value); }    
    operator int() const { return static_cast<int> (*value); }

    DoubleType& add (const double rhs);
    DoubleType& divide (const double rhs);
    DoubleType& multiply (const double rhs);
    DoubleType& pow (const double exponent);
    DoubleType& pow (const DoubleType& exponent);
    DoubleType& pow (const FloatType& exponent);
    DoubleType& pow (const IntType& exponent);
    DoubleType& subtract (const double rhs);

    std::string toString() const override;

private:
    double* value = nullptr;

    DoubleType& powInternal (const double exponent);
};
