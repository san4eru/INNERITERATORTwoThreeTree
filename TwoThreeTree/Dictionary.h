#include <fstream>
#include "Node.h"
#include "InteriorNode.h"
#include "LeafNode.h"
#include "TempNode.h"

using namespace std;

class Dictionary
{
private:
		Node* root;

		void AddChild(TempNode* trans); // ��������� 4 ������� � ������� � ��������� ��� ���, ����� �� ����������
		TempNode* MakeTransitoryNode(InteriorNode* parent, LeafNode* child); // ������� ��������� ���� 4
	
		void freeAllElementsHelper(Node* node); // ����������� ��� �������� ����������
		void Update(InteriorNode* node); // ��������� min1, min2, min3 ���� �� �����
		
		InteriorNode* FindParent(StringKey* key); // ������� �������� ����
		
		void print23(ofstream &outputFile, Node* node, int son); // ���������� �������� � ���������� �������
		void print23Console(Node* node, int son);
public:
	//�����������
	Dictionary():root(0)
	{
	}

	//����������
	~Dictionary()
	{
		//  ������� �����, ������� � ������ ���� ����������
		delete root; 
	}

	// ��������� worker
	int Insert(StringKey*k, Worker *d);

	// ������� worker �� �����
	Worker *Delete(StringKey*k);

	// ������� worker �� �����
	Worker *Find(StringKey*k);

	// ������� ���������� ������
	int Dictionary::CountOfKey();

	// ����������� ��� �������� � �������
	void FreeAllElements(); 
	// �������� ������� � ���������� �������

	void PrintDictionary(ofstream &outputFile);

	void PrintDictionaryConsole();

	int IsEmpty();// ���������, �������� �� ������� ������, ���� �����, ������� 1 (true), ����� ������� 0 (false)
	
};


int Dictionary::Insert(StringKey* k, Worker* d)
{
	if (IsEmpty())
	{
		root = new LeafNode(k, d);
	}
	else
	{
		// ���� k ���� ������
		if (Find(k) != NULL)
		{
			// ��� ����������
			return 0;
		}
		else
		{
			//  ����� ����
			LeafNode* newleaf = new LeafNode(k, d);

			// �������

			if (root->IsLeaf()) // ������ ���� ������� � ������
			{
				LeafNode* leafRoot = (LeafNode*)root;
				InteriorNode* newRoot = new InteriorNode();

				// leafRoot >= new
				if (leafRoot->Key()->Compare(newleaf->Key()) > 0)
				{
					newRoot->setLeft(newleaf);
					newRoot->setMin1(newleaf->Key());
					newRoot->setMid(leafRoot);
					newRoot->setMin2(leafRoot->Key());
				}
				else // new >leafRoot
				{
					newRoot->setLeft(leafRoot);
					newRoot->setMin1(leafRoot->Key());
					newRoot->setMid(newleaf);
					newRoot->setMin2(newleaf->Key());
				}

				//��������� ������
				root = newRoot;
			}
			else // ������ �� ����
			{
				InteriorNode* parent = FindParent(newleaf->Key());

				// ���� � �������� 2-�� �����
				if (parent->getRight() == NULL)
				{
					LeafNode* left = (LeafNode*)parent->getLeft();
					LeafNode* mid = (LeafNode*)parent->getMid();

					if (newleaf->Key()->Compare(mid->Key()) > 0) // ����� ���� � ������
					{
						parent->setRight(newleaf);
						parent->setMin3(newleaf->Key());
						// �� ����� ��������� min2 min3 - ����� "��������"
					}
					else if (newleaf->Key()->Compare(left->Key()) > 0) // ����� ���� � ��������
					{
						parent->setRight(mid);
						parent->setMin3(mid->Key());
						parent->setMid(newleaf);
						parent->setMin2(newleaf->Key());
						// �� ����� ��������� min2 min3 - ����� "��������"
					}
					else if (newleaf->Key()->Compare(left->Key()) < 0) // ����� ���� �����
					{
						parent->setRight(mid);
						parent->setMin3(mid->Key());
						parent->setMid(left);
						parent->setMin2(left->Key());
						parent->setLeft(newleaf);
						parent->setMin1(newleaf->Key());
					}

					Update(parent); // ������ ���� ����� "��������" �� �����
				}
				else // � �������� 3-�� �����
				{
					TempNode* temp = MakeTransitoryNode(parent, newleaf);

					parent->setLeft(NULL);
					parent->setMid(NULL);
					parent->setRight(NULL);
					delete parent; // �� ������� ���������� ���������� ���� �� �����

					AddChild(temp);

				}
			}
		}
	}

	return 1; // ������
}

InteriorNode* Dictionary::FindParent(StringKey* k)
{
	Node* node = root;
	InteriorNode* Interior = (InteriorNode*)node;

	InteriorNode* parent = NULL;

	while (!node->IsLeaf())
	{
		Interior = (InteriorNode*)node;

		parent = Interior;

		// k ������ ��� min3
		if ((Interior->getRight() != NULL) && (k->Compare(Interior->getMin3()) >= 0))
		{
			node = Interior->getRight();
		}
		else if (k->Compare(Interior->getMin2()) >= 0) // k ����� min2 � min3
		{
			node = Interior->getMid();
		}
		else // k ����� min1 � min2
			node = Interior->getLeft();
	}

	return parent;
}

TempNode* Dictionary::MakeTransitoryNode(InteriorNode* parent, LeafNode* child)
{
	TempNode* retFourSons = new TempNode(); // ����� ������ ��������

	LeafNode* right = (LeafNode*)parent->getRight();
	LeafNode* left = (LeafNode*)parent->getLeft();
	LeafNode* mid = (LeafNode*)parent->getMid();

	StringKey* newChildKey = child->Key();

	//������ 1: ����� - ����� �������
	if (newChildKey->Compare(right->Key()) > 0)
	{
		retFourSons->setLeft(left);
		retFourSons->setMid(mid);
		retFourSons->setRight(right);
		retFourSons->setBiggest(child);
		retFourSons->setMin1(left->Key());
		retFourSons->setMin2(mid->Key());
		retFourSons->setMin3(right->Key());
		retFourSons->setMin4(child->Key());
	}
	//������ 2: ����� - ����� 3 � 4
	else if (newChildKey->Compare(mid->Key()) > 0)
	{
		retFourSons->setLeft(left);
		retFourSons->setMid(mid);
		retFourSons->setRight(child);
		retFourSons->setBiggest(right);
		retFourSons->setMin1(left->Key());
		retFourSons->setMin2(mid->Key());
		retFourSons->setMin3(child->Key());
		retFourSons->setMin4(right->Key());
	}
	//������ 3: ����� - ����� 2 � 3
	else if (newChildKey->Compare(left->Key()) > 0) // ����� 2/4
	{
		retFourSons->setLeft(left);
		retFourSons->setMid(child);
		retFourSons->setRight(mid);
		retFourSons->setBiggest(right);
		retFourSons->setMin1(left->Key());
		retFourSons->setMin2(child->Key());
		retFourSons->setMin3(mid->Key());
		retFourSons->setMin4(right->Key());
	}
	else
	{
		retFourSons->setLeft(child);
		retFourSons->setMid(left);
		retFourSons->setRight(mid);
		retFourSons->setBiggest(right);
		retFourSons->setMin1(child->Key());
		retFourSons->setMin2(left->Key());
		retFourSons->setMin3(mid->Key());
		retFourSons->setMin4(right->Key());
	}

	if (parent != root)
	{
		InteriorNode* FatherOfParent = (InteriorNode*)parent->getParent(); // ���� retFourSons (= ��������, �� � 4 ���������)

		retFourSons->SetParent(FatherOfParent);

		if (FatherOfParent->getLeft() == parent)//�������� - ����� ����
			FatherOfParent->setLeft(retFourSons);
		else if (FatherOfParent->getMid() == parent)//�������� - ������� ����
			FatherOfParent->setMid(retFourSons);
		else if (FatherOfParent->getRight() == parent)//�������� - ������ ����
			FatherOfParent->setRight(retFourSons);

		Update(FatherOfParent);
	}
	return retFourSons;
}

void Dictionary::Update(InteriorNode* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		if (node->getLeft()->IsLeaf())//������� ������
		{
			// ���������� �� ���� ��� ���� �������
			node->setMin1(((LeafNode*)node->getLeft())->Key());

			if (node->getMid() != NULL)
			{
				node->setMin2(((LeafNode*)node->getMid())->Key());
			}
			else
			{
				node->setMin2(NULL);
			}

			if (node->getRight() != NULL)
			{
				node->setMin3(((LeafNode*)node->getRight())->Key());
			}
			else
			{
				node->setMin3(NULL);
			}

			node = ((InteriorNode*)node->getParent());
		}

		// ���������� �����, �� �����
		while (node != NULL)
		{
			node->setMin1(((InteriorNode*)node->getLeft())->getMin1());

			if (node->getMid() != NULL)
			{
				node->setMin2(((InteriorNode*)node->getMid())->getMin1());
			}
			else
			{
				node->setMin2(NULL);
			}

			if (node->getRight() != NULL)
			{
				node->setMin3(((InteriorNode*)node->getRight())->getMin1());
			}
			else
			{
				node->setMin3(NULL);
			}

			if (node == root)
			{
				node = NULL;
			}
			else
			{
				node = ((InteriorNode*)node->getParent());
			}

		}
	}
}

void Dictionary::AddChild(TempNode* trans)
{
	InteriorNode* rightMostInterior = new InteriorNode;

	rightMostInterior->setLeft(trans->getRight());
	rightMostInterior->setMid(trans->getBiggest());
	rightMostInterior->setMin1(trans->getMin3());
	rightMostInterior->setMin2(trans->getMin4());

	InteriorNode* leftMostInterior = new InteriorNode;

	leftMostInterior->setLeft(trans->getLeft());
	leftMostInterior->setMid(trans->getMid());
	leftMostInterior->setMin1(trans->getMin1());
	leftMostInterior->setMin2(trans->getMin2());

	if (trans->getParent() == NULL)
	{
		InteriorNode* parent = new InteriorNode;

		parent->setLeft(leftMostInterior);
		parent->setMid(rightMostInterior);
		parent->setMin1(leftMostInterior->getMin1());
		parent->setMin2(rightMostInterior->getMin1());

		root = parent;

		trans->setLeft(NULL);
		trans->setMid(NULL);
		trans->setRight(NULL);
		trans->setBiggest(NULL);
		delete trans;
	}
	else // ���������� ���� - �� ������
	{
		InteriorNode* parent = (InteriorNode*)trans->getParent();

		if (parent->getRight() == NULL) // �������� ����� 2-�� �����. ��� ���������, ����� ��������
		{
			if (trans == parent->getLeft()) // ���� 4-���� �������� ���������� �� ����
			{
				parent->setRight(parent->getMid());
				parent->setLeft(leftMostInterior);
				parent->setMid(rightMostInterior);
			}
			else if (trans == parent->getMid())
			{
				parent->setMid(leftMostInterior);
				parent->setRight(rightMostInterior);
			}

			// ���������� min1 min2 min3 �� �����
			Update(parent);
		}
		else // �������� ��� ����� 3-�� �����. ������� 4-��� ���� - ���������� �����
		{
			TempNode* tmpFather = new TempNode;

			if (trans == parent->getLeft())
			{
				tmpFather->setLeft(leftMostInterior);
				tmpFather->setMid(rightMostInterior);
				tmpFather->setRight(parent->getMid());
				tmpFather->setBiggest(parent->getRight());

				tmpFather->setMin1(leftMostInterior->getMin1());
				tmpFather->setMin2(rightMostInterior->getMin1());
				tmpFather->setMin3(((InteriorNode*)parent->getMid())->getMin1());
				tmpFather->setMin4(((InteriorNode*)parent->getRight())->getMin1());
			}
			else if (trans == parent->getMid())
			{
				tmpFather->setLeft(parent->getLeft());
				tmpFather->setMid(leftMostInterior);
				tmpFather->setRight(rightMostInterior);
				tmpFather->setBiggest(parent->getRight());

				tmpFather->setMin1(((InteriorNode*)parent->getLeft())->getMin1());
				tmpFather->setMin2(leftMostInterior->getMin1());
				tmpFather->setMin3(rightMostInterior->getMin1());
				tmpFather->setMin4(((InteriorNode*)parent->getRight())->getMin1());
			}
			else if (trans == parent->getRight())
			{
				tmpFather->setLeft(parent->getLeft());
				tmpFather->setMid(parent->getMid());
				tmpFather->setRight(leftMostInterior);
				tmpFather->setBiggest(rightMostInterior);

				tmpFather->setMin1(((InteriorNode*)parent->getLeft())->getMin1());
				tmpFather->setMin2(((InteriorNode*)parent->getMid())->getMin1());
				tmpFather->setMin3(leftMostInterior->getMin1());
				tmpFather->setMin4(rightMostInterior->getMin1());
			}

			InteriorNode* FatherOfParent = (InteriorNode*)parent->getParent();
			tmpFather->SetParent(parent->getParent());

			if (FatherOfParent != NULL) // ���� �������� �� ������.
			{
				if (FatherOfParent->getLeft() == parent)//�������� - ����� ����
					FatherOfParent->setLeft(tmpFather);
				else if (FatherOfParent->getMid() == parent)//�������� - ������� ����
					FatherOfParent->setMid(tmpFather);
				else if (FatherOfParent->getRight() == parent)//�������� - ������ ����
					FatherOfParent->setRight(tmpFather);

				Update(FatherOfParent); // �������� ���� ������ ����������� ���� �� �����
			}
			else // �������� ��� ������
			{
				root = tmpFather;
			}

			parent->setLeft(NULL);
			parent->setMid(NULL);
			parent->setRight(NULL);
			delete parent; // �� �������� �������� � ����� ����� tmpFather

			trans->setLeft(NULL);
			trans->setMid(NULL);
			trans->setRight(NULL);
			trans->setBiggest(NULL);
			delete trans; // ���������� ���� ��� ������� ����� ���������

			// ������ � ��� ���� ���� � 4 ���������. �����. ����� ������� "�������� �������" ����������
			AddChild(tmpFather);
		}
	}
}

Worker* Dictionary::Delete(StringKey* k)
{
	Worker* retWorkerDeleted = Find(k);

	if (retWorkerDeleted == NULL)
	{
		return NULL;
	}
	else
	{
		InteriorNode* parent = FindParent(k);

		if (parent == NULL) // ���� ��� �������� => ������� ������ �������
		{
			delete root;
			root = NULL;
		}
		else
		{
			LeafNode* leafToDel;

			// ��� �������� �������
			if (parent->getMin1()->Compare(k) == 0)
			{
				leafToDel = (LeafNode*)parent->getLeft();

				parent->setLeft(parent->getMid()); // �������� ��� �����
				if (parent->getRight() != NULL)
				{
					parent->setMid(parent->getRight());
					parent->setRight(NULL);
				}
				else
				{
					parent->setMid(NULL);
				}
			}
			else if (parent->getMin2()->Compare(k) == 0)
			{
				leafToDel = (LeafNode*)parent->getMid();

				//3 ����
				if (parent->getRight() != NULL)
				{
					parent->setMid(parent->getRight());
					parent->setRight(NULL);
				}
				//2 ����
				else
				{
					parent->setMid(NULL);
				}
			}
			else if ((parent->getRight() != NULL) && (parent->getMin3()->Compare(k) == 0))
			{
				leafToDel = (LeafNode*)parent->getRight();

				parent->setRight(NULL);
			}

			delete leafToDel;

			Update(parent);
			// ��������� ������������� ����
			while ((parent != NULL) && (!parent->IsLeaf()) && ((InteriorNode*)parent->getMid() == NULL))
			{
				//��� ��������
				if (parent->getParent() == NULL)
				{
					root = parent->getLeft();

					parent->setLeft(NULL);
					parent->setMid(NULL);
					parent->setRight(NULL);
					delete parent;

					if (!root->IsLeaf())
					{
						parent = (InteriorNode*)root; // ������ ��������� ��������
					}
					else
					{
						parent = NULL;
					}
				}
				else // ���� �������� ��� ��������
				{
					InteriorNode* grandpa = (InteriorNode*)parent->getParent();

					InteriorNode* leftSibling = (InteriorNode*)grandpa->getLeft();
					InteriorNode* midSibling = (InteriorNode*)grandpa->getMid();
					InteriorNode* rightSibling = (InteriorNode*)grandpa->getRight();


					if (leftSibling == parent)
					{
						//������� ������ ����
						if (midSibling->getRight() != NULL)
						{
							leftSibling->setMid(midSibling->getLeft());

							// ����� ������ �� ��������
							midSibling->setLeft(midSibling->getMid());
							midSibling->setMid(midSibling->getRight());
							midSibling->setRight(NULL);

							Update(leftSibling);
							Update(midSibling);
							Update(rightSibling);
						}
						// ������� ������ ����� ���� �������. ���� ��� ���� � ��������� ��� �����
						else
						{
							midSibling->setRight(midSibling->getMid());
							midSibling->setMid(midSibling->getLeft());
							midSibling->setLeft(leftSibling->getLeft());

							leftSibling->setLeft(NULL);
							leftSibling->setMid(NULL);
							leftSibling->setRight(NULL);
							delete leftSibling;

							grandpa->setLeft(midSibling);//����� �����
							grandpa->setMid(rightSibling);
							grandpa->setRight(NULL);

							Update(midSibling);
							Update(rightSibling);

							parent = grandpa; // ��� ��������� ��������
						}
					}
					else if (midSibling == parent)
					{
						if (leftSibling->getRight() != NULL) // ����� ����� ����� 3 ����. ������� ��� ������� ����.
						{
							midSibling->setMid(midSibling->getLeft());
							midSibling->setLeft(leftSibling->getRight());

							leftSibling->setRight(NULL);

							Update(leftSibling);
							Update(midSibling);
							Update(rightSibling);
						}
						else // ����� ������, 2-�� �������. ���� ��� ���� � ��������� ��� ������
						{
							leftSibling->setRight(midSibling->getLeft());

							midSibling->setLeft(NULL);
							midSibling->setMid(NULL);
							midSibling->setRight(NULL);
							delete midSibling;

							grandpa->setMid(rightSibling);//����� �����
							grandpa->setRight(NULL);

							Update(leftSibling);
							Update(rightSibling);
							parent = grandpa; // ��� ��������� ��������
						}
					}
					else if (rightSibling == parent)
					{
						if (midSibling->getRight() != NULL) //������� ������ ����� 3 ����. ������ ��� ������� ����.
						{
							rightSibling->setMid(rightSibling->getLeft());
							rightSibling->setLeft(midSibling->getRight());

							midSibling->setRight(NULL);

							Update(leftSibling);
							Update(midSibling);
							Update(rightSibling);
						}
						else // ������� ������ ����� 2 ����. ���� ��� ���� � ��������� ��� ������
						{
							midSibling->setRight(rightSibling->getLeft());

							rightSibling->setLeft(NULL);
							rightSibling->setMid(NULL);
							rightSibling->setRight(NULL);

							// ������ ������ ���� - ����
							delete rightSibling;

							grandpa->setRight(NULL);

							Update(midSibling);
							Update(leftSibling);

							parent = grandpa; // ��� ��������� ��������
						}
					}
				}
			} // ����� while 
		}
	}

	return retWorkerDeleted;
}

void Dictionary::PrintDictionary(ofstream& outputFile)
{
	if (IsEmpty()) // ���� ������
	{
		outputFile << "������ ������!" << endl;
		outputFile.flush();
	}
	else
	{
		print23(outputFile, root, 0);
	}
}

void Dictionary::print23(ofstream& outputFile, Node* node, int son)
{
	if (node == NULL)
		return;
	if (node->IsLeaf())
	{
		LeafNode* leaf = (LeafNode*)node;
		outputFile << *(leaf->Data()) << endl;
		outputFile.flush();
	}
	else
	{
		InteriorNode* interior = (InteriorNode*)node;

		// ����������� � ���������� �������
		print23(outputFile, interior->getLeft(), 1);
		print23(outputFile, interior->getMid(), 2);
		print23(outputFile, interior->getRight(), 3);
	}
}

void Dictionary::PrintDictionaryConsole()
{
	if (IsEmpty()) // ������ 
		cout << "������ ������!" << endl;
	else
		print23Console(root, 0);
}

void Dictionary::print23Console(Node* node, int son)
{
	if (node == NULL)
		return;
	if (node->IsLeaf())
	{
		LeafNode* leaf = (LeafNode*)node;
		cout << *(leaf->Data());
		if (son == 0)
			cout << "!������!";
		else if (son == 1)
			cout << "!�����!";
		else if (son == 2)
			cout << "!�������!";
		else if (son == 3)
			cout << "!������!";
		cout << endl;
	}
	else
	{
		InteriorNode* interior = (InteriorNode*)node;

		// ����������� � ���������� �������
		print23Console(interior->getLeft(), 1);
		print23Console(interior->getMid(), 2);
		print23Console(interior->getRight(), 3);
	}
}

void Dictionary::FreeAllElements()
{
	freeAllElementsHelper(root); // ������ � �����
}
void Dictionary::freeAllElementsHelper(Node* node)
{
	if (node == NULL)
		return;
	if (node->IsLeaf())
	{
		LeafNode* leaf = (LeafNode*)node;

		delete leaf->Data(); // worker's dtor ������� ��� (StringKey)

		delete leaf;
	}
	else
	{
		InteriorNode* interior = (InteriorNode*)node;

		// ������� ��� ������, �������� � ������� ������� ����������

		freeAllElementsHelper(interior->getLeft());
		freeAllElementsHelper(interior->getMid());
		freeAllElementsHelper(interior->getRight());

		if (interior == root)
		{
			root = NULL;
		}

		interior->setLeft(NULL);
		interior->setMid(NULL);
		interior->setRight(NULL);
		delete interior;
	}
}

int Dictionary::IsEmpty()// ���������, �������� �� ������� ������, ���� �����, ������� 1 (true), ����� ������� 0 (false)
{
	return (root == NULL);
}

Worker* Dictionary::Find(StringKey* k)
{
	//������ 1: ������� ���� ��� k ����� ����, ������� ��� ������
	if (IsEmpty() || k == NULL)
	{
		return NULL;
	}

	InteriorNode* Interior;
	Node* node = root;

	while (!node->IsLeaf())
	{
		Interior = (InteriorNode*)node;

		// k >= min3
		if ((Interior->getRight() != NULL) && (k->Compare(Interior->getMin3()) >= 0))
		{
			node = Interior->getRight();
		}
		// k >= min2 && k < min3
		else if (k->Compare(Interior->getMin2()) >= 0)
		{
			node = Interior->getMid();
		}
		// k <min2
		else
			node = Interior->getLeft();
	}

	// ����
	LeafNode* leaf = (LeafNode*)node;

	if (k->Compare(leaf->Key()) == 0)
		return leaf->Data();
	else
		return NULL;

}

int Dictionary::CountOfKey()
{
	//���� ������� ����, ������� ��� ��������
	if (IsEmpty())
		return 0;

	InteriorNode* Interior;
	Node* node = root;
	unsigned int count_k = 0;

	while (!node->IsLeaf())
	{
		Interior = (InteriorNode*)node;
		count_k++;
		
		if (Interior->getRight() != NULL)
			node = Interior->getRight();

		if (Interior->getMid() != NULL)
			node = Interior->getMid();

		if (Interior->getLeft() != NULL)
			node = Interior->getLeft();
	}

	// ����
	if (Interior->getRight() != NULL) {
		count_k++;
	}

	if (Interior->getMid() != NULL) {
		count_k++;
	}

	if (Interior->getLeft() != NULL) {
		count_k++;
	}

	return count_k;
}