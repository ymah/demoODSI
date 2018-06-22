/*
 * Compile Linux Intel
 * cc dhry_1.c dhry_2.c  cpuidc.c -lm -lrt -O3 -o dhrystoneIL
 *
 * Cross Compile on Linux Intel for ARM
 * ~/toolchain/raspbian-toolchain-gcc-4.7.2-linux32/bin/arm-linux-gnueabihf-gcc dhry_1.c dhry_2.c cpuidc.c -lm -lrt -O3 -march=armv6 -o dhrystonePiA6
 *
 * Compile on Raspberry Pi
 * gcc dhry_1.c dhry_2.c cpuidc.c -lm -lrt -O3 -march=armv6 -o dhrystonePiA6
 * #define options   "Opt 3 32 Bit"
 * gcc dhry_1.c dhry_2.c cpuidc.c -lm -lrt -O3 -mcpu=cortex-a7 -o dhrystonePiA7
 * #define options   "A7 32 Bit"
 *************************************************************************
 *
 *                   "DHRYSTONE" Benchmark Program
 *                   -----------------------------
 *
 *  Version:    C, Version 2.1
 *
 *  File:       dhry_1.c (part 2 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Author:     Reinhold P. Weicker
 *
 *************************************************************************
 *
 *     #define options not used
 */



/* Make the compiler happy :p */

//#include <inttypes.h>
#include "pip/compat.h"
#include "dhry.h"
#include "cpuidh.h"
#include "pip/debug.h"
#include <stdint.h>
#include "pip/api.h"

 #ifdef CNNT
    #define options   "Non-optimised"
    #define opt "0"
 #else
//    #define options   "Optimised"
//    #define options   "Opt 3 32 Bit"
    #define options   "A7 32 Bit"
    #define opt ""
 #endif

/* Global Variables: */

Rec_Pointer     Ptr_Glob,
                 Next_Ptr_Glob;
int             Int_Glob;
 Boolean         Bool_Glob;
 char            Ch_1_Glob,
                 Ch_2_Glob;
 int             Arr_1_Glob [50];
 int             Arr_2_Glob [50] [50];

 char Reg_Define[40] = "Register option      Selected.";


 Enumeration Func_1 (Capital_Letter Ch_1_Par_Val,
                                           Capital_Letter Ch_2_Par_Val);
   /*
   forward declaration necessary since Enumeration may not simply be int
   */

 #ifndef ROPT
 #define REG
         /* REG becomes defined as empty */
         /* i.e. no register variables   */
 #else
 #define REG register
 #endif

 void Proc_1 (REG Rec_Pointer Ptr_Val_Par);
 void Proc_2 (One_Fifty *Int_Par_Ref);
 void Proc_3 (Rec_Pointer *Ptr_Ref_Par);
 void Proc_4 ();
 void Proc_5 ();
 void Proc_6 (Enumeration Enum_Val_Par, Enumeration *Enum_Ref_Par);
 void Proc_7 (One_Fifty Int_1_Par_Val, One_Fifty Int_2_Par_Val,
                                              One_Fifty *Int_Par_Ref);
 void Proc_8 (Arr_1_Dim Arr_1_Par_Ref, Arr_2_Dim Arr_2_Par_Ref,
                               int Int_1_Par_Val, int Int_2_Par_Val);

 Boolean Func_2 (Str_30 Str_1_Par_Ref, Str_30 Str_2_Par_Ref);


 /* variables for time measurement: */

 #define Too_Small_Time 2
                 /* Measurements should last at least 2 seconds */

uint64_t        User_Time;

 uint64_t          Microseconds,
                 Dhrystones_Per_Second,
                 Vax_Mips;

 /* end of variables for time measurement */

Rec_Type heap1;
Rec_Type heap2;




