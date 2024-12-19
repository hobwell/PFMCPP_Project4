#pragma once

struct DoubleType;
struct IntType;

struct FloatType
{
    explicit FloatType (float f);

    ~FloatType();

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

private:
    float* value = nullptr;

    FloatType& powInternal (const float exponent);
};
