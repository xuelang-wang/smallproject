/*
 * Singleton.h
 *
 *  Created on: 2017年7月29日
 *      Author: xiaoquan
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

class Manager {
private:
	// 静态成员变量,提供全局惟一的一个实例
	static Manager *m_pStatic;
public:
	Manager();
	virtual ~Manager();

	// 静态成员函数,提供全局访问的接口
	static Manager * GetManager();

	void test();
};

#endif /* SINGLETON_H_ */
