/*
 * Thread.h
 *
 *  Created on: Apr 22, 2014
 *      Author: wing
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include <stdexcept>

class Thread {

public:
	Thread();
	virtual ~Thread();

	void start();
	void join();
	static void *thread_func(void *);
	virtual void run() = 0;
	pthread_t get_tid() const;

protected:
	pthread_t _tid;
};

#endif /* THREAD_H_ */
