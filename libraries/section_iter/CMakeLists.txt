add_library(section_iter STATIC src/nrf_section_iter.c)
target_include_directories(section_iter PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")


target_link_libraries(section_iter system)


target_compile_options(section_iter PRIVATE -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv4-sp-d16)
target_compile_options(section_iter PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(section_iter PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)


target_compile_definitions(section_iter PRIVATE FLOAT_ABI_HARD NRF52840_XXAA NRF_SD_BLE_API_VERSION=6 S140 SOFTDEVICE_PRESENT)
target_compile_definitions(section_iter PRIVATE $<$<COMPILE_LANGUAGE:C>:FREERTOS>)
target_compile_definitions(section_iter PRIVATE $<$<COMPILE_LANGUAGE:ASM>:__HEAP_SIZE=8192 __STACK_SIZE=8192>)
