####################################################################################################
# @brief    lbr\ CMake Description
# @details  IDF Progrmming Guide -> Build system -> component CMakeLists.txt 
####################################################################################################

# Build Config
idf_component_register(
                       SRC_DIRS
                         "."
                         "../appl"
                         "../lbr"
                         "mcu"
                         "rtos"
                         "system"
                       PRIV_REQUIRES
                         spi_flash
                         driver
                       INCLUDE_DIRS
                         "." 
                         "../appl"
                         "../lbr"
                         "mcu"
                         "rtos"
                         "system"
                      )

