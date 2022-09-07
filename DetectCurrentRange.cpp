#include "includes/DetectCurrentRange.hpp"
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

string RangeData::toString()
{
    stringstream strValue;
    copy(m_range.begin(), m_range.end()-1, ostream_iterator<uint32_t>(strValue, "-"));
    strValue<<*(m_range.end()-1) << string(", ") << to_string(m_numElements);
    return strValue.str();
}

vector<RangeData> findConsecutiveRanges(std::vector<uint32_t> input)
{
    uint32_t numElements {1};
    vector<RangeData> rangeList {};

    if (!input.empty()) {
        std::sort(input.begin(), input.end());
        size_t sizeOfcurrentInAmpere = input.size();
        for(uint32_t counter = 1; counter <= sizeOfcurrentInAmpere; counter++) {
            if ((counter == sizeOfcurrentInAmpere) || ((input[counter] - input[counter - 1]) > 1))
            {
                if (1 == numElements) 
                {
                    rangeList.emplace_back(RangeData({input[counter - numElements]}, numElements));
                }
                else 
                {
                    rangeList.emplace_back(RangeData({input[counter - numElements], input[counter - 1]}, numElements));
                }
                numElements = 1;
            }
            else
            {
                ++numElements;
            }
        }
    }
    return rangeList;
}
