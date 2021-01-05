#ifndef _NODE_H_
#define _NODE_H_

#include "Worker.h"

class Node
{

protected:
	
	Node *current;
	int isleaf;

public:
	 //  онструктор
	Node()
	{
	}

	 // ƒеструктор
	virtual ~Node()
	{
	}

	int IsLeaf(); // предположим, что узел €вл€етс€ листовым возвратом true. false в противном случае.

	//методы родителей
	void SetParent(Node* p);
	Node* getParent();	
};

#endif