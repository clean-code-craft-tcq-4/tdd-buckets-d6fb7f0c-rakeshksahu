#ifndef __A2DCONVERTER12BIT_HPP_
#define __A2DCONVERTER12BIT_HPP_

#include <iostream>
#include <vector>

class A2DConverter12Bit
{
    public:
        bool checkIfInputWithInRange(const std::vector<uint32_t>& inputData);
        std::vector<uint32_t> convertADCValueToAmpere(const std::vector<uint32_t>& currentSensorValue);

    private:
        const uint32_t ADC_12BIT_UPPER_LIMIT {4094};
        const uint32_t ADC_12BIT_LOWER_LIMIT {0};
        const uint32_t ADC_12BIT_MAX_CURRENT_IN_AMPS {10};
};
#endif /*__A2DCONVERTER12BIT_HPP_ */