#pragma once

#include <string>

struct NumericType
{
    NumericType();
    virtual ~NumericType();

    // force derived types to implement toString()
    virtual std::string toString() const = 0;

};
