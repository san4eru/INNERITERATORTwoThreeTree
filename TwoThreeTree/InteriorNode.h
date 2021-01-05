#ifndef _INTERIOR_H_
#define _INTERIOR_H_

#include "Node.h"
class InteriorNode : public Node
{
protected:
	StringKey *min1, *min2, *min3;
	Node *left, *mid, *right;

public:
	// Пустой конструктор
	InteriorNode():left(NULL),mid(NULL),right(NULL),min1(NULL),min2(NULL),min3(NULL)
	{
		SetParent(NULL);
		isleaf = false;
	} 
	// Конструктор
	InteriorNode(Node *l,Node *m, Node* r, StringKey*imin1, StringKey*imin2, StringKey*imin3);
	
	virtual ~InteriorNode(void)
	{
		delete left;
		delete mid;
		delete right;
	} 		

	//set'ы и get'ы
	void setMin1(StringKey* min);
	StringKey* getMin1();
	void setMin2(StringKey* min);
	StringKey* getMin2();
	void setMin3(StringKey* min);
	StringKey* getMin3();
	  
	void setLeft(Node* node); 
	Node* getLeft();
	void setMid(Node* node);
	Node* getMid();
	void setRight(Node* node);
	Node* getRight();

};

#endif