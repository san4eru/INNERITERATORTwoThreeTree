#include "Node.h"
class LeafNode : public Node
{
private:
	Worker* worker;
	StringKey* key;
	
public:
	// �����������
	LeafNode()
	{
		isleaf = true;
	}

	LeafNode(StringKey* k, Worker* d);

	Worker* Data()const; // ���������� ������ �������� ����
	StringKey* Key()const; // ���������� ������� ���� ����

	~LeafNode(void)
	{
	} // ����������
	
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

StringKey* LeafNode::Key()const //������� ���� �������� ���� (���)
{
	return worker->GetKey();
}