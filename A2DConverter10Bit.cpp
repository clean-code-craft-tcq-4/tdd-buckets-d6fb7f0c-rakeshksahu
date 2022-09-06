#include "includes/A2DConverter10Bit.hpp"
#include <algorithm>
#include <cmath>

using namespace std;

bool A2DConverter10Bit::checkIfInputWithInRange(const std::vector<int32_t>& inputData) {
   auto result = std::find_if(inputData.begin(), inputData.end(), [this](const int32_t& i){
    return (i < ADC_10BIT_LOWER_LIMIT) || (i > ADC_10BIT_UPPER_LIMIT);
  });

  return result != inputData.end();
}

vector<int32_t> A2DConverter10Bit::convertADCValueToAmpere(const std::vector<int32_t>& currentSensorValue)
{
    vector<int32_t> currentInAmpereList;
    if (checkIfInputWithInRange(currentSensorValue))
    {
      for (auto itr : currentSensorValue)
      {
        int32_t roundOffValue = round((2* ADC_10BIT_MAX_CURRENT_IN_AMPS * static_cast<float> (itr) / ADC_10BIT_UPPER_LIMIT) - (ADC_10BIT_MAX_CURRENT_IN_AMPS));
        currentInAmpereList.emplace_back(static_cast<int32_t>(roundOffValue)); 
      }
    }
    return currentInAmpereList;
}