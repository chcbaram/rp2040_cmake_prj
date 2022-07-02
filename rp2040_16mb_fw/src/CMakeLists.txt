add_executable(
  ${PRJ_NAME}
  
  main.cpp

  ap/ap.cpp 
  bsp/bsp.c
  common/core/qbuffer.c
  hw/hw.c
  hw/driver/led.c
  hw/driver/uart.c
  hw/driver/cli.c
  hw/driver/log.c
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
  pico_stdlib
  hardware_spi
  hardware_dma
  hardware_irq
  hardware_i2c
  )

pico_add_extra_outputs(${PRJ_NAME})
pico_enable_stdio_usb(${PRJ_NAME}  1)
pico_enable_stdio_uart(${PRJ_NAME} 0)

#pico_set_linker_script(${PRJ_NAME} "${CMAKE_SOURCE_DIR}/src/bsp/ldscript/pico_flash.ld")

set_target_properties(${PRJ_NAME} PROPERTIES SUFFIX ".elf")
add_custom_command(TARGET ${PRJ_NAME} POST_BUILD
        COMMAND arm-none-eabi-size --format=berkeley --totals "$<TARGET_FILE:${PRJ_NAME}>"
        COMMENT "Invoking: Cross ARM GNU Print Size")