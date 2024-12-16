struct DoubleType
{
    double* value = nullptr;

    DoubleType (double d) : value {new double (d)} { }

    ~DoubleType() 
    {
        delete value;
    }

    DoubleType& add (double rhs);
    DoubleType& divide (double rhs);    
    DoubleType& multiply (double rhs);
    DoubleType& subtract (double rhs);
};
