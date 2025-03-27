# SX1302 / SX1303 Gateway Modules for [Thingsat @ INISAT 📡 🚀](../Thingsat_INISAT)

## RAK5146 Gateway Concentrator Module for LoRaWAN SPI

* Manufacturer: [RAK Wireless](https://store.rakwireless.com/products/wislink-concentrator-module-sx1303-rak5146-lorawan?srsltid=AfmBOorAl43FJtvq0f6k6GQTX6-MeB1SWc8eSZecXvENYsJIkCYQmvOO&variant=39667784908998)
* Interface: mini-PCIe
* Bus: SPI (exists with USB interface with SX1261 for LBT)
* Chip: SX1303 + 2x SX1250
* Temperature: No
* GNSS: Yes UBlox UBlox ZOE-M8Q (UART)
* PPS: Yes
* LBT: Yes (for USB)
* Spectral Scan: Yes (for USB)
* Fine timestamp (for TDOA): Yes (when includes UBlox ZOE-M8Q)
* Regions: EU868, IN865, US915, AS923, KR920, AU915. (RAK5146L supports CN470 or EU433)
* Compliance with [Thingsat @ INISAT 📡 🚀](../Thingsat_INISAT) : Yes

![](images/rak5146-pinout.png)

## RAK2287 WisLink LPWAN Concentrator SPI

* Manufacturer: [RAK Wireless](https://docs.rakwireless.com/Product-Categories/WisLink/RAK2287/Overview/#product-description)
* Interface: mini-PCIe
* Bus: [SPI](https://store.rakwireless.com/products/wislink-concentrator-module-sx1302-rak2287-lorawan?variant=39660564283590) (exists with USB)
* Chip: SX1302 + 2x SX1250
* Temperature: No
* GNSS: Yes UBlox ZOE-M8Q (UART)
* PPS: Probably
* LBT: No (requires SX126x)
* Spectral Scan: No
* Fine timestamp (for TDOA): No
* Regions: EU868, IN865, US915, AS923, KR920, AU915. (RAK5146L supports CN470 or EU433)
* Compliance with [Thingsat @ INISAT 📡 🚀](../Thingsat_INISAT) : Probably since same pinout as RAK5146.


## RAK5166 WisLink LPWAN Concentrator SPI

* Manufacturer: [RAK Wireless](https://docs.rakwireless.com/product-categories/wislink/rak5166/overview)
* Interface: PCI Express M.2 Type 3042 andKey B-M Dual Key IDs
* Bus: SPI
* Chip: SX1303 + 2x SX1250
* Temperature: No
* GNSS: Yes UBlox ZOE-M8Q (UART)
* PPS: Yes
* LBT: Yes
* Spectral Scan: Yes
* Fine timestamp (for TDOA): No
* Regions: EU868
* Compliance with [Thingsat @ INISAT 📡 🚀](../Thingsat_INISAT) : No

![](images/rak5166-pinout.png)

## Nebra NBR-0094 (SPI Version)

* Manufacturer: [Nebra](https://support.nebra.com/support/solutions/articles/24000078841-nebra-sx1302-3-concentrator-module)
* Interface: mini-PCIe
* Chip: SX1303 + 2x SX1250 + SX1261 (rx only)
* Temperature: NA
* GNSS: No
* PPS: No
* Fine timestamp (for TDOA): No
* LBT: Yes
* Spectral Scan: Yes
* Fine timestamp (for TDOA): No
* Regions: EU868
* Compliance with [Thingsat @ INISAT 📡 🚀](../Thingsat_INISAT) : Yes

![](images/nbr0094-pinout.jpg)


## Seeedstudio Wio-WM1303 Long Range Gateway Module (SPI Version)

* Manufacturer: [Seeedstudio](https://wiki.seeedstudio.com/Network/SenseCAP_Network/SenseCAP_M1-Helium_gateway/SenseCAP_M1_Overview/)
* Interface: mini-PCIe
* Chip: SX1303 + 2x SX1250 + SX1261 (rx only)
* Temperature: NA
* GNSS: NA
* PPS: NA
* Fine timestamp (for TDOA): No
* LBT: Yes
* Spectral Scan: Yes
* Regions: EU868
* Compliance with [Thingsat @ INISAT 📡 🚀](../Thingsat_INISAT) : Yes
* Remark: only available into [Seeedstudio SenseCAP M1 Helium Miner](https://wiki.seeedstudio.com/Network/SenseCAP_Network/SenseCAP_M1-Helium_gateway/SenseCAP_M1_Overview/)

## Seeedstudio Wio-WM1302 Long Range Gateway Module (SPI Version)

* Manufacturer: [Seeedstudio](https://www.seeedstudio.com/WM1302-LoRaWAN-Gateway-Module-SPI-EU868-p-4889.html)
* Interface: mini-PCIe
* Chip: SX1303 + 2x SX1250 + SX1262 (rx only)
* Temperature: NA
* GNSS: No
* PPS: No
* Fine timestamp (for TDOA): No
* LBT: Yes
* Spectral Scan: Yes
* Regions: EU868, US915
* Price: ~30 USD
* Compliance with [Thingsat @ INISAT 📡 🚀](../Thingsat_INISAT) : Yes

![](images/wm1302-pinout.jpg)

## Heltec HT1303 (SPI Version)

* Manufacturer: [heltec](https://heltec.org/project/ht1303/)
* Interface: mini-PCIe
* Bus: SPI (or USB))
* Chip: SX1302 + 2x SX1250 
* Temperature: Unknown
* GNSS: No
* PPS: No
* Fine timestamp (for TDOA): No
* LBT: No
* Spectral Scan: No
* Regions: EU868
* Compliance with [Thingsat @ INISAT 📡 🚀](../Thingsat_INISAT) : Probably

![](images/ht1303-pinout.jpg)

##  Semtech SX1302C868GW1 Corecell Devkit (SPI Version)

* Manufacturer: [Semtech](https://www.semtech.fr/products/wireless-rf/lora-core/sx1302cssxxxgw1)
* Interface: mini-PCIe
* Bus: SPI
* Chip: SX1302 + 2x SX1250
* Temperature: Yes (STTS751)
* GNSS: No (but slot available on connection board)
* PPS: No (but slot available on connection board)
* Fine timestamp (for TDOA): No
* LBT: No
* Spectral Scan: No
* Regions: EU868
* Compliance with [Thingsat @ INISAT 📡 🚀](../Thingsat_INISAT) : No

![](images/sx1302cssxxxgw1-pinout.jpg)


