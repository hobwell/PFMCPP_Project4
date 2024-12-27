#pragma once

#include <functional>
#include <cmath>
#include <memory>

template <typename T>
struct Temporary;

template <typename T>
struct Numeric
{
    using Type = Temporary<T>;
  
    Numeric& operator= (T&& rhs)
    {
        *value = std::move(rhs);
        return *this;
    }

    Numeric (Type t) : value (std::make_unique<Type>(std::move (t))) {}

    operator T() const { return static_cast<T> (*value); }

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
    Numeric& operator/= (RHS rhs)
    {
        if constexpr (std::is_same<int, T>::value)
        {
            if constexpr (std::is_same<int, RHS>::value)
            {
                if (rhs == 0)
                {
                    std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
                    return *this;
                }
            }
            else if (static_cast<RHS> (rhs) < std::numeric_limits<RHS>::epsilon())
            {
                std::cout << "can't divide integers by zero!" << std::endl;
                return *this;
            }
        }
        else if (static_cast<RHS> (rhs) <= std::numeric_limits<RHS>::epsilon())
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }
    
        *value /= static_cast<T> (rhs);
        return *this;
    }

    template <typename CallableType>
    Numeric& apply (CallableType&& callable)
    {
        callable(value);
        return *this;
    }

    Numeric& pow (Type exponent)
    {
       *value = std::pow (*value, exponent);
        
        return *this;
    }

private:
    std::unique_ptr<Type> value;
};

// Deduction guide
template <typename T>
Numeric(T) -> Numeric<T>;
