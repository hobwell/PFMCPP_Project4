#pragma once

#include <functional>
#include <cmath>
#include <memory>
#include "Temporary.h"

template <typename T>
struct Numeric
{
    using Type = Temporary<T>;
  
    Numeric& operator= (T&& rhs)
    {
        *value = std::move(rhs);
        return *this;
    }

    Numeric (Type t) : value (std::make_unique<Temporary<T>>(std::move (t))) {}

    operator T() const { return static_cast<T> (*value); }

    Numeric& operator+= (T rhs)
    {
        *value += rhs;
        return *this;
    }

    Numeric& operator-= (T rhs)
    {
        *value -= rhs;
        return *this;
    }

    Numeric& operator*= (T rhs)
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

    Numeric& pow (T exponent)
    {
       *value = static_cast<T> (std::pow (*value, exponent));
        
        return *this;
    }

private:
    std::unique_ptr<Temporary<T>> value;
};

// Deduction guide
template <typename T>
Numeric(T) -> Numeric<T>;
