#include "gtest/gtest.h"
#include <FreeRTOS_FFF_MocksDeclaration.h>

extern "C" {
#include <LoRaWANHandler.h>
#include <lora_driver.h>
#include <terrarium.h>
}

FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_rn2483FactoryReset);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_configureToEu868);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setDeviceIdentifier, const char*);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setOtaaIdentity, char*, char*, char*);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_saveMac);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setAdaptiveDataRate, lora_driver_adaptiveDataRate_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setReceiveDelay, uint16_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_getRn2483Hweui, char*);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_join, lora_driver_joinMode_t);
FAKE_VALUE_FUNC(char*, lora_driver_mapReturnCodeToText, lora_driver_returnCode_t);
FAKE_VOID_FUNC(lora_driver_resetRn2483, uint8_t);
FAKE_VOID_FUNC(lora_driver_flushBuffers);
FAKE_VALUE_FUNC(Terrariumdata_p, prepareTerrariumData);
FAKE_VALUE_FUNC(int16_t, getTerrariumTemp, Terrariumdata_p);
FAKE_VALUE_FUNC(int16_t, getTerrariumHum, Terrariumdata_p);
FAKE_VALUE_FUNC(uint16_t, getTerrariumCO2, Terrariumdata_p);
FAKE_VALUE_FUNC(int8_t, getTerrariumIsFed, Terrariumdata_p);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_sendUploadMessage, bool, lora_driver_payload_t*);
//FAKE_VALUE_FUNC(int, taskYIELD);
//FAKE_VALUE_FUNC(TickType_t, xTaskGetTickCount);


class LoraWANHandlerTest : public ::testing::Test {
protected:
    void SetUp() override {

    }
    void TearDown() override {
        RESET_FAKE(vTaskDelay);
        RESET_FAKE(lora_driver_rn2483FactoryReset);
        RESET_FAKE(lora_driver_configureToEu868);
        RESET_FAKE(lora_driver_setDeviceIdentifier);
        RESET_FAKE(lora_driver_setOtaaIdentity);
        RESET_FAKE(lora_driver_saveMac);
        RESET_FAKE(lora_driver_setAdaptiveDataRate);
        RESET_FAKE(lora_driver_setReceiveDelay);
        RESET_FAKE(lora_driver_join);
        RESET_FAKE(lora_driver_mapReturnCodeToText);
        RESET_FAKE(lora_driver_resetRn2483);
        RESET_FAKE(lora_driver_getRn2483Hweui);
        RESET_FAKE(lora_driver_flushBuffers);
        RESET_FAKE(prepareTerrariumData);
        RESET_FAKE(getTerrariumTemp);
        RESET_FAKE(getTerrariumHum);
        RESET_FAKE(getTerrariumCO2);
        RESET_FAKE(getTerrariumIsFed);
        RESET_FAKE(lora_driver_sendUploadMessage);
        FFF_RESET_HISTORY();
    }
};

#pragma region LoraDriverTests

TEST_F(LoraWANHandlerTest, TestIfGetRnIsCalledOnce) {
    //Arange
    
    //Act
    _lora_setup();
    //Assert/Expect
    EXPECT_EQ(1, lora_driver_getRn2483Hweui_fake.call_count);
}

#pragma endregion