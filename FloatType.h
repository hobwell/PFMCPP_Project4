#pragma once

#include "NumericType.h"

struct DoubleType;
struct IntType;

struct FloatType : NumericType
{
    explicit FloatType (float f);

    ~FloatType() override;

    operator double() const { return static_cast<double> (*value); }
    operator float() const { return *value; }
    operator int() const { return static_cast<int> (*value); }

    FloatType& add (const float rhs);
    FloatType& divide (const float rhs);
    FloatType& multiply (const float rhs);
    FloatType& pow (const float exponent);
    FloatType& pow (const DoubleType& exponent);
    FloatType& pow (const FloatType& exponent);
    FloatType& pow (const IntType& exponent);
    FloatType& subtract (const float rhs);

    std::string toString() const override;

private:
    float* value = nullptr;

    FloatType& powInternal (const float exponent);
};
