/*
 * WorkThread.h
 *
 *  Created on: Apr 23, 2014
 *      Author: wing
 */

#ifndef WORKTHREAD_H_
#define WORKTHREAD_H_

#include <pthread.h>
#include "Thread.h"

class ThreadPool;

class WorkThread: public Thread {

public:
	void run();
	void register_thread_pool(ThreadPool *p_thread_pool);
	void compute_task(int num);

private:
	ThreadPool *_p_thread_pool;


};

#endif /* WORKTHREAD_H_ */
