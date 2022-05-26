#include "gtest/gtest.h"

#include <FreeRTOS_FFF_MocksDeclaration.h>

extern "C" {
#include <terrarium.h>
#include <servomotor.h>
#include "portable.h"
}


FAKE_VOID_FUNC(rotateFullyRight);
FAKE_VOID_FUNC(rotateFullyLeft);
FAKE_VALUE_FUNC(void*, pvPortMalloc, size_t);

SemaphoreHandle_t semaphore = xSemaphoreCreateMutex();

float testTempValue = 23.6;
float testHumValue = 72.5;
uint16_t testCO2Value = 4200;
typedef struct Terrariumdata {
	int16_t  temperature;
	int16_t  humidity;
	uint16_t  co2;
	int8_t isFed;

} Terrariumdata;

class TerrariumTest : public ::testing::Test {
	
protected:
	void SetUp() override {
		
	}
	void TearDown() override {
		resetData();
		RESET_FAKE(xSemaphoreCreateMutex);
		RESET_FAKE(rotateFullyLeft);
		RESET_FAKE(rotateFullyRight);
		RESET_FAKE(xSemaphoreTake);
		RESET_FAKE(xSemaphoreGive);
		RESET_FAKE(pvPortMalloc);
		FFF_RESET_HISTORY();
		
	}
};

#pragma region UpdateTerrariumTemperatureTest
TEST_F(TerrariumTest, TestUpdateTempTakeSemaphoreCallsOnce) {
	//Arrange
	
	//Act
	updateTerrariumTemperature(testTempValue);
	//Assert/Except
	EXPECT_EQ(xSemaphoreTake_fake.call_count, 1);

}
TEST_F(TerrariumTest, TestUpdateTempTakeSemaphoreGetsRightParams) {
	//Arrange
	float test = 23.6;
	//SemaphoreHandle_t arg0 = xSemaphoreCreateMutex();
	TickType_t arg1= portMAX_DELAY;
	//Act
	updateTerrariumTemperature(testTempValue);
	//Assert/Except
	EXPECT_EQ(xSemaphoreTake_fake.arg0_val, semaphore);
	EXPECT_EQ(xSemaphoreTake_fake.arg1_val, arg1);

}
TEST_F(TerrariumTest, TestUpdateTempGiveSemaphoreCallsOnce) {
	//Arrange

	//Act
	updateTerrariumTemperature(testTempValue);
	//Assert/Except
	EXPECT_EQ(xSemaphoreGive_fake.call_count, 1);
}

TEST_F(TerrariumTest, TestUpdateTempGiveSemaphoreGetsRightParam) {
	//Arrange
	
	//Act
	
	updateTerrariumTemperature(testTempValue);
	//Assert/Except
	EXPECT_EQ(xSemaphoreGive_fake.arg0_val, semaphore);
}

#pragma endregion

#pragma region TerrariumInitTests

TEST_F(TerrariumTest, TestInitCreateSempahoreCallsOnce) {
	//Arrange

	//Act
	initTerrarium();
	//Assert/Except
	EXPECT_EQ(xSemaphoreCreateMutex_fake.call_count, 1);

}
TEST_F(TerrariumTest, TestInitCreatesSemaphore) {
	//Arrange

	xSemaphoreCreateMutex_fake.return_val = semaphore;
	//Act
	initTerrarium();
	//Assert/Except
	EXPECT_EQ(xSemaphoreCreateMutex_fake.return_val, semaphore);
}
#pragma endregion

#pragma region UpdateTerrariumHumidityTests

TEST_F(TerrariumTest, TestUpdateHimudityTakeSemaphoreCallsOnce){
//Arrange

//Act

updateTerrariumHumidity(testHumValue);
//Assert/Except
EXPECT_EQ(xSemaphoreTake_fake.call_count, 1);

}
TEST_F(TerrariumTest, TestUpdateHumTakeSemaphoreGetsRightParams) {
	//Arrange
	//SemaphoreHandle_t arg0 = xSemaphoreCreateMutex();
	TickType_t arg1 = portMAX_DELAY;
	//Act
	updateTerrariumHumidity(testHumValue);
	//Assert/Except
	EXPECT_EQ(xSemaphoreTake_fake.arg0_val, semaphore);
	EXPECT_EQ(xSemaphoreTake_fake.arg1_val, arg1);

}
TEST_F(TerrariumTest, TestUpdateHumGiveSemaphoreCallsOnce) {
	//Arrange

	//Act
	updateTerrariumHumidity(testHumValue);
	//Assert/Except
	EXPECT_EQ(xSemaphoreGive_fake.call_count, 1);
}

TEST_F(TerrariumTest, TestUpdatehumGiveSemaphoreGetsRightParam) {
	//Arrange

	//Act

	updateTerrariumHumidity(testHumValue);
	//Assert/Except
	EXPECT_EQ(xSemaphoreGive_fake.arg0_val, semaphore);
}
#pragma endregion

#pragma region UpdateTerrariumCO2Tests

TEST_F(TerrariumTest, TestUpdateCO2TakeSemaphoreCallsOnce) {
	//Arrange

	//Act

	updateTerrariumCO2(testCO2Value);
	//Assert/Except
	EXPECT_EQ(xSemaphoreTake_fake.call_count, 1);

}
TEST_F(TerrariumTest, TestUpdateCO2TakeSemaphoreGetsRightParams) {
	//Arrange
	//SemaphoreHandle_t arg0 = xSemaphoreCreateMutex();
	TickType_t arg1 = portMAX_DELAY;
	//Act
	updateTerrariumCO2(testCO2Value);
	//Assert/Except
	EXPECT_EQ(xSemaphoreTake_fake.arg0_val, semaphore);
	EXPECT_EQ(xSemaphoreTake_fake.arg1_val, arg1);

}
TEST_F(TerrariumTest, TestUpdateCO2GiveSemaphoreCallsOnce) {
	//Arrange

	//Act
	updateTerrariumCO2(testCO2Value);
	//Assert/Except
	EXPECT_EQ(xSemaphoreGive_fake.call_count, 1);
}

TEST_F(TerrariumTest, TestUpdateCO2GiveSemaphoreGetsRightParam) {
	//Arrange

	//Act

	updateTerrariumCO2(testCO2Value);
	//Assert/Except
	EXPECT_EQ(xSemaphoreGive_fake.arg0_val, semaphore);
}
#pragma endregion

#pragma region FeedAnimalTest
TEST_F(TerrariumTest, TestFeedAnimalTakeSemaphoreCallsOnce) {
	//Arrange

	//Act

	feedAnimalTerrarium();
	//Assert/Except
	EXPECT_EQ(xSemaphoreTake_fake.call_count, 1);

}
TEST_F(TerrariumTest, TestFeedAnimalTakeSemaphoreGetsRightParams) {
	//Arrange

	TickType_t arg1 = portMAX_DELAY;
	//Act
	feedAnimalTerrarium();
	//Assert/Except
	EXPECT_EQ(xSemaphoreTake_fake.arg0_val, semaphore);
	EXPECT_EQ(xSemaphoreTake_fake.arg1_val, arg1);

}
TEST_F(TerrariumTest, TestFeedAnimalGiveSemaphoreCallsOnce) {
	//Arrange

	//Act
	feedAnimalTerrarium();
	//Assert/Except
	EXPECT_EQ(xSemaphoreGive_fake.call_count, 1);
}

TEST_F(TerrariumTest, TestFeedAnimalGiveSemaphoreGetsRightParam) {
	//Arrange

	//Act

	feedAnimalTerrarium();
	//Assert/Except
	EXPECT_EQ(xSemaphoreGive_fake.arg0_val, semaphore);
}


TEST_F(TerrariumTest, TestFeedAnimalFullyLeftCalledOnce) {

	feedAnimalTerrarium();
	EXPECT_EQ(rotateFullyLeft_fake.call_count, 1);
}

