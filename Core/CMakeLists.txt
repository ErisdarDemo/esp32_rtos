
# Build Configuration
idf_component_register(
						SRC_DIRS
						  "Mcu"
						  "Rtos"
					   SRCS 
					   	  "main.c" 
					   	  "System/utils.c"
					   	  "Rtos/freertos.c"
					   	  "Mcu/uart_handler.c"
					   INCLUDE_DIRS 
					   	  "../" 
					   	  "." 
					   	  "Mcu"
					   	  "Rtos"
					   	  "Middlewares/FreeRTOS/Source/CMSIS_RTOS_V2"
                      )

