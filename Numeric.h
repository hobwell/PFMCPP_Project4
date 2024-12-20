#pragma once

#include <functional>
#include <cmath>
#include <memory>

template <typename T>
struct Numeric
{
    using Type = T;

    Numeric (Type t) : value (std::make_unique<Type>(t)) {}

    ~Numeric();

    operator double() const { return static_cast<double> (*value); }
    operator float() const { return static_cast<float> (*value); }
    operator int() const { return static_cast<int> (*value); }

    Numeric& operator+= (Type rhs)
    {
        *value += rhs;
        return *this;
    }

    Numeric& operator-= (Type rhs)
    {
        *value -= rhs;
        return *this;
    }

    Numeric& operator*= (Type rhs)
    {
        *value *= rhs;
        return *this;
    }

    Numeric& operator/= (Type rhs)
    {
        if (rhs == 0.0)
        {
            std::cout << "warning: division by zero!" << std::endl;
        }
        
        *value /= rhs;
        return *this;
    }

    Numeric& apply (std::function<Numeric& (Type&)> func)
    {
        if (func)
        {
            return func(*value);
        }
    
        return *this;
    }

    Numeric& apply (void (*func) (Type&))
    {
        if (func)
        {
            func(*value);
        }
    
        return *this;
    }

    Numeric& pow (Type exponent)
    {
       return powInternal (exponent);
    }

    Numeric& pow (const Numeric& exponent)
    {
        return powInternal (exponent);
    }

private:
    std::unique_ptr<Type> value;

    Numeric& powInternal (Type exponent)
    {
        *value = static_cast<Type> (std::pow (*value, exponent));
        
        return *this;
    }
};
