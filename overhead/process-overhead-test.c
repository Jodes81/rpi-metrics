#include<stdio.h>
#include<time.h>

#define NUM 5000000

struct timespec ats[NUM];
double diff[NUM-1];

double timespec_to_double(struct timespec ts);


int main(void)
{
    long i, above3us = 0, above10us = 0, above31us = 0, above100us = 0, 
            above316us = 0, above1ms = 0, above3ms = 0, above10ms = 0;

    double tot, avg, max;

    printf("\n ========= Starting... ========= \n");

    for (i = 0; i < NUM; i++)
    {
        clock_gettime(CLOCK_REALTIME, &ats[i]);
    }

    printf("Done samples.\n");

//    printf("Start time (s) %lu\n", ats[0]);
//    printf("Start time (s) %f\n", timespec_to_double(ats[0]));
//    printf("End time (s) %lu\n", ats[NUM-1]);
//    printf("End time (s) %f\n", timespec_to_double(ats[NUM-1]));

    tot =     timespec_to_double(ats[NUM-1] )
            - timespec_to_double(ats[0]     );
    
    avg = tot / ((double)NUM - 1.0);

    printf("Creating stats...\n");

    for (i = 1; i < NUM; i++)
    {
        diff[i] = timespec_to_double(ats[i])
                  - timespec_to_double(ats[i-1]);
    }

    max = 0;
    for (i = 1; i < NUM; i++)
    {
        if (max < diff[i]) max = diff[i];

        if (diff[i] < 3.16e-6) continue; above3us++;
        if (diff[i] < 1e-5) continue;    above10us++;
        if (diff[i] < 3.16e-5) continue; above31us++;
        if (diff[i] < 1e-4) continue;    above100us++;
        if (diff[i] < 3.16e-4) continue; above316us++;
        if (diff[i] < 1e-3) continue;    above1ms++;
        if (diff[i] < 3.16e-3) continue; above3ms++;
        if (diff[i] < 10e-3) continue;   above10ms++;
    }
    
    printf("\n");
    printf("Num: %lu\n", NUM);
    printf("\n");
    printf("Total time (ms): %f\n", tot * 1.0e3);
    printf("Number above 3.16us: %lu \n", above3us);
    printf("Number above 10us:   %lu \n", above10us);
    printf("Number above 31.6us: %lu \n", above31us);
    printf("Number above 100us:  %lu \n", above100us);
    printf("Number above 316us:  %lu \n", above316us);
    printf("Number above 1ms:    %lu \n", above1ms);
    printf("Number above 3.16ms: %lu \n", above3ms);
    printf("Number above 10ms:   %lu \n", above10ms);
    printf("\n");
    printf("Average time (us): %f\n", avg * 1.0e6);
    printf("Max time: %f ms\n", max * 1.0e3);

    printf("\n");

    return 0;

}

double timespec_to_double(struct timespec ts)
{
    return    (double)ts.tv_sec 
            + ((double)ts.tv_nsec / 1.0e9);  
}
