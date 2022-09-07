#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "includes/DetectCurrentRange.hpp"
#include "includes/A2DConverter10Bit.hpp"
#include "includes/A2DConverter12Bit.hpp"

using namespace std;

/*****************************************************************************************************************************
 * Start with the simplest test case of an empty input and move to one and two charging samples
 * **************************************************************************************************************************/
TEST_CASE("test set 1 - empty input") {
    auto rangeReadings = findConsecutiveRanges({});
    CHECK(rangeReadings.size() == 0);
}

TEST_CASE("test set 2 - single charging sample") {
    vector<uint32_t> currentInAmpere {4};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    CHECK(rangeReadings[0].toString() == "4, 1");
}

TEST_CASE("test set 3 - Multiple charging samples") {
    vector<uint32_t> currentInAmpere {4,5,6};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    CHECK(rangeReadings[0].toString() == "4-6, 3");
}

/*****************************************************************************************************************************
 * Test for similar charging samples
 * **************************************************************************************************************************/
TEST_CASE("test set 4 - duplicate charging samples") {
    vector<uint32_t> currentInAmpere {5,5,5,5,5};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    CHECK(rangeReadings[0].toString() == "5-5, 5");
}

/*****************************************************************************************************************************
 * Test for irregular charging samples
 * **************************************************************************************************************************/
TEST_CASE("test set 5 - irregular charging samples") {
    vector<uint32_t> currentInAmpere {5,3,4,2,6,9,8};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 2);
    CHECK(rangeReadings[0].toString() == "2-6, 5");
    CHECK(rangeReadings[1].toString() == "8-9, 2");
}

/*****************************************************************************************************************************
 * Test for decreasing charging samples elements
 * **************************************************************************************************************************/
TEST_CASE("test set 6 - Decreasing charging samples") {
    vector<uint32_t> currentInAmpere {4,3,2,1};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 1);
    CHECK(rangeReadings[0].toString() == "1-4, 4");
}

/*****************************************************************************************************************************
 * Test for Multiple charging samples with multiple ranges
 * **************************************************************************************************************************/
TEST_CASE("test set 6 - Multiple charging samples with multiple ranges") {
    vector<uint32_t> currentInAmpere {4,2,1,3,6,9,7,8,13,11,12};
    auto rangeReadings = findConsecutiveRanges(currentInAmpere);
    REQUIRE(rangeReadings.size() == 3);
    CHECK(rangeReadings[0].toString() == "1-4, 4");
    CHECK(rangeReadings[1].toString() == "6-9, 4");
    CHECK(rangeReadings[2].toString() == "11-13, 3");
}


TEST_CASE("test A2DConverter12Bit.checkIfInputWithInRange : valid value")
{
    vector<uint32_t> currentSensorValue {0, 1000, 2000, 3000, 4094};
    CHECK(A2DConverter12Bit().checkIfInputWithInRange(currentSensorValue));
}

TEST_CASE("test A2DConverter12Bit.A2DConverter12Bit : value more than limit")
{
    vector<uint32_t> currentSensorValue {0, 1000, 2000, 3000, 5000};
    CHECK_FALSE(A2DConverter12Bit().checkIfInputWithInRange(currentSensorValue));
}

TEST_CASE("test A2DConverter12Bit.convertADCValueToAmpere : value within boundary") {
    vector<uint32_t> currentSensorValue {500, 1146, 1500, 2000, 2500, 3000, 3500, 4000};
    vector<uint32_t> expectedCurrentValueInAmpere {1, 3, 4, 5, 6, 7, 9, 10};

    auto actual12BitCurrentValueInAmpere = A2DConverter12Bit().convertADCValueToAmpere(currentSensorValue);
    REQUIRE (actual12BitCurrentValueInAmpere.size() == expectedCurrentValueInAmpere.size());
    CHECK (std::equal(actual12BitCurrentValueInAmpere.begin(), 
        actual12BitCurrentValueInAmpere.begin() + actual12BitCurrentValueInAmpere.size(), expectedCurrentValueInAmpere.begin()));
}

TEST_CASE("test A2DConverter12Bit.convertADCValueToAmpere : value more than limit")
{
    vector<uint32_t> currentSensorValue {4095};

    auto actual12BitCurrentValueInAmpere = A2DConverter12Bit().convertADCValueToAmpere(currentSensorValue);
    CHECK(actual12BitCurrentValueInAmpere.empty());
}

TEST_CASE("test A2DConverter10Bit.checkIfInputWithInRange : value within boundary")
{
    vector <int32_t> currentSensorValue {0, 100, 200, 300, 400, 512, 750, 1022};
    CHECK(A2DConverter10Bit().checkIfInputWithInRange(currentSensorValue));
}

TEST_CASE("test A2DConverter10Bit.checkIfInputWithInRange : value < boundary")
{
    vector<int32_t> currentSensorValue {-1, 100, 200, 300, 400, 512, 750, 1022};
    CHECK_FALSE(A2DConverter10Bit().checkIfInputWithInRange(currentSensorValue));
}

TEST_CASE("test A2DConverter10Bit.checkIfInputWithInRange : value > boundary")
{
    vector<int32_t> currentSensorValue {0, 100, 200, 300, 400, 512, 750, 1023};
    CHECK_FALSE(A2DConverter10Bit().checkIfInputWithInRange(currentSensorValue));
}

TEST_CASE("test A2DConverter10Bit.convertADCValueToAmpere : value within boundary")
{
    vector<int32_t> currentSensorValue {0, 512, 1022};
    vector<int32_t> expectedCurrentValueInAmpere {-15, 0 ,15};
    auto actual10BitCurrentValueInAmpere = A2DConverter10Bit().convertADCValueToAmpere(currentSensorValue);
    REQUIRE ((actual10BitCurrentValueInAmpere.size() == expectedCurrentValueInAmpere.size()));
    REQUIRE (std::equal(actual10BitCurrentValueInAmpere.begin(), 
        actual10BitCurrentValueInAmpere.begin() + actual10BitCurrentValueInAmpere.size(), expectedCurrentValueInAmpere.begin()));
}

TEST_CASE("test A2DConverter10Bit.convertADCValueToAmpere : value < lower limit")
{
    vector<int32_t> currentSensorValue {-1};
    auto actual10BitCurrentValueInAmpere = A2DConverter10Bit().convertADCValueToAmpere(currentSensorValue);
    REQUIRE(actual10BitCurrentValueInAmpere.empty());
}

TEST_CASE("test A2DConverter10Bit.convertADCValueToAmpere : value > upper limit")
{
    vector<int32_t> currentSensorValue {1023};
    auto actual10BitCurrentValueInAmpere = A2DConverter10Bit().convertADCValueToAmpere(currentSensorValue);
    REQUIRE(actual10BitCurrentValueInAmpere.empty());
}