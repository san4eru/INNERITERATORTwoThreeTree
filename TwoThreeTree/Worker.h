#ifndef _WORKER_H_
#define _WORKER_H_

#include "StringKey.h"

class Worker
{
private:
	StringKey* name;
	unsigned int years;
	unsigned int position;
public:
	// �����������
	Worker():name(0), years(0), position(0){}

	Worker(StringKey* name,unsigned int years,unsigned int position):name(name), years(years), position(position){}

	// ����������
	~Worker()
	{
		delete name;
	}

	Worker(const Worker& otherWorker)throw(char*); // ����������� �����������. ������ ����������, ���� ��� ������� worker �������� �������
	
	// ���������� ���� (��� worker)
	StringKey* GetKey()const;
	
	//������ ����� worker �� �����. null, ���� ��������� ������ ������
	static Worker* Read(ifstream& inputFile);

	//������ ����� worker � ����������
	static Worker* Readfromkeyboard(string new_k, unsigned int new_years, unsigned int new_position);

	//operator << ��� ������
	friend ostream& operator<<(ostream& out, const Worker& worker)
	{
		out << worker.name->getString() << "\t " << worker.years
			<< "\t " << worker.position;
		return out;
	}

	
	unsigned int getseniority(); // ���������� years
	unsigned int getPosition(); // ���������� �������
};

#endif