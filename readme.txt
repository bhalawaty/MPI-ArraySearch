Kevin Carlisle
CS 131
Lab 2

Readme File

Array Search Using MPI.

Part A 
	Write an MPI program to search an array of strings for a given pattern. 
	Each MPI task works on a seperate slice of the array. Produce the 
	location of the string in the array.
	The input file defines the number of tasks (NT) in the first line, 
	the number of slices (NS) in the second line, the search string in 
	the third line. The remaining 100k lines in the input file contain 
	strings (up to 15 char in length).
	A master task reads 3 parameters into variables and the string file
	into the seach array declared in your program.
	The master task (mpi_rank = 0) distributes the array in slices to all tasks
	(slice i to task i) (NT = NS). Use MPI_Scatter() to do this.
	Each task checks for the exact match with the search string in its slice 
	and sends the answer back to the master. 
	After all tasks complete execution, the master task writes the results
	of each thread to an output file, followed by the total execution time
	(in milliseconds) of the program. Use MPI_W time for timing. 


Part B 
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