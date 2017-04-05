#include <time.h>
int SLEEP(clock_t wait)
{
    clock_t goal;
    wait *= 1000;
    goal = wait + clock();
    while (goal > clock() )
       ;

    return (0);
}

int new_sleep (int amount)
{
        SLEEP(amount);
        return (0);
}
