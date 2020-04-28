add_library(system STATIC
  src/system_nrf52840.c
  src/gcc_startup_nRF52840.S
  src/nrf_sdh_freertos.c
  src/nrf_sdh_soc.c
  src/nrf_sdh.c)
target_include_directories(system PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

target_link_libraries(system section_iter)
target_link_libraries(system freertos)
target_link_libraries(system log)


target_compile_options(system PRIVATE -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16)
target_compile_options(system PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(system PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)


target_compile_definitions(system PRIVATE FLOAT_ABI_HARD NRF52 NRF52840_XXAA NRF_SD_BLE_API_VERSION=6 S140 SOFTDEVICE_PRESENT)
target_compile_definitions(system PRIVATE $<$<COMPILE_LANGUAGE:C>:FREERTOS>)
target_compile_definitions(system PRIVATE $<$<COMPILE_LANGUAGE:ASM>:__HEAP_SIZE=8192 __STACK_SIZE=8192>)
