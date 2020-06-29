add_library (mpu9250_drv STATIC "")
target_sources(mpu9250_drv PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/mpu9250_drv.c)
target_include_directories(mpu9250_drv PUBLIC ${CMAK_CURRENT_LIST_DIR}/include/mpu9250.h)


target_compile_options(nrf52 PRIVATE -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16)
target_compile_options(nrf52 PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
