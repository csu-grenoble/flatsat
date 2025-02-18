# Premiers pas avec la carte INISAT Nucleo L432KC + RAK 5146

Clonez les dépôts (si ce n'est pas déjà fait):
```bash
mkdir -p ~/github/RIOT-OS
cd  ~/github/RIOT-OS
git clone https://github.com/RIOT-OS/RIOT.git
mkdir -p ~/github/thingsat
cd  ~/github/thingsat
git clone https://github.com/thingsat/riot_modules
```

Configurez `RIOTBASE`
```bash
export RIOTBASE=~/github/RIOT-OS/RIOT
```

Configurez la carte cible pour `make`
```bash
export EXTERNAL_BOARD_DIRS=~/github/thingsat/riot_modules/boards/
export BOARD=nucleo-l432kc-inisat
```

Recherchez le  `tty` de la console et connectez-vous à celle-ci avec `tio`.

Sur Linux
```bash
lsusb
tio
tio -b 115200 -m INLCRNL /dev/ttyUSB0
```

Sur MacOS
```bash
lsusb
tio
tio -L
tio -b 115200 -m INLCRNL /dev/tty.usbmodem-XXXX
```

> Pour mémoire, si vous utilisez Linux dans une machine virtuelle VirtualBox, il faut monter les 2 périphériques USBSerial et STLink dans le menu Péripériques de la machine virtuelle.
