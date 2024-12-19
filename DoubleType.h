#pragma once

struct FloatType;
struct IntType;

struct DoubleType
{
    explicit DoubleType (double d);

    ~DoubleType();

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

private:
    double* value = nullptr;

    DoubleType& powInternal (const double exponent);
};
