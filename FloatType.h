#pragma once

#include <string>
#include "NumericType.h"

struct DoubleType;
struct IntType;

struct FloatType : NumericType
{
    FloatType (float f) : value {new float (f)} { }

    ~FloatType() override;

    operator double() const { return static_cast<double> (*value); }
    operator float() const { return *value; }
    operator int() const { return static_cast<int> (*value); }

    FloatType& add (float rhs);
    FloatType& divide (float rhs);
    FloatType& multiply (float rhs);
    FloatType& pow (const float exponent);
    FloatType& pow (const DoubleType& exponent);
    FloatType& pow (const FloatType& exponent);
    FloatType& pow (const IntType& exponent);
    FloatType& subtract (float rhs);

    std::string toString() const override
    {
        return std::to_string (*value);
    }

private:
    float* value = nullptr;

    FloatType& powInternal (const float exponent);
};
