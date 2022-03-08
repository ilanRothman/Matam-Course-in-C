
#ifndef PROJECT7_COMMON_H
#define PROJECT7_COMMON_H

#define ALLOC(typ,no) ((typ *) checked_malloc(sizeof(typ)*(no)))
#define FREE(ptr) checked_free(ptr)
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

/*MATAM functions - */

void *checked_malloc(unsigned int);
void checked_free(void *);
void check_for_exit();

/*MATAM functions */


/*Will check the validation of the input date based on the value of the day, month and year*/
int valid_date(int dd, int mm, int yy);

/*flusher that will clear the buffer once needed*/
void flusher();

#endif
