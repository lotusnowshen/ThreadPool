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

struct Task {
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

	bool is_task_queue_empty() const;
	std::queue<Task>::size_type get_task_queue_size() const;

private:
	std::queue<Task> _task_queue;   //任务队列
	std::vector<WorkThread>::size_type _max_thread; //线程的数目
	std::vector<WorkThread> _thread_vector;  //用来存储线程
	bool _is_started;  //标示线程池是否开启

	mutable MutexLock _lock;    //用来保持对队列的互斥操作
	mutable Condition _cond;	//实现对队列任务的同步操作

};

#endif /* THREADPOOL_H_ */