#pragma endregion

#pragma region ResetAnimalFeederTests
TEST_F(TerrariumTest, TestFeedAnimalFullyRightCalledOnce) {

	resetAnimalFeeder();
	EXPECT_EQ(rotateFullyRight_fake.call_count, 1);
}
#pragma endregion

#pragma region PrepareDataGeneralTests
TEST_F(TerrariumTest, TestMallocCalledOnceInPrepareData) {
	prepareTerrariumData();
	EXPECT_EQ(pvPortMalloc_fake.call_count, 1);
}

TEST_F(TerrariumTest, TestMallocGetsRightParam) {
	size_t arg0 = sizeof(Terrariumdata);
	prepareTerrariumData();
	EXPECT_EQ(pvPortMalloc_fake.arg0_val, arg0);
}

TEST_F(TerrariumTest, TestMallocNotEnoughMemory) {
	
	pvPortMalloc_fake.return_val = NULL;

	Terrariumdata_p prepareReturn = prepareTerrariumData();
	EXPECT_EQ(prepareReturn, pvPortMalloc_fake.return_val);
}

TEST_F(TerrariumTest, TestPrepareDataTakeSemaphoreCalledOnce) {
	
	 
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();
	
	
	//EXPECT_EQ(toTest, false);
	EXPECT_EQ(xSemaphoreTake_fake.call_count, 1);
	
	free(returnData);

}

TEST_F(TerrariumTest, TestPrepareDataTakeSemaphoreGetsRightParams) {
	

	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	TickType_t arg1 = portMAX_DELAY;

	Terrariumdata_p returnData = prepareTerrariumData();

	//EXPECT_EQ(toTest, false);
	EXPECT_EQ(xSemaphoreTake_fake.arg0_val, semaphore);
	EXPECT_EQ(xSemaphoreTake_fake.arg1_val, arg1);

	free(returnData);

}
TEST_F(TerrariumTest, TestPrepareDataGiveSemaphorCalledOnce) {
	updateTerrariumTemperature(testTempValue);
	updateTerrariumHumidity(testHumValue);
	updateTerrariumCO2(testCO2Value);
	RESET_FAKE(xSemaphoreGive);
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();

	EXPECT_EQ(xSemaphoreGive_fake.call_count, 2);

	free(returnData);
}

TEST_F(TerrariumTest, TestPrepareDataGiveSemaphorRightParam) {
	updateTerrariumTemperature(testTempValue);
	updateTerrariumHumidity(testHumValue);
	updateTerrariumCO2(testCO2Value);
	RESET_FAKE(xSemaphoreGive);
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();

	EXPECT_EQ(xSemaphoreGive_fake.arg0_val, semaphore);

	free(returnData);
}
//TODO Skriv
TEST_F(TerrariumTest, TestPrepareDataCallsResetDataOnce) {
	bool check = true;
	updateTerrariumTemperature(testTempValue);
	updateTerrariumHumidity(testHumValue);
	updateTerrariumCO2(testCO2Value);
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();
	
	//Allokere ny memory.
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));
    Terrariumdata_p newReturn = prepareTerrariumData();
	if (newReturn == NULL) { check = false; }

	EXPECT_FALSE(check);

	free(returnData);
	
}

#pragma endregion

#pragma region PrepareTerrariumDataWithHumidity
TEST_F(TerrariumTest, TestPrepareTwoHums) {
	int16_t expectedValue = 200;
	updateTerrariumTemperature(testTempValue);
	updateTerrariumHumidity(10.0);
	updateTerrariumHumidity(30.0);
	updateTerrariumCO2(testCO2Value);
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();
	int16_t avgHumX10 = returnData->humidity;

	EXPECT_EQ(avgHumX10, expectedValue);
	free(returnData);
}

TEST_F(TerrariumTest, TestPrepareNoHum) {
	bool check = true;
	updateTerrariumTemperature(testTempValue);
	updateTerrariumCO2(testCO2Value);
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();
	if (returnData == NULL) { check = false; }
	EXPECT_FALSE(check);
	free(returnData);
}
#pragma endregion

