/*******************************************************************************/
/*  © Université Lille 1, The Pip Development Team (2015-2017)                 */
/*                                                                             */
/*  This software is a computer program whose purpose is to run a minimal,     */
/*  hypervisor relying on proven properties such as memory isolation.          */
/*                                                                             */
/*  This software is governed by the CeCILL license under French law and       */
/*  abiding by the rules of distribution of free software.  You can  use,      */
/*  modify and/ or redistribute the software under the terms of the CeCILL     */
/*  license as circulated by CEA, CNRS and INRIA at the following URL          */
/*  "http://www.cecill.info".                                                  */
/*                                                                             */
/*  As a counterpart to the access to the source code and  rights to copy,     */
/*  modify and redistribute granted by the license, users are provided only    */
/*  with a limited warranty  and the software's author,  the holder of the     */
/*  economic rights,  and the successive licensors  have only  limited         */
/*  liability.                                                                 */
/*                                                                             */
/*  In this respect, the user's attention is drawn to the risks associated     */
/*  with loading,  using,  modifying and/or developing or reproducing the      */
/*  software by the user in light of its specific status of free software,     */
/*  that may mean  that it is complicated to manipulate,  and  that  also      */
/*  therefore means  that it is reserved for developers  and  experienced      */
/*  professionals having in-depth computer knowledge. Users are therefore      */
/*  encouraged to load and test the software's suitability as regards their    */
/*  requirements in conditions enabling the security of their systems and/or   */
/*  data to be ensured and,  more generally, to use and operate it in the      */
/*  same conditions as regards security.                                       */
/*                                                                             */
/*  The fact that you are presently reading this means that you have had       */
/*  knowledge of the CeCILL license and that you accept its terms.             */
/*******************************************************************************/

#include <stdint.h>
#include <pip/fpinfo.h>
#include <pip/paging.h>
#include <pip/vidt.h>
#include <pip/api.h>
#include <pip/compat.h>
#include <queue.h>

extern int printf(const char *c,...);
#define returnServiceAddress 0x801000

struct sbrkService{
  uint32_t size;
  uint32_t begin;
};
typedef struct xQueueReceiveParameters_s xQueueReceiveParameters;

INTERRUPT_HANDLER(serviceRoutineAsm,serviceRoutine)
  printf("Service routing return\r\n");
  printf("Data from service at %x",data1);

END_OF_INTERRUPT



struct comCanal
{
  uint32_t numberOfChannels;
  uint32_t * listOfChannel;
};



void parse_bootinfo(pip_fpinfo* bootinfo)
{
    if(bootinfo->magic == FPINFO_MAGIC)
        printf("\tBootinfo seems to be correct.\r\n");
    else {
        printf("\tBootinfo is invalid. Aborting.\r\n");
    }


    printf("\tAvailable memory starts at 0x%x and ends at 0x%x\r\n",(uint32_t)bootinfo->membegin,(uint32_t)bootinfo->memend);

    printf("Bootinfo ok\r\n");
    return;
}

struct AMessage
{
    char ucMessageID;
    char ucData[ 20 ];
};
void main()
{
    int i;
    pip_fpinfo * bootinfo = (pip_fpinfo*)0xFFFFC000;
    //Get Bootinfo for the available memory
    parse_bootinfo(bootinfo);

    uint32_t * parameters = (uint32_t*)0xFFFFA000;

    for(i=0;i<5;i++){
      printf("%x\r\n",parameters[i]);
    }
    //Initialize the avaible pages
    printf("Init paging\r\n");
    uint32_t paging = initPaging((void*)bootinfo->membegin,(void*)bootinfo->memend);
    printf("Begining work! \r\n");
    printf("Test queue creating\r\n");
    uint32_t queue = xProtectedQueueCreate(10,sizeof(struct AMessage));


    printf("Test sending\r\n");
    struct AMessage * data =(struct AMessage*) allocPage();
    data->ucMessageID = 0x11;

    for(i=0;i<20;i++)
      data->ucData[i] = i;

    xProtectedQueueSend(queue,(uint32_t)data,100);


    printf("Test receiving\r\n");

    struct AMessage * recData = (struct AMessage*) allocPage();

    xProtectedQueueReceive(queue,(uint32_t)recData,100);
    printf("Received something\r\n");
    printf("ID : %x",recData->ucMessageID);
    printf("Data : {");
    for(i=0;i<20;i++)
      printf("%x ",recData->ucData[i]);




    printf("Back to execution\r\n");

    for(;;);

}
