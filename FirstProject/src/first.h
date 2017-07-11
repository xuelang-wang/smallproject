/*
 * first.h
 *
 *  Created on: 2017年7月10日
 *      Author: xiaoquan
 */

#ifndef FIRST_H_
#define FIRST_H_

#include<ostream>
/*题目1：编写递归函数char *itostr (int n,char *string)，
 *该函数将整数n转换为十进制表示的字符串。（提示：使用递归方法）*/
char *itostr(int n,char *string);
char *itostr(long long n);//用于递归

/*题目2：编码实现字符串类CNString*/
class CNString{
private:
	char *str;
	int len;
public:
	CNString();
	CNString(const char*st);
	CNString(const CNString &s);

	char *strcpy_s(char*s1,const char *s2);

	CNString& operator=(const CNString &s);
	CNString operator+(const CNString &s);
	char operator[](const int n);
	bool operator<(const CNString &s);
	bool operator>(const CNString &s);
	bool operator==(const CNString &s);

	friend std::ostream& operator<<(std::ostream & os,const CNString &s);

	~CNString();
};



//题目3：创建双向链表类
struct dNode{
	int key;
	dNode * pre;
	dNode * next;
	dNode():key(0),pre(NULL),next(NULL){}
	dNode(int nkey):key(nkey),pre(NULL),next(NULL){}
};//定义双向链表的节点

class dlist{
private:
	dNode * head;//链表头
	dNode * tail;//链表尾
	int len;//链表长度
public:
	dlist();
	dlist(dlist & dl);
	void insert(dNode & Node);
	void insert(int nkey);
	void sort(const int index = 0);
	int search(dNode & Node);
	bool del(int nk);
	bool del(dNode & Node);

	void printNode() const;
	~dlist();
};

//题目4：创建单向链表类
struct sNode{
	int key;
	sNode *next;
	sNode():key(0),next(NULL){}
	sNode(int nkey):key(nkey),next(NULL){}
};
class slist{
private:
	sNode *head;
	int len;
public:
	slist();
	slist(slist & sl);

	void insert(int nk);
	void insert(sNode & Node);
	int search(sNode & Node);
	void del(int nk);
	void del(sNode & Node);
	void sort(const int index = 0);

	void printNode() const;
	~slist();
};






#endif /* FIRST_H_ */
