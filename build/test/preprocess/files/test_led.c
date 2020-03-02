#include "build/temp/_test_led.c"
#include "RuntimeErrorStub.h"
#include "led.h"
#include "unity.h"


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

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOnLedOne(void)

{

 LedDriver_TurnOn(1);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOffLedOne(void)

{

 LedDriver_TurnOn(1);

 LedDriver_TurnOff(1);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOnMultipleLeds(void)

{

 LedDriver_TurnOn(9);

 LedDriver_TurnOn(8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x180)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_HEX16);

}



void test_TurnOffAnyLed(void)

{

 LedDriver_TurnAllOn();

 LedDriver_TurnOff(8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xff7f)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(47), UNITY_DISPLAY_STYLE_HEX16);

}



void test_AllOn(void)

{

 LedDriver_TurnAllOn();

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xffff)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_HEX16);

}



void test_LedMemoryIsNotReadable(void)

{

 virtualLeds = 0xffff;

 LedDriver_TurnOn(8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x80)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_HEX16);

}



void test_UpperAndLowerBounds(void)

{

 LedDriver_TurnOn(1);

 LedDriver_TurnOn(16);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x8001)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_HEX16);

}



void test_OutOfBoundsTurnOnDoesNoHarm(void)

{

 LedDriver_TurnOn(-1);

 LedDriver_TurnOn(0);

 LedDriver_TurnOn(17);

 LedDriver_TurnOn(3141);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_HEX16);

}



void test_OutOfBoundsTurnOffDoesNoHarm(void)

{

 LedDriver_TurnAllOn();



 LedDriver_TurnOff(-1);

 LedDriver_TurnOff(0);

 LedDriver_TurnOff(17);

 LedDriver_TurnOff(3141);



 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xffff)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_HEX16);

}



void test_OutOfBoundsProduceRuntimeError(void)

{

 LedDriver_TurnOn(-1);

 UnityAssertEqualString((const char*)(("LED Driver: out-of-bounds LED")), (const char*)((RuntimeErrorStub_GetLastError())), (

((void *)0)

), (UNITY_UINT)(96))

                                  ;

 UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((RuntimeErrorStub_GetLastParameter())), (

((void *)0)

), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_INT);

}



void test_OutOfBoundsToDo(void)

{

 UnityIgnore( (("What should we do during runtime?")), (UNITY_UINT)(102));

}



void test_IsOn(void)

{

 if (!(LedDriver_IsOn(11))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(107)));};

 LedDriver_TurnOn(11);

 if ((LedDriver_IsOn(11))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(109)));};



 if (!(LedDriver_IsOn(6))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(111)));};

 LedDriver_TurnOn(6);

 if ((LedDriver_IsOn(6))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(113)));};

}



void test_OutOfBoundsLedsAreAlwaysOff(void)

{

 if ((LedDriver_IsOff(0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(118)));};

 if ((LedDriver_IsOff(17))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(119)));};

 if (!(LedDriver_IsOn(0))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(120)));};

 if (!(LedDriver_IsOn(17))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(121)));};

}



void test_IsOff(void)

{

 if ((LedDriver_IsOff(11))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(126)));};

 LedDriver_TurnOn(11);

 if (!(LedDriver_IsOff(11))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(128)));};

}



void test_TurnOffMultipleLeds(void)

{

 LedDriver_TurnAllOn();

 LedDriver_TurnOff(9);

 LedDriver_TurnOff(8);

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)(((~0x180)&0xffff)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(136), UNITY_DISPLAY_STYLE_HEX16);

}



void test_AllOff(void)

{

 LedDriver_TurnAllOn();

 LedDriver_TurnAllOff();

 UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0)), (UNITY_INT)(UNITY_INT16)((virtualLeds)), (

((void *)0)

), (UNITY_UINT)(143), UNITY_DISPLAY_STYLE_HEX16);

}
