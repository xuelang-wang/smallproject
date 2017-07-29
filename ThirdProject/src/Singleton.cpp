/*
 * Singleton.cpp
 *
 *  Created on: 2017年7月29日
 *      Author: xiaoquan
 */

#include "Singleton.h"
#include<iostream>
#include<cstdlib>


// 类的静态成员变量要在类体外进行定义
Manager* Manager::m_pStatic = NULL;

Manager::Manager() {
	// TODO Auto-generated constructor stub

}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}

// 静态成员函数,提供全局访问的接口
Manager * Manager::GetManager(){
	if(NULL == m_pStatic){
		m_pStatic =  new Manager();
	}
	return m_pStatic;
}

void Manager::test(){
	std::cout << "Test Manager!\n";
}
