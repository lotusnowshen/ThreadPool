/*
 * ThreadPool.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: wing
 */

#include "ThreadPool.h"

ThreadPool::ThreadPool(std::vector<WorkThread>::size_type max_thread) :
		_task_queue(), _max_thread(max_thread), _thread_vector(_max_thread), _is_started(
				false), _lock(), _cond(&_lock)

{
	for (std::vector<WorkThread>::iterator iter = _thread_vector.begin();
			iter != _thread_vector.end(); ++iter) {
		iter->register_thread_pool(this);
	}

}

ThreadPool::~ThreadPool() {
	stop_thread_pool();
}

void ThreadPool::start_thread_pool() {
	if (_is_started == false) {
		_is_started = true;  // first
		for (std::vector<WorkThread>::iterator iter = _thread_vector.begin();
				iter != _thread_vector.end(); ++iter) {
			iter->start();
		}

	}
}
void ThreadPool::stop_thread_pool() {
	if (_is_started == false) {
		return;
	}

	_is_started = false;     //
	_cond.notify_all();

	for (std::vector<WorkThread>::iterator iter = _thread_vector.begin();
			iter != _thread_vector.end(); ++iter) {
		iter->join();
	}
	while(!_task_queue.empty()){
		_task_queue.pop();
	}
}

bool ThreadPool::get_task_queue(Task &task) {
	_lock.lock();
	while (_is_started && _task_queue.empty()) {
		_cond.wait();
	}

	if (_is_started == false) {
		_lock.unlock();
		return false;
	}

	task = _task_queue.front();
	_task_queue.pop();
	_lock.unlock();
	return true;
}

bool ThreadPool::add_task_queue(Task task) {
	_lock.lock();

	bool ret = false;
	if (_is_started) {
		_task_queue.push(task);
		_cond.notify();
		ret = true;
	}

	_lock.unlock();
	return ret;
}

bool ThreadPool::is_task_queue_empty() {
	_lock.lock();
	bool ret = _task_queue.empty();
	_lock.unlock();
	return ret;
}
std::queue<Task>::size_type ThreadPool::get_task_queue_size() {
	_lock.lock();
	std::queue<Task>::size_type ret = _task_queue.size();
	_lock.unlock();
	return ret;
}

