#include "Node.h"

int Node::IsLeaf()
{
	return isleaf;
}

void Node::SetParent(Node* p)
{
	current = p;
}

Node* Node::getParent()
{
	return current;
}


