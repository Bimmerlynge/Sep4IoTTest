#include "gtest/gtest.h"

#include <FreeRTOS_FFF_MocksDeclaration.h>

extern "C" {
#include <co2Sensor.h>
#include <mh_z19.h>
#include <terrarium.h>
}

FAKE_VALUE_FUNC(void*, pvPortMalloc, size_t);
FAKE_VOID_FUNC(updateTerrariumCO2, uint16_t);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_takeMeassuring);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_getCo2Ppm, uint16_t*);


class CO2Test : public ::testing::Test {
public:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(CO2Test, test) {
}