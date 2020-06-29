#define _MAIN_TEST1_C_SRC

//-------------------------MODULES USED-------------------------------------
#include "unity.h"
#include "test1.h"


//-------------------------DEFINITIONS AND MACORS---------------------------

//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------



//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------



//-------------------------EXPORTED FUNCTIONS-------------------------------


int main(void)
{
    UnityBegin("test1.c");
    // DO_TEST(test_freertosSystickCorrectFreq);
    DO_TEST(test_thatSucceeds);
    DO_TEST(test_succeedsWithCondition);
    // DO_TEST(test_failsWithCondition);
    //run test 2

    UnityEnd();
    while(1);
    return 0;
}


void HardFault_Handler(void)
{

    while(1);
}

//-------------------------LOCAL FUNCTIONS----------------------------------
