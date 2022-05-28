#include "gtest/gtest.h"
#include <FreeRTOS_FFF_MocksDeclaration.h>

extern "C" {
#include <lorawanUplinkHandler.h>
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
FAKE_VALUE_FUNC(uint16_t, getTerrariumLight, Terrariumdata_p);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_sendUploadMessage, bool, lora_driver_payload_t*);
FAKE_VALUE_FUNC(int, taskYIELD);

typedef struct Terrariumdata {
    int16_t  temperature;
    int16_t  humidity;
    uint16_t  co2;
    int8_t isFed;
    uint16_t light;
} Terrariumdata;

Terrariumdata_p terrariumdata_p = (Terrariumdata_p)malloc(sizeof(Terrariumdata));

class lorawanUplinkHandlerTest : public ::testing::Test {
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
        /*RESET_FAKE(getTerrariumTemp);
        RESET_FAKE(getTerrariumHum);
        RESET_FAKE(getTerrariumCO2);
        RESET_FAKE(getTerrariumIsFed);
        RESET_FAKE(getTerrariumLight);*/
        RESET_FAKE(lora_driver_sendUploadMessage);
        FFF_RESET_HISTORY();
    }
};

#pragma region TaskDelayTests
TEST_F(lorawanUplinkHandlerTest, TestIfTaskDelayIsCalledOnce) {
    //Arrange
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(1, vTaskDelay_fake.call_count);
}

TEST_F(lorawanUplinkHandlerTest, TestTaskDelayParam) {
    //Arrange
    int ticks = pdMS_TO_TICKS(300000);
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(ticks, vTaskDelay_fake.arg0_val);
}
#pragma endregion

#pragma region TerrariumDataTests
TEST_F(lorawanUplinkHandlerTest, TestIfPrepareTerrariumDataIsCalledOnce) {
    //Arrange
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(1, prepareTerrariumData_fake.call_count);
}

TEST_F(lorawanUplinkHandlerTest, TestPrepareTerrariumDataReturnVal) {
    //Arrange
    prepareTerrariumData_fake.return_val = terrariumdata_p;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(terrariumdata_p, prepareTerrariumData_fake.return_val);
}

TEST_F(lorawanUplinkHandlerTest, TestIfGetTempIsCalledOnce) {
    //Arrange
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(1, getTerrariumTemp_fake.call_count);
}

TEST_F(lorawanUplinkHandlerTest, TestGetTempParam) {
    //Arrange
    
    getTerrariumTemp_fake.arg0_val = terrariumdata_p;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(terrariumdata_p, getTerrariumTemp_fake.arg0_val);
}

TEST_F(lorawanUplinkHandlerTest, TestGetTempReturnVal) {
    //Arrange
    int16_t temp = 20;
    getTerrariumTemp_fake.return_val = temp;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(temp, getTerrariumTemp_fake.return_val);
}

TEST_F(lorawanUplinkHandlerTest, TestIfGetHumIsCalledOnce) {
    //Arrange
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(1, getTerrariumHum_fake.call_count);
}

TEST_F(lorawanUplinkHandlerTest, TestGetHumParam) {
    //Arrange

    getTerrariumHum_fake.arg0_val = terrariumdata_p;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(terrariumdata_p, getTerrariumHum_fake.arg0_val);
}

TEST_F(lorawanUplinkHandlerTest, TestGetHumReturnVal) {
    //Arrange
    int16_t hum = 41;
    getTerrariumHum_fake.return_val = hum;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(hum, getTerrariumHum_fake.return_val);
}

TEST_F(lorawanUplinkHandlerTest, TestIfGetCo2IsCalledOnce) {
    //Arrange
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(1, getTerrariumCO2_fake.call_count);
}

TEST_F(lorawanUplinkHandlerTest, TestGetCo2Param) {
    //Arrange

    getTerrariumCO2_fake.arg0_val = terrariumdata_p;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(terrariumdata_p, getTerrariumCO2_fake.arg0_val);
}

TEST_F(lorawanUplinkHandlerTest, TestGetCO2ReturnVal) {
    //Arrange
    uint16_t CO2 = 433;
    getTerrariumCO2_fake.return_val = CO2;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(CO2, getTerrariumCO2_fake.return_val);
}

TEST_F(lorawanUplinkHandlerTest, TestIfGetIsFedIsCalledOnce) {
    //Arrange
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(1, getTerrariumIsFed_fake.call_count);
}

TEST_F(lorawanUplinkHandlerTest, TestIfGetIsFedIsCalledOnce2) {
    //Arrange
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(1, getTerrariumIsFed_fake.call_count);
}

TEST_F(lorawanUplinkHandlerTest, TestGetIsFedParam) {
    //Arrange

    getTerrariumIsFed_fake.arg0_val = terrariumdata_p;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(terrariumdata_p, getTerrariumIsFed_fake.arg0_val);
}

TEST_F(lorawanUplinkHandlerTest, TestGetIsFedReturnVal) {
    //Arrange
    int8_t IsFed = 1;
    getTerrariumIsFed_fake.return_val = IsFed;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(IsFed, getTerrariumIsFed_fake.return_val);
}

TEST_F(lorawanUplinkHandlerTest, TestIfGetLightIsCalledOnce) {
    //Arrange
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(1, getTerrariumLight_fake.call_count);
}

TEST_F(lorawanUplinkHandlerTest, TestGetLightParam) {
    //Arrange

    getTerrariumLight_fake.arg0_val = terrariumdata_p;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(terrariumdata_p, getTerrariumLight_fake.arg0_val);
}

TEST_F(lorawanUplinkHandlerTest, TestGetLightReturnVal) {
    //Arrange
    uint16_t light = 1;
    getTerrariumLight_fake.return_val = light;
    //Act
    loraHandlerRun();
    //Assert/Expect
    EXPECT_EQ(light, getTerrariumLight_fake.return_val);
}
#pragma endregion