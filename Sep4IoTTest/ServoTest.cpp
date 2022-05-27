#include "gtest/gtest.h"

#include <FreeRTOS_FFF_MocksDeclaration.h>

extern "C" {
#include <servomotor.h>
#include <rc_servo.h>

}
FAKE_VOID_FUNC(rc_servo_setPosition, uint8_t, int8_t);

class ServoTest : public ::testing::Test {
protected:
	void SetUp() override {}
	void TearDown() override {
	
		RESET_FAKE(rc_servo_setPosition);
		FFF_RESET_HISTORY();
	}
};


TEST_F(ServoTest, TestRotateFullyRightCallsSetPositionOnce) {
	rotateFullyRight();
	EXPECT_EQ(rc_servo_setPosition_fake.call_count, 1);
}

TEST_F(ServoTest, TestRotateFullyRightSetPositionGetsRightParams) {

	rotateFullyRight();
	EXPECT_EQ(rc_servo_setPosition_fake.arg0_val, 1);
	EXPECT_EQ(rc_servo_setPosition_fake.arg1_val, 100);
}

TEST_F(ServoTest, TestRotateFullyLeftCallsSetPositionOnce) {
	rotateFullyLeft();
	EXPECT_EQ(rc_servo_setPosition_fake.call_count, 1);
}

TEST_F(ServoTest, TestRotateFullyLeftSetPositionGetsRightParams) {

	rotateFullyLeft();
	EXPECT_EQ(rc_servo_setPosition_fake.arg0_val, 1);
	EXPECT_EQ(rc_servo_setPosition_fake.arg1_val, -100);
}