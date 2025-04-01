/**************************************************************************************************/
/** @file     mcu.c
 *  @brief    Application microcontroller component
 *  @details  x
 */
/**************************************************************************************************/

//Standard Library includes
#include <stdio.h>
#include <inttypes.h>

//SDK Includes
#include "sdkconfig.h"

//Library Includes
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

//FreeRTOS Includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


/**************************************************************************************************/
/** @fcn        void mcu_print_info(void)
 *  @brief      test print for mcu config
 *  @details    display contents from hello_world
 *
 *  @pre    system_initialize()
 */
/**************************************************************************************************/
void mcu_print_info(void) {
    
    //Locals
    esp_err_t stat;                                 /* sdk response code                          */
    esp_chip_info_t chip_info;                      /* Chip information from EEPROM               */
    unsigned major_rev;                             /* Chip ID major revision number              */
    unsigned minor_rev;                             /* Chip ID minor revision number              */
    uint32_t flash_size;                            /* flash bank memory size in bytes            */


    /* Get information */
    esp_chip_info(&chip_info);
    
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN)   ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT)         ? "BT"    : "",
           (chip_info.features & CHIP_FEATURE_BLE)        ? "BLE"   : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    //Get ID
    major_rev = (chip_info.revision / 100);
    minor_rev = (chip_info.revision % 100);
    
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    
    //Get Size
    stat = esp_flash_get_size(NULL, &flash_size);
    
    //Safety
    if(stat != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", 
            flash_size / (uint32_t)(1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    return;
}

