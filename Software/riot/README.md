# Firmwares with [RIOT OS](https://github.com/RIOT-OS/RIOT)

[Getting started](https://doc.riot-os.org/getting-started.html)

Clonez le dépôt RIOT (si ce n'est pas déjà fait):
```bash
mkdir -p ~/github/RIOT-OS
cd  ~/github/RIOT-OS
git clone https://github.com/RIOT-OS/RIOT.git
cd RIOT
```

[Testez les fonctionnalités de base de RIOT sur la carte Nucleo L432KC](basics.md)

## Sensors (on Sensors board)

* [Bosch Sensortec BNO055](https://www.bosch-sensortec.com/products/smart-sensor-systems/bno055/) [lib](https://search.arduino.cc/search?q=bno055)
* [NXP MPL3115A2](https://www.nxp.com/docs/en/data-sheet/MPL3115A2.pdf) [driver]([https://search.arduino.cc/search?q=MPL3115A2](https://doc.riot-os.org/group__drivers__mpl3115a2.html))
* [ADS1015](https://www.ti.com/product/ADS1015) [driver](https://doc.riot-os.org/group__drivers__ads101x.html)
* [GNSS uBlox Neo M8N](https://www.u-blox.com/en/product/neo-m8-series) [pkg](https://doc.riot-os.org/group__pkg__minmea.html)

## CAN Bus ([ST L9616 CAN Driver](https://www.st.com/en/automotive-analog-and-power/l9616.html))

* [conn_can](https://github.com/RIOT-OS/RIOT/tree/master/tests/sys/conn_can)

## LoRa gateway ([RAK5146 SPI + GPS module](https://store.rakwireless.com/products/wislink-concentrator-module-sx1303-rak5146-lorawan?_pos=1&_sid=ff8527039&_ss=r&variant=39667784908998))

* [SX1302/3 driver](https://github.com/thingsat/riot_modules/tree/main/modules/sx1302_2_1_0)
* [driver test](https://github.com/thingsat/riot_modules/tree/main/tests/driver_sx1302)

## Utils
* [AioP13 library : "Another implementation of PLAN-13" library](https://github.com/thingsat/riot_modules/tree/main/modules/aiop13)
