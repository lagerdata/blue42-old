add_library(log STATIC
  src/nrf_log_backend_flash.c
  src/nrf_log_backend_rtt.c
  src/nrf_log_backend_serial.c
  src/nrf_log_backend_uart.c
  src/nrf_log_ctrl_internal.h
  src/nrf_log_default_backends.c
  src/nrf_log_frontend.c
  src/nrf_log_str_formatter.c)

target_include_directories(log PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")
target_include_directories(log PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src")



target_link_libraries(log system)

target_compile_options(log PRIVATE -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16)
target_compile_options(log PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(log PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)


target_compile_definitions(log PRIVATE FLOAT_ABI_HARD NRF52840_XXAA NRF_SD_BLE_API_VERSION=7 S140 SOFTDEVICE_PRESENT)
target_compile_definitions(log PRIVATE $<$<COMPILE_LANGUAGE:C>:FREERTOS>)
target_compile_definitions(log PRIVATE $<$<COMPILE_LANGUAGE:ASM>:__HEAP_SIZE=8192 __STACK_SIZE=8192>)
