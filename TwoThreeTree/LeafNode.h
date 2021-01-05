#include "Node.h"
class LeafNode : public Node
{
private:
	Worker* worker;
	StringKey* key;
	
public:
	// Конструктор
	LeafNode()
	{
		isleaf = true;
	}

	LeafNode(StringKey* k, Worker* d);

	Worker* Data()const; // Возвращает данные текущего узла
	StringKey* Key()const; // Возвращает текущий ключ узла

	~LeafNode(void)
	{
	} // Диструктор
	
};

LeafNode::LeafNode(StringKey* k, Worker* d)
{
	key = d->GetKey();
	worker = d;

	isleaf = true;
}

Worker* LeafNode::Data()const
{
	return worker;
}

StringKey* LeafNode::Key()const //вернуть ключ текущего узла (Имя)
{
	return worker->GetKey();
}