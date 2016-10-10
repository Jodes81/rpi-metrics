#include <stdio.h>
#include <time.h>

#define NUM 10000

double timespec_to_double(struct timespec ts);

int main(void)
{
    int i, num_chars, num_bits;

    double 	diff,
                expected_time,
                error_time,
		expected_Bps = 11500, 
		recorded_bps,
                recorded_Bps;

    struct timespec ts_start, ts_end;

    clock_gettime(CLOCK_REALTIME, &ts_start);
    for (i = 0; i < NUM; i++)
    {
        printf("%10d", i);
    }
    clock_gettime(CLOCK_REALTIME, &ts_end);
    
    diff = timespec_to_double(ts_end)
        - timespec_to_double(ts_start);

    num_chars = NUM * 10;
    num_bits = num_chars * 10;
    recorded_Bps = num_chars / diff;
    recorded_bps = num_bits / diff;
    expected_time = num_chars / expected_Bps;

    printf("\nNum characters printed: %u\n", NUM * 10);
    printf("Time taken: %f ms \n", diff * 1e3);
    printf("Speed: %f KB/s\n", recorded_Bps / 1e3);
    printf("Speed: %f Kb/s\n", recorded_bps / 1e3);
    
    error_time = expected_time - diff;

    printf("\n");
    printf("Expected time taken: %f\n", expected_time);
    printf("Time error: %f\n", error_time);
    printf("Est. Buff size @ 115kb/s: %f B\n", expected_Bps * error_time);

    return 0;
}

double timespec_to_double(struct timespec ts)
{
    return    (double)ts.tv_sec
            + ((double)ts.tv_nsec / 1.0e9);
}
