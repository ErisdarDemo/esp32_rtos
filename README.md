# esp32_rtos

ESP32 Base RTOS Project for new development

# Project Organization

- appl\ - Application

- lbr\ - Library Content

- core\mcu - Microcontroller Access & Drivers

- core\rtos - FreeRTOS contents with calls to appl\ for application operations

- core\system - Application setup & configure

# RTOS Demonstrations

The following demonstrations are provided in this template example


# Queue

- @open 	Messages are sent to a Console object for console printing		

# Semaphore

## Binary Semaphore

- currently console printing access

## Counting Semaphores

- task activity count (mutex & counter!! nice)

# Mutex

- @open 	Tasks have mutual exclusion to console printing

# Event

- @open 	Threads are woken back up on key console messages


# Version History

- v1 - Core demonstration of RTOS & project architecture for application & system development