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
    IntType& subtract (int rhs);

private:
    int* value;

};
