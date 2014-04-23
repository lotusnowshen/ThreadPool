#include "ThreadPool.h"
#include <stdlib.h>
#include <unistd.h>
using namespace std;


int main(int argc, char **argv) {
	ThreadPool pool(10);
	pool.start_thread_pool();

	srand(1024);


	while(true){
		Task tmp;
		tmp._num = rand()%100;
		pool.add_task_queue(tmp);
		sleep(1);
	}


	return 0;
}
