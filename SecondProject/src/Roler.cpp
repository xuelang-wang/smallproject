/*
 * Roler.cpp
 *
 *  Created on: 2017年7月20日
 *      Author: xiaoquan
 */

#include "Roler.h"
#include<iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////
//						基类  CRole 定义
//////////////////////////////////////////////////////////////////////

CRole::CRole(string Init_name,int Init_HP,int Init_ATK,int Init_DEF,int Init_Lv,int Init_EXP) {
	name = Init_name;
	HP = Init_HP;
	ATK = Init_ATK;
	DEF = Init_DEF;
	Lv = Init_Lv;
	EXP = Init_EXP;
}

bool CRole::attack(CRole &CR){
	//武器攻击
	int Damage = ATK - CR.DEF;//攻击的掉血量

	cout << name << " attack " << CR.getname() << " " << Damage << "Hp\n";//显示伤害情况

	if(CR.HP > Damage)
		CR.HP -= Damage;//对方血量足够，能够承受伤害
	else
		CR.HP = 0;//对方血量不够，死亡

	return CR.HP == 0 ? true : false;
}
bool CRole::jump(){//跳跃
	cout << name << " jump.\n";

	return true;
}

string CRole::getname() const{
	return name;
}

int CRole::getHP() const{
	return HP;
}

int CRole::getATK() const{
	return ATK;
}

int CRole::getDEF() const{
	return DEF;
}

int CRole::getLv() const{
	return Lv;
}

int CRole::getEXP() const{
	return EXP;
}

void CRole::chargename(string s){
	cout << "name: "<< name << " ---> " << s << "\n";//显示

	name = s;
}

void CRole::chargeHP(int hp){
	cout << "HP: " << HP << " ---> " << hp << "\n";

	HP = hp;
}

void CRole::chargeATK(int atk){
	cout << "ATK: " << ATK << " ---> " << atk << "\n";

	ATK = atk;
}

void CRole::chargeDEF(int def){
	cout << "DEF: " << DEF << " ---> " << def << "\n";

	DEF = def;
}

void CRole::chargeLv(int lv){
	cout << "Lv: " << Lv << " ---> " << lv << "\n";

	Lv = lv;
}

void CRole::chargeEXP(int exp){
	cout << "EXP: " << EXP << " ---> " << exp << "\n";

	EXP = exp;
}

//////////////////////////////////////////////////////////////////////
//						英雄类  CHero 定义
//////////////////////////////////////////////////////////////////////

CHero::CHero():CRole(Hero_Init_name,Hero_HP_Max[0],Hero_Init_ATK,Hero_Init_DEF,Hero_Init_Lv,Hero_Init_EXP){
	kick_ATK = Init_kick;
	counter_ATK = Init_kick;
}

CHero::~CHero() {

}

bool CHero::kick(CRole & CE){//踢腿
	//踢腿攻击
	int Damage = kick_ATK + getATK() - CE.getDEF();//攻击的掉血量

	cout << getname() << " kick " << CE.getname() << " " << Damage << "Hp\n";//显示伤害情况

	int resHP = CE.getHP() - Damage;//剩余血量
	if(resHP <= 0)//对方血量不够，死亡
		resHP = 0;

	CE.chargeHP(resHP);

	return resHP == 0 ? true : false;
}

bool CHero::counter(CRole & CE){
	//踢腿攻击
	int Damage = counter_ATK + getATK() - CE.getDEF();//攻击的掉血量

	cout << getname() << " counter " << CE.getname() << " " << Damage << "Hp\n";//显示伤害情况

	int resHP = CE.getHP() - Damage;//剩余血量
	if(resHP <= 0)//对方血量不够，死亡
		resHP = 0;

	CE.chargeHP(resHP);

	return resHP == 0 ? true : false;
}


void CHero::addexp(int exp){
	int cur_exp = getEXP() + exp;//获得更新后的经验值
	chargeEXP(cur_exp);
	if(cur_exp >= Hero_EXP_Max[getLv()])
		upgrade();//升级
}

void CHero::upgrade(){
	//当前经验已经超出当前级数的最大经验

	cout << "congratulations!!! " << getname() << " upgrade!!!!\n";

	int curLv = getLv();//当前等级
	if(curLv == Hero_Lv_Max){//已经到最高等级，不能再升
		cout << "Your have are the highest grade.\n";

		chargeHP(Hero_HP_Max[Hero_Lv_Max]);//重新满血
		chargeEXP(Hero_EXP_Max[Hero_Lv_Max]);//经验为当前级数最大经验
	}else{
		//等级增加，人物属性也随之改变
		cout << getname() << " \'s changing situation：\n";

		chargeEXP(getEXP() - Hero_EXP_Max[curLv]);
		chargeLv(curLv+1);
		chargeHP(Hero_HP_Max[curLv+1]);
		chargeATK(int(getATK() * Hero_ATK_Ratio));
		chargeDEF( int(getDEF() * Hero_DEF_Ratio));

		kick_ATK *= Hero_kick_Ratio;
		counter_ATK *= Hero_counter_Ratio;
	}
}

//////////////////////////////////////////////////////////////////////
//						敌人类  CEnemy 定义
//////////////////////////////////////////////////////////////////////

CEnemy::CEnemy():CRole(Enemy_Init_name,Enemy_HP_Max[0],Enemy_Init_ATK,Enemy_Init_DEF,Enemy_Init_Lv,Enemy_Init_EXP) {
	chop_ATK = Init_chop;
	catching_ATK = Init_catching;
}

CEnemy::~CEnemy() {

}


bool CEnemy::chop(CRole & CH){//劈掌
	int Damage = chop_ATK + getATK() - CH.getDEF();//攻击的掉血量

	cout << getname() << " chop " << CH.getname() << " " << Damage << "Hp\n";//显示伤害情况

	int resHP = CH.getHP() - Damage;//剩余血量
	if(resHP <= 0)//对方血量不够，死亡
		resHP = 0;

	CH.chargeHP(resHP);

	return resHP == 0 ? true : false;
}
bool CEnemy::catching(CRole & CH){//连环腿
	int Damage = catching_ATK + getATK() - CH.getDEF();//攻击的掉血量

	cout << getname() << " catching " << CH.getname() << " " << Damage << "Hp\n";//显示伤害情况

	int resHP = CH.getHP() - Damage;//剩余血量
	if(resHP <= 0)//对方血量不够，死亡
		resHP = 0;

	CH.chargeHP(resHP);

	return resHP == 0 ? true : false;
}


void CEnemy::addexp(int exp){
	int cur_exp = getEXP() + exp;//获得更新后的经验值
	chargeEXP(cur_exp);

	if(cur_exp >= Hero_EXP_Max[getLv()])
		upgrade();//升级
}

void CEnemy::upgrade(){
	//当前经验已经超出当前级数的最大经验

	cout << "congratulations!!! " << getname() << " upgrade!!!!\n";

	int curLv = getLv();//当前等级
	if(curLv == Hero_Lv_Max){//已经到最高等级，不能再升
		cout << "Your have are the highest grade.\n";

		chargeHP(Hero_HP_Max[Hero_Lv_Max]);//重新满血
		chargeEXP(Hero_EXP_Max[Hero_Lv_Max]);//经验为当前级数最大经验
	}else{
		//等级增加，人物属性也随之改变
		cout << getname() << " \'s changing situation：\n";

		chargeEXP(getEXP() - Hero_EXP_Max[curLv]);
		chargeLv(curLv+1);
		chargeHP(Hero_HP_Max[curLv+1]);
		chargeATK(int(getATK() * Hero_ATK_Ratio));
		chargeDEF( int(getDEF() * Hero_DEF_Ratio));

		chop_ATK *= Enemy_chop_Ratio;
		catching_ATK *= Enemy_catching_Ratio;
	}


}


