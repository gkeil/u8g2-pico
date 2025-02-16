# Add library and the correspondin source files
# an INTERFACE Library is produce. No lib object is generated.
# In order to use this library the u8g2 folder must be included
# with add_subdirectory()

# prevent multiple definitions
if ( NOT TARGET u8g2 )

    add_library( u8g2 INTERFACE )

    file(GLOB COMPONENT_SRCS ./*.c)
    file(GLOB COMPONENT_HDRS ./*.h)

    #add_subdirectory( ../sh1106_i2c )


    target_sources( u8g2 INTERFACE ${COMPONENT_SRCS}
                                    ../sh1106_i2c/u8g2_hal.c 
                                    )

    target_include_directories(u8g2 INTERFACE . )

    # Add the standard library to the build
    target_link_libraries(  u8g2     INTERFACE
                            pico_stdlib
                            hardware_i2c
                           
    )

endif()