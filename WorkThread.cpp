/*
 * WorkThread.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: wing
 */

#include "WorkThread.h"
#include <iostream>
#include "ThreadPool.h"
using namespace std;

void WorkThread::run() {
	while (true) {
		Task task;
		bool ret = _p_thread_pool->get_task_queue(task);
		if (ret == false) {
			return;
		}
		compute_task(task._num);
	}
}

void WorkThread::compute_task(int num) {
	cout << num * num << endl;
}

void WorkThread::register_thread_pool(ThreadPool *p_thread_pool) {
	_p_thread_pool = p_thread_pool;
}
