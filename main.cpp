#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "samples.hpp"

using namespace std;


TEST_CASE("test set 1") {
    vector<int> currentInAmpere {4,5,6};
    auto rangeReadings = inRangeReading(currentInAmpere);
    REQUIRE(rangeReadings.start == 4);
    REQUIRE(rangeReadings.end == 6);
    REQUIRE(rangeReadings.numElements == 3);
}


TEST_CASE("test set 2") {
    vector<int> currentInAmpere {2,3,1};
    auto rangeReadings = inRangeReading(currentInAmpere);
    REQUIRE(rangeReadings.start == 1);
    REQUIRE(rangeReadings.end == 3);
    REQUIRE(rangeReadings.numElements == 3);
}

TEST_CASE("test set 3") {
    vector<int> currentInAmpere {5,5,5,5,5};
    auto rangeReadings = inRangeReading(currentInAmpere);
    REQUIRE(rangeReadings.start == 5);
    REQUIRE(rangeReadings.end == 5);
    REQUIRE(rangeReadings.numElements == 5);
}

TEST_CASE("test set 4") {
    vector<int> currentInAmpere {2,2,3,4};
    auto rangeReadings = inRangeReading(currentInAmpere);
    REQUIRE(rangeReadings.start == 2);
    REQUIRE(rangeReadings.end == 4);
    REQUIRE(rangeReadings.numElements == 5);
}