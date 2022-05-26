#include "gtest/gtest.h"

#include <FreeRTOS_FFF_MocksDeclaration.h>

extern "C" {
#include <terrarium.h>
#include <servomotor.h>
#include "portable.h"

}

//FAKE_VOID_FUNC(feedAnimalTerrarium);
FAKE_VOID_FUNC(rotate180Servo);
FAKE_VALUE_FUNC(void*, pvPortMalloc, size_t);

class TerrariumTest : public ::testing::Test {
protected:
	void SetUp() override {}
	void TearDown() override {}
};

#pragma region TerrariumInitTests
TEST_F(TerrariumTest, TestInitCreatesSemaphore) {
	//Arrange

	//Act
	
	//Assert/Except

}

#pragma endregion