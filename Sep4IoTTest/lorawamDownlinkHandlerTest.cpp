#include "gtest/gtest.h"

#include <FreeRTOS_FFF_MocksDeclaration.h>

extern "C"
{
#include "LoRaWANDownlinkHandler.h"
#include <lora_driver.h>
#include <terrarium.h>
#include <message_buffer.h>
}

FAKE_VOID_FUNC(resetAnimalFeeder);
FAKE_VOID_FUNC(feedAnimalTerrarium);

class LoRaWANDownlinkHandlerTest : public::testing::Test
{
protected:

    void SetUp() override {
        RESET_FAKE(xMessageBufferReceive);
        RESET_FAKE(vTaskDelay);
        RESET_FAKE(resetAnimalFeeder);
        RESET_FAKE(feedAnimalTerrarium);
        FFF_RESET_HISTORY();
    }

    void TearDown() override {
       
    }
};

MessageBufferHandle_t downLinkMessageBuffer = xMessageBufferCreate(sizeof(lora_driver_payload_t) * 2);
lora_driver_payload downlinkPayload = { 1, 11, 0 };
lora_driver_payload_t* downlinkPayload_p = &downlinkPayload;
/*
* Test for denne fil er ikke komplet - 
downlinkPayload kan vi ikke sætte og if statementet
i loraDownlinkRun() vil aldrig være true.
*/

#pragma region LoraWanTests
TEST_F(LoRaWANDownlinkHandlerTest, TestMessageBufferIsCalledOnce) {
    //Arrange
    //Act
    init_downlink_handler(downLinkMessageBuffer);
    loraDownlinkRun();
    //Assert/Except
    EXPECT_EQ(1, xMessageBufferReceive_fake.call_count);
}

TEST_F(LoRaWANDownlinkHandlerTest, TestMessageBufferParams) {
    //Arrange
    xMessageBufferReceive_fake.arg0_val = downLinkMessageBuffer;
    xMessageBufferReceive_fake.arg1_val = downlinkPayload_p;
    xMessageBufferReceive_fake.arg2_val = sizeof(lora_driver_payload_t);
    xMessageBufferReceive_fake.arg3_val = portMAX_DELAY;
    //Act
    loraDownlinkRun();
    //Assert/Except
    EXPECT_EQ(downLinkMessageBuffer, xMessageBufferReceive_fake.arg0_val);
    EXPECT_EQ(downlinkPayload_p, xMessageBufferReceive_fake.arg1_val);
    EXPECT_EQ(sizeof(lora_driver_payload_t), xMessageBufferReceive_fake.arg2_val);
    EXPECT_EQ(portMAX_DELAY, xMessageBufferReceive_fake.arg3_val);
}
#pragma endregion

#pragma region TestAnimalFeed
TEST_F(LoRaWANDownlinkHandlerTest, TestIfFeedAnimalIsNotCalled) {
    //Arrange
    //Act
    init_downlink_handler(downLinkMessageBuffer);
    loraDownlinkRun();
    //Assert/Except
    EXPECT_EQ(0, feedAnimalTerrarium_fake.call_count);
}

TEST_F(LoRaWANDownlinkHandlerTest, TestIfResetAnimalFeederIsCalledOnce) {
    //Arrange
    //Act
    init_downlink_handler(downLinkMessageBuffer);
    loraDownlinkInit();
    loraDownlinkRun();
    //Assert/Except
    EXPECT_EQ(1, resetAnimalFeeder_fake.call_count);
}
#pragma endregion
