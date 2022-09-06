#include "includes/A2DConverter12Bit.hpp"

#include <algorithm>
#include <cmath>

using namespace std;

bool A2DConverter12Bit::checkIfInputWithInRange(const std::vector<uint32_t>& inputData) {

  auto result = std::find_if(inputData.begin(), inputData.end(), [this](const uint32_t& i){
    return (i < ADC_12BIT_LOWER_LIMIT) || (i > ADC_12BIT_UPPER_LIMIT);
  });

  return result != inputData.end();
}

vector<uint32_t> A2DConverter12Bit::convertADCValueToAmpere(const std::vector<uint32_t>& currentSensorValue)
{
    vector<uint32_t> currentInAmpereList;
    if (checkIfInputWithInRange(currentSensorValue))
    {
      for (auto itr : currentSensorValue)
      {
        const uint32_t roundOffValue = round(ADC_12BIT_MAX_CURRENT_IN_AMPS * static_cast<float> (itr) / ADC_12BIT_UPPER_LIMIT);
        currentInAmpereList.emplace_back(static_cast<uint32_t>(roundOffValue)); 
      }
    }
    return currentInAmpereList;
}
