#include "StringKey.h"

string StringKey::getString()const // Возвращает str
{
	return strK;
}

// алфавитное сравнение между 2 строками
int StringKey::Compare(const StringKey* s)const
{
	return (strK.compare(s->strK)); 
}

// Чтение из файла
StringKey* StringKey::Read(ifstream& inputFile)
{
	string inKey;
	StringKey* outKey = NULL;

	if(inputFile >> inKey)
	{
		outKey = new StringKey(inKey);
		
		return outKey;
	}

	return NULL;
}

// Чтение с клавиатуры
StringKey* StringKey::Readfromkeyboard(string new_k)
{
	StringKey* outKey = new StringKey(new_k);

	return outKey;
}