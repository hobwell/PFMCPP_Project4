#pragma once

#include <functional>
#include <cmath>
#include <memory>
#include "Temporary.h"

template <typename T>
struct Numeric
{
    using Type = T;

    Numeric (Type&& t) : value (std::make_unique<Temporary<Type>>(std::move (t))) {}

    operator T() const { return *value; }

    template <typename OtherType>
    Numeric& operator+= (OtherType&& rhs)
    {
        *value += static_cast<Type> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator-= (OtherType&& rhs)
    {
        *value -= static_cast<Type> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator*= (OtherType&& rhs)
    {
        *value *= static_cast<Type> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator/= (OtherType&& rhs)
    {
        *value /= static_cast<Type> (rhs);
        return *this;
    }

    template <typename CallableType>
    Numeric& apply (CallableType&& callable)
    {
        callable(*value);
        return *this;
    }

    template <typename OtherType>
    Numeric& pow (OtherType&& exponent)
    {
       *value = static_cast<Type> (std::pow (static_cast<Type> (*value), static_cast<Type> (exponent)));
        
        return *this;
    }

private:
    std::unique_ptr<Temporary<Type>> value;
};

// Deduction guide
template <typename T>
Numeric(T) -> Numeric<T>;
