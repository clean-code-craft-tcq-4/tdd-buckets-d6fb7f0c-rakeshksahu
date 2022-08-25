#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "samples.hpp"

using namespace std;

/*****************************************************************************************************************************
 * Start with the simplest test case of an empty input and move to one and two charging samples
 * **************************************************************************************************************************/
TEST_CASE("test set 1 - empty input") {
    auto rangeReadings = findConsecutiveRanges({});
    REQUIRE(rangeReadings.size() == 0);
}

TEST_CASE("test set 2 - single charging sample") {
    vector<uint32_t> currentInAmpere {4};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    REQUIRE(rangeReadings[0].toString() == "4, 1");
}

TEST_CASE("test set 3 - Multiple charging samples") {
    vector<uint32_t> currentInAmpere {4,5,6};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    REQUIRE(rangeReadings[0].toString() == "4-6, 3");
}

/*****************************************************************************************************************************
 * Test for similar charging samples
 * **************************************************************************************************************************/
TEST_CASE("test set 4 - duplicate charging samples") {
    vector<uint32_t> currentInAmpere {5,5,5,5,5};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    REQUIRE(rangeReadings[0].toString() == "5-5, 5");
}

/*****************************************************************************************************************************
 * Test for irregular charging samples
 * **************************************************************************************************************************/
TEST_CASE("test set 5 - irregular charging samples") {
    vector<uint32_t> currentInAmpere {5,3,4,2,6,9,8};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 2);
    REQUIRE(rangeReadings[0].toString() == "2-6, 5");
    REQUIRE(rangeReadings[1].toString() == "8-9, 2");
}

/*****************************************************************************************************************************
 * Test for decreasing charging samples elements
 * **************************************************************************************************************************/
TEST_CASE("test set 6 - Decreasing charging samples") {
    vector<uint32_t> currentInAmpere {4,3,2,1};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    REQUIRE(rangeReadings[0].toString() == "1-4, 4");
}

/*****************************************************************************************************************************
 * Test for Multiple charging samples with multiple ranges
 * **************************************************************************************************************************/
TEST_CASE("test set 6 - Multiple charging samples with multiple ranges") {
    vector<uint32_t> currentInAmpere {4,2,1,3,6,9,7,8,13,11,12};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 3);
    REQUIRE(rangeReadings[0].toString() == "1-4, 4");
    REQUIRE(rangeReadings[1].toString() == "6-9, 4");
    REQUIRE(rangeReadings[2].toString() == "11-13, 3");
}