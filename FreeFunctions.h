#pragma once

#include <iostream>
#include "NumericType.h"

// overload << operator for NumericTypes, to remove the need for explicit casting when using the << operator
std::ostream& operator<<(std::ostream& os, const NumericType& p)
{
    os << p.toString();
    return os;  // Return the output stream to allow chaining
}
