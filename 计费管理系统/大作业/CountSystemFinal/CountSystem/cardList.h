#pragma once
#include "cardModel.h"
#define pNode cardList::node *
/*
�����ع�vector
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
	pNode begin(); //lengthΪ0 ���� nullptr
	bool insert(card* element, int position = 0); //positionλ�õ�node������
	void pushback(card* element);
	bool empty();
	void clear();
private:
	pNode head;
	pNode tail;
	int length;
};

/*
ʹ�ô���������cardList�е�Ԫ��
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