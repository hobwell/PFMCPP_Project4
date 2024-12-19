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

    FloatType& operator+= (float rhs);
    FloatType& operator-= (float rhs);
    FloatType& operator*= (float rhs);
    FloatType& operator/= (float rhs);
   
    FloatType& pow (float exponent);
    FloatType& pow (const DoubleType& exponent);
    FloatType& pow (const FloatType& exponent);
    FloatType& pow (const IntType& exponent);
    

private:
    float* value = nullptr;

    FloatType& powInternal (float exponent);
};
