/*
 * Roler.h
 *
 *  Created on: 2017年7月20日
 *      Author: xiaoquan
 */
#include<string>

using namespace std;

#ifndef ROLER_H_
#define ROLER_H_

//////////////////////////////////////////////////////////////////////
//						基类  CRole
//////////////////////////////////////////////////////////////////////
class CRole {
private:
	string name;//头像显示名字
	int HP;//血量
	int ATK;//攻击力
	int DEF;//防御力
	int Lv;//等级
	int EXP;//经验值
public:
	CRole():name(""),HP(0),ATK(0),DEF(0),Lv(0),EXP(0){}
	CRole(string Init_name,int Init_HP,int Init_ATK,int Init_DEF,int Init_Lv,int Init_EXP);
	virtual ~CRole(){}

	/*普通攻击对方，若对方能够承受伤害，则返回false,
	 * 否则，则对方死亡，返回true*/
	bool attack(CRole &CR);//武器攻击

	/*跳跃动作，免除下一次对手的攻击*/
	bool jump();//跳跃

	string getname() const;//获得人物当前的名称
	int getHP() const;//获取人物当前的血量
	int getATK() const;//获取人物当前的普通攻击
	int getDEF() const;//获取人物当前的防御力
	int getLv() const;//获得人物当前的等级
	int getEXP() const;//获得人物当前的经验

	void chargename(string s);//更改名字
	void chargeHP(int hp);//更改血量
	void chargeATK(int atk);//更改攻击
	void chargeDEF(int def);//更改防御力
	void chargeLv(int lv);//更改等级
	void chargeEXP(int exp);//更改经验值

};

//////////////////////////////////////////////////////////////////////
//						英雄类  CHero 公共继承自 类CRole
//////////////////////////////////////////////////////////////////////

static string Hero_Init_name = "Hero";
const int Hero_Init_ATK = 5;//初始攻击力
const int Hero_Init_DEF = 3;//初始防御力
const int Hero_Init_Lv = 0;//初始等级
const int Hero_Init_EXP = 0;//初始经验值
const int Init_kick = 10;//初始踢腿伤害
const int Init_counter = 15;//初始抱摔伤害

const int Hero_Lv_Max = 8;//英雄最高的等级（0到8级）
const int Hero_HP_Max[] = {100,200,300,400,500,600,700,800,900};//英雄每级对应的最大血量
const int Hero_EXP_Max[] = {2,20,40,80,160,320,640,1280,2560};//升到下个级别所需要的最大经验值
const int Hero_EXP_Per[] = {2,4,8,16,32,64,128,256,512};//杀死相应等级的敌人所获的经验值

const double Hero_ATK_Ratio = 1.2;//普通攻击的增长倍率（随等级增加，普通攻击增加一次）
const double Hero_DEF_Ratio = 1.1;//防御的增长倍率（同上）

const double Hero_kick_Ratio = 1.3;//踢腿攻击的增长倍率（随等级增加，普通攻击增加一次）
const double Hero_counter_Ratio = 1.5;//抱摔的增长倍率（同上）

class CHero:public CRole{
private:
	int kick_ATK;//踢腿伤害
	int counter_ATK;//抱摔伤害
public:
	CHero();
	~CHero();

	bool kick(CRole & CE);//踢腿
	bool counter(CRole & CE);//抱摔

	void addexp(int exp);//杀敌增加相应的经验值
	void upgrade();//升级
};

//////////////////////////////////////////////////////////////////////
//						敌人类  CEnemy 公共继承自 类CRole
//////////////////////////////////////////////////////////////////////

static string Enemy_Init_name = "Enemy";
const int Enemy_Init_ATK = 3;//初始攻击力
const int Enemy_Init_DEF = 4;//初始防御力
const int Enemy_Init_Lv = 0;//初始等级
const int Enemy_Init_EXP = 0;//初始经验值
const int Init_chop = 10;//初始劈掌伤害
const int Init_catching = 15;//初始连环腿伤害

const int Enemy_Lv_Max = 8;//英雄最高的等级（0到8级）
const int Enemy_HP_Max[] = {100,200,300,400,500,600,700,800,900};//英雄每级对应的最大血量
const int Enemy_EXP_Max[] = {2,20,40,80,160,320,640,1280,2560};//升到下个级别所需要的最大经验值
const int Enemy_EXP_Per[] = {2,4,8,16,32,64,128,256,512};//杀死相应等级的敌人所获的经验值

const double Enemy_ATK_Ratio = 1.1;//普通攻击的增长倍率（随等级增加，普通攻击增加一次）
const double Enemy_DEF_Ratio = 1.2;//防御的增长倍率（同上）

const double Enemy_chop_Ratio = 1.3;//踢腿攻击的增长倍率（随等级增加，普通攻击增加一次）
const double Enemy_catching_Ratio = 1.5;//抱摔的增长倍率（同上）


class CEnemy:public CRole{
private:
	int chop_ATK;
	int catching_ATK;
public:
	CEnemy();
	~CEnemy();

	bool chop(CRole & CH);//劈掌
	bool catching(CRole & CH);//连环腿

	void addexp(int exp);//杀敌增加相应的经验值
	void upgrade();//升级

};

#endif /* ROLER_H_ */
