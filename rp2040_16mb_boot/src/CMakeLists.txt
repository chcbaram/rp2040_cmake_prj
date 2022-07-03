
file(GLOB SRC_FILES 
  bsp/*.c
  hw/*.c
  hw/driver/*.c
)

file(GLOB_RECURSE SRC_FILES_RECURSE
  ap/*.cpp
  common/*.c 
)

add_executable(
  ${PRJ_NAME}
  
  main.cpp

  ${SRC_FILES}
  ${SRC_FILES_RECURSE}
)

target_include_directories(${PRJ_NAME} PUBLIC 
  ap
  bsp
  common 
  common/core
  common/hw/include 
  hw
)

target_link_libraries(${PRJ_NAME} 
  cmsis_core
  pico_stdlib
  hardware_spi
  hardware_dma
  hardware_irq
  hardware_i2c
  hardware_flash
  )

pico_add_extra_outputs(${PRJ_NAME})
pico_enable_stdio_usb(${PRJ_NAME}  1)
pico_enable_stdio_uart(${PRJ_NAME} 0)

pico_set_linker_script(${PRJ_NAME} "${CMAKE_SOURCE_DIR}/src/bsp/ldscript/pico_flash.ld")

set_target_properties(${PRJ_NAME} PROPERTIES SUFFIX ".elf")
add_custom_command(TARGET ${PRJ_NAME} POST_BUILD
        COMMAND arm-none-eabi-size --format=berkeley --totals "$<TARGET_FILE:${PRJ_NAME}>"
        COMMENT "Invoking: Cross ARM GNU Print Size")