# Premiers pas avec la carte INISAT Nucleo L432KC + RAK 5146


## Module gateway LoRa RAK5146

```bash
cd ~/github/thingsat/riot_modules/tests/driver_sx1302
make SX1302_LIB_VERSION=2_1_0 flash term
```

```console
help
lgw
lgw start
lgw eui
lgw listen
lgw bench
lgw bench 10 7 125 8 14 on false 20 2000
```

## Module GNSS de la gateway LoRa RAK5146

TODO

## Module Lambda80 SX1280 LoRa 2.4 GHz

```bash
cd ~/github/thingsat/riot_modules/tests/driver_sx1280
make flash term
```


## CAN Bus ([ST L9616 CAN Driver](https://www.st.com/en/automotive-analog-and-power/l9616.html))

* [conn_can](https://github.com/RIOT-OS/RIOT/tree/master/tests/sys/conn_can)
