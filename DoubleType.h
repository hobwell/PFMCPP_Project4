struct DoubleType
{
    DoubleType (double d) : value {new double (d)} { }

    ~DoubleType() 
    {
        delete value;
    }

    operator double() const { return *value; }

    DoubleType& add (double rhs);
    DoubleType& divide (double rhs);    
    DoubleType& multiply (double rhs);
    DoubleType& subtract (double rhs);

private:
    double* value = nullptr;

};
