/*
 * main.cpp
 *
 *  Created on: 2017年7月29日
 *      Author: xiaoquan
 */

#include"Singleton.h"
#include"Factory.h"

int main(){


	//第2题测试
	// 不用初始化类对象就可以访问了
	Manager * p = Manager::GetManager();
	p->test();

	//第4题测试
	// 生产Player实现
	PlayerFactory *pPlayerFactory = new PlayerFactory;
	Actor *pPlayer = pPlayerFactory->CreateActor();

	// 生产Demon实现
	DemonFactory *pDemonFactory = new DemonFactory;
	Actor *pDemon = pDemonFactory->CreateActor();

	// 生产Fairy实现
	FairyFactory * pFairyFactory = new FairyFactory;
	Actor *pFairy = pFairyFactory->CreateActor();

	// 生产Civilian实现
	CivilianFactory *pCivilianFactory = new CivilianFactory;
	Actor *pCivilian = pCivilianFactory->CreateActor();

	delete pPlayerFactory;
	delete pPlayer;
	delete pDemonFactory;
	delete pDemon;
	delete pFairyFactory;
	delete pFairy;
	delete pCivilianFactory;
	delete pCivilian;

	return 0;
}


