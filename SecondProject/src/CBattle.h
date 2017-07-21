/*
 * CBattle.h
 *
 *  Created on: 2017年7月20日
 *      Author: xiaoquan
 */

#ifndef CBATTLE_H_
#define CBATTLE_H_

#include"Roler.h"

class CBattle{
private:
	CHero  *CH;//英雄
	CEnemy *CE;//敌人
public:
	CBattle();
	~CBattle();

	void fight();//战斗
	void show();//显示上方状态
};

#endif /* CBATTLE_H_ */
