#pragma once
#include "cardModel.h"
#define pNode cardList::node *
/*
链表重构vector
*/
class cardList
{
public:
	struct node
	{
		card* card_;
		pNode pre;
		pNode next;
	};
public:
	cardList();
	~cardList();
	int size();
	pNode begin(); //length为0 返回 nullptr
	bool insert(card* element, int position = 0); //position位置的node向右移
	void pushback(card* element);
	bool empty();
	void clear();
private:
	pNode head;
	pNode tail;
	int length;
};

/*
使用此类来访问cardList中的元素
*/
class cardCursor
{
public:
	cardCursor(_Notnull_ pNode pointer);
	~cardCursor();
	bool hasNext();
	bool hasPre();
	bool moveNext();
	bool movePre();
	card* getItem();
private:
	pNode cursor;
};