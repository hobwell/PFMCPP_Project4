#include <iostream>
#include "IntType.h"

IntType& IntType::add (int rhs)
{
    *value += rhs;
    return *this;
}

IntType& IntType::divide (const int rhs)
{
    if (rhs == 0)
    {
        std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
    }
    else
    {
        *value /= rhs;    
    }
    
    return *this;
}

IntType& IntType::multiply (int rhs)
{
    *value *= rhs;
    return *this;
}

IntType& IntType::subtract (int rhs)
{
    *value -= rhs;
    return *this;
}
