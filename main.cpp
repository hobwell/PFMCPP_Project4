/*
Project 4: Part 9 / 9
 video: Chapter 5 Part 8

Create a branch named Part9

 Rule of 3-5-0 and S.R.P.
 
 DO NOT EDIT YOUR PREVIOUS main(). 
 
 1) add the Leak Detector files from Project5
 
 2) move these macros after the JUCE_LEAK_DETECTOR macro :
 */



/*
 3) add JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Temporary) to the end of the  Temporary<> struct
 
 4) add JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Numeric) to the end of the Numeric<> struct
 
 if you compile it, you'll see lots of errors about deleted functions.
 
 5) Implement the Rule of 5 on Numeric<> and Temporary<> to fix this.
 
 You should end up with the same program output as Part 8's task if you did it right.
 */


/*
 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/

#include <typeinfo>
#include <memory>
#include <iostream>
#include <cmath>
#include <functional>
#include "LeakedObjectDetector.h"

template<typename NumericType>
struct Temporary
{
    Temporary (NumericType t) : v (t)
    {
        std::cout << "I'm a Temporary<" << typeid (v).name() << "> object, #"
                  << counter++ << std::endl;
    }

    // rule of 5: define destructor 
    ~Temporary() = default; // nothing in this class requires management

    // rule of 5: define move constructor
    Temporary (Temporary&& other) : v (other.v) { }

    operator NumericType() const 
    { 
        return v;
    }

    operator NumericType&() 
    {
       return v;
    }

    // rule of 5: define move assignment operator
    Temporary& operator= (Temporary&& other)
    {
        v = std::move (other.v);
        return *this;
    }

    
private:
    static int counter;
    NumericType v;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Temporary)
};


template<typename Type>
int Temporary<Type>::counter = 0;

template <typename T>
struct Numeric
{
    using Type = Temporary<T>;

    // rule of 5: define destructor 
    ~Numeric() = default; // std::unique_ptr<Type> does not require management

    // rule of 5: define move constructor
    Numeric (Numeric&& other) : value (std::move (other.value)) 
    {
        other.value = nullptr;
    }

    // rule of 5: define move assignment operator
    Numeric& operator= (Numeric&& other)
    {
        value = std::move (other.value);
        other.value = nullptr;
        return *this;
    }

    Numeric (T t) : value (std::make_unique<Type> (std::move (t))) {}

    //this is the read-only conversion function
    operator T() const { return *value; } // invoke Temporary<T>s conversion function
    
    // this is the read-write conversion function
    operator T&() { return *value; } // invoke Temporary<T>s conversion function

    template <typename OtherType>
    Numeric& operator+= (const OtherType& rhs)
    {
        *value += static_cast<T> (rhs); // this will rely on the conversion operator of Temporary
        return *this;
    }

    template <typename OtherType>
    Numeric& operator-= (const OtherType& rhs)
    {
        *value -= static_cast<T> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator*= (const OtherType& rhs)
    {
        *value *= static_cast<T> (rhs);
        return *this;
    }

    template <typename OtherType>
    Numeric& operator/= (const OtherType& rhs)
    {
        if constexpr (std::is_same<int, T>::value)
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
        {
            *value /= static_cast<T> (rhs);
        }
        return *this;
    }

    template <typename CallableType>
    Numeric& apply (CallableType&& callable)
    {
        callable (value);
        return *this;
    }

    template <typename OtherType>
    Numeric& pow (const OtherType& exponent)
    {
        *value = std::pow (static_cast<T> (*value), static_cast<T> (exponent));
        return *this;
    }

private:
    std::unique_ptr<Type> value;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Numeric)
};

//void part3()
//{
//    Numeric ft( 5.5f );
//    Numeric dt( 11.1 );
//    Numeric it ( 34 );
//    Numeric pi( 3.14 );
//
//    ft *= ft;
//    ft *= ft;
//    ft /= static_cast<float> (it);    
//    std::cout << "The result of FloatType^4 divided by IntType is: " << static_cast<float> (ft) << std::endl;
//
//    dt *= 3;
//    dt += it;
//    std::cout << "The result of DoubleType times 3 plus IntType is : " << static_cast<double> (dt) << std::endl;
//
//    it /= static_cast<int> (pi);
//    it *= static_cast<int> (dt);
//    it -= static_cast<int> (ft);
//    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << static_cast<int> (it) << std::endl;
//    
//    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
//
//    it *= it;
//    it /= 0;
//    it /= 0.f;
//    it /= 0.0f;
//    std::cout << static_cast<int> (it) << std::endl;
//
//    it *= static_cast<int> (ft);    
//    std::cout << "FloatType x IntType  =  " << static_cast<int> (it) << std::endl;
//
//    it += static_cast<int> (dt);
//    it += static_cast<int> (ft);
//    it *= 24;
//    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << static_cast<int> (it) << std::endl;
//}



struct A {};
struct HeapA
{ 
    HeapA() : a(std::make_unique<A>()) {}

    ~HeapA()
    {
        //delete a; // no longer needed - unique_ptr will take care of it!
    }

    std::unique_ptr<A> a = nullptr;
};

struct Point
{
    Point (float x_, float y_) : x (x_), y (y_) { }

    template <typename T1, typename T2>
    Point (const Numeric<T1>& x_, const Numeric<T2>& y_) : Point (static_cast<float> (x_), static_cast<float> (y_)) {}

    Point& multiply (const float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    Point& multiply (const Numeric<double>& m)
    {
        x *= static_cast<float> (m);
        y *= static_cast<float> (m);
        return *this;
    }

    Point& multiply (const Numeric<float>& m)
    {
        x *= static_cast<float> (m);
        y *= static_cast<float> (m);
        return *this;
    }

    Point& multiply (const Numeric<int>& m)
    {
        x *= static_cast<float> (m);
        y *= static_cast<float> (m);
        return *this;
    }

    void toString()
    {
        std::cout << "Point { x: " << x << ", y: " << y << " }" << std::endl;
    }

private:
    float x{0}, y{0};
};

//void part4()
//{
//    // ------------------------------------------------------------
//    //                          Power tests
//    // ------------------------------------------------------------
//    Numeric ft1(2.f);
//    Numeric dt1(2.0);
//    Numeric it1(2);    
//    float floatExp = 2.0f;
//    double doubleExp = 2.0;
//    int intExp = 2;
//    Numeric itExp(2);
//    Numeric ftExp(2.0f);
//    Numeric dtExp(2.0);
//    
//    // Power tests with FloatType
//    std::cout << "Power tests with FloatType" << std::endl;
//    std::cout << "pow(ft1, floatExp) = " << static_cast<float> (ft1) << "^" << static_cast<float> (floatExp) << " = " << static_cast<float> (ft1.pow(floatExp))  << std::endl;
//    std::cout << "pow(ft1, itExp) = " << static_cast<float> (ft1) << "^" << static_cast<int> (itExp) << " = " << static_cast<float> (ft1.pow(static_cast<float> (itExp)))  << std::endl;
//    std::cout << "pow(ft1, ftExp) = " << static_cast<float> (ft1) << "^" << static_cast<float> (ftExp) << " = " << static_cast<float> (ft1.pow(ftExp))  << std::endl;    
//    std::cout << "pow(ft1, dtExp) = " << static_cast<float> (ft1) << "^" << static_cast<double> (dtExp) << " = " << static_cast<float> (ft1.pow(static_cast<float> (dtExp)))  << std::endl;    
//    std::cout << "---------------------\n" << std::endl;  
//
//    // Power tests with DoubleType
//    std::cout << "Power tests with DoubleType" << std::endl;
//    std::cout << "pow(dt1, doubleExp) = " << static_cast<double> (dt1) << "^" << static_cast<double> (doubleExp) << " = " << static_cast<double> (dt1.pow(intExp))  << std::endl;
//    std::cout << "pow(dt1, itExp) = " << static_cast<double> (dt1) << "^" << static_cast<int> (itExp) << " = " << static_cast<double> (dt1.pow(static_cast<double> (itExp)))  << std::endl;
//    std::cout << "pow(dt1, ftExp) = " << static_cast<double> (dt1) << "^" << static_cast<float> (ftExp) << " = " << static_cast<double> (dt1.pow(static_cast<double> (ftExp)))  << std::endl;    
//    std::cout << "pow(dt1, dtExp) = " << static_cast<double> (dt1) << "^" << static_cast<double> (dtExp) << " = " << static_cast<double> (dt1.pow(dtExp))  << std::endl;    
//    std::cout << "---------------------\n" << std::endl;    
//
//    // Power tests with IntType
//    std::cout << "Power tests with IntType" << std::endl;
//    std::cout << "pow(it1, intExp) = " << static_cast<int> (it1) << "^" << static_cast<int> (intExp) << " = " << static_cast<int> (it1.pow(intExp))  << std::endl;
//    std::cout << "pow(it1, itExp) = " << static_cast<int> (it1) << "^" << static_cast<int> (itExp)<< " = " << static_cast<int> (it1.pow(itExp))  << std::endl;
//    std::cout << "pow(it1, ftExp) = " << static_cast<int> (it1) << "^" << static_cast<float> (ftExp)<< " = " << static_cast<int> (it1.pow(static_cast<int> (ftExp)))  << std::endl;    
//    std::cout << "pow(it1, dtExp) = " << static_cast<int> (it1) << "^" << static_cast<double> (dtExp)<< " = " << static_cast<int> (it1.pow(static_cast<int> (dtExp)))  << std::endl;    
//    std::cout << "===============================\n" << std::endl; 
//
//    // ------------------------------------------------------------
//    //                          Point tests
//    // ------------------------------------------------------------
//    Numeric ft2(3.0f);
//    Numeric dt2(4.0);
//    Numeric it2(5);
//    float floatMul = 6.0f;
//
//    // Point tests with float
//    std::cout << "Point tests with float argument:" << std::endl;
//    Point p0(static_cast<float> (ft2), floatMul);
//    p0.toString();   
//    std::cout << "Multiplication factor: " << floatMul << std::endl;
//    p0.multiply(floatMul); 
//    p0.toString();   
//    std::cout << "---------------------\n" << std::endl;
//
//    // Point tests with FloatType
//    std::cout << "Point tests with FloatType argument:" << std::endl;
//    Point p1(ft2, ft2);
//    p1.toString();   
//    std::cout << "Multiplication factor: " << static_cast<float> (ft2) << std::endl;
//    p1.multiply(ft2); 
//    p1.toString();   
//    std::cout << "---------------------\n" << std::endl;
//
//    // Point tests with DoubleType
//    std::cout << "Point tests with DoubleType argument:" << std::endl;
//    Point p2(static_cast<float>(ft2), static_cast<float>(dt2));
//    p2.toString();   
//    std::cout << "Multiplication factor: " << static_cast<double> (dt2) << std::endl;
//    p2.multiply(dt2); 
//    p2.toString();   
//    std::cout << "---------------------\n" << std::endl;
//
//    // Point tests with IntType
//    std::cout << "Point tests with IntType argument:" << std::endl;
//    Point p3(static_cast<float>(ft2), static_cast<float>(dt2));
//    p3.toString();   
//    std::cout << "Multiplication factor: " << static_cast<int> (it2) << std::endl;
//    p3.multiply(it2); 
//    p3.toString();   
//    std::cout << "---------------------\n" << std::endl;
//}

//template <typename T>
//void myNumericFreeFunct(std::unique_ptr<T>& t)
//{
//    t += 7;
//}

template <typename T>
void cube(std::unique_ptr<T>& t)
{
    auto& v = *t;
    v = v * v * v;
}

/*
void part6()
{
    FloatType ft3(3.0f);
    DoubleType dt3(4.0);
    IntType it3(5);
    
    std::cout << "Calling FloatType::apply() using a lambda (adds 7.0f) and FloatType as return type:" << std::endl;
    std::cout << "ft3 before: " << static_cast<float> (ft3) << std::endl;
    ft3.apply (
        [&ft = ft3] (float& val)
        { 
            val += 7; 
            return &ft; 
        } 
    );
    std::cout << "ft3 after: " << static_cast<float> (ft3) << std::endl;
    std::cout << "Calling FloatType::apply() using a free function (adds 7.0f) and void as return type:" << std::endl;
    std::cout << "ft3 before: " << static_cast<float> (ft3) << std::endl;
    ft3.apply (myFloatFreeFunct);
    std::cout << "ft3 after: " << static_cast<float> (ft3) << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling DoubleType::apply() using a lambda (adds 6.0) and DoubleType as return type:" << std::endl;
    std::cout << "dt3 before: " << static_cast<double> (dt3) << std::endl;
    dt3.apply (
        [&dt = dt3] (double& d) -> DoubleType&
        {
            d += 6.0;
            return &dt;
        }
    );
    std::cout << "dt3 after: " << static_cast<double> (dt3) << std::endl;
    std::cout << "Calling DoubleType::apply() using a free function (adds 6.0) and void as return type:" << std::endl;
    std::cout << "dt3 before: " << static_cast<double> (dt3) << std::endl;
    dt3.apply (myDoubleFreeFunct);
    std::cout << "dt3 after: " << static_cast<double> (dt3) << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling IntType::apply() using a lambda (adds 5) and IntType as return type:" << std::endl;
    std::cout << "it3 before: " << static_cast<int> (it3) << std::endl;
    it3.apply (
        [&it = it3] (int& i) -> IntType&
        {
            i += 5;
            return &it;
        } 
    );
    std::cout << "it3 after: " << static_cast<int> (it3) << std::endl;
    std::cout << "Calling IntType::apply() using a free function (adds 5) and void as return type:" << std::endl;
    std::cout << "it3 before: " << static_cast<int> (it3) << std::endl;
    it3.apply (myIntFreeFunct);
    std::cout << "it3 after: " << static_cast<int> (it3) << std::endl;
    std::cout << "---------------------\n" << std::endl;    
}
*/

