#include <iostream>

template<typename NumericType>
struct Temporary
{
    Temporary (NumericType&& t) : v (std::move (t))
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
     */
    operator NumericType&&() const
    { 
        /* read-only function */
        return std::move (v);
    }

    operator NumericType&&()
    { 
        /* read/write function */
        return std::move (v);
    }

    Temporary& operator+= (const NumericType& rhs) 
    { 
        v += rhs; 
        return *this; 
    }

    Temporary& operator-= (const NumericType& rhs) 
    { 
        v -= rhs; 
        return *this; 
    }

    Temporary& operator*= (const NumericType& rhs) 
    { 
        v *= rhs; 
        return *this; 
    }

    Temporary& operator/= (const NumericType& rhs) 
    { 
        v /= rhs; 
        return *this; 
    }

private:
    static int counter;
    NumericType v;
};
