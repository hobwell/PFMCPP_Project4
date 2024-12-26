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

    template<typename OtherType>
    operator OtherType&() 
    {
        return static_cast<OtherType&>(v);
    }

    Temporary& operator+= (NumericType&& rhs) 
    {
        v += std::move(rhs);
        return *this;
    }

    Temporary& operator-= (NumericType&& rhs) 
    {
        v -= std::move(rhs);
        return *this;
    }

    Temporary& operator*= (NumericType&& rhs) 
    {
        v *= std::move(rhs);
        return *this;
    }

    Temporary& operator/= (NumericType&& rhs) 
    {
        if constexpr (std::is_same<int, NumericType>::value)
        {
            if (rhs == 0)
            {
                std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
                return *this;
            }
        }
        else if (static_cast<NumericType> (rhs) <= std::numeric_limits<NumericType>::epsilon())
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }

        v /= std::move(rhs);
        return *this;
    }

private:
    static int counter;
    NumericType v;
};
