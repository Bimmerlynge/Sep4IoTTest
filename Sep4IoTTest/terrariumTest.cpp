#include "gtest/gtest.h"

#include <FreeRTOS_FFF_MocksDeclaration.h>

extern "C" {


#include <terrarium.h>
}

class TerrariumTest : public ::testing::Test {
protected:
	void SetUp() override {}
	void TearDown() override {}
};

#pragma region TerrariumInitTests
TEST_F(TerrariumTest, TestInitCreatesSemaphore) {
	//Arrange

	//Act
	initTerrarium();
	//Assert/Except



}

#pragma endregion