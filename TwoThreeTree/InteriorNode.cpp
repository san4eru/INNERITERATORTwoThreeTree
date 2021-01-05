#include "InteriorNode.h"

InteriorNode::InteriorNode(Node *l, Node *m, Node *r, StringKey*imin1, StringKey*imin2, StringKey*imin3)
{
	min1 = imin1;
	min2 = imin2;
	min3 = imin3;
	left = l;
	mid = m;
	right = r;

	//установка родителей
	right->SetParent(this);
	left->SetParent(this);
	mid->SetParent(this);
	
	isleaf = false;
}
	
void InteriorNode::setRight(Node* node)
{
	right = node;

	if (node != NULL)
		node->SetParent(this);
}

void InteriorNode::setMid(Node* node)
{
	mid = node;

	if (node != NULL)
		node->SetParent(this);
}

void InteriorNode::setLeft(Node* node)
{
	left = node;
				
	if (node != NULL)
		node->SetParent(this);
}

Node* InteriorNode::getMid()
{
	return mid;
}

Node* InteriorNode::getRight()
{
	return right;
}



Node* InteriorNode::getLeft()
{
	return left;
}

void InteriorNode::setMin1(StringKey* min)
{
	min1 = min;
}

void InteriorNode::setMin2(StringKey* min)
{
	min2 = min;
}

void InteriorNode::setMin3(StringKey* min)
{
	min3 = min;
}

StringKey* InteriorNode::getMin1()
{
	return min1;
}
		
StringKey* InteriorNode::getMin2()
{
	return min2;
}


StringKey* InteriorNode::getMin3()
{
	return min3;
}