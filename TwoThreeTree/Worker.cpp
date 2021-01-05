#include "Worker.h"

//Конструктор копирования
Worker::Worker(const Worker& otherWorker) throw(char*)
{
	if (otherWorker.name != NULL)
	{
		name = new StringKey(*otherWorker.name);
		years=otherWorker.years;
		position=otherWorker.position;
	}
	else
	{
		throw "allocation error!";
	}
}



unsigned int Worker::getseniority()
{
	return this->years;
}

unsigned int Worker::getPosition()
{
	return this->position;
}

StringKey* Worker::GetKey()const
{
	return name;
}

//ввод от пользователя, вернуть ноль, если произошла ошибка
Worker* Worker::Read(ifstream& inputFile)
{
	StringKey* tempSKey;
	Worker* outWorker;
	
	try
	{
		tempSKey= StringKey::Read(inputFile);
	}
	catch (...)
	{
		return NULL;
	}
	if (!tempSKey)
	{
		return NULL;
	}

	outWorker=new Worker;

	outWorker->name=tempSKey;
	try
	{
		if (!(inputFile >> outWorker->years >> outWorker->position))
		{
			delete outWorker;

			return NULL;
		}
	}
	catch (...)
	{
		delete outWorker;

		return NULL;
	}
	return outWorker;
}

// чтение ввода worker с клавиатуры
Worker* Worker::Readfromkeyboard(string new_k, unsigned int new_years, unsigned int new_position)
{
	StringKey* tempSKey = StringKey::Readfromkeyboard(new_k);

	Worker* outWorker = new Worker;

	outWorker->name = tempSKey;
	outWorker->years = new_years;
	outWorker->position = new_position;

	return outWorker;
}