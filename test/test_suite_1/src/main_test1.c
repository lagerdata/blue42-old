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
    RUN_TEST(test_freertosSystickCorrectFreq);
    //run test 2

    return (UnityEnd());
}


//-------------------------LOCAL FUNCTIONS----------------------------------
