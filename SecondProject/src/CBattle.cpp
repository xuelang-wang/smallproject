/*
 * CBattle.cpp
 *
 *  Created on: 2017年7月20日
 *      Author: xiaoquan
 */

#include "CBattle.h"
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;


CBattle::CBattle() {
	CH = new CHero();
	CE = new CEnemy();
}

CBattle::~CBattle() {
	delete CH;
	delete CE;
}

void CBattle::fight(){
	//jump动作意味下次对方动作无效（包括jump）

	srand(time(0));
	show();
	cout << "Fight Start:\n";
	int priority = rand()%2;//优先攻击权，产生随机数0-1,0代表英雄先出手，1代表敌人先出手

	int H_index,E_index;
	//随机数H_index产生的范围为0-3，依次表示英雄的出招招式 ：武器攻击，跳跃，踢腿，抱摔
	//随机数E_index产生的范围为0-3，依次表示敌人的出招招式：武器攻击，跳跃，劈掌，连环腿

	bool H_dead = false;//代表英雄没死（活的）
	bool E_dead = false;//代表敌人没死(活的）

	bool H_jump = false;//英雄是否跳跃
	bool E_jump = false;//敌人是否跳跃

	while(1){
		if(priority == 0){
			if(!E_jump){
				H_index = rand() % 4;
				switch(H_index){
				case 0 : E_dead = CH->attack(*CE); break;
				case 1 : H_jump = CH->jump();break;
				case 2 : E_dead = CH->kick(*CE);break;
				default : E_dead = CH->counter(*CE);break;
				}
			}else{
				E_jump = false;
				cout << CH->getname() << " miss!!!\n";
			}
			priority = 1;
			show();
		}else{
			if(!H_jump){
				E_index = rand() % 4;
				switch(E_index){
				case 0 : H_dead = CE->attack(*CH);break;
				case 1 : E_jump = CE->jump();break;
				case 2 : H_dead = CE->chop(*CH);break;
				default : H_dead = CE->catching(*CH);break;
				}
			}else{
				H_jump = false;
				cout << CE->getname() << " miss!!!\n";
			}
			priority = 0;
			show();
		}
		if(H_dead){
			CE->addexp(Hero_EXP_Per[CH->getLv()]);
			cout << "The hero died!!!";
			break;
		}
		if(E_dead){
			CH->addexp(Enemy_EXP_Per[CE->getLv()]);
			cout << "The enemy died!!!";
			break;
		}
	}
	cout << "Battle finish!!!\n";
}

void CBattle::show(){
	cout << "The two sides battle situation：\n";
	cout << CH->getname() << string(6,' ') << CE->getname() << "\n";
	cout << "HP: " << CH->getHP() << string(3,' ') << "HP: " << CE->getHP() << "\n";
	cout << "ATK: " << CH->getATK() << string(4,' ') << "ATK: " << CE->getATK() << "\n";
	cout << "DEF: " << CH->getDEF() << string(4,' ') << "DEF: " << CE->getDEF() << "\n";
	cout << "Lv: " << CH->getLv() << string(5,' ') << "Lv: " << CE->getLv() << "\n";
	cout << "EXP: " << CH->getEXP() << string(4,' ') << "EXP: " << CE->getEXP() << "\n";
}
