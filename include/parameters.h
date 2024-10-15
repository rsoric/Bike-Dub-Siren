#include "Arduino.h"
class parameter
{
private:
    float value;
    float stepIncrementValue;
    int currentStep;
    float min;
    float max;
    String name;

public:
    parameter(String name, float min, float max)
    {
        this->name = name;
        this->currentStep = 64;
        this->stepIncrementValue = (max - min) / 128.0;
        this->min = min;
        this->max = max;
        this->value = (currentStep * stepIncrementValue) + this->min;
    }
    void update(bool icr)
    {
        if(icr)
        {
            increment();
        }
        else
        {
            decrement();
        }
    }
    void increment()
    {
        if (currentStep < 128)
        {
            this->currentStep++;
            this->value = (currentStep * stepIncrementValue) + this->min;
        }
    }
    void increment8Times()
    {
        if (currentStep < 120)
        {
            this->currentStep = this->currentStep + 8;
            this->value = (currentStep * stepIncrementValue) + this->min;
        }
    }
    void decrement()
    {
        if (currentStep > 0)
        {
            this->currentStep--;
            this->value = (currentStep * stepIncrementValue) + this->min;
        }
    }
    void decrement8Times()
    {
        if (currentStep > 8)
        {
            this->currentStep = this->currentStep - 8;
            this->value = (currentStep * stepIncrementValue) + this->min;
        }
    }
    float getValue()
    {
        return this->value;
    }
    String getName()
    {
        return this->name;
    }
    int getCurrentStep()
    {
        return this->currentStep;
    }
};