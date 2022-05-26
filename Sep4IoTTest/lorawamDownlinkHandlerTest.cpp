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

    /*lora_driver_payload_t downlinkPayload = 1;
    lora_driver_payload_t* downlinkPayload_p = &downlinkPayload;*/


    void SetUp() override {
        
    }

    void TearDown() override {
        RESET_FAKE(xMessageBufferReceive);
        RESET_FAKE(vTaskDelay);
        FFF_RESET_HISTORY();
    }

};


#pragma region loraWandTests

TEST_F(LoRaWANDownlinkHandlerTest, TestDownLinkMessageBufferIsCalledOnce) {
    //Arrange

    //Act
    loraDownlinkRun();

    //Assert/Except
    EXPECT_EQ(1, xMessageBufferReceive_fake.call_count);
}

TEST_F(LoRaWANDownlinkHandlerTest, TestIfDownlinkMessageIs) {
    //Arrange

    //Act
    loraDownlinkRun();
    //Assert/Except
    
}


#pragma endregion
