//KEVIN CARLISLE
//CS 131
//LAB 2 
// PROGRAM B
// MY_BARRIER
// MAY 8th, 2015


/*
	Implement a function my_barries using point-to-point communication
	e.g. Send/Recv functions. My_barrier takes no parameters and should 
	function the exact same way as MPI's MPI_Barrier.
	Your implemenattion should do the following. The master task (rank=0)
	executing my_barrier wait for all other tasks in its Comm_world to 
	send it a message to inform them that barrier is completed. The master 
	can then continue past my_barrier and measure the time taken.
	All other nodes executing my_barrier 
		 A) send a message with its rank to the master task
		 B) then wait until they receive a message from the master that
			the barrier is completed. Then can then continue.
	Print to the output file the total time in milliseconds to exeute 
	my_barrier on the master task. 

*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_barrier.c"

int my_barrier();


int main(int argc, char** argv)
{

	int pSize;
	int Rank;
	double iTime;
	double eTime;
	FILE* fWrite;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &pSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);


	if (Rank == 0) {iTime = MPI_Wtime();}
	
	//BARRIER FUNCTION
	my_barrier(MPI_COMM_WORLD);

	if (Rank == 0) {
		eTime = MPI_Wtime();
		fWrite = fopen("out.txt", "w");
		fprintf(fWrite,"RUN TIME = [%f] MS\n", (eTime-iTime)*1000);
		fclose(fWrite);
	}
	
	MPI_Finalize();
	return 0;
}		
int my_barrier()
{

        int nRank;
        int nSize;
        int sNum;
		double rTime = -1;

        MPI_Comm_rank(MPI_COMM_WORLD, &nRank);
        MPI_Comm_size(MPI_COMM_WORLD, &nSize);

        if (nRank == 0)
        {
             sNum = -1;
			double iTime = MPI_Wtime();

            int i;
            for ( i = 1; i < nSize; i++)
            {
                MPI_Recv(&sNum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
                
            for (i = 1; i < nSize; i++)
            {
                MPI_Send(&sNum, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }	
			double eTime = MPI_Wtime();
			rTime = (eTime - iTime) * 1000;
			//printf("-----------[%f]\n", rTime);
        }
        else
        {
			sNum = nRank;
            MPI_Send(&sNum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Recv(&sNum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

   	return 0;     

}

