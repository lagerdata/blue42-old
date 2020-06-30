#define _TEST1_C_SRC

//-------------------------MODULES USED-------------------------------------
#include "unity.h"
#include "mpu9250_drv.h"

//-------------------------DEFINITIONS AND MACORS---------------------------
#define WHO_AM_I_VAL (0x68)


//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------



//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------



//-------------------------EXPORTED FUNCTIONS-------------------------------
void setUp(void)
{
    mpu9250_drv_init();
}

void tearDown(void)
{
    mpu9250_drv_unit();
}


void test_who_am_i_read(void)
{
    uint8_t val_who_am_i;
    int32_t ret = mpu9250_drv_who_am_i(&val_who_am_i);
    TEST_ASSERT_EQUAL_INT(MPU9250_OK, ret);
    TEST_ASSERT_EQUAL_UINT8(WHO_AM_I_VAL, val_who_am_i);

}


//-------------------------LOCAL FUNCTIONS----------------------------------
