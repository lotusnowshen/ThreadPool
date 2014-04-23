/*
 * noncopyable.h
 *
 *  Created on: Apr 22, 2014
 *      Author: wing
 */

#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_

/*
 * 把拷贝构造函数和赋值运算符设为私有，是为了防止对象的复制
 * 把构造函数和析构函数设为protected，是防止生成本类的对象
 */
class noncopyable {

protected:
	noncopyable() {

	}
	~noncopyable() {

	}

private:
	noncopyable(const noncopyable&);
	noncopyable &operator=(const noncopyable &);
};

#endif /* NONCOPYABLE_H_ */
