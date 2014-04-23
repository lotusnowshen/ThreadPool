/*
 * Thread.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: wing
 */

#include "Thread.h"



Thread::Thread() :
		_tid(0) {

}
Thread::~Thread() {

}

void Thread::start() {
	pthread_create(&_tid, NULL, Thread::thread_func, this);
}
void Thread::join() {
	pthread_join(_tid, NULL);
}
void *Thread::thread_func(void *arg) {
	Thread *p_thread = static_cast<Thread*>(arg);
	p_thread->run();
	return NULL;
}

#include <iostream>
void Thread::run() {

	while (1) {
		std::cout << "run" << std::endl;
	}
}
pthread_t Thread::get_tid() const {
	return _tid;
}