#pragma region PrepareTerrariumDataWithTemperatur
TEST_F(TerrariumTest, TestPrepareTwoTemps) {
	int16_t expectedValue = 150;
	updateTerrariumTemperature(10.0);
	updateTerrariumTemperature(20.0);
	updateTerrariumHumidity(testHumValue);
	updateTerrariumCO2(testCO2Value);
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();
	int16_t avgTempX10 = returnData->temperature;

	EXPECT_EQ(avgTempX10, expectedValue);
	free(returnData);
}

TEST_F(TerrariumTest, TestPrepareNoTemp) {
	bool check = true;
	updateTerrariumHumidity(testHumValue);
	updateTerrariumCO2(testCO2Value);
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();
	if (returnData == NULL) { check = false; }
	EXPECT_FALSE(check);
	free(returnData);
}
#pragma endregion

#pragma region PrepareTerrariumDataWithCO2
TEST_F(TerrariumTest, TestPrepareTwoCO2s) {
	uint16_t expectedValue = 350;
	updateTerrariumTemperature(testTempValue);
	updateTerrariumHumidity(testHumValue);
	updateTerrariumCO2(300);
	updateTerrariumCO2(400);
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();
	uint16_t avgCO2 = returnData->co2;

	EXPECT_EQ(avgCO2, expectedValue);
	free(returnData);
}

TEST_F(TerrariumTest, TestPrepareNoCO2) {
	bool check = true;
	updateTerrariumTemperature(testTempValue);
	updateTerrariumHumidity(testHumValue);
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();
	if (returnData == NULL) { check = false; }
	EXPECT_FALSE(check);
	free(returnData);
}
#pragma endregion

#pragma region PrepareDataWithFeed
TEST_F(TerrariumTest, TestPrepareWithNoFeed) {
	updateTerrariumTemperature(testTempValue);
	updateTerrariumHumidity(testHumValue);
	updateTerrariumCO2(testCO2Value);
	
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();
	int8_t fed = returnData->isFed;
	EXPECT_EQ(fed, 0);

}

TEST_F(TerrariumTest, TestPrepareWithFeed) {
	updateTerrariumTemperature(testTempValue);
	updateTerrariumHumidity(testHumValue);
	updateTerrariumCO2(testCO2Value);
	feedAnimalTerrarium();
	pvPortMalloc_fake.return_val = malloc(sizeof(Terrariumdata));

	Terrariumdata_p returnData = prepareTerrariumData();
	int8_t fed = returnData->isFed;
	EXPECT_EQ(fed, 1);
}
#pragma endregion

#pragma region TestGetters
TEST_F(TerrariumTest, TestGetTerrariumTemp) {
	Terrariumdata_p testStruct = (Terrariumdata_p)malloc(sizeof(Terrariumdata));
	testStruct->temperature = 15.0;
	

	EXPECT_EQ(getTerrariumTemp(testStruct), 15.0);

}
TEST_F(TerrariumTest, TestGetTerrariumHum) {
	Terrariumdata_p testStruct = (Terrariumdata_p)malloc(sizeof(Terrariumdata));
	testStruct->humidity = 27.0;


	EXPECT_EQ(getTerrariumHum(testStruct), 27.0);

}
TEST_F(TerrariumTest, TestGetTerrariumCO2) {
	Terrariumdata_p testStruct = (Terrariumdata_p)malloc(sizeof(Terrariumdata));
	testStruct->co2 = 1300;

	EXPECT_EQ(getTerrariumCO2(testStruct), 1300);
}
TEST_F(TerrariumTest, TestGetTerrariumIsFed) {
	Terrariumdata_p testStruct = (Terrariumdata_p)malloc(sizeof(Terrariumdata));
	testStruct->isFed = 1;

	EXPECT_EQ(getTerrariumIsFed(testStruct), 1);
}
#pragma endregion

