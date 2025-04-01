# esp32_rtos

Example ESP32 FreeRTOS reference for new project

## Summary

Use of multiple tasks & intertask signaling to get started

## Folders

* core - main code
* doc  - documentation
* drv  - drivers
* lbr  - libraries
* mw   - middlewares
* out  - published output contents
* test - System test procedure & results 

## Hardware

- Current: ESP32-S3

## Source

* [esp32_base](https://github.com/ErisdarDemo/esp32_base/tree/v1) 'v1'

## View Configurations

* Eclipse - Hide 'build\' & 'sdkconfig.ci' from Project Explorer

* File Explorer - Hide '.clangd', '.clang-format', .gitignore/ & 'sdkconfig.ci' from view

# Source Project - FreeRTOS Real Time Stats Example (ESP-IDF)

FreeRTOS provides the function `vTaskGetRunTimeStats()` to obtain CPU usage statistics of tasks. However, these statistics are with respect to the entire runtime of FreeRTOS (i.e. **run time stats**). Furthermore, statistics of `vTaskGetRunTimeStats()` are only valid whilst the timer for run time statistics has not overflowed.

This example demonstrates how to get CPU usage statistics of tasks with respect to a specified duration (i.e. **real time stats**) rather than over the entire runtime of FreeRTOS. The `print_real_time_stats()` function of this example demonstrates how this can be achieved.

## How to use example

### Hardware Required

This example should be able to run on any commonly available ESP32 development board.

### Configure the project

```
idf.py menuconfig
```

* Select `Enable FreeRTOS to collect run time stats` under `Component Config > FreeRTOS` (this should be enabled in the example by default)

* `Choose the clock source for run time stats` configured under `Component Config > FreeRTOS`. The `esp_timer` should be selected be default. This option will affect the time unit resolution in which the statistics are measured with respect to.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(Replace PORT with the name of the serial port to use.)

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.

## Example Output

The example should have the following log output:

```
...
Getting real time stats over 100 ticks
| Task | Run Time | Percentage
| stats | 1304 | 0%
| IDLE0 | 206251 | 10%
| IDLE1 | 464785 | 23%
| spin2 | 225389 | 11%
| spin0 | 227174 | 11%
| spin4 | 225303 | 11%
| spin1 | 207264 | 10%
| spin3 | 225331 | 11%
| spin5 | 225369 | 11%
| Tmr Svc | 0 | 0%
| esp_timer | 0 | 0%
| ipc1 | 0 | 0%
| ipc0 | 0 | 0%
Real time stats obtained
...
```

## Example Breakdown

### Spin tasks

During the examples initialization process, multiple `spin` tasks are created. These tasks will simply spin a certain number of CPU cycles to consume CPU time, then block for a predetermined period.

### Understanding the stats

From the log output, it can be seen that the spin tasks consume nearly an equal amount of time over the specified stats collection period of `print_real_time_stats()`. The real time stats also display the CPU time consumption of other tasks created by default in ESP-IDF (e.g. `IDLE` and `ipc` tasks).