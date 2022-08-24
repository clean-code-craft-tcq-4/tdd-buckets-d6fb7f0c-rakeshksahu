#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "samples.hpp"

using namespace std;

//tdd kata
TEST_CASE("test set 1") {
    vector<uint32_t> currentInAmpere {4,5,6,10,11,13};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 3);
    REQUIRE(rangeReadings[0].toString() == "4-6, 3");
    REQUIRE(rangeReadings[1].toString() == "10-11, 2");
    REQUIRE(rangeReadings[2].toString() == "13, 1");
}


TEST_CASE("test set 2") {
    vector<uint32_t> currentInAmpere {2,3,1};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    REQUIRE(rangeReadings[0].toString() == "1-3, 3");
}

TEST_CASE("test set 3") {
    vector<uint32_t> currentInAmpere {5,5,5,5,5};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    REQUIRE(rangeReadings[0].toString() == "5-5, 5");
}

TEST_CASE("test set 4") {
    vector<uint32_t> currentInAmpere {2,2,3,4};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    REQUIRE(rangeReadings[0].toString() == "2-4, 4");
}