/*
   ;  nasm -f elf cpuida.asm   for cpuida.o
   ;  gcc cpuidc.c -c          for cpuidc.o
   ;  gcc test.c cpuidc.o cpuida.o -lrt -lc -lm -o test
   ;  ./test
   */

/* #include <stdio.h> */
#include "cpuidh.h"
/* #include <stdlib.h>      */
/* #include <string.h>  */
/*#include "string.h"*/
#include <time.h>
#include "pip/api.h"
#include "pip/debug.h"
#include <stdint.h>
#include "pip/compat.h" /* #include <math.h> */
/* #include <sys/time.h> */
/* #include <sys/resource.h> */

char    configdata[2][1024];
char    timeday[30];
char    idString1[100] = " ";
char    idString2[100] = " ";
uint64_t   theseMilliSecs = 0;
uint64_t  startMilliSecs = 0;
uint64_t  milliSecs;
struct  timespec tp1;

/* double  ramGB; */

/* FILE * info; */

int CPUconf;
int CPUavail;


uint64_t millisecs  = 0;


/* #include <sys/sysinfo.h>  */
/* #include <sys/utsname.h>  */


/* void local_time() */
/* { */
/*    time_t t; */

/*    t = time(NULL); */
/*    sprintf(timeday, "%s", asctime(localtime(&t))); */
/*    return; */
/* } */



uint64_t getRdtsc()
{
    /* clock_gettime(CLOCK_REALTIME, &tp1); */

    //uint64_t time;
    uint32_t cycles_low,cycles_high;
    //__asm__ volatile ("rdtsc" :  "=A"(time));
    asm volatile (
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low) :: "eax","edx");

    /* theseSecs =  tp1.tv_sec + tp1.tv_nsec / 1e9;*/

    return ( ((uint64_t)cycles_high << 32) | cycles_low );
    //theseMilliSecs = time;
}



void start_time()

{

    startMilliSecs =   getRdtsc();
    return;
}

void end_time()
{

    milliSecs =   getRdtsc() - startMilliSecs;

    return;
}
void  ullx(uint64_t val)
{

    static char buf[34] = { [0 ... 33] = 0 };
    char* out = &buf[33];
    uint64_t hval = val;
    unsigned int hbase = 10;

    do {
        *out = "0123456789"[hval % hbase];
        --out;
        hval /= hbase;
    } while(hval);

    *out-- = ' ', *out = ' ';

    puts(out);
}
void print64(uint64_t c){
    ullx(c); 
}

/* int getDetails() */
/* { */
/*    size_t bytes; */

/*    info = fopen ("/proc/cpuinfo", "r"); */
/*    if (info == NULL) */
/*    { */
/*         sprintf (configdata[0], " Cannot open /proc/cpuinfo\n"); */
/*         return 1; */
/*    } */
/*    bytes = fread (configdata[0], 1, sizeof(configdata[0]), info); */
/*    fclose (info); */
/*    if (bytes == 0) sprintf (configdata[0], " No data read from /proc/cpuinfo\n"); */

/*    info = fopen ("/proc/version", "r"); */
/*    if (info == NULL) */
/*    { */
/*         sprintf (configdata[0], " Cannot open /proc/version\n"); */
/*         return 1; */
/*    } */
/*    bytes = fread (configdata[1], 1, sizeof(configdata[1]), info); */
/*    fclose (info); */
/*    if (bytes == 0) sprintf (configdata[1], " No data read from /proc/version\n"); */
/*    return 0;  */
/* } */
