#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

int main()
{
    printf("vous utilisez la version Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION,
    MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    led1=0;
    led2=1;
    led3=0;
    led4=1;
    while (true) {
    led1=!led1;
    led2=!led2;
    led3=!led3;
    led4=!led4;
    wait(1);
}
}