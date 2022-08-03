#ifndef __SAMPLES_HPP_
#define __SAMPLES_HPP_

#include <iostream>
#include <vector>

struct rangeData
{
    int start;
    int end;
    int numElements;
};

rangeData inRangeReading(std::vector<int> input);

#endif /*__SAMPLES_HPP_ */