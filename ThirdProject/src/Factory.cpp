/*
 * Factory.cpp
 *
 *  Created on: 2017Äê7ÔÂ29ÈÕ
 *      Author: xiaoquan
 */

#include "Factory.h"
#include<iostream>

using namespace std;

Player::Player(){
	cout << "Construct a Player£¡\n";
}
Player::~Player(){
	cout << "Destruct a Player!\n";
}

Demon::Demon(){
	cout << "Construct a Demon!\n";
}

Demon::~Demon(){
	cout << "Destruct a Demon!\n";
}

Fairy::Fairy(){
	cout << "Construct a Fairy!\n";
}

Fairy::~Fairy(){
	cout << "Destruct a Fairy!\n";
}

Civilian::Civilian(){
	cout << "Construct a Civilian!\n";
}

Civilian::~Civilian(){
	cout << "Destruct a Civilian!\n";
}

PlayerFactory::PlayerFactory(){
	cout << "Construct a PlayerFactory!\n";
}

PlayerFactory::~PlayerFactory(){
	cout << "Destruct a PlayerFactory!\n";
}

Actor* PlayerFactory::CreateActor(){
	return new Player();
}

DemonFactory::DemonFactory(){
	cout << "Construct a DemonFactory!\n";
}

DemonFactory::~DemonFactory(){
	cout << "Destruct a DemonFactory!\n";
}

Actor * DemonFactory::CreateActor(){
	return new Demon();
}

FairyFactory::FairyFactory(){
	cout << "Construct a FairyFactory!\n";
}

FairyFactory::~FairyFactory(){
	cout << "Destruct a FairyFactory!\n";
}

Actor * FairyFactory::CreateActor(){
	return new Fairy();
}

CivilianFactory::CivilianFactory(){
	cout << "Contruct a CivilianFactory!\n";
}

CivilianFactory::~CivilianFactory(){
	cout << "Destruct a CivilianFactory!\n";
}

Actor * CivilianFactory::CreateActor(){
	return new Civilian();
}
