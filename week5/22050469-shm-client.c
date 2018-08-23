/*
 * Shared Memory Client Process as per D.A. Curry `Using C on the Unix System'
 * shm-clinet-test.c
 * Author: C. Kopp
 * (c) 2004, Monash University, SCCSE
 *
 * $Id: MyID-client-template.c,v 1.2 2015/08/17 06:53:03 carlo Exp carlo $
 *
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include "segment.h"

#include <unistd.h>


int main()
{

	int
		shmid;
	key_t
		mykey;
	void *
    	shmat(int shmid, const void *addr, int flag);
	int
		shmdt(const void *shmaddr);
	SEG_DATA
		*shm, *mydata;

	int z;
	/*
	 * The shared memory segment is identified by SEGMENTID
	 */
	mykey = SEGMENTID;

	/*
	 * here we create the shared memory segment using the `shmget' system call.
	 */
	 if( (shmid = shmget( mykey, sizeof(SEG_DATA), IPC_CREAT | 0666)) < 0 )
 		{
 		perror("shmget: cannot create shared memory segment; exiting now");
 		exit(1);
 		}

	/*
	 * We must now map the segment into our process address space using the
	 * `shmat' [attach] system call.
	 */
	 if( (shm = (SEG_DATA *)shmat( shmid, NULL, 0)) == ((SEG_DATA *)-1) )
 		{
 		perror("shmat: cannot attach shared memory segment; exiting now");
 		exit(1);
 		}
//start of working
	 fprintf(stdout, "Reading from Server Process SHM\n");
	 mydata = shm;
	 int client;
	 printf("present before setting client: %d\n", mydata->present);
	 for (int i = 0; i < 4; i++){// i = 0: 0000 & 0001 == 0000, i = 1: 0000 & 0010, i = 2: 0000 & 0100, i = 3: 0000 & 1000

		 if ((mydata->present | (1<<i)) != mydata->present){
			 client = i;
			 printf("client: %d\n", client);
			 break;
		 }//one at a time, now just checking if clients work with no safety measures
		 //wait?

	 }

	 switch (client){
		case 0:
			while (mydata->mylock != 0){
				pause();
			}
			// if (mydata->mylock == 0){
			// 	printf("client 1 on\n");
			// 	mydata->mylock = 1;
			// 	mydata->present |= CLIENT_1; //1010 | 0001 = 1011 (11)
			// 	mydata->exit &= ~(CLIENT_1);
			// 	mydata->mylock = 0;
			// }
			printf("client 1 on\n");
			mydata->mylock = 1;
			mydata->present |= CLIENT_1; //1010 | 0001 = 1011 (11)
			mydata->exit &= ~(CLIENT_1);
			mydata->mylock = 0;
			break;
		case 1:
			while (mydata->mylock != 0){
				pause();
			}
			printf("client 2 on\n");
			mydata->mylock = 1;
			mydata->present |= CLIENT_2;
			mydata->exit &= ~(CLIENT_2);
			mydata->mylock = 0;
			break;
		case 2:
			while (mydata->mylock != 0){
				pause();
			}
			printf("client 3 on\n");
			mydata->mylock = 1;
			mydata->present |= CLIENT_3;
			mydata->exit &= ~(CLIENT_3);
			mydata->mylock = 0;
			break;
		case 3:
			while (mydata->mylock != 0){
				pause();
			}
			printf("client 4 on\n");
			mydata->mylock = 1;
			mydata->present |= CLIENT_4;
			mydata->exit &= ~(CLIENT_4);
			mydata->mylock = 0;
			break;
		default:
			printf("not yet tested\n");
		}

	 printf("clients after setting client: %d\n", mydata->present);

	 while (z != 1){
		 printf("enter code: ");
		 scanf("%d", &z);
		 if (z == 0){
			 printf("RPM = %d\n", mydata->rpm);
			 printf("Crank Angle = %d\n", mydata->crankangle);
			 printf("Throttle Setting = %d\n", mydata->throttle);
			 printf("Fuel Flow = %d\n", mydata->fuelflow);
			 printf("Engine Temp = %d\n", mydata->temp);
			 printf("Fan Speed = %d\n", mydata->fanspeed);
			 printf("Oil Pressure = %d\n", mydata->oilpres);
			 printf("\n");
		 }
		 if (z == 1){
			 switch (client){
				case 0:
					while (mydata->mylock != 0){
						pause();
					}
					printf("client 1 off\n");
					mydata->mylock = 1;
					mydata->present ^= CLIENT_1;
					mydata->exit |= CLIENT_1;
					mydata->mylock = 0;
					break;
				case 1:
					while (mydata->mylock != 0){
						pause();
					}
					printf("client 2 off\n");
					mydata->mylock = 1;
					mydata->present ^= CLIENT_2;
					mydata->exit |= CLIENT_2;
					mydata->mylock = 0;
					break;
				case 2:
					while (mydata->mylock != 0){
						pause();
					}
					printf("client 3 off\n");
					mydata->mylock = 1;
					mydata->present ^= CLIENT_3;
					mydata->exit |= CLIENT_3;
					mydata->mylock = 0;
					break;
				case 3:
					while (mydata->mylock != 0){
						pause();
					}
					printf("client 4 off\n");
					mydata->mylock = 1;
					mydata->present ^= CLIENT_4;
					mydata->exit |= CLIENT_4;
					mydata->mylock = 0;
					break;
				default:
					printf("not yet tested\n");
				}
		 }
	 }//server is exiting when all 4 clients switch on

	/*
	 * We must now unmap the segment into our process address space using the
	 * `shmdt' [detach] system call.
	 */
	 if( (shmid = shmdt( shm )) == (-1) )
 		{
 		perror("shmdt: cannot detach shared memory segment; exiting now");
 		exit(1);
 		}

	fprintf(stdout, "Task completed\n");
	exit(0);

}
