# Add executable. Default name is the project name, version 0.1

add_executable(u8g2-test u8g2-test.c )

pico_set_program_name(u8g2-test "u8g2-test")
pico_set_program_version(u8g2-test "0.1")

pico_enable_stdio_uart(u8g2-test 1)
pico_enable_stdio_usb(u8g2-test 0)

# Add the standard library to the build
target_link_libraries(  u8g2-test
                        pico_stdlib
                        u8g2 
                        )

pico_add_extra_outputs(u8g2-test)                        