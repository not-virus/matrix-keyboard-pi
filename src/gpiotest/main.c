#include <stdio.h>
#include <pigpio.h>

#define TEST_PIN 4

int main()
{

    if (gpioInitialise() < 0)
    {
        fprintf(stderr, "pigpio initialization failed\n");
        return 1;
    }

    gpioSetMode(TEST_PIN, PI_OUTPUT);

    printf("GPIO Test\n");

    int readval = gpioRead(TEST_PIN);

    printf("Pin 4 read: %d", readval);

    gpioTerminate();
    return 0;
}