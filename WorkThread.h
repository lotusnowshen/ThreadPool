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
	void register_thread_pool(ThreadPool *p_thread_pool); //注册线程池
	void compute_task(int num);   //实际的工作函数，由run来调用

private:
	ThreadPool *_p_thread_pool; //线程池的指针，用来指定线程去哪里获取任务


};

#endif /* WORKTHREAD_H_ */
