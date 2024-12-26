#pragma once

#include <functional>
#include <cmath>
#include <memory>
#include "Temporary.h"

template <typename T>
struct Numeric
{
    using Type = Temporary<T>;

    Numeric (T&& t) : value (std::make_unique<Temporary<T>>(std::move (t))) {}

    operator T() const { return *value; }

    template <typename OtherType>
    Numeric& operator+= (OtherType&& rhs)
    {
        *value += static_cast<T> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator-= (OtherType&& rhs)
    {
        *value -= static_cast<T> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator*= (OtherType&& rhs)
    {
        *value *= static_cast<T> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator/= (OtherType&& rhs)
    {
        *value /= static_cast<T> (rhs);
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
       *value = static_cast<T> (std::pow (static_cast<T> (*value), static_cast<T> (exponent)));
        
        return *this;
    }

private:
    std::unique_ptr<Temporary<T>> value;
};

// Deduction guide
template <typename T>
Numeric(T) -> Numeric<T>;
