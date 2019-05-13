===========================================================================
Issues that I ran into

1.
First of all, I need to design a way to split the pixels evenly across multiple threads
The method that I think of is:
Let the thread #n compute column n, column nthread+n, column nthread*2+n, etc
For instance, thread 1 will do the case when px = 1, nthread+1, nthread*2+1, etc
So I modify the first for loop condition from:
	for( int px=0; px<width; px++ )
to:
	for( int px=thread_index; px<width; px+=nthreads )

This method ensures that the outermost iteration of two threads differ at most by 1
Also, when the number of threads exceed the width, threads whose thread index is greater than or equal to the width would not enter the loop, so it will not cause any problems.

2.
When I am writing the function for multiple threads to run, I noticed there are variable that should be accessed by all threads.

So I first think about packing them as a argument struct, and pass the pointer to the struct to the function.

struct argsPack{
	int nthreads;
	scene_t scene;
	float*** all_scaled_color;
	int thread_index;
};

Then I notice the first three variables is the same across all threads, so this is a unnecessary duplicate of resource. 
So I decide to declare them as global variables, and only pass a pointer to the thread_index, which would be different for all threads.

global variables that I declare:
	int nthreads;
	scene_t scene;
	float all_scaled_color[width][height][3];

all_scaled_color is an 3 dimensional array of floating point numbers that stores pixels computed by all threads
The array is printed in proper format in the main function

Signature of parallel_func:
	void* parallel_func(void* index);

a pointer to the thread index is passed into the function

3.
I first wrote my pthread_join as follows:
	pthread_join(&tids[t], NULL);
which produces an compiler warning.
Then I found out the first parameter of pthread_join should be of type int
After editing this line to:
	pthread_join(tids[t], NULL);
The compiler warning is solved.

===========================================================================
performace of multithread implementation of SRT

The time taken by the program using different number of threads is as follows:
time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m43.601s
user    0m43.592s
sys     0m0.002s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m22.640s
user    0m44.947s
sys     0m0.002s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m11.291s
user    0m44.571s
sys     0m0.003s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m5.732s
user    0m44.504s
sys     0m0.003s
mv 8-test.ppm.tmp 8-test.ppm

Approximately, when the number of threads is doubled, the time taken by the SRT is reduced to half. This indicates that my implementation of SRT improves its performace.
