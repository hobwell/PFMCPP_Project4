struct FloatType
{
    float* value = nullptr;

    FloatType (float f) : value {new float (f)} { }

    ~FloatType() 
    {
        delete value;
    }

    FloatType& add (float rhs);
    FloatType& divide (float rhs);
    FloatType& multiply (float rhs);
    FloatType& subtract (float rhs);
};
