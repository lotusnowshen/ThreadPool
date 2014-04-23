/*
 * ThreadPool.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: wing
 */

#include "ThreadPool.h"

/*
 * 构造函数除了初始化每个成员变量之外
 * 还需要依次对线程数组中的每个线程注册自身
 */
ThreadPool::ThreadPool(std::vector<WorkThread>::size_type max_thread) :
		_task_queue(), _max_thread(max_thread), _thread_vector(_max_thread), _is_started(
				false), _lock(), _cond(&_lock)

{
	for (std::vector<WorkThread>::iterator iter = _thread_vector.begin();
			iter != _thread_vector.end(); ++iter) {
		//注册线程池
		iter->register_thread_pool(this);
	}

}

ThreadPool::~ThreadPool() {
	stop_thread_pool();
}

void ThreadPool::start_thread_pool() {
	if (_is_started == false) {
		/*
		 * 下面这行代码必须放在开头，防止线程启动后
		 * 因为is_start这个变量异常退出
		 */
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
	/*
	 * 这句话同样必须放在开头，以便于线程及时退出
	 */
	_is_started = false;
	/*
	 * 用来激活所有正在等待任务的线程
	 * 让它们退出循环，同时检测到布尔值的变化
	 * 而使得线程退出
	 */
	_cond.notify_all();

	for (std::vector<WorkThread>::iterator iter = _thread_vector.begin();
			iter != _thread_vector.end(); ++iter) {
		iter->join();
	}
	//清空队列
	while(!_task_queue.empty()){
		_task_queue.pop();
	}
}

bool ThreadPool::get_task_queue(Task &task) {
	_lock.lock();

	/*
	 * 这里必须使用while循环
	 */
	while (_is_started && _task_queue.empty()) {
		_cond.wait();
	}
	/*
	 * 这里布尔值为false存在三种情况：
	 * 1.运行到这里线程池还没有开启
	 * 2.线程拿到了任务，退出了循环，但是线程池此刻关闭
	 * 3.线程正在等待任务，被stop函数中的notify_all函数
	 * 所激活，此时需要退出
	 */
	if (_is_started == false) {
		_lock.unlock();
		return false;
	}

	task = _task_queue.front();
	_task_queue.pop();
	_lock.unlock();
	return true;
}
/*
 * 向任务队列中添加任务
 */
bool ThreadPool::add_task_queue(Task task) {
	_lock.lock();

	bool ret = false;
	if (_is_started) {
		_task_queue.push(task);
		//激活某个正在等待任务的线程
		_cond.notify();
		ret = true;
	}

	_lock.unlock();
	return ret;
}

bool ThreadPool::is_task_queue_empty() const{
	_lock.lock();
	bool ret = _task_queue.empty();
	_lock.unlock();
	return ret;
}
std::queue<Task>::size_type ThreadPool::get_task_queue_size() const{
	_lock.lock();
	std::queue<Task>::size_type ret = _task_queue.size();
	_lock.unlock();
	return ret;
}

