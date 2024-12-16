struct FloatType
{
    FloatType (float f) : value {new float (f)} { }

    ~FloatType() 
    {
        delete value;
    }

    operator float() const { return *value; }

    FloatType& add (float rhs);
    FloatType& divide (float rhs);
    FloatType& multiply (float rhs);
    FloatType& subtract (float rhs);

private:
    float* value = nullptr;

};
