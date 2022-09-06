#ifndef __A2DCONVERTER10BIT_HPP_
#define __A2DCONVERTER10BIT_HPP_

#include <iostream>
#include <vector>

class A2DConverter10Bit
{
    public:
    bool checkIfInputWithInRange(const std::vector<int32_t>& inputData);
    std::vector<int32_t> convertADCValueToAmpere(const std::vector<int32_t>& currentSensorValue);
    private:
    const uint32_t ADC_10BIT_UPPER_LIMIT {1022};
    const uint32_t ADC_10BIT_LOWER_LIMIT {0};
    const uint32_t ADC_10BIT_MAX_CURRENT_IN_AMPS {15};
};

#endif /*__A2DCONVERTER10BIT_HPP_ */