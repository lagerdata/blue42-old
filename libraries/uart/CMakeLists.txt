add_library(uart STATIC src/uart_drv.c)
target_include_directories(uart PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")



target_link_libraries(uart system)
target_link_libraries(uart gpio)

target_compile_options(uart PRIVATE -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16)
target_compile_options(uart PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(uart PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)


target_compile_definitions(uart PRIVATE FLOAT_ABI_HARD NRF52840_XXAA NRF_SD_BLE_API_VERSION=7 S140 SOFTDEVICE_PRESENT)
target_compile_definitions(uart PRIVATE $<$<COMPILE_LANGUAGE:C>:FREERTOS>)
target_compile_definitions(uart PRIVATE $<$<COMPILE_LANGUAGE:ASM>:__HEAP_SIZE=8192 __STACK_SIZE=8192>)
