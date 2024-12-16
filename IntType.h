struct IntType
{
    int* value;

    IntType (int i) : value {new int (i)} { }

    ~IntType() 
    {
        delete value;
    }

    IntType& add (int rhs);
    IntType& divide (int rhs);
    IntType& multiply (int rhs);
    IntType& subtract (int rhs);
};
