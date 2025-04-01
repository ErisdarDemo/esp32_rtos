####################################################################################################
# @brief 	core\ CMake Description
# @details 	IDF Progrmming Guide -> Build system -> component CMakeLists.txt 
#
# @warn 	adding SRC & SRC_DIRS together not recommended
#
####################################################################################################

# Build Config
idf_component_register(
					   SRC_DIRS
					     "."
					     "../lbr"
					     "mcu"
					     "rtos"
					     "system"
					   PRIV_REQUIRES
					     spi_flash
					   INCLUDE_DIRS
					     "." 
					     "../lbr"
					     "mcu"
					     "rtos"
					     "system"
					  )

