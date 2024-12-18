struct DoubleType;
struct FloatType;

struct IntType
{
    IntType (int i) : value {new int (i)} { }

    ~IntType() 
    {
        delete value;
    }

    operator int() const { return *value; }

    IntType& add (int rhs);
    IntType& divide (int rhs);
    IntType& multiply (int rhs);
    IntType& pow (int exponent);
    IntType& pow (const DoubleType& exponent);
    IntType& pow (const FloatType& exponent);
    IntType& pow (const IntType& exponent);
    IntType& subtract (int rhs);

private:
    int* value;

    IntType& powInternal (int exponent);
};
