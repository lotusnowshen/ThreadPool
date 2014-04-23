/*
 * ThreadPool.h
 *
 *  Created on: Apr 23, 2014
 *      Author: wing
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <queue>
#include <vector>
#include "WorkThread.h"
#include "MutexLock.h"
#include "Condition.h"
#include "noncopyable.h"

struct Task{
	int _num;
};

class ThreadPool: public noncopyable {
public:

	ThreadPool(std::vector<WorkThread>::size_type max_thread);
	~ThreadPool();

	void start_thread_pool();
	void stop_thread_pool();

	bool add_task_queue(Task task);
	bool get_task_queue(Task &task);

	bool is_task_queue_empty();
	std::queue<Task>::size_type get_task_queue_size();

private:
	std::queue<Task> _task_queue;
	std::vector<WorkThread>::size_type _max_thread;
	std::vector<WorkThread> _thread_vector;
	bool _is_started;

	MutexLock _lock;
	Condition _cond;

};

#endif /* THREADPOOL_H_ */
