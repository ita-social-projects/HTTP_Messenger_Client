#ifndef IJSONDESERIALIZER_H
#define IJSONDESERIALIZER_H


class IJsonDeserializer
{
public:
    IJsonDeserializer();

    virtual void extract() = 0;
};

#endif // IJSONDESERIALIZER_H
