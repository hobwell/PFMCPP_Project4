#pragma once

struct DoubleType;
struct FloatType;

struct IntType
{
    IntType (int i);

    ~IntType();

    operator double() const { return static_cast<double> (*value); }
    operator float() const { return static_cast<float> (*value); }
    operator int() const { return *value; }

    IntType& operator+= (const int rhs);
    IntType& operator-= (const int rhs);
    IntType& operator*= (const int rhs);
    IntType& operator/= (const int rhs);

    IntType& pow (int exponent);
    IntType& pow (const DoubleType& exponent);
    IntType& pow (const FloatType& exponent);
    IntType& pow (const IntType& exponent);
    

private:
    int* value;

    IntType& powInternal (const int exponent);
};
