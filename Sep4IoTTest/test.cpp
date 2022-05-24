//#include "pch.h"
#include "gtest/gtest.h"

#include <FreeRTOS_FFF_MocksDeclaration.h>

extern "C" {
#include <tempHumSensor.h>
#include <hih8120.h>
#include <terrarium.h>
}

FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(float, hih8120_getTemperature);
FAKE_VALUE_FUNC(bool, hih8120_isReady);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);
FAKE_VALUE_FUNC(float, hih8120_getHumidity);
FAKE_VOID_FUNC(updateTerrariumTemperature, float);
FAKE_VOID_FUNC(updateTerrariumHumidity, float);


class MyTest : public ::testing::Test {
protected:
    void SetUp() override {
        RESET_FAKE(xTaskCreate);
        RESET_FAKE(vTaskDelay);

        RESET_FAKE(hih8120_initialise);
        RESET_FAKE(hih8120_wakeup);

        RESET_FAKE(hih8120_getTemperature);
        RESET_FAKE(hih8120_getHumidity);
        RESET_FAKE(hih8120_isReady);
        RESET_FAKE(hih8120_measure);
        RESET_FAKE(updateTerrariumHumidity);
        RESET_FAKE(updateTerrariumTemperature);
        FFF_RESET_HISTORY();
    }
    void TearDown() override {}
};

TEST(MyTest, TestName) {
    //Arrange
    hih8120_getTemperature_fake.return_val = 20.0;
    //Act
    float _temperature = hih8120_getTemperature();
    //Asser/Except
    ASSERT_EQ(20, _temperature);
    //FHEUHFEOU
}