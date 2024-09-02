# Firmwares with [RIOT OS](https://github.com/RIOT-OS/RIOT)

[Getting started](https://doc.riot-os.org/getting-started.html)

```bash
cd ~/github/RIOT-OS/RIOT
cd examples/blinky
BOARD=nucleo-l432kc
make BOARD=$BOARD flash term
```

## Sensors

* [Bosch Sensortec BNO055](https://www.bosch-sensortec.com/products/smart-sensor-systems/bno055/) [lib](https://search.arduino.cc/search?q=bno055)
* [NXP MPL3115A2](https://www.nxp.com/docs/en/data-sheet/MPL3115A2.pdf) [driver]([https://search.arduino.cc/search?q=MPL3115A2](https://doc.riot-os.org/group__drivers__mpl3115a2.html))
* [ADS1015](https://www.ti.com/product/ADS1015) [driver](https://doc.riot-os.org/group__drivers__ads101x.html)
* GNSS [pkg](https://doc.riot-os.org/group__pkg__minmea.html)

## CAN Bus ([ST L9616 CAN Driver](https://www.st.com/en/automotive-analog-and-power/l9616.html))

* [conn_can](https://github.com/RIOT-OS/RIOT/tree/master/tests/sys/conn_can)

## Utils
* [AioP13 library : "Another implementation of PLAN-13" library)](https://github.com/thingsat/riot_modules/tree/main/modules/aiop13)
