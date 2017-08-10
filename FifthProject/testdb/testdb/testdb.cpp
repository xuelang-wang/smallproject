// testdb.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
#include<iomanip>
#include"winsock.h"
#include"mysql.h"
#include<string>
#include<direct.h>
#pragma comment(lib,"libmySQL.lib")

using namespace std;

int rt;
MYSQL * m_sqlCon = NULL;
MYSQL_RES * res = NULL;
MYSQL_ROW row;
MYSQL_FIELD *field;

//创建数据库
void createDB();

//创建表
void createTable();

//导入数据（pet.txt）
void importDB();

//插入数据
void insertDB();

//删除数据
void deleteDB();

//更新数据
void updateDB();

//查询数据
void queryDB();

//使用数据库（激活）
void useDB();


int main(){
	m_sqlCon = mysql_init((MYSQL*)0);
	char password[20];
	cout << "输入你的数据库服务密码: ";
	scanf("%s",password);
	if (!mysql_real_connect(m_sqlCon, "localhost", "root", password, "", 3306, NULL, 0))
		cout << "数据库服务器连接失败" << endl;
	else{
		cout << "数据库服务器连接成功" << endl;

		createDB();//创建数据库menagerie
		useDB();//使用数据库menagerie
		createTable();//创建表pet
		importDB();//导入数据pet.txt
		queryDB();
		insertDB();//插入一条记录
		queryDB();//查询当前表pet的记录
		updateDB();//修改表中记录
		queryDB();
		deleteDB();//删除表中记录
		queryDB();
	}
	mysql_close(m_sqlCon);
	system("pause");

	return 0;
}


//创建数据库
void createDB(){
	char tmp[400];
	char DB_name[20] = { "menagerie" };
	sprintf(tmp, "create database %s", DB_name);
	rt = mysql_real_query(m_sqlCon, tmp, strlen(tmp));
	if (rt){
		cout << "创建数据库失败！" << endl;
		const char * str = mysql_error(m_sqlCon);
		cout << str << endl;
	}
	else
		cout << "创建数据库" << DB_name << endl;
}

void createTable(){
	char tmp[400];
	char * t_name = "pet";
	sprintf(tmp, "create table %s (name varchar(20),owner varchar(20),species varchar(20),sex char(1),birth date,death date)", t_name);
	rt = mysql_real_query(m_sqlCon, tmp, strlen(tmp));
	if (rt){
		cout << "创建表失败！" << endl;
		const char * str = mysql_error(m_sqlCon);
		cout << str << endl;
	}
	else
		cout << "创建表" << t_name << endl;
}

//导入数据（pet.txt）
void importDB(){
	char tmp[400];
	char path[100] = { "./pet.txt" };
	char t_name[20] = { "pet" };
	sprintf(tmp, "load data local infile '%s' into table %s lines terminated by '\r\n'", path, t_name);
	rt = mysql_real_query(m_sqlCon, tmp, strlen(tmp));
	if (rt){
		cout << "导入数据失败！" << endl;
		const char *str = mysql_error(m_sqlCon);
		cout << str << endl;
	}
	else
		cout << "导入数据成功！" << endl;
}

//插入数据
void insertDB(){
	char tmp[400];
	sprintf(tmp, "insert into %s values('%s','%s','%s','%s','%s',%s)", "pet", "Slim", "Benny", "snake", "m", "1996-04-29", "NULL");
	rt = mysql_real_query(m_sqlCon, tmp, strlen(tmp));
	if (rt){
		cout << "插入数据失败！" << endl;
		const char *str = mysql_error(m_sqlCon);
		cout << str << endl;
	}
	else{
		cout << tmp << endl;
		cout << "插入数据成功！" << endl;
	}
}

//删除数据
void deleteDB(){
	char tmp[400];
	sprintf(tmp, "delete from %s where name='%s'", "pet", "Fang");
	rt = mysql_real_query(m_sqlCon, tmp, strlen(tmp));
	if (rt){
		cout << "删除数据失败！" << endl;
		const char * str = mysql_error(m_sqlCon);
		cout << str << endl;
	}
	else{
		cout << tmp << endl;
		cout << "删除数据成功！" << endl;
	}
}

//更新数据
void updateDB(){
	char tmp[400];
	sprintf(tmp, "update %s set birth = '%s' where name = '%s'", "pet", "1999-09-09", "Slim");
	rt = mysql_real_query(m_sqlCon, tmp, strlen(tmp));
	if (rt){
		cout << "更新失败！" << endl;
		const char * str = mysql_error(m_sqlCon);
		cout << str << endl;
	}
	else{
		cout << tmp << endl;
		cout << "更新成功！" << endl;
	}
}

//查询数据
void queryDB(){
	char tmp[400];
	sprintf(tmp, "select * from %s", "pet");
	rt = mysql_real_query(m_sqlCon, tmp, strlen(tmp));
	res = mysql_store_result(m_sqlCon);
	//输出属性名
	while (field = mysql_fetch_field(res)){
		cout << setiosflags(ios::left) << setw(12) << field->name;
	}
	cout << endl;
	//输出各条记录
	while (row = mysql_fetch_row(res)){
		for (int i = 0; i < mysql_num_fields(res); i++){
			cout << setiosflags(ios::left) << setw(12) << (row[i] == NULL ? "NULL" : row[i]);
		}
		cout << endl;
	}
	mysql_free_result(res);
}

//使用数据库（激活）
void useDB(){
	char tmp[400];
	char db_name[20] = { "menagerie" };
	sprintf(tmp, "use %s", db_name);
	rt = mysql_real_query(m_sqlCon, tmp, strlen(tmp));
	if (rt){
		const char * str = mysql_error(m_sqlCon);
		cout << str << endl;
	}
}