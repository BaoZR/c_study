#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stdatomic.h>

//来自第五课 大道并行：创建和管理线程
//体验三种情况，无锁，mutex锁，atomic锁，加一的情况
//注意要在多于一个cpu的情况下运行

char msg_brd[100];

volatile long total_progress = 0;
pthread_mutex_t prog_mutex;

#define GE_FLAG_WILD 1
#define GE_FLAG_ATOMIC 2

unsigned int flags = 0;

int usage()
{
	printf("gepthread <thread num> -<cmd char>\n"
	"cmd char:\n"
	"w - without lock\n"
	"a - atomic lock\n"
	"defalut - mutex lock\n");
}


void inc_progress()
{
	pthread_mutex_lock(&prog_mutex);
	total_progress++;
	pthread_mutex_unlock(&prog_mutex);
}

void inc_progress_wild()
{
	total_progress++;
}

void inc_progress_atomic()
{
	atomic_fetch_add_explicit(&total_progress,1,memory_order_relaxed);
}


void * ge_worker(void* ctx)
{
    int i = 0;
	// work to do
	for(i = 0;i<1000;i++)
	{
		if(flags & GE_FLAG_WILD)
			inc_progress_wild();
		else if(flags & GE_FLAG_ATOMIC)
			inc_progress_atomic();
		else
			inc_progress();
	}
		
	
	snprintf(msg_brd, sizeof(msg_brd),"worker thread %d left this msg.\n",gettid());
	return (void*)(long)8888;
}


int main(int argc, char* argv[])
{
	int ret,i, child_count = 10;
	pthread_t *ptids;
	void* pret;
	
	if(argc > 1 && atoi(argv[1]) == 0)
		return usage();
	if(argc > 2 && (argv[2][1] != 'a' && argv[2][1] != 'w') )
		return usage();
	if(argc > 1)
		child_count = atoi(argv[1]);
	if(argc > 2){
		if(strcmp(argv[2],"-w") == 0)
		 	flags |= GE_FLAG_WILD;
		if(strcmp(argv[2],"-a") == 0)
			flags |= GE_FLAG_ATOMIC;
	}
		
	ptids = malloc(child_count * sizeof(pthread_t));
	pthread_mutex_init(&prog_mutex,NULL);
	
	
	for(i = 0;i < child_count; i++)
	{
		ret = pthread_create(&ptids[i], NULL,ge_worker, NULL);
		if(ret != 0){
			printf("create thread failed with %d\n",ret);
			exit(-1);
		}	
		printf("created child thread ptid = %ld\n",ptids[i]);
	}
	
	for(i = 0;i<child_count;i++){
		
		pthread_join(ptids[i],&pret );
		printf("joined with child %ld, its return %p\n",ptids[i],pret);
	}
	
	printf("joined with all children, total_progress %ld\n",total_progress);
	
	pthread_mutex_destroy(&prog_mutex);
	return 0;
	
	
}

