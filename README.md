# Easy-Space Flatsat  📡 🚀 extensions

![logo](./media/Logo-EASY-SPACE-Diffusion-blanc-1.png)

Extensions to [Easy Space](https://www.easy-space.fr/) INISAT flatsat mockup

![mockup](./media/flatsat.png)
![cubesat 2U](./media/inisat-02.jpg)

## [Board #1: ThingSat @ INISAT](Hardware/Thingsat_INISAT)  📡 🚀 (OBC + LoRa Gateway + CAN Bus)

* 1x [ST Nucleo L432KC](https://www.st.com/en/evaluation-tools/nucleo-l432kc.html)
* 1x [RAK Wireless RAK5146 (all bands)](https://store.rakwireless.com/products/wislink-concentrator-module-sx1303-rak5146-lorawan?_pos=1&_sid=c9dc2f56d&_ss=r&variant=39667784908998)
* 1x Mikrobus slots for homebrew LoRa click boards (Lambda80, GNSS RTK) or [others click boards](https://www.mikroe.com/shop)
* 3x [Groove connectors](https://wiki.seeedstudio.com/Grove_System/)
* 1x [ST L9616 Automotive High Speed Can Bus Transceiver](https://www.st.com/en/automotive-analog-and-power/l9616.html)
  
![OBC + RAK5146 board for INISAT](Hardware/Thingsat_INISAT/images/inisat-l432kc+rak5146+lambda80-01.jpg)

## [Board #2 ESP32 TinyGS](Hardware/2U-PCB-TinyGS)

* 1x [ESP32 Wroom](https://www.espressif.com/en/products/devkits)
* 2x Mikrobus slots for homebrew LoRa click boards (Lambda80, RN2483) or [others click boards](https://www.mikroe.com/shop)
* 6x [Groove connectors](https://wiki.seeedstudio.com/Grove_System/)
* 1x [ST L9616 Automotive High Speed Can Bus Transceiver](https://www.st.com/en/automotive-analog-and-power/l9616.html)

See [TinyGS 2G4 Station](https://github.com/thingsat/tinygs_2g4station)

![ESP32 Wroom + 2x Mikrobus Slots](./media/inisat+esp32+mikrobusx2.png)

## Board #3 Nucleo L476RG

* 1x [Nucleo L476RG](https://www.st.com/en/evaluation-tools/nucleo-l476rg.html)
* 1x [ST L9616 Automotive High Speed Can Bus Transceiver](https://www.st.com/en/automotive-analog-and-power/l9616.html)


![OBC](media/inisat-l476rg.png)

## References

* [EasySpace Diffusion](https://github.com/EasySpace-Diffusion)
* [TinyGS 2G4 Station](https://github.com/thingsat/tinygs_2g4station)
