/*
Project 4: Part 4 / 9
 Chapter 4 Part 7
 Function/Constructor Overloading

 Create a branch named Part4
 
 Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add pow() functions, and a powInternal() function to each of your UDTs
     a) your pow() functions should call powInternal()
     b) add a pow() whose argument type is the primitive your UDT owns.  the argument should be passed by copy.
     c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
         the argument should be passed as const ref
         i.e. if you had UDTs named IntType, FloatType, DoubleType
             in your IntType class, you'd have:
                 pow(const IntType&),
                 pow(const FloatType&),
                 pow(const DoubleType&),
                 and pow(int)
     d) be sure to remember the rules about what member functions can be called on const objects.
             (const objects can only call their const member functions)
     e) the pow() functions should be chainable.
 
 2) your powInternal() function should do something like this in its body:    *val = std::pow( *val, arg );
         where 'arg' is the passed-in type, converted to whatever type your object is holding.
             if your UDT owns an int, then arg would be an int.
             if your UDT owns a float, then arg would be a float.
         std::pow's documentation is found here: https://en.cppreference.com/w/cpp/numeric/math/pow so be sure to include
             the proper header file listed there.
         powInternal() should be chainable.
         powInternal() should be a private member function
 
 3) modify the Point class below to have 3 Constructors that accept your UDTs and one that accepts primitives.
     a) make the constructor that takes primitives initialize the two member variables.
     b) for each of your 3 Ctors that accept UDTs: correctly implement a Delegating Constructor that calls the constructor which takes primitives
     c) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     d) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) mark your UDT constructors as 'explicit'.  
    Adding this keyword prevents the compiler from implicitly creating instances of your UDT whenever primitives are passed to functions that take your UDT by const reference.
    This keyword means you can only create an instance of the class by Explicitly writing the type name.
    You can learn more about the explicit keyword here: 
    https://en.cppreference.com/w/cpp/language/explicit
 
 5) insert part4(); at the end of main, before the 'good to go'
 
 6) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 */




/*
your program should generate the following output EXACTLY.
This includes the warnings.  
 The output should have zero warnings.


FloatType add result=4
FloatType subtract result=2
FloatType multiply result=4
FloatType divide result=0.25

DoubleType add result=4
DoubleType subtract result=2
DoubleType multiply result=4
DoubleType divide result=0.8

IntType add result=4
IntType subtract result=2
IntType multiply result=4
IntType divide result=1

Chain calculation = 590
New value of ft = (ft + 3.0f) * 1.5f / 5.0f = 0.975
---------------------

Initial value of dt: 0.8
Initial value of it: 590
Use of function concatenation (mixed type arguments) 
New value of dt = (dt * it) / 5.0f + ft = 95.375
---------------------

Intercept division by 0 
New value of it = it / 0 = error: integer division by zero is an error and will crash the program!
590
New value of ft = ft / 0 = warning: floating point division by zero!
inf
New value of dt = dt / 0 = warning: floating point division by zero!
inf
---------------------

The result of FloatType^4 divided by IntType is: 26.9136
The result of DoubleType times 3 plus IntType is : 67.3
The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: 711
An operation followed by attempts to divide by 0, which are ignored and warns user: 
error: integer division by zero is an error and will crash the program!
error: integer division by zero is an error and will crash the program!
error: integer division by zero is an error and will crash the program!
505521
FloatType x IntType  =  13143546
(IntType + DoubleType + FloatType) x 24 = 315447336
Power tests with FloatType 
pow(ft1, floatExp) = 2^2 = 4
pow(ft1, itExp) = 4^2 = 16
pow(ft1, ftExp) = 16^2 = 256
pow(ft1, dtExp) = 256^2 = 65536
---------------------

Power tests with DoubleType 
pow(dt1, doubleExp) = 2^2 = 4
pow(dt1, itExp) = 4^2 = 16
pow(dt1, ftExp) = 16^2 = 256
pow(dt1, dtExp) = 256^2 = 65536
---------------------

Power tests with IntType 
pow(it1, intExp) = 2^2 = 4
pow(it1, itExp) = 4^2 = 16
pow(it1, ftExp) = 16^2 = 256
pow(it1, dtExp) = 256^2 = 65536
===============================

Point tests with float argument:
Point { x: 3, y: 6 }
Multiplication factor: 6
Point { x: 18, y: 36 }
---------------------

Point tests with FloatType argument:
Point { x: 3, y: 3 }
Multiplication factor: 3
Point { x: 9, y: 9 }
---------------------

Point tests with DoubleType argument:
Point { x: 3, y: 4 }
Multiplication factor: 4
Point { x: 12, y: 16 }
---------------------

Point tests with IntType argument:
Point { x: 3, y: 4 }
Multiplication factor: 5
Point { x: 15, y: 20 }
---------------------

good to go!

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/
#include <iostream>
#include "DoubleType.h"
#include "FloatType.h"
#include "IntType.h"

void part3()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    std::cout << "The result of FloatType^4 divided by IntType is: " << static_cast<float> (ft.multiply (ft).multiply (ft).divide (static_cast<float> (it))) << std::endl;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << static_cast<double> (dt.multiply (3).add (it)) << std::endl;
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << static_cast<int> (it.divide (static_cast<int> (pi)) .multiply (static_cast<int> (dt)).subtract (static_cast<int> (ft))) << std::endl;
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    std::cout << static_cast<int> (it.multiply (it).divide (0).divide (0.0f).divide (0.0)) << std::endl;
    
    std::cout << "FloatType x IntType  =  " << static_cast<int> (it.multiply (static_cast<int> (ft))) << std::endl;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << static_cast<int> (it.add (static_cast<int> (dt)).add (static_cast<int> (ft)).multiply (24)) << std::endl;
}



struct A {};
struct HeapA
{ 
    HeapA() : a(new A) {}

    ~HeapA()
    {
        delete a;
    }

    A* a = nullptr;
};

struct Point
{
    Point (float x_, float y_) : x (x_), y (y_) { }

    Point (const DoubleType& x_, const DoubleType& y_) : Point (static_cast<float> (x_), static_cast<float> (y_)) {}
    Point (const FloatType& x_, const FloatType& y_) : Point (static_cast<float> (x_), static_cast<float> (y_)) {}
    Point (const IntType& x_, const IntType& y_) : Point (static_cast<float> (x_), static_cast<float> (y_)) {}

    Point& multiply (const float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    Point& multiply (const DoubleType& m)
    {
        x *= static_cast<float> (m);
        y *= static_cast<float> (m);
        return *this;
    }

    Point& multiply (const FloatType& m)
    {
        x *= static_cast<float> (m);
        y *= static_cast<float> (m);
        return *this;
    }

    Point& multiply (const IntType& m)
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

void part4()
{
    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    FloatType ft1(2);
    DoubleType dt1(2);
    IntType it1(2);    
    float floatExp = 2.0f;
    double doubleExp = 2.0;
    int intExp = 2;
    IntType itExp(2);
    FloatType ftExp(2.0f);
    DoubleType dtExp(2.0);
    
    // Power tests with FloatType
    std::cout << "Power tests with FloatType" << std::endl;
    std::cout << "pow(ft1, floatExp) = " << static_cast<float> (ft1) << "^" << static_cast<float> (floatExp) << " = " << static_cast<float> (ft1.pow(floatExp))  << std::endl;
    std::cout << "pow(ft1, itExp) = " << static_cast<float> (ft1) << "^" << static_cast<int> (itExp) << " = " << static_cast<float> (ft1.pow(itExp))  << std::endl;
    std::cout << "pow(ft1, ftExp) = " << static_cast<float> (ft1) << "^" << static_cast<float> (ftExp) << " = " << static_cast<float> (ft1.pow(ftExp))  << std::endl;    
    std::cout << "pow(ft1, dtExp) = " << static_cast<float> (ft1) << "^" << static_cast<double> (dtExp) << " = " << static_cast<float> (ft1.pow(dtExp))  << std::endl;    
    std::cout << "---------------------\n" << std::endl;  

    // Power tests with DoubleType
    std::cout << "Power tests with DoubleType" << std::endl;
    std::cout << "pow(dt1, doubleExp) = " << static_cast<double> (dt1) << "^" << static_cast<double> (doubleExp) << " = " << static_cast<double> (dt1.pow(intExp))  << std::endl;
    std::cout << "pow(dt1, itExp) = " << static_cast<double> (dt1) << "^" << static_cast<int> (itExp) << " = " << static_cast<double> (dt1.pow(itExp))  << std::endl;
    std::cout << "pow(dt1, ftExp) = " << static_cast<double> (dt1) << "^" << static_cast<float> (ftExp) << " = " << static_cast<double> (dt1.pow(ftExp))  << std::endl;    
    std::cout << "pow(dt1, dtExp) = " << static_cast<double> (dt1) << "^" << static_cast<double> (dtExp) << " = " << static_cast<double> (dt1.pow(dtExp))  << std::endl;    
    std::cout << "---------------------\n" << std::endl;    

    // Power tests with IntType
    std::cout << "Power tests with IntType" << std::endl;
    std::cout << "pow(it1, intExp) = " << static_cast<int> (it1) << "^" << static_cast<int> (intExp) << " = " << static_cast<int> (it1.pow(intExp))  << std::endl;
    std::cout << "pow(it1, itExp) = " << static_cast<int> (it1) << "^" << static_cast<int> (itExp )<< " = " << static_cast<int> (it1.pow(itExp))  << std::endl;
    std::cout << "pow(it1, ftExp) = " << static_cast<int> (it1) << "^" << static_cast<float> (ftExp )<< " = " << static_cast<int> (it1.pow(ftExp))  << std::endl;    
    std::cout << "pow(it1, dtExp) = " << static_cast<int> (it1) << "^" << static_cast<double> (dtExp )<< " = " << static_cast<int> (it1.pow(dtExp))  << std::endl;    
    std::cout << "===============================\n" << std::endl; 

    // ------------------------------------------------------------
    //                          Point tests
    // ------------------------------------------------------------
    FloatType ft2(3.0f);
    DoubleType dt2(4.0);
    IntType it2(5);
    float floatMul = 6.0f;

    // Point tests with float
    std::cout << "Point tests with float argument:" << std::endl;
    Point p0(ft2, floatMul);
    p0.toString();   
    std::cout << "Multiplication factor: " << floatMul << std::endl;
    p0.multiply(floatMul); 
    p0.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with FloatType
    std::cout << "Point tests with FloatType argument:" << std::endl;
    Point p1(ft2, ft2);
    p1.toString();   
    std::cout << "Multiplication factor: " << static_cast<float> (ft2) << std::endl;
    p1.multiply(ft2); 
    p1.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with DoubleType
    std::cout << "Point tests with DoubleType argument:" << std::endl;
    Point p2(ft2, static_cast<float>(dt2));
    p2.toString();   
    std::cout << "Multiplication factor: " << static_cast<double> (dt2) << std::endl;
    p2.multiply(dt2); 
    p2.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with IntType
    std::cout << "Point tests with IntType argument:" << std::endl;
    Point p3(ft2, static_cast<float>(dt2));
    p3.toString();   
    std::cout << "Multiplication factor: " << static_cast<int> (it2) << std::endl;
    p3.multiply(it2); 
    p3.toString();   
    std::cout << "---------------------\n" << std::endl;
}


int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;
    
    std::cout << "FloatType add result=" << static_cast<float> (ft.add (2.0f)) << std::endl;
    std::cout << "FloatType subtract result=" << static_cast<float> (ft.subtract (2.0f)) << std::endl;
    std::cout << "FloatType multiply result=" << static_cast<float> (ft.multiply (2.0f)) << std::endl;
    std::cout << "FloatType divide result=" << static_cast<float> (ft.divide (16.0f)) << std::endl << std::endl;

    std::cout << "DoubleType add result=" << static_cast<double> (dt.add (2.0)) << std::endl;
    std::cout << "DoubleType subtract result=" << static_cast<double> (dt.subtract (2.0)) << std::endl;
    std::cout << "DoubleType multiply result=" << static_cast<double> (dt.multiply (2.0)) << std::endl;
    std::cout << "DoubleType divide result=" << static_cast<double> (dt.divide ( static_cast<double> (5.f))) << std::endl << std::endl;

    std::cout << "IntType add result=" << static_cast<int> (it.add (2)) << std::endl;
    std::cout << "IntType subtract result=" << static_cast<int> (it.subtract (2)) << std::endl;
    std::cout << "IntType multiply result=" << static_cast<int> (it.multiply (2)) << std::endl;
    std::cout << "IntType divide result=" << static_cast<int> (it.divide (3)) << std::endl << std::endl;
    std::cout << "Chain calculation = " << static_cast<int> (it.multiply (1000).divide (2).subtract (10).add (100)) << std::endl;

        // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << static_cast<float> (ft.add (3.0f).multiply (1.5f).divide (5.0f)) << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << static_cast<double> (dt) << std::endl;
    std::cout << "Initial value of it: " << static_cast<int> (it) << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << static_cast<double> (dt.multiply (it).divide (static_cast<double> (5.0f)).add (static_cast<double> (ft))) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << static_cast<int> (it.divide (0)) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << static_cast<float> (ft.divide (0)) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << static_cast<double> (dt.divide (0)) << std::endl;

    std::cout << "---------------------\n" << std::endl; 

    part3();
    
    part4();
    
    std::cout << "good to go!\n";

    return 0;
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
