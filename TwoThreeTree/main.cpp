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
	cout << "- МЕНЮ 2-3 дерева" << endl;
	cout << "=====================================================" << endl;
	cout << " (1) добавать ключи и значения в дерево из файла" << endl;
	cout << " (2) ??????добавать случайные ключи и значения" << endl;
	cout << " (3) добавать в дерево ключ и значение с клавиатуры" << endl;
	cout << " (4) вывести дерево в консоль" << endl;
	cout << " (5) сохранить дерево в файле" << endl;
	cout << " (6) искать значение по ключу" << endl;
	cout << " (7) удалить ключ и значение" << endl;
	cout << " (8) удалить ВСЕ дерево" << endl;
	cout << " (9) ??????получить кол-во хранящихся ключей" << endl;
	cout << "(10) ??????получить высоту дерева" << endl;
	cout << "(11) выйти " << endl;
	int choice;
	while (1) {
		choice = 0;
		cout << "Введите действие: "; cin >> choice;
		
		// добавать из файла
		if (choice == 1) {
			string pNameOfFile;
			//cout << "Введите название файла: "; cin >> pNameOfFile;
			pNameOfFile = "progEx2_Test1.txt";
			ifstream ifs; // входной файл
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
								else // ошибка - ввод недействителен, зафиксировать выход
								{
									cout << "Неверный входной файл!" << endl;

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
				cout << "Неверное имя файла." << endl;
		}
		// добавать случайные
		else if (choice == 2) {
			
		}
		// добавать с клавиатуры
		else if (choice == 3) {
			string newk;
			cout << "Введите ключ: "; cin >> newk;
			unsigned int years;
			cout << "Введите years: "; cin >> years;
			unsigned int position;
			cout << "Введите position: "; cin >> position;
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
					cout << "Успешно добавлено!" << endl;
				}
			}
		}
		// вывести в консоль
		else if (choice == 4) {
			d->PrintDictionaryConsole();
		}
		// сохранить дерево в файле
		else if (choice == 5) {
			string outputFile;
			cout << "Введите название нового файла: "; cin >> outputFile;

			ofstream ofs; // фвйл вывода
			ofs.open(outputFile);

			d->PrintDictionary(ofs);
			
			ofs.close();
		}
		// искать значение по ключу
		else if (choice == 6) {
			string k;
			cout << "Введите ключ: "; cin >> k;
			StringKey* sName = new StringKey(k);

			cout << "Ключ " << k << " со значением " << *(d->Find(sName)) << endl;
		}
		// удалить ключ и значение
		else if (choice == 7) {
			string kdel;
			cout << "Введите ключ, который нужно удалить: "; cin >> kdel;

			StringKey* sName = new StringKey(kdel);

			Worker* currentWorker = d->Delete(sName);

			if (d->Find(sName) == NULL)
				cout << "Успешно удалено!" << endl;
			else
				cout << "Удаление не удалось!" << endl;

			delete currentWorker; // удаление временных
			delete sName; // переменных
		}
		// удалить все дерево
		else if (choice == 8) {
			string flag;
			cout << "Вы действительно хотите удалить ВСЕ дерево (Y/N): "; cin >> flag;
			if (flag == "Y") {
				d->FreeAllElements();
				if(d->IsEmpty())
					cout << "Дерево очищено!" << endl;
				else
					cout << "Ошибка! Дерево НЕ очищено." << endl;
			}
			else
				cout << "Удаление отменено!" << endl;
		}
		// получить кол-во хранящихся ключей
		else if (choice == 9) {
			int count_k = d->CountOfKey();
			if (count_k == 0)
				cout << "Дерево пустое! Количество хранящихся ключей: 0" << endl;
			else
				cout << "Количество хранящихся ключей: " << count_k << endl;
		}
		//получить высоту дерева
		else if (choice == 10) {

		}
		else
			break;
	}

	// Очистка памяти от данных
	d->FreeAllElements();
	delete d; // удаление словаря

	return 0;
}

bool ConvertStringToInt(const string& s, unsigned int& num)
{
	istringstream myStream(s);

	if (myStream >> num) // вставил в unsigned int успешно
		return true;
	else
		return false;
}