#ifndef _TRANS_H_
#define _TRANS_H_

#include "Node.h"
#include "InteriorNode.h"

class TempNode : public InteriorNode
{
private:
	// ������� "������ ��������"
	StringKey*min4;
	// ��������� �������, ������� ������, ��� ��� "������ �������"
	Node *biggest;
	
public:

	//�����������
	TempNode():biggest(NULL),min4(NULL)
	{
	};
	
	//����������
	~TempNode(void)
	{
	};

	//get'� � set'�
	void setMin4(StringKey* min); // ������������� min4
	void setBiggest(Node* node); // ������������� ������ �������� �������

	
	StringKey* getMin4(); // �������� ���4
	Node* getBiggest(); // ������������ ����� �������
};

#endif