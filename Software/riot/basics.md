# Premiers pas avec la carte INISAT Nucleo L432KC + RAK 5146

Dans ce chapitre, vous apprendrez à utiliser les fonctions de base offertes par RIOT pour la plupart des MCU STM32.

[Installation et configuration](install.md)

## LED
Construisez le firmware avec la commande suivante:
```bash
cd ~/github/RIOT-OS/RIOT/tests/leds
make -j 4
```

## Shell

Construisez le firmware avec la commande suivante:
```bash
cd ~/github/RIOT-OS/RIOT/tests/shell
make -j 4
```

Exercice: la commande `make` affiche les lignes suivantes. A quoi correspondent les [valeurs `text`, `data`, `bss`, `dec` et `hex` ?](https://mirzafahad.github.io/2021-05-08-text-data-bss/)
```
   text	   data	    bss	    dec	    hex	filename
  17124	    132	   1912	  19168	   4ae0	~/github/RIOT-OS/RIOT/tests/shell/bin/nucleo-l432kc/test-shell.elf
```

<details>
<summary>Réponse</summary>
En un mot:
<ul>
<li>‘text’ est votre code et vos constantes (et aussi la table de vecteurs).</li>
<li>‘data’ concerne les variables initialisées. Cela compte à la fois pour la RAM et le FLASH. La valeur initialisée alloue de l'espace dans FLASH qui est ensuite copié de la ROM vers la RAM dans le code de démarrage.</li>
<li>‘bss’ concerne les données non initialisées dans la RAM qui sont initialisées avec zéro dans le code de démarrage.</li>    
</ul>
</details>

Regardez les fichiers produits:
```bash
cat bin/$BOARD/riotbuild/riotbuild.h
ls -al bin/$BOARD
file bin/$BOARD/test-shell.*
```

* Le fichier `.elf` est un fichier binaire contenant le firmware et des informations sur celui-ci. [En savoir plus.](https://gist.github.com/x0nu11byt3/bcb35c3de461e5fb66173071a2379779)
* Le fichier `.bin` est un fichier binaire contenant le firmware qui est écrit dans la mémoire Flash du STM32L151 à l'adresse `0x08000000` par `openocd`.

Chargez le binaire `.bin` dans la mémoire Flash (adresse `0x08000000`) du STM32L151 avec la commande suivante.
```bash
make flash-only
```

> Note: la commande `make -j 4 flash` enchaine les commandes `make -j 4` puis `make flash-only`


<details>
<summary>Console (tio)</summary>
<pre>
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)
test_shell.
> help
Command          	Description
---------------------------------------
bufsize          	Get the shell's buffer size
start_test       	starts a test
end_test         	ends a test
echo             	prints the input command
empty            	print nothing on command
app_metadata     	Returns application metadata
pm               	interact with layered PM subsystem
ps               	Prints information about running threads.
reboot           	Reboot the node
version          	Prints current RIOT_VERSION
xfa_test1        	xfa test command 1
xfa_test2        	xfa test command 2
> ps
    pid | name             	| state	Q | pri | stack  ( used) ( free) | base addr  | current	 
      - | isr_stack        	| -    	- |   - |	512 (  172) (  340) | 0x20000000 | 0x200001c8
      1 | main             	| running  Q |   7 |   1024 (  536) (  488) | 0x20000398 | 0x2000071c
    	| SUM              	|        	| 	|   1536 (  708) (  828)
> bufsize
60
> pm
Usage:
    pm show: display current blockers for each power mode
    pm set <mode>: manually set power mode (lasts until WFI returns)
    pm block <mode>: manually block power mode
    pm unblock <mode>: manually unblock power mode
    pm off: call pm_off()
> pm show
mode 0 blockers: 1
mode 1 blockers: 2
mode 2 blockers: 0
Lowest allowed mode: 2
> app_metadata
{"cmd": "app_metadata_print_json()"}
{"data": {"APP_NAME": "test-shell"}}
{"data": {"BOARD": "nucleo-l432kc-init"}}
{"data": {"CPU": "stm32"}}
{"data": {"APP_SHELL_FMT": "NONE"}}
{"data": {"MCU": "stm32"}}
{"data": {"OS_VERSION": "2023.07-devel-325-g2863d"}}
{"result": "SUCCESS"}
> ps
	pid | name                 | state    Q | pri | stack  ( used) ( free) | base addr  | current     
	  - | isr_stack            | -        - |   - |    512 (  172) (  340) | 0x20000000 | 0x200001c8
	  1 | main                 | running  Q |   7 |   1024 (  536) (  488) | 0x20000398 | 0x2000071c 
	    | SUM                  |            |     |   1536 (  708) (  828)
> reboot
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)
test_shell.
>
</pre>
</details>

Exercice: Qu'affiche la commande `ps` ?

<details>
<summary>Réponse</summary>
La commande `ps` affiche les threads qui sont créés. Elle donne les tailles des piles (stack) des threads.

`isr_stack` n'est pas une thread (pas de pid) : `isr_stack` représente la pile d'exécution des traitants d'interuption, timers ...
</details>

Que se passe t'il quand la taille de la pile du thread est sous-dimensionnée ?

Essayez la commande suivante:
```bash
make CFLAGS+=-DTHREAD_STACKSIZE_MAIN=512U flash
```

Que se passe t'il ?


## Erreurs au moment de l'installation

hla_swd
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
Info : clock speed 300 kHz
Info : STLINK V2J16S0 (API v2) VID:PID 0483:3748
Info : Target voltage: 2.926341
Error: init mode failed (unable to connect to the target)


## Ajout d'une commande

Le shell est aisement extensible avec des commandes que vous pouvez écrire.

On peut par exemple ajouter la commande `git` qui affiche des informations sur le dépôt de code ayant servi à la production du firmware.

Ajoutez les lignes suivantes au fichier `main.c` de `~/github/RIOT-OS/RIOT/tests/shell`

```c
...
#include "git_utils.h"
...

static const shell_command_t shell_commands[] = {
  ...
	{ "git", "Get git info", git_cmd },
  ...
```

```bash
cd ~/github/RIOT-OS/RIOT/tests/shell
make -j 4 flash
```

## Timers

Les MCU disposent d'un ou plusieurs périphériques temporisateurs (timers). Les timers de RIOT simplifient leurs usages. Ils peuvent être utilsé pour déclancher une fonction (dite de rappel ou callback en anglais) apres plusieurs micro-secondes ou milli-secondes.

```bash
cd ~/github/RIOT-OS/RIOT/tests/periph/timer_periodic/
make -j 4 flash
```

<details>
<summary>Console (tio)</summary>
<pre>
Help: Press s to start test, r to print it is ready
START
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)

Running Timer 0 at 1000000 Hz.
One counter cycle is 25000 ticks or 25 ms
Will print 'tick' every cycle.

TEST START
Running iteration 1 of 3
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick

Cycles:
channel 0 = 12	[OK]
Running iteration 2 of 3
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick

Cycles:
channel 0 = 12	[OK]
Running iteration 3 of 3
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick
[0] tick

Cycles:
channel 0 = 12	[OK]
TEST SUCCEEDED
{ "threads": [{ "name": "main", "stack_size": 1536, "stack_used": 412}]}

</pre>
</details>

## Threads

Les threads sont des processus légers partageant le même espace mémoire qui accèdent de manière concurrente mais qui ont chacun une pile privée (stack) dimensionnée en général à la fabrication (build time) du binaire du programme (firmware).

> Note: il convient donc de dimensionner correctement la taille de la pile d'une thread afin d'éviter que le sommet de la pile soit atteint pendant l'exécution.

Les threads permettent de réaliser plusieurs tâches en parellele par le programme. RIOT offre de mécanismes de barrière de concurrence entre les threads (mutex par exemple) et des moyens de communication par message.

```bash
cd ~/github/RIOT-OS/RIOT/tests/shell
make -j 4 flash
```

La commande `ps` du Shell permet de lister les threads courantes dans le programme. `main` correspond à la fonction `main()` qui exécute le Shell et `isr_stack` correspond à la thread qui exécute les traitants des interuptions, timers ... Il faut fréquent ajuster la taille de la pile de `isr_stack` avec `CFLAGS += -DISR_STACKSIZE=2048` par exemple. Idem pour `main` avec `THREAD_STACKSIZE_MAIN`.

<details>
<summary>Console (tio)</summary>
<pre>
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)
test_shell.
> ps
	pid | name                 | state    Q | pri | stack  ( used) ( free) | base addr  | current     
	  - | isr_stack            | -        - |   - |    512 (  172) (  340) | 0x20000000 | 0x200001c8
	  1 | main                 | running  Q |   7 |   1024 (  536) (  488) | 0x20000398 | 0x2000071c 
	    | SUM                  |            |     |   1536 (  708) (  828)
</pre>
</details>


```bash
cd ~/github/RIOT-OS/RIOT/tests/core/thread_float/
make -j 4 flash
```

<details>
<summary>Console (tio)</summary>
<pre>
> Help: Press s to start test, r to print it is ready
START
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)
THREADS CREATED

Context switch every 1562 µs
{ "threads": [{ "name": "main", "stack_size": 1536, "stack_used": 388 }]}
THREAD t1 start
THREAD t2 start
THREAD t3 start
t1: 141.443787
t3: 141.466812
t1: 141.443787
t3: 141.466812
t1: 141.443787
t3: 141.466812
t1: 141.443787
t3: 141.466812
t1: 141.443787
t3: 141.466812
t1: 141.443787
t3: 141.466812
t1: 141.443787
t3: 141.466812
t1: 141.443787
</pre>
</details>

```bash
cd ~/github/RIOT-OS/RIOT/tests/core/thread_msg_bus/
make -j 4 flash
```


<details>
<summary>Console (tio)</summary>
<pre>
Help: Press s to start test, r to print it is ready
START
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)
THREAD 1 start
THREAD 2 start
THREAD 3 start
THREADS CREATED
Posted event 22 to 0 threads
T1 recv: Hello Threads! (type=23) from bus
T3 recv: Hello Threads! (type=23) from bus
Posted event 23 to 2 threads
T1 recv: Hello Threads! (type=24) from bus
T2 recv: Hello Threads! (type=24) from bus
Posted event 24 to 2 threads
Post message to thread 1
T1 recv: Hello Thread 1 (type=4919)
Post shutdown request to all threads
T1 recv: shutdown request (type=0) from bus
{ "threads": [{ "name": "nr1", "stack_size": 1536, "stack_used": 412 }]}
T2 recv: shutdown request (type=0) from bus
{ "threads": [{ "name": "nr2", "stack_size": 1536, "stack_used": 412 }]}
T3 recv: shutdown request (type=0) from bus
{ "threads": [{ "name": "nr3", "stack_size": 1536, "stack_used": 412 }]}
SUCCESS
{ "threads": [{ "name": "main", "stack_size": 1536, "stack_used": 456 }]}
</pre>
</details>


```bash
cd ~/github/RIOT-OS/RIOT/tests/core/thread_cooperation/
make -j 4 flash
```

<details>
<summary>Console (tio)</summary>
<pre>
Help: Press s to start test, r to print it is ready
START
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)
[START] compute 12! (factorial).
MAIN: create thread, arg: 1
MAIN: msg to T-2
T-02: alive
T-02: got arg 1
MAIN: create thread, arg: 2
MAIN: msg to T-3
T-03: alive
T-03: got arg 2
MAIN: create thread, arg: 3
MAIN: msg to T-4
T-04: alive
T-04: got arg 3
MAIN: create thread, arg: 4
MAIN: msg to T-5
T-05: alive
T-05: got arg 4
MAIN: create thread, arg: 5
MAIN: msg to T-6
T-06: alive
T-06: got arg 5
MAIN: create thread, arg: 6
MAIN: msg to T-7
T-07: alive
T-07: got arg 6
MAIN: create thread, arg: 7
MAIN: msg to T-8
T-08: alive
T-08: got arg 7
MAIN: create thread, arg: 8
MAIN: msg to T-9
T-09: alive
T-09: got arg 8
MAIN: create thread, arg: 9
MAIN: msg to T-10
T-10: alive
T-10: got arg 9
MAIN: create thread, arg: 10
MAIN: msg to T-11
T-11: alive
T-11: got arg 10
MAIN: create thread, arg: 11
MAIN: msg to T-12
T-12: alive
T-12: got arg 11
MAIN: create thread, arg: 12
MAIN: msg to T-13
T-13: alive
T-13: got arg 12
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-2
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-3
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-4
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-5
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-6
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-7
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-8
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-9
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-10
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-11
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-12
{ "threads": [{ "name": "thread", "stack_size": 1024, "stack_used": 372 }]}
MAIN: reply from T-13
MAIN: 12! = 479001600
[SUCCESS]
{ "threads": [{ "name": "main", "stack_size": 1536, "stack_used": 516 }]}
</pre>
</details>


## Aide au déboggage

TODO

* https://doc.riot-os.org/group__utils.html
* `assert()` et `expect()`
 https://doc.riot-os.org/group__test__utils__expect.html#gadd37fb477fadd68ccc0f938027ba132e


## RTC (Realtime Clock)

La plupart des microcontroleurs possède un périphérique horloge temps-réel (en anglais Realtime Clock, RTC) qui maintient la date et l'heure courante et définir des alarmes tant que le microcontroleur est alimenté. Il est possible de supporter la perte d'alimentation (par exemple, changement de batterie) en ajoutant une pile de secours à cette horloge.

```bash
cd ~/github/RIOT-OS/RIOT/tests/periph/rtc/
make -j 4 flash
```

<details>
<summary>Console (tio)</summary>
<pre>
> Help: Press s to start test, r to print it is ready
START
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)

RIOT RTC low-level driver test
This test will display 'Alarm!' every 2 seconds for 4 times
RTC mem OK
Clock value is now   2020-01-02 05:58:26
  Setting clock to   2020-02-28 23:59:57
Clock value is now   2020-02-28 23:59:57
  Setting alarm to   2020-02-28 23:59:59
   Alarm is set to   2020-02-28 23:59:59
  Alarm cleared at   2020-02-28 23:59:57
       No alarm at   2020-02-28 23:59:59
  Setting alarm to   2020-02-29 00:00:01

Alarm!
Alarm!
Alarm!
Alarm!
RTC mem OK
{ "threads": [{ "name": "main", "stack_size": 1536, "stack_used": 500 }]}
</pre>
</details>

Modifiez le `Makefile` de l'exemple `shell` pour ajouter:

```makefile
FEATURES_REQUIRED += periph_rtc
FEATURES_OPTIONAL += periph_rtc_ms
FEATURES_OPTIONAL += periph_rtc_mem

DISABLE_MODULE += periph_init_rtc
```

Reflashez la carte avec les commandes suivantes :

```bash
cd ~/github/RIOT-OS/RIOT/tests/sys/shell
make -j 4 flash
```

<details>
<summary>Console (tio)</summary>
<pre>
> help
> rtc
usage: rtc <command> [arguments]
commands:
	poweron		power the interface on
	poweroff	power the interface off
	clearalarm	deactivate the current alarm
	getalarm	print the currently alarm time
	setalarm YYYY-MM-DD HH:MM:SS
			set an alarm for the specified time
	gettime		print the current time
	settime YYYY-MM-DD HH:MM:SS
			set the current time
> rtc gettime
2020-02-29 00:05:33
> rtc settime 2023-11-15 22:00:00
> rtc gettime
2023-11-15 22:00:04
> setalarm 2023-11-15 22:01:00
>
> 
2023-11-15 22:01:00
</pre>
</details>

> A quoi peuvent servir les alarmes de la RTC ?
<details>
<summary>Réponse(s)</summary>
<ul>
<li>A vous réveiller à l'heure le matin</li>
<li>A lancer l'arrossage de votre champs</li> 
<li>A mettre votre bâtiment sous radar</li> 
<li>...</li> 
</ul>
</details>

> Exercice : ajoutez d'une commande `sun` au shell qui calcule les heures de lever et de coucher du soleil.

Vous pouvez vous aider de [ChatGPT](https://chat.openai.com) : Write the C function which computes sunrise time and sunset time for the current position.


## WDT (Watchdog Timer)

Le chien de garde (Watchdog Timer en anglais) est un périphérique qui veille à redémarrer (reboot) le microcontroleur quand le programme a planté (débordement de pile) ou boucle.

```bash
cd ~/github/RIOT-OS/RIOT/tests/periph/wdt
make -j 4 flash
```

`setup 0 10000` fixe le WDG à 10 seconds. Il faut ensuite lancer le watchdog avec la commande `start`. Sans `kick`, il reboote la carte.

<details>
<summary>Console (tio)</summary>
<pre>
This is RIOT! (Version: 2023.07-devel-325-g2863d)
RIOT wdt test application
> help
Command              Description
---------------------------------------
range                Return wdt Timer range
setup                Setup wdt Timer
kick                 Delay wdt timer
start                Start wdt timer
startloop            Start wdt timer, loop print system time
> setup
usage: setup <min_time[ms]> <max_time[ms]>
> setup 0 10000
valid configuration
> start
starting wdt timer
> kick
delaying wdt timer
> kick
delaying wdt timer
> main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)
RIOT wdt test application</pre>
</details>

## EEPROM

L'EEPROM est une (petite) mémoire persistante qui est en général utilisé des paramêtres de personnalisation ou de configuration de l'équipement. 

Le microcontroleur de la carte Nucleo L432KC Base ne dispose pas d'EEPROM. Cependant, une [EEPROM I2C externe](https://www.st.com/en/memories/standard-i2c-eeprom.html) peut être ajoutée sur le PCB de la carte support ou via le commecteur Mikrobus avec la platine [MIKROE-1200](https://www.mikroe.com/eeprom-click).

```bash
cd tests/drivers/at24cxxx
make -j 4 flash
```


<details>
<summary>Console (tio)</summary>
<pre>
> main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)

TODO

</pre>
</details>

> Attention: il faut mieux ne pas stocker des secrets (clés cryptographiques par exemple) dans l'EEPROM : il est préférable d'utiliser la mémoire persistante sécurisée d'un Secure Element (SE) intégré au microcontroleur ou d'un composant externe. Le MCU de la carte L432KC n'est pas doté d'un tel composant SE.

## CPU ID

Chaque MCU STM32 possède un numéro de série unique donnée par le fabricant ST Microelectronic.

```bash
cd ~/github/RIOT-OS/RIOT/tests/periph/cpuid
make -j 4 flash
```

<details>
<summary>Console (tio)</summary>
<pre>
Help: Press s to start test, r to print it is ready
START
main(): This is RIOT! (Version: 2023.07-devel-325-g2863d)
Test for the CPUID driver
This test is reading out the CPUID of the platforms CPU

CPUID_LEN: 12
CPUID: 0x33 0x37 0x47 0x05 0x30 0x37 0x38 0x37 0x00 0x6c 0xa0 0x6e
{ "threads": [{ "name": "main", "stack_size": 1536, "stack_used": 388 }]}
</pre>
</details>

> A quoi peut servir ce `cpuid` ?
<details>
<summary>Réponse(s)</summary>
<ul>
<li>numéro pour la garantie constructeur de l'équipement</li>
<li>numéro d'inventaire de l'équipement chez le propriétaire</li>
<li>lutte contre la contrefaçon</li>
<li>lutter contre le marché gris</li>
<li>...</li>
</ul>
</details>

## Tension de l'alimentation

```bash
cd ~/github/RIOT-OS/RIOT/tests/periph/vbat
make -j 4 flash
```

> Exercice: quel est l'intéret de connaître la tension d'alimentation ?
<details>
<summary>Réponse(s)</summary>
<li>Savoir à quel moment une opération de maintenance doit être planifier pour remplacer la batterie.</li>
</details>

## Extra

* True random number generator
* [STM32 last reset status](../tests/last_reset_status/)
* [STM32 internal temperature](../tests/internal_temperature/)
