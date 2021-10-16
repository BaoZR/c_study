//g++ -g3 -o gethread gethread.cpp -lpthread
//用c++写的线程锁操作

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <cstring>
#include <atomic>

#define FLAG_WITHOUT_LOCK 1
#define FLAG_AUTOMIC_LOCK 2
#define FLAG_MUTEX_LOCK   4

std::mutex scr_lock;
volatile long g_count = 0;
std::atomic<int> g_count_atomic(0);
int flag = 0;

int usage()
{
	std::cout	<< "usage: \n"
				<< "./gethread <thread number> -<cmd>\n"
				<< "m - mutex lock\n"
				<< "a - atomic lock\n"
				<< "w - without lock\n"
				<< std::endl;	
	return 0;
}


void inc_process_mutex()
{
	scr_lock.lock();
	g_count++;
	scr_lock.unlock();
	return;
}

void inc_process_wild()
{
	g_count++;
	return;
}

void inc_process_atomic()
{
	std::atomic_fetch_add(&g_count_atomic,1);
	return;
}

void ge_worker(int n)
{
	std::cout << "thread " << n << " is running..." << std::endl;
	for(int i=0;i<1000;i++)
	{
		if(flag & FLAG_WITHOUT_LOCK)
			inc_process_wild();
		if(flag & FLAG_AUTOMIC_LOCK)
			inc_process_atomic();
		if(flag & FLAG_MUTEX_LOCK)
			inc_process_mutex();
	}
	
	
	return;
	
}

int main(int argc, char* argv[])
{
	int child_count = 10;
	std::vector<std::thread> threads;
	
	if(argc != 3 || (atoi(argv[1]) == 0))
	{
		return usage();
	}
	
	child_count = atoi(argv[1]);
	
	if(strcmp(argv[2],"-m") == 0)
		flag |= FLAG_MUTEX_LOCK;
	else if(strcmp(argv[2],"-a") == 0)
		flag |= FLAG_AUTOMIC_LOCK;
	else if(strcmp(argv[2],"-w") == 0)
		flag |= FLAG_WITHOUT_LOCK;
	else
		return usage();
	
	
	for(int i = 0 ; i<child_count;i++)
	{
		threads.push_back(std::thread(ge_worker, i));
	}
	for(int i = 0; i< child_count;i++)
	{
		threads[i].join();
	}
	
	//show
	if(flag & FLAG_AUTOMIC_LOCK)
	{
		std::cout<< "g_count_atomic: " << g_count_atomic <<std::endl;
	}else{
		std::cout<< "g_count: " << g_count <<std::endl;
	}
	
	std::cout << "main thread is quiting." << std::endl;
	return 0;

}





