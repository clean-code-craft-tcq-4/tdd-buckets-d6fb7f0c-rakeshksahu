#ifndef __SAMPLES_HPP_
#define __SAMPLES_HPP_

#include <iostream>
#include <vector>

struct RangeData
{
    std::vector<uint32_t> m_range;
    size_t m_numElements;
    RangeData(std::vector<uint32_t> range, size_t numElements) : m_range(range), m_numElements(numElements){};
    std::string toString();
};

std::vector<RangeData> findConsecutiveRanges(std::vector<uint32_t> input);

#endif /*__SAMPLES_HPP_ */