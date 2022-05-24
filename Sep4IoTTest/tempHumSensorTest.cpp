//#include "pch.h"
#include "gtest/gtest.h"

#include <FreeRTOS_FFF_MocksDeclaration.h>

extern "C" {
#include <tempHumSensor.h>
#include <hih8120.h>
#include <terrarium.h>
}

FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(float, hih8120_getTemperature);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);
FAKE_VALUE_FUNC(float, hih8120_getHumidity);
FAKE_VOID_FUNC(updateTerrariumTemperature, float);
FAKE_VOID_FUNC(updateTerrariumHumidity, float);


class TempHumSensorTest : public ::testing::Test {
protected:
    void SetUp() override {
     
    }
    void TearDown() override {
        RESET_FAKE(vTaskDelay);
        RESET_FAKE(hih8120_wakeup);
        RESET_FAKE(hih8120_getTemperature);
        RESET_FAKE(hih8120_getHumidity);
        RESET_FAKE(hih8120_measure);
        RESET_FAKE(updateTerrariumHumidity);
        RESET_FAKE(updateTerrariumTemperature);
        RESET_FAKE(xSemaphoreTake);
        RESET_FAKE(xSemaphoreGive);
        FFF_RESET_HISTORY();
    }
};

#pragma region WakeUpTests
TEST_F(TempHumSensorTest, TestIfWakeupIsCalledOnce) {
    //Arrange

    //Act
    run();
    //Assert/Except
    EXPECT_EQ(hih8120_wakeup_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestWakeupReturnCodeOK) {
    //Arrange
    hih8120_wakeup_fake.return_val = HIH8120_OK;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(HIH8120_OK ,hih8120_wakeup_fake.return_val);
    EXPECT_EQ(hih8120_measure_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestWakeupReturnCodeBusy) {
    //Arrange
    hih8120_wakeup_fake.return_val = HIH8120_TWI_BUSY;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(HIH8120_TWI_BUSY, hih8120_wakeup_fake.return_val);
    EXPECT_EQ(hih8120_measure_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestWakeupReturnCodeOutOfHeap) {
    //Arrange
    hih8120_wakeup_fake.return_val = HIH8120_OUT_OF_HEAP;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(HIH8120_OUT_OF_HEAP, hih8120_wakeup_fake.return_val);
    EXPECT_EQ(hih8120_measure_fake.call_count, 0);
}

TEST_F(TempHumSensorTest, TestWakeupReturnCodeNotInitialised) {
    //Arrange
    hih8120_wakeup_fake.return_val = HIH8120_DRIVER_NOT_INITIALISED;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(HIH8120_DRIVER_NOT_INITIALISED, hih8120_wakeup_fake.return_val);
    EXPECT_EQ(hih8120_measure_fake.call_count, 0);
}
#pragma endregion

#pragma region MeasureTests
TEST_F(TempHumSensorTest, TestIfMeasureIsCalledOnce) {
    //Arrange

    //Act
    run();
    //Assert/Except
    EXPECT_EQ(hih8120_measure_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestMeasureReturnCodeOK) {
    //Arrange
    hih8120_measure_fake.return_val = HIH8120_OK;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(HIH8120_OK, hih8120_measure_fake.return_val);
    EXPECT_EQ(hih8120_getTemperature_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestMeasureReturnCodeBusy) {
    //Arrange
    hih8120_measure_fake.return_val = HIH8120_TWI_BUSY;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(HIH8120_TWI_BUSY, hih8120_measure_fake.return_val);
    EXPECT_EQ(hih8120_getTemperature_fake.call_count, 0);
}

TEST_F(TempHumSensorTest, TestMeasureReturnCodeOutOfHeap) {
    //Arrange
    hih8120_measure_fake.return_val = HIH8120_OUT_OF_HEAP;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(HIH8120_OUT_OF_HEAP, hih8120_measure_fake.return_val);
    EXPECT_EQ(hih8120_getTemperature_fake.call_count, 0);
}

TEST_F(TempHumSensorTest, TestMeasureReturnCodeNotInitialised) {
    //Arrange
    hih8120_measure_fake.return_val = HIH8120_DRIVER_NOT_INITIALISED;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(HIH8120_DRIVER_NOT_INITIALISED, hih8120_measure_fake.return_val);
    EXPECT_EQ(hih8120_getTemperature_fake.call_count, 0);
}
#pragma endregion

#pragma region GetTemperatureTests
TEST_F(TempHumSensorTest, TestIfGetTemperatureIsCalledOnce) {
    //Arrange

    //Act
    run();
    //Assert/Except
    EXPECT_EQ(hih8120_getTemperature_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestIfGetTemperature) {
    //Arrange
    float temperature = 20.6;
    hih8120_getTemperature_fake.return_val = temperature;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(temperature, hih8120_getTemperature_fake.return_val);
}
#pragma endregion

#pragma region GetHumidityTests
TEST_F(TempHumSensorTest, TestIfGetHumidityIsCalledOnce) {
    //Arrange

    //Act
    run();
    //Assert/Except
    EXPECT_EQ(hih8120_getHumidity_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestIfGetHumidity) {
    //Arrange
    float humidity = 45.8;
    hih8120_getTemperature_fake.return_val = humidity;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(humidity, hih8120_getTemperature_fake.return_val);
}
#pragma endregion

#pragma region TaskDelayTests
TEST_F(TempHumSensorTest, TestIfTaskDelayIsCalled) {
    //Arrange

    //Act
    run();
    //Assert/Except
    EXPECT_EQ(vTaskDelay_fake.call_count, 3);
}

TEST_F(TempHumSensorTest, TestIfTaskDelayParam) {
    //Arrange
    int ticks1 = 100;
    int ticks2 = 5;
    int ticks3 = 500;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(ticks1, vTaskDelay_fake.arg0_history[0]);
    EXPECT_EQ(ticks2, vTaskDelay_fake.arg0_history[1]);
    EXPECT_EQ(ticks3, vTaskDelay_fake.arg0_history[2]);
}
#pragma endregion

#pragma region SemaphoreTests
TEST_F(TempHumSensorTest, TestIfSemaphoreTakeIsCalledOnce) {
    //Arrange

    //Act
    run();
    //Assert/Except
    EXPECT_EQ(xSemaphoreTake_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestIfSemaphoreGiveIsCalledOnce) {
    //Arrange

    //Act
    run();
    //Assert/Except
    EXPECT_EQ(xSemaphoreGive_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestIfSemaphoreTakeParams) {
    //Arrange
    
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(xSemaphoreTake_fake.arg0_val, semaphore);
    EXPECT_EQ(xSemaphoreTake_fake.arg1_val, portMAX_DELAY);
}

TEST_F(TempHumSensorTest, TestIfSemaphoreGiveParam) {
    //Arrange

    //Act
    run();
    //Assert/Except
    EXPECT_EQ(xSemaphoreTake_fake.arg0_val, semaphore);
}
#pragma endregion

#pragma region UpdateTemperatureTests
TEST_F(TempHumSensorTest, TestIfUpdateTempIsCalledOnce) {
    //Arrange

    //Act
    run();
    //Assert/Except
    EXPECT_EQ(updateTerrariumTemperature_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestUpdateTemperature) {
    //Arrange
    float temperature = 21.6;
    hih8120_getTemperature_fake.return_val = temperature;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(temperature, updateTerrariumTemperature_fake.arg0_val);
}
#pragma endregion

#pragma region UpdateHumidityTests
TEST_F(TempHumSensorTest, TestIfUpdateHumIsCalledOnce) {
    //Arrange

    //Act
    run();
    //Assert/Except
    EXPECT_EQ(updateTerrariumHumidity_fake.call_count, 1);
}

TEST_F(TempHumSensorTest, TestUpdateHumidity) {
    //Arrange
    float humidity = 40.6;
    hih8120_getHumidity_fake.return_val = humidity;
    //Act
    run();
    //Assert/Except
    EXPECT_EQ(humidity, updateTerrariumHumidity_fake.arg0_val);
}
#pragma endregion


