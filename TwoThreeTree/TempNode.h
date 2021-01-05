#ifndef _TRANS_H_
#define _TRANS_H_

#include "Node.h"
#include "InteriorNode.h"

class TempNode : public InteriorNode
{
private:
	// минимум "самого большого"
	StringKey*min4;
	// Четвертый ребенок, который больше, чем его "Правый ребенок"
	Node *biggest;
	
public:

	//Конструктор
	TempNode():biggest(NULL),min4(NULL)
	{
	};
	
	//Диструктор
	~TempNode(void)
	{
	};

	//get'ы и set'ы
	void setMin4(StringKey* min); // устанавливает min4
	void setBiggest(Node* node); // устанавливает самого большого ребенка

	
	StringKey* getMin4(); // получает мин4
	Node* getBiggest(); // возвращается самый большой
};

#endif