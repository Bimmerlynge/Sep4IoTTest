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


class CO2SensorTest : public ::testing::Test {
public:
	void SetUp() override {}
	void TearDown() override {
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(pvPortMalloc);
		RESET_FAKE(updateTerrariumCO2);
		RESET_FAKE(mh_z19_takeMeassuring);
		RESET_FAKE(mh_z19_getCo2Ppm);
		FFF_RESET_HISTORY();
	}
};

#pragma region pvPortMallocTests
TEST_F(CO2SensorTest, TestIfMallocIsCalledOnce) {
	//Arrange

	//Act
	co2SensorInit();
	//Assert/Except
	EXPECT_EQ(pvPortMalloc_fake.call_count, 1);
}

TEST_F(CO2SensorTest, TestMallocParam) {
	//Arrange
	size_t size = sizeof(uint16_t);
	//Act
	co2SensorInit();
	//Assert/Except
	EXPECT_EQ(size, pvPortMalloc_fake.arg0_val);
}

#pragma endregion