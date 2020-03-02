#include "unity.h"
#include "led.h"
#include "RuntimeErrorStub.h"

uint16_t virtualLeds;

void setUp(void)
{
	LedDriver_Create(&virtualLeds);
}

void tearDown(void)
{
}

void test_LedsOffAfterCreate(void)
{
	uint16_t virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_TurnOnLedOne(void)
{
	LedDriver_TurnOn(1);
	TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

void test_TurnOffLedOne(void)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_TurnOnMultipleLeds(void)
{
	LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);
	TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}

void test_TurnOffAnyLed(void)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(8);
	TEST_ASSERT_EQUAL_HEX16(0xff7f, virtualLeds);
}

void test_AllOn(void)
{
	LedDriver_TurnAllOn();
	TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

void test_LedMemoryIsNotReadable(void)
{
	virtualLeds = 0xffff;
	LedDriver_TurnOn(8);
	TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}

void test_UpperAndLowerBounds(void)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(16);
	TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

void test_OutOfBoundsTurnOnDoesNoHarm(void)
{
	LedDriver_TurnOn(-1);
	LedDriver_TurnOn(0);
	LedDriver_TurnOn(17);
	LedDriver_TurnOn(3141);
	
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_OutOfBoundsTurnOffDoesNoHarm(void)
{
	LedDriver_TurnAllOn();
	
	LedDriver_TurnOff(-1);
	LedDriver_TurnOff(0);
	LedDriver_TurnOff(17);
	LedDriver_TurnOff(3141);
	
	TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

void test_OutOfBoundsProduceRuntimeError(void)
{
	LedDriver_TurnOn(-1);
	TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED",
		RuntimeErrorStub_GetLastError());
	TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

void test_OutOfBoundsToDo(void)
{
	TEST_IGNORE_MESSAGE("What should we do during runtime?");
}

void test_IsOn(void)
{
	TEST_ASSERT_FALSE(LedDriver_IsOn(11));
	LedDriver_TurnOn(11);
	TEST_ASSERT_TRUE(LedDriver_IsOn(11));
	
	TEST_ASSERT_FALSE(LedDriver_IsOn(6));
	LedDriver_TurnOn(6);
	TEST_ASSERT_TRUE(LedDriver_IsOn(6));
}

void test_OutOfBoundsLedsAreAlwaysOff(void)
{
	TEST_ASSERT_TRUE(LedDriver_IsOff(0));
	TEST_ASSERT_TRUE(LedDriver_IsOff(17));
	TEST_ASSERT_FALSE(LedDriver_IsOn(0));
	TEST_ASSERT_FALSE(LedDriver_IsOn(17));
}

void test_IsOff(void)
{
	TEST_ASSERT_TRUE(LedDriver_IsOff(11));
	LedDriver_TurnOn(11);
	TEST_ASSERT_FALSE(LedDriver_IsOff(11));
}

void test_TurnOffMultipleLeds(void)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(9);
	LedDriver_TurnOff(8);
	TEST_ASSERT_EQUAL_HEX16((~0x180)&0xffff, virtualLeds);
}

void test_AllOff(void)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnAllOff();
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}