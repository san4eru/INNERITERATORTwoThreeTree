#include <fstream>
#include <sstream>
#include "Dictionary.h"

using namespace std;

bool ConvertStringToInt(const string& s, unsigned int& num);

int main()
{
	setlocale(LC_ALL, "Russian");

	Dictionary* d = new Dictionary();

	cout << endl;
	cout << "=====================================================" << endl;
	cout << "- ���� 2-3 ������" << endl;
	cout << "=====================================================" << endl;
	cout << " (1) �������� ����� � �������� � ������ �� �����" << endl;
	cout << " (2) ??????�������� ��������� ����� � ��������" << endl;
	cout << " (3) �������� � ������ ���� � �������� � ����������" << endl;
	cout << " (4) ������� ������ � �������" << endl;
	cout << " (5) ��������� ������ � �����" << endl;
	cout << " (6) ������ �������� �� �����" << endl;
	cout << " (7) ������� ���� � ��������" << endl;
	cout << " (8) ������� ��� ������" << endl;
	cout << " (9) ??????�������� ���-�� ���������� ������" << endl;
	cout << "(10) ??????�������� ������ ������" << endl;
	cout << "(11) ����� " << endl;
	int choice;
	while (1) {
		choice = 0;
		cout << "������� ��������: "; cin >> choice;
		
		// �������� �� �����
		if (choice == 1) {
			string pNameOfFile;
			//cout << "������� �������� �����: "; cin >> pNameOfFile;
			pNameOfFile = "progEx2_Test1.txt";
			ifstream ifs; // ������� ����
			ifs.open(pNameOfFile);

			unsigned int N;
			
			if (ifs.is_open()) {
				string nextString;
				while (ifs >> nextString)
				{
					if (ConvertStringToInt(nextString, N))
					{
						int success;
						unsigned int i;

						for (i = 0; i < N; i++)
						{
							try
							{
								Worker* currentWorker = Worker::Read(ifs);

								if (currentWorker != NULL)
								{
									success = d->Insert(currentWorker->GetKey(), currentWorker);

									if (!success)
									{
										delete currentWorker;
									}
								}
								else // ������ - ���� ��������������, ������������� �����
								{
									cout << "�������� ������� ����!" << endl;

									ifs.close();
									d->FreeAllElements();
								}
							}
							catch (char* message)
							{
								cout << message << endl;
							}
						}
						break;
					}
					else
					{
						ifs.close();
						d->FreeAllElements();
					}
				}
				ifs.close();
			}
			else 
				cout << "�������� ��� �����." << endl;
		}
		// �������� ���������
		else if (choice == 2) {
			
		}
		// �������� � ����������
		else if (choice == 3) {
			string newk;
			cout << "������� ����: "; cin >> newk;
			unsigned int years;
			cout << "������� years: "; cin >> years;
			unsigned int position;
			cout << "������� position: "; cin >> position;
			Worker* currentWorker = Worker::Readfromkeyboard(newk, years, position);
			int success;
			if (currentWorker != NULL)
			{
				success = d->Insert(currentWorker->GetKey(), currentWorker);

				if (!success)
				{
					delete currentWorker;
				}
				else {
					cout << "������� ���������!" << endl;
				}
			}
		}
		// ������� � �������
		else if (choice == 4) {
			d->PrintDictionaryConsole();
		}
		// ��������� ������ � �����
		else if (choice == 5) {
			string outputFile;
			cout << "������� �������� ������ �����: "; cin >> outputFile;

			ofstream ofs; // ���� ������
			ofs.open(outputFile);

			d->PrintDictionary(ofs);
			
			ofs.close();
		}
		// ������ �������� �� �����
		else if (choice == 6) {
			string k;
			cout << "������� ����: "; cin >> k;
			StringKey* sName = new StringKey(k);

			cout << "���� " << k << " �� ��������� " << *(d->Find(sName)) << endl;
		}
		// ������� ���� � ��������
		else if (choice == 7) {
			string kdel;
			cout << "������� ����, ������� ����� �������: "; cin >> kdel;

			StringKey* sName = new StringKey(kdel);

			Worker* currentWorker = d->Delete(sName);

			if (d->Find(sName) == NULL)
				cout << "������� �������!" << endl;
			else
				cout << "�������� �� �������!" << endl;

			delete currentWorker; // �������� ���������
			delete sName; // ����������
		}
		// ������� ��� ������
		else if (choice == 8) {
			string flag;
			cout << "�� ������������� ������ ������� ��� ������ (Y/N): "; cin >> flag;
			if (flag == "Y") {
				d->FreeAllElements();
				if(d->IsEmpty())
					cout << "������ �������!" << endl;
				else
					cout << "������! ������ �� �������." << endl;
			}
			else
				cout << "�������� ��������!" << endl;
		}
		// �������� ���-�� ���������� ������
		else if (choice == 9) {
			int count_k = d->CountOfKey();
			if (count_k == 0)
				cout << "������ ������! ���������� ���������� ������: 0" << endl;
			else
				cout << "���������� ���������� ������: " << count_k << endl;
		}
		//�������� ������ ������
		else if (choice == 10) {

		}
		else
			break;
	}

	// ������� ������ �� ������
	d->FreeAllElements();
	delete d; // �������� �������

	return 0;
}

bool ConvertStringToInt(const string& s, unsigned int& num)
{
	istringstream myStream(s);

	if (myStream >> num) // ������� � unsigned int �������
		return true;
	else
		return false;
}