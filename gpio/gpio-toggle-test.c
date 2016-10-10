#include <stdio.h>
#include <time.h>
#include <wiringPi.h>

#define LED 4
#define NUM 10000000

double timespec_to_double(struct timespec ts);

int main(void)
{
    int i, num_loops;
    double diff;
    struct timespec ts_start, ts_end;

    wiringPiSetup();
    pinMode(LED, OUTPUT);
    
    clock_gettime(CLOCK_REALTIME, &ts_start);

    num_loops = NUM / 10;
    for (i = 0; i < num_loops; i++)
    {
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
    }
    clock_gettime(CLOCK_REALTIME, &ts_end);

    diff =   timespec_to_double(ts_end)
           - timespec_to_double(ts_start);

    printf("Num oscillations: %u \n", NUM);
    printf("Total time taken: %f ms\n", diff * 1e3);
    printf("Speed: %f kHz\n", (NUM / diff) / 1e3);

    return 0;
}

double timespec_to_double(struct timespec ts)
{
    return    (double)ts.tv_sec
            + ((double)ts.tv_nsec / 1.0e9);
}
