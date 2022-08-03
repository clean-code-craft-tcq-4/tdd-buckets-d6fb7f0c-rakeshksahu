#include "samples.hpp"
#include <algorithm>
using namespace std;

rangeData inRangeReading(std::vector<int> input)
{
    rangeData output;
    std::sort(input.begin(), input.end());
    output.numElements = 1;
    for(int counter = 0; counter < input.size(); ++counter)
    {
        if (((input[counter] + 1) == (input[counter + 1])) || (input[counter] == input[counter + 1])){
            ++output.numElements;
        }
    }
    output.start = input[0];
    output.end = input[input.size() - 1];
    return output;
}
