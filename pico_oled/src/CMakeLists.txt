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
  hw/driver/gpio.c
  hw/driver/spi.c
  hw/driver/lcd.c
  hw/driver/resize.c
  hw/driver/i2c.c

  hw/driver/lcd/ili9341.c  
  hw/driver/lcd/lcd_fonts.c
  hw/driver/lcd/ssd1306.c
  hw/driver/hangul/han.c  
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

set_target_properties(${PRJ_NAME} PROPERTIES SUFFIX ".elf")
add_custom_command(TARGET ${PRJ_NAME} POST_BUILD
        COMMAND arm-none-eabi-size --format=berkeley --totals "$<TARGET_FILE:${PRJ_NAME}>"
        COMMENT "Invoking: Cross ARM GNU Print Size")