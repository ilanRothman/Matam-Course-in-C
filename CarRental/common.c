#include "common.h"

#include <stdio.h>
#include <malloc.h>

/*MATAM functions - */

static unsigned int allocated_blocks = 0;

void *checked_malloc(unsigned int size)
{
    void * ret;

    ret = malloc(size);
    if (!ret) {
        perror ("Memory allocation error");
        exit (1);
    }
    allocated_blocks++;
    return ret;
}

void checked_free (void *ptr)
{

    free(ptr);
    allocated_blocks--;
    return;
}

void check_for_exit() {
    if (allocated_blocks) {
        fprintf (stderr, "Memory leak: %d memory blocks still allocated \n", allocated_blocks);
        exit(1);
    }
    return;
}
/*MATAM functions - */



/*flusher that will clear the buffer once needed*/
void flusher(){
    while(getchar() != '\n') {
        continue;
    }
}

/*Will check the validation of the input date based on the value of the day, month and year*/
int valid_date(int dd, int mm, int yy)
{
    int days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int leapYeardays[] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
    int daymax;
    int leap = ((yy%4 == 0) && (yy%100 != 0)) || (yy%400 == 0);

    if (mm < 1 || mm > 12)
    {
        return 0;
    }

    daymax = (leap == 1) ? leapYeardays[mm] : days[mm];

    if (dd < 1 || dd > daymax)
    {
        return 0;
    }

    return 1;
}


