#pragma once

#include <functional>
#include <cmath>
#include <memory>

template <typename T>
struct Numeric
{
    using Type = T;

    Numeric (Type t) : value (std::make_unique<Type>(t)) {}

    operator T() const { return static_cast<T> (*value); }

    template <typename OtherType>
    Numeric& operator+= (OtherType rhs)
    {
        *value += static_cast<Type> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator-= (OtherType rhs)
    {
        *value -= static_cast<Type> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator*= (OtherType rhs)
    {
        *value *= static_cast<Type> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator/= (OtherType rhs)
    {
        if constexpr (std::is_same<int, Type>::value)
        {
            if constexpr (std::is_same<int, OtherType>::value)
            {
                if (rhs == 0)
                {
                    std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
                    return *this;
                }
            }
            else if (static_cast<OtherType> (rhs) < std::numeric_limits<OtherType>::epsilon())
            {
                std::cout << "can't divide integers by zero!" << std::endl;
                return *this;
            }
        }
        else if (static_cast<OtherType> (rhs) <= std::numeric_limits<OtherType>::epsilon())
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }

        *value /= static_cast<Type> (rhs);
        return *this;
    }

    template <typename CallableType>
    Numeric& apply (CallableType& callable)
    {
        callable(*value);
        return *this;
    }

    template <typename OtherType>
    Numeric& pow (OtherType exponent)
    {
       *value = static_cast<Type> (std::pow (*value, static_cast<Type> (exponent)));
        
        return *this;
    }

private:
    std::unique_ptr<Type> value;
};

// Deduction guide
template <typename T>
Numeric(T) -> Numeric<T>;
