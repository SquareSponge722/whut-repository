#include "cardList.h"

cardList::cardList()
{
	head = new node;
	tail = new node;
	head->pre = nullptr;
	head->next = tail;
	head->card_ = nullptr;
	tail->pre = head;
	tail->next = nullptr;
	tail->card_ = nullptr;
	length = 0;
}
cardList::~cardList()
{
	for (pNode nextNode = head->next; nextNode != nullptr; nextNode = nextNode->next) delete nextNode->pre;
	delete tail;
	tail = head = nullptr;
}
int cardList::size()
{
	return length;
}
bool cardList::insert(card* element, int position)
{
	if (position < 0 || position > length) return false;

	pNode preNode = head;
	while (position--) preNode = preNode->next;
	pNode nextNode = preNode->next;

	pNode insertNode = new node;
	insertNode->card_ = new card;
	insertNode->card_->clone(element);

	preNode->next = insertNode;
	nextNode->pre = insertNode;
	insertNode->pre = preNode;
	insertNode->next = nextNode;

	length++;
	return true;
}
void cardList::pushback(card* element)
{
	pNode insertNode = new node;
	insertNode->card_ = new card;
	insertNode->card_->clone(element);

	pNode preNode = tail->pre;
	preNode->next = insertNode;
	tail->pre = insertNode;
	insertNode->pre = preNode;
	insertNode->next = tail;

	length++;
}
pNode cardList::begin()
{
	if (length == 0) return nullptr;
	return head->next;
}
bool cardList::empty()
{
	return length ? false : true;
}
void cardList::clear()
{
	if (!length) return;
	
	pNode nextNode = head->next;
	do
	{
		nextNode = nextNode->next;
		delete nextNode->pre;
	} while (nextNode->next != nullptr);
	
	length = 0;
	head->next = tail;
	tail->pre = head;
}


cardCursor::cardCursor(_Notnull_ pNode pointer)
{
	cursor = pointer;
}
cardCursor::~cardCursor(){}
bool cardCursor::hasNext()
{
	if ((cursor->next)->next == nullptr) return false;
	return true;
}
bool cardCursor::hasPre()
{
	if ((cursor->pre)->pre == nullptr) return false;
	return true;
}
card* cardCursor::getItem()
{
	return cursor->card_;
}
bool cardCursor::moveNext()
{
	if (hasNext())
	{
		cursor = cursor->next;
		return true;
	}
	return false;
}
bool cardCursor::movePre()
{
	if (hasPre())
	{
		cursor = cursor->pre;
		return true;
	}
	return false;
}
