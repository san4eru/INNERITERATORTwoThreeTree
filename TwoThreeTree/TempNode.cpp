#include "TempNode.h"

//setû

void TempNode::setMin4(StringKey* min)
{
	min4 = min;
}

void TempNode::setBiggest(Node* node)
{
	biggest = node;

	if (node != NULL)
		node->SetParent(this);
}

//getû

StringKey* TempNode::getMin4()
{
	return min4;
}

Node* TempNode::getBiggest()
{
	return biggest;
}


