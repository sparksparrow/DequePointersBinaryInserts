#include "dequePointers.h"
#include <iostream>
#include <time.h>


using namespace std;

long long int nOperations = 0;

Deque::Node::Node(int data, Node* nextPtr, Node* previousPtr)
{
	this->data = data;
	this->nextPtr = nextPtr;
	this->previousPtr = previousPtr;
}

Deque::Deque()
{
	size = 0;
	startPtr = nullptr;
	endPtr = nullptr;
}


int& Deque::operator[] (const int index)        //2+1+2+1+13n+1+1+13n+1+2=+26n
{
	if (index >= size || index < 0)             //2
	{
		int rtrn = -1;							//1
		return rtrn;
	}	   	 	
	nOperations += 3;
	
	Node* current;
	Node* save;	

if (size / 2 >= index)                          //2         //Узнаем, с какой стороны быстрее пойти
{
	nOperations += 2;

	nOperations += 1;
	for (int i = 0; i < index; i++)				//1+13n	   	//Переносим ненужные элементы в хвост дека
	{
		startPtr->previousPtr = endPtr;			//2
		endPtr->nextPtr = startPtr;				//2
		save = startPtr;						//1
		startPtr = startPtr->nextPtr;			//2
		save->nextPtr = nullptr;				//2
		endPtr = endPtr->nextPtr;				//2
		startPtr->previousPtr = nullptr;		//2
		nOperations += 13;
	}

	current = startPtr;							//1			//Берем нужное значение
	nOperations += 1;

	nOperations += 1;
	for (int i = 0; i < index; i++)				//1+13n		//Возвращаем элементы на место
	{
		endPtr->nextPtr = startPtr;				//2
		startPtr->previousPtr = endPtr;			//2
		save = endPtr;							//1
		endPtr = endPtr->previousPtr;			//2
		save->previousPtr = nullptr;			//2
		startPtr = startPtr->previousPtr;		//2
		endPtr->nextPtr = nullptr;				//2
		nOperations += 13;
	}
}
else
{
	nOperations += 2;
	int sizeEnd = size - 1;  
	nOperations += 2;
	nOperations += 1;
	for (int i = sizeEnd; i > index; i--)        //1+13n	//Переносим ненужные элементы в начало дека
	{
		endPtr->nextPtr = startPtr;				 //2
		startPtr->previousPtr = endPtr;			 //2
		save = endPtr;							 //1
		endPtr = endPtr->previousPtr;			 //2
		save->previousPtr = nullptr;			 //2
		startPtr = startPtr->previousPtr;		 //2
		endPtr->nextPtr = nullptr;	             //2
		nOperations += 13;
	}											 

	current = endPtr;							 //1		 //Берем нужное значение
	nOperations += 1;

	nOperations += 1;
	for (int i = sizeEnd; i > index; i--)		 //1+13n	 //Возвращаем элементы на место
	{
		startPtr->previousPtr = endPtr;			 //2
		endPtr->nextPtr = startPtr;				 //2
		save = startPtr;						 //1
		startPtr = startPtr->nextPtr;			 //2
		save->nextPtr = nullptr;				 //2
		endPtr = endPtr->nextPtr;				 //2
		startPtr->previousPtr = nullptr;		 //2
		nOperations += 13;
	}
}
nOperations += 1;
	return current->data;						 //1
}

void Deque::pushBack(int data)
{	
	if (size == 0)								 //Проверка на отсутствие через переменную size
	{
		Node* node = new Node(data, nullptr, nullptr);
		startPtr = node;
		endPtr = node;
	}
	else
	{
		Node* node = new Node(data, nullptr, endPtr);       //Создание новой ноды (указатель на предыдущие ноды сразу инициализируется)
		endPtr->nextPtr = node;                             //Последняя нода указывает на новую ноду
		endPtr = node;										//Указатель класса ссылается на последнюю ноду (добавленную) 
	}
	size++;
}

void Deque::popBack()
{
	if (size == 0)								    //Проверка на отсутствие через переменную size
	{
		cout << "Дек пуст!" << endl;
		return;
	}
	int data = endPtr->data;                        //Берем значение ноды
	if (endPtr->previousPtr == nullptr)             //Проверяем, является ли нода последней
	{		
		delete endPtr;								//Удаляем последнюю ноду
		endPtr = nullptr;                           //Все указатели класса ссылаются на nullptr
		startPtr = nullptr;
	}
	else
	{
		endPtr = endPtr->previousPtr;                //Указатель класса ссылается на предпоследнюю ноду
		delete endPtr->nextPtr;                      //Удаляем последнюю ноду (через указатель предпоследней)
		endPtr->nextPtr = nullptr;                   //Последняя нода ссылается на nullptr
	}
	size--;                                          //Уменьшаем значение количетсва 
}

void Deque::pushFront(int data)
{
	if (size == 0)									 //Проверка на отсутствие через переменную size
	{
		Node* node = new Node(data, nullptr, nullptr);
		startPtr = node;
		endPtr = node;
	}
	else
	{
		Node* node = new Node(data, startPtr, nullptr);               //Создание новой ноды (указатель на следующую ноды сразу инициализируется)
		startPtr->previousPtr = node;								  //Первая нода указывает на новую ноду
		startPtr = node;											  //Указатель класса указывает на первую ноду (добавленную) 
	}
	size++;
}

void Deque::popFront()
{
	if (size == 0)                            //Проверка на отсутствие через переменную size
	{
		cout << "Дек пуст!" << endl;
		return;
	}
	int data = startPtr->data;							//Берем значение ноды
	if (startPtr->nextPtr == nullptr)					//Проверяем, является ли нода последней
	{
		delete startPtr;								//удаляем последнюю ноду
		endPtr = nullptr;								//Все указатели класса ссылаются на nullptr
		startPtr = nullptr;
	}
	else
	{													  //Указатель класса ссылается на вторую ноду от начала
		startPtr = startPtr->nextPtr;					  //Удаляем первую ноду (через указатель второй ноды)
		delete startPtr->previousPtr;					  //Первая нода ссылается на nullptr
		startPtr->previousPtr = nullptr;
	}													 
	size--;													//Уменьшаем значение количетсва 
}

void Deque::show()
{
	if (size == 0)                           //Проверка на отсутствие через переменную size
	{
		cout << "пуст!";
	return;
	}                              

	Node* current = startPtr;
		while (current != nullptr)
		{
			cout << current->data << " ";
			current = current->nextPtr;
		}	
}

bool  Deque::isEmpty()
{
	
	return startPtr == nullptr;
}

int Deque::getSize()
{
	return size;
}


void Deque::clear()                       //Очистка дека
{
	Node* current = startPtr;
	while (current != nullptr)
	{
		startPtr = startPtr->nextPtr;
		delete current;
		current = startPtr;
	}
	endPtr = nullptr;
	size = 0;
}

int Deque::head()                             //Вернуть первый элемент
{
	if (startPtr == nullptr)
		return 0;
	return startPtr->data;
}

int Deque::tail()                             //Вернуть второй элемент
{
	if (endPtr == nullptr)
		return 0;
	return endPtr->data;
}

void Deque::fill(int count)                      //Заполнить дек случайными знапчениями
{
	srand(time(NULL));
	while (count > 0) {
		if (size == 0)                           
		{
			Node* node = new Node(rand()%100, nullptr, nullptr);
			startPtr = node;
			endPtr = node;
		}
		else
		{
			Node* node = new Node(rand()%100, nullptr, endPtr);
			endPtr->nextPtr = node;                             
			endPtr = node;										
		}
		size++;
		count--;
	}
}



Deque::~Deque()
{

}