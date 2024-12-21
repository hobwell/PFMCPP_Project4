#pragma once

#include <functional>
#include <cmath>
#include <memory>

template <typename T>
struct Numeric
{
    using Type = T;

    Numeric (Type t) : value (std::make_unique<Type>(t)) {}

    Numeric(const Numeric& other) : value (std::make_unique<Type>(*other.value)) {}

    ~Numeric() {}

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

    template <typename RHS>
    // PLEASE NOTE: Not sure if the intention was to need a template here, but I couldn't figure out how to do it without it.
    Numeric& operator/= (RHS rhs)
    {
        if constexpr (std::is_same<int, Type>::value)
        {
            if constexpr (std::is_same<int, decltype(rhs)>::value)
            {
                if (rhs == 0)
                {
                    std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
                    return *this;
                }
            }
            else if (static_cast<float> (rhs) < std::numeric_limits<float>::epsilon())
            {
                std::cout << "can't divide integers by zero!" << std::endl;
                return *this;
            }
        }
        else if (static_cast<float> (rhs) < std::numeric_limits<float>::epsilon())
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }

        *value /= static_cast<Type> (rhs);
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

template<>
struct Numeric<double>
{
    using Type = double;

    Numeric (Type t) : value (std::make_unique<Type>(t)) {}

    Numeric(const Numeric& other) : value (std::make_unique<Type>(*other.value)) {}

    ~Numeric() {}

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
            std::cout << "warning: floating point division by zero!" << std::endl;
        }
        
        *value /= rhs;
        return *this;
    }

    template <typename CallableType>
    Numeric& apply (CallableType& callable)
    {
        callable(*value);
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

// Deduction guide
template <typename T>
Numeric(T) -> Numeric<T>;
