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
	// Конструктор
	Worker():name(0), years(0), position(0){}

	Worker(StringKey* name,unsigned int years,unsigned int position):name(name), years(years), position(position){}

	// Деструктор
	~Worker()
	{
		delete name;
	}

	Worker(const Worker& otherWorker)throw(char*); // Конструктор копирования. Выдает исключение, если имя другого worker является нулевым
	
	// Возвращает ключ (имя worker)
	StringKey* GetKey()const;
	
	//чтение ввода worker из файла. null, если произошла ошибка чтения
	static Worker* Read(ifstream& inputFile);

	//чтение ввода worker с клавиатуры
	static Worker* Readfromkeyboard(string new_k, unsigned int new_years, unsigned int new_position);

	//operator << для вывода
	friend ostream& operator<<(ostream& out, const Worker& worker)
	{
		out << worker.name->getString() << "\t " << worker.years
			<< "\t " << worker.position;
		return out;
	}

	
	unsigned int getseniority(); // Возвращает years
	unsigned int getPosition(); // Возвращает позицию
};

#endif