#ifndef _STRING_KEY_H_
#define _STRING_KEY_H_

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class StringKey
{
private:
	string strK;
	
public:
	StringKey(){}// Пустой конструктор
	StringKey(const StringKey& otherStringKey) // Конструктор копирования
	{
		strK = otherStringKey.strK;
	}

	// Конструктор, который получает строку
	StringKey(const string& strString)
	{
		strK=strString;
	}

	~StringKey() {} // Деструктор
	
	//алфавитный сравнение между 2 строками
	int Compare(const StringKey* s)const;
	string getString()const; // Возвращвет str

	// Чтение stringKey из файла. null, если при чтении произошла ошибка
	static StringKey* Read(ifstream& inputFile);
	// Чтение с клавиатуры
	static StringKey* Readfromkeyboard(string new_k);
};

#endif