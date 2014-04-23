/*
 * Condition.h
 *
 *  Created on: Apr 22, 2014
 *      Author: wing
 */

#ifndef CONDITION_H_
#define CONDITION_H_

#include "noncopyable.h"
#include <pthread.h>
#include "MutexLock.h"

class Condition: public noncopyable {
public:

	Condition(MutexLock *p_lock);
	~Condition();

	void wait();
	void notify();
	void notify_all();

private:
	pthread_cond_t _cond;
	MutexLock *_p_lock;

};

#endif /* CONDITION_H_ */
