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
protected:
	uint16_t ppm = 1;
	uint16_t* ppm_p = &ppm;
	void SetUp() override {
	
	}
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
	EXPECT_EQ(1, pvPortMalloc_fake.call_count);
}

TEST_F(CO2SensorTest, TestMallocParam) {
	//Arrange
	size_t size = sizeof(uint16_t);
	//Act
	co2SensorInit();
	//Assert/Except
	EXPECT_EQ(size, pvPortMalloc_fake.arg0_val);
}

TEST_F(CO2SensorTest, TestMallocReturnValue) {
	//Arrange
	int a = 1;
	void* ppm = &a;
	pvPortMalloc_fake.return_val = ppm;
	//Act
	co2SensorInit();
	//Assert/Except
	EXPECT_EQ(ppm, pvPortMalloc_fake.return_val);	
}

#pragma endregion

#pragma region TakeMeassuringTests
TEST_F(CO2SensorTest, TestIfTakeMeassuringIsCalledOnce) {
	//Arrange
	
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(1, mh_z19_takeMeassuring_fake.call_count);
}

TEST_F(CO2SensorTest, TestTakeMeassuringRCOK) {
	//Arrange
	mh_z19_takeMeassuring_fake.return_val = MHZ19_OK;
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(MHZ19_OK, mh_z19_takeMeassuring_fake.return_val);
	EXPECT_EQ(1, mh_z19_getCo2Ppm_fake.call_count);
}

TEST_F(CO2SensorTest, TestTakeMeassuringRCNoMeassuringAvailable) {
	//Arrange
	mh_z19_takeMeassuring_fake.return_val = MHZ19_NO_MEASSURING_AVAILABLE;
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(MHZ19_NO_MEASSURING_AVAILABLE, mh_z19_takeMeassuring_fake.return_val);
	EXPECT_EQ(0, mh_z19_getCo2Ppm_fake.call_count);
}

TEST_F(CO2SensorTest, TestTakeMeassuringRCNoSerial) {
	//Arrange
	mh_z19_takeMeassuring_fake.return_val = MHZ19_NO_SERIAL;
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(MHZ19_NO_SERIAL, mh_z19_takeMeassuring_fake.return_val);
	EXPECT_EQ(0, mh_z19_getCo2Ppm_fake.call_count);
}

TEST_F(CO2SensorTest, TestTakeMeassuringRCPPMMustBeGt) {
	//Arrange
	mh_z19_takeMeassuring_fake.return_val = MHZ19_PPM_MUST_BE_GT_999;
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(MHZ19_PPM_MUST_BE_GT_999, mh_z19_takeMeassuring_fake.return_val);
	EXPECT_EQ(0, mh_z19_getCo2Ppm_fake.call_count);
}

#pragma endregion

#pragma region TaskDelayTests
TEST_F(CO2SensorTest, TestIfTaskDelayIsCalledTwice) {
	//Arrange

	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(2, vTaskDelay_fake.call_count);
}

TEST_F(CO2SensorTest, TestTaskDelayParams) {
	//Arrange
	int ticks1 = 100;
	int ticks2 = pdMS_TO_TICKS(10000);
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(ticks1, vTaskDelay_fake.arg0_history[0]);
	EXPECT_EQ(ticks2, vTaskDelay_fake.arg0_history[1]);
}
#pragma endregion

#pragma region GetCo2PPMTests

TEST_F(CO2SensorTest, TestIfGetCo2PPMIsCalledOnce) {
	//Arrange

	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(1, mh_z19_getCo2Ppm_fake.call_count);
}

TEST_F(CO2SensorTest, TestGetCo2PPMRCOK) {
	//Arrange
	mh_z19_getCo2Ppm_fake.return_val = MHZ19_OK;
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(MHZ19_OK, mh_z19_getCo2Ppm_fake.return_val);
	EXPECT_EQ(1, updateTerrariumCO2_fake.call_count);
}

TEST_F(CO2SensorTest, TestGetCo2PPMRCNoMeassuringAvailable) {
	//Arrange
	mh_z19_getCo2Ppm_fake.return_val = MHZ19_NO_MEASSURING_AVAILABLE;
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(MHZ19_NO_MEASSURING_AVAILABLE, mh_z19_getCo2Ppm_fake.return_val);
	EXPECT_EQ(0, updateTerrariumCO2_fake.call_count);
}

TEST_F(CO2SensorTest, TestGetCo2PPMRCNoSerial) {
	//Arrange
	mh_z19_getCo2Ppm_fake.return_val = MHZ19_NO_SERIAL;
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(MHZ19_NO_SERIAL, mh_z19_getCo2Ppm_fake.return_val);
	EXPECT_EQ(0, updateTerrariumCO2_fake.call_count);
}

TEST_F(CO2SensorTest, TestGetCo2PPMRCPPMMustBeGt) {
	//Arrange
	mh_z19_getCo2Ppm_fake.return_val = MHZ19_PPM_MUST_BE_GT_999;
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(MHZ19_PPM_MUST_BE_GT_999, mh_z19_getCo2Ppm_fake.return_val);
	EXPECT_EQ(0, updateTerrariumCO2_fake.call_count);
}

#pragma endregion

#pragma region UpdateTerrariumCo2Tests

TEST_F(CO2SensorTest, TestIfUpdateTerrariumIsCalledOnce) {
	//Arrange

	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(1, updateTerrariumCO2_fake.call_count);
}

TEST_F(CO2SensorTest, TestUpdateTerrariumParam) {
	//Arrange
	updateTerrariumCO2_fake.arg0_val = ppm;
	//Act
	co2SensorRun(ppm_p);
	//Assert/Except
	EXPECT_EQ(ppm, updateTerrariumCO2_fake.arg0_val);
}

#pragma endregion