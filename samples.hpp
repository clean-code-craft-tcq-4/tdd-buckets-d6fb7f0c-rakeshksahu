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

/*****************************************************************************************************************************
 * 1. capture the range of current measurements - what range of currents are most often encountered while charging.
 * Input is A set of periodic current samples from a charging session, as an array of integers.
 * For example: 3, 3, 5, 4, 10, 11, 12
 * The expected output would be in comma-separated (csv format):
 * Range, Readings
 * 3-5, 4
 * 10-12, 3
 * **************************************************************************************************************************/
std::vector<RangeData> findConsecutiveRanges(std::vector<uint32_t> input);

#endif /*__SAMPLES_HPP_ */