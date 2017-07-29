/*
 * Factory.h
 *
 *  Created on: 2017年7月29日
 *      Author: xiaoquan
 */

#ifndef FACTORY_H_
#define FACTORY_H_

//抽象角色  代表角色的抽象
class Actor{
public:
	Actor(){}
	virtual ~Actor(){}
};

//各种实例角色

//代表Player角色的实现
class Player:public Actor{
public:
	Player();
	~Player();
};

//代表Demon角色的实现
class Demon:public Actor{
public:
	Demon();
	~Demon();
};

//代表Fairy角色的实现
class Fairy:public Actor{
public:
	Fairy();
	~Fairy();
};

//代表Civilian角色的实现
class Civilian:public Actor{
public:
	Civilian();
	~Civilian();
};

//工厂的抽象类,生产角色
class Factory {
public:
	Factory(){}
	virtual ~Factory(){}

	virtual Actor * CreateActor(){ return new Actor();}
};

// 生产Player
class PlayerFactory:public Factory{
public:
	PlayerFactory();
	~PlayerFactory();

	virtual Actor * CreateActor();
};

// 生产Demon
class DemonFactory:public Factory{
public:
	DemonFactory();
	~DemonFactory();

	virtual Actor * CreateActor();
};

// 生产Fairy
class FairyFactory:public Factory{
public:
	FairyFactory();
	~FairyFactory();

	virtual Actor * CreateActor();
};

// 生产Civilian
class CivilianFactory:public Factory{
public:
	CivilianFactory();
	~CivilianFactory();

	virtual Actor *CreateActor();
};

#endif /* FACTORY_H_ */