char *lstrcpy(char *dest, const char *src){
  char *d = (char *) dest;
  char *s = (char *) src;
  while (*s != 0) {
    *d++ = *s++;
  }

  return dest;
}




 void dhrystone ( void )
 /*****/

   /* main program, corresponds to procedures        */
   /* Main and Proc_0 in the Ada version             */
 {

         One_Fifty   Int_1_Loc;
   REG   One_Fifty   Int_2_Loc;
         One_Fifty   Int_3_Loc;
   REG   char        Ch_Index;
         Enumeration Enum_Loc;
         Str_30      Str_1_Loc;
         Str_30      Str_2_Loc;
   REG   int         Run_Index;
   REG   int         Number_Of_Runs;
         int         count = 1;

/***********************************************************************
 *         Change for compiler and optimisation used                   *
 ***********************************************************************/

   /* Next_Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type)); */
   /* Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type)); */
   Next_Ptr_Glob = (Rec_Pointer) &heap1;
   Ptr_Glob = (Rec_Pointer) &heap2;

   Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
   Ptr_Glob->Discr                       = Ident_1;
   Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
   Ptr_Glob->variant.var_1.Int_Comp      = 40;
   lstrcpy (Ptr_Glob->variant.var_1.Str_Comp,
           "DHRYSTONE PROGRAM, SOME STRING");
   lstrcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

   Arr_2_Glob [8][7] = 10;
         /* Was missing in published program. Without this statement,   */
         /* Arr_2_Glob [8][7] would have an undefined value.            */
         /* Warning: With 16-Bit processors and Number_Of_Runs > 32000, */
         /* overflow may occur for this array element.                  */

    /* getDetails(); */


   Number_Of_Runs = 100000;

   do
   {

       Number_Of_Runs = Number_Of_Runs * 2;
       count = count - 1;
       Arr_2_Glob [8][7] = 10;

       /***************/
       /* Start timer */
       /***************/

       //puts("Starting\n");
       start_time();

       for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
       {

         Proc_5();
         Proc_4();
           /* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
         Int_1_Loc = 2;
         Int_2_Loc = 3;
         lstrcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
         Enum_Loc = Ident_2;
         Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc);
           /* Bool_Glob == 1 */
         while (Int_1_Loc < Int_2_Loc)  /* loop body executed once */
         {
           Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
             /* Int_3_Loc == 7 */
           Proc_7 (Int_1_Loc, Int_2_Loc, &Int_3_Loc);
             /* Int_3_Loc == 7 */
           Int_1_Loc += 1;
         }   /* while */
            /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
         Proc_8 (Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);
           /* Int_Glob == 5 */
         Proc_1 (Ptr_Glob);
         for (Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
                              /* loop body executed twice */
         {
           if (Enum_Loc == Func_1 (Ch_Index, 'C'))
               /* then, not executed */
             {
               Proc_6 (Ident_1, &Enum_Loc);
               lstrcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
               Int_2_Loc = Run_Index;
               Int_Glob = Run_Index;
             }
         }
           /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
         Int_2_Loc = Int_2_Loc * Int_1_Loc;
	 //Int_1_Loc = Int_2_Loc / Int_3_Loc;       TODO : implementations of division
         Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
           /* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
         Proc_2 (&Int_1_Loc);
           /* Int_1_Loc == 5 */

       }   /* loop "for Run_Index" */

       /**************/
       /* Stop timer */
       /**************/

       end_time();
       User_Time = milliSecs;

       if (User_Time > 2)
       {
             count = 0;
       }
       else
       {
             if (User_Time < 50)
             {
                  Number_Of_Runs = Number_Of_Runs * 5;
             }
       }

       print64(User_Time);
       puts("\r\n");

   }   /* calibrate/run do while */
   while (count >0);

   return;
 }

 void Proc_1 (REG Rec_Pointer Ptr_Val_Par)
 /******************/

     /* executed once */
 {
   REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;
                                         /* == Ptr_Glob_Next */
   /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
   /* corresponds to "rename" in Ada, "with" in Pascal           */

   structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob);
   Ptr_Val_Par->variant.var_1.Int_Comp = 5;
   Next_Record->variant.var_1.Int_Comp
         = Ptr_Val_Par->variant.var_1.Int_Comp;
   Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
   Proc_3 (&Next_Record->Ptr_Comp);
     /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp
                         == Ptr_Glob->Ptr_Comp */
   if (Next_Record->Discr == Ident_1)
     /* then, executed */
   {
     Next_Record->variant.var_1.Int_Comp = 6;
     Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp,
            &Next_Record->variant.var_1.Enum_Comp);
     Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
     Proc_7 (Next_Record->variant.var_1.Int_Comp, 10,
            &Next_Record->variant.var_1.Int_Comp);
   }
   else /* not executed */
     structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
 } /* Proc_1 */


 void Proc_2 (One_Fifty *Int_Par_Ref)
 /******************/
     /* executed once */
     /* *Int_Par_Ref == 1, becomes 4 */

 {
   One_Fifty  Int_Loc;
   Enumeration   Enum_Loc;

   Int_Loc = *Int_Par_Ref + 10;
   do /* executed once */
     if (Ch_1_Glob == 'A')
       /* then, executed */
     {
       Int_Loc -= 1;
       *Int_Par_Ref = Int_Loc - Int_Glob;
       Enum_Loc = Ident_1;
     } /* if */
   while (Enum_Loc != Ident_1); /* true */
 } /* Proc_2 */


 void Proc_3 (Rec_Pointer *Ptr_Ref_Par)
 /******************/
     /* executed once */
     /* Ptr_Ref_Par becomes Ptr_Glob */

 {
   if (Ptr_Glob != Null)
     /* then, executed */
     *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
   Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
 } /* Proc_3 */


void Proc_4 () /* without parameters */
 /*******/
     /* executed once */
 {
   Boolean Bool_Loc;

   Bool_Loc = Ch_1_Glob == 'A';
   Bool_Glob = Bool_Loc | Bool_Glob;
   Ch_2_Glob = 'B';
 } /* Proc_4 */


 void Proc_5 () /* without parameters */
 /*******/
     /* executed once */
 {
   Ch_1_Glob = 'A';
   Bool_Glob = false;
 } /* Proc_5 */


         /* Procedure for the assignment of structures,          */
         /* if the C compiler doesn't support this feature       */
 #ifdef  NOSTRUCTASSIGN
 memcpy (d, s, l)
 register char   *d;
 register char   *s;
 register int    l;
 {
         while (l--) *d++ = *s++;
 }
 #endif