//void part7()
//{
//    
//    // steps 8 - 10
//    Numeric<double> step8(23.0); // step 8
//
//    {        
//        using numericType = decltype(step8)::Type;
//        using returnType = decltype(step8);
//            
//        // Note: I couldn't figure out how to do this without creating an lvalue
//        auto necessaryLValue = [&dt = step8] (numericType& value) -> returnType&
//        {
//            value += 5.0;
//            // step 10
//            dt += 14.0;
//            return dt;
//        };
//    
//        step8.apply(necessaryLValue).apply(myNumericFreeFunct<double>); // step 9
//    }
//    
//    Numeric ft3(3.0f);
//    Numeric dt3(4.0);
//    Numeric it3(5);
//    
//    std::cout << "Calling Numeric<float>::apply() using a lambda (adds 7.0f) and Numeric<float> as return type:" << std::endl;
//    std::cout << "ft3 before: " << static_cast<float> (ft3) << std::endl;
//
//    {
//        using numericType = decltype(ft3)::Type;
//        using returnType = decltype(ft3);
//        
//        ft3.apply( 
//            [&ft = ft3] (numericType& value) -> returnType&
//            {
//                value += 7.0f;
//                return ft;
//            }
//        );
//    }
//
//    std::cout << "ft3 after: " << static_cast<float> (ft3) << std::endl;
//    std::cout << "Calling Numeric<float>::apply() twice using a free function (adds 7.0f) and void as return type:" << std::endl;
//    std::cout << "ft3 before: " << static_cast<float> (ft3) << std::endl;
//    ft3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
//    std::cout << "ft3 after: " << static_cast<float> (ft3) << std::endl;
//    std::cout << "---------------------\n" << std::endl;
//
//    std::cout << "Calling Numeric<double>::apply() using a lambda (adds 6.0) and Numeric<double> as return type:" << std::endl;
//    std::cout << "dt3 before: " << static_cast<double> (dt3) << std::endl;
//
//    {
//        using numericType = decltype(dt3)::Type;
//        using returnType = decltype(dt3);
//        // NOTE: I couldn't figure out how to do this without creating an lvalue
//        auto neededLValue = 
//            [&dt = dt3] (numericType& value) -> returnType&
//            { 
//                value += 6.0;
//                return dt;
//            };
//        dt3.apply(neededLValue); // This calls the templated apply fcn
//    }
//    
//    std::cout << "dt3 after: " << static_cast<double> (dt3) << std::endl;
//    std::cout << "Calling Numeric<double>::apply() twice using a free function (adds 7.0) and void as return type:" << std::endl;
//    std::cout << "dt3 before: " << static_cast<double> (dt3) << std::endl;
//    dt3.apply(myNumericFreeFunct<double>).apply(myNumericFreeFunct<double>); // This calls the templated apply fcn
//    std::cout << "dt3 after: " << static_cast<double> (dt3) << std::endl;
//    std::cout << "---------------------\n" << std::endl;
//
//    std::cout << "Calling Numeric<int>::apply() using a lambda (adds 5) and Numeric<int> as return type:" << std::endl;
//    std::cout << "it3 before: " << static_cast<int> (it3) << std::endl;
//
//    {
//        using numericType = decltype(it3)::Type;
//        using returnType = decltype(it3);
//        
//        it3.apply( 
//            [&it = it3] (numericType& value) -> returnType&
//            {
//                value += 5;
//                return it;
//            }   
//        );
//    }
//    std::cout << "it3 after: " << static_cast<int> (it3) << std::endl;
//    std::cout << "Calling Numeric<int>::apply() twice using a free function (adds 7) and void as return type:" << std::endl;
//    std::cout << "it3 before: " << static_cast<int> (it3) << std::endl;
//    it3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
//    std::cout << "it3 after: " << static_cast<int> (it3) << std::endl;
//    std::cout << "---------------------\n" << std::endl;    
//}

int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);

    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;

    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;

    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;

    Point p(f, i);
    p.toString();

    d *= -1;
    std::cout << "d: " << d << std::endl;

    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;

    p.toString();

    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<int> (static_cast<double>(floatNum) / 2.3);
    std::cout << "intNum: " << intNum << std::endl;

    {
        using Type = decltype(f)::Type;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;

        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }

    {
        using Type = decltype(d)::Type;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;

        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }

    {
        using Type = decltype(i)::Type;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;

        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
}

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */
