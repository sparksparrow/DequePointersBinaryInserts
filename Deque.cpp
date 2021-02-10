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

if (size / 2 >= index)                          //2         //������, � ����� ������� ������� �����
{
	nOperations += 2;

	nOperations += 1;
	for (int i = 0; i < index; i++)				//1+13n	   	//��������� �������� �������� � ����� ����
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

	current = startPtr;							//1			//����� ������ ��������
	nOperations += 1;

	nOperations += 1;
	for (int i = 0; i < index; i++)				//1+13n		//���������� �������� �� �����
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
	for (int i = sizeEnd; i > index; i--)        //1+13n	//��������� �������� �������� � ������ ����
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

	current = endPtr;							 //1		 //����� ������ ��������
	nOperations += 1;

	nOperations += 1;
	for (int i = sizeEnd; i > index; i--)		 //1+13n	 //���������� �������� �� �����
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
	if (size == 0)								 //�������� �� ���������� ����� ���������� size
	{
		Node* node = new Node(data, nullptr, nullptr);
		startPtr = node;
		endPtr = node;
	}
	else
	{
		Node* node = new Node(data, nullptr, endPtr);       //�������� ����� ���� (��������� �� ���������� ���� ����� ����������������)
		endPtr->nextPtr = node;                             //��������� ���� ��������� �� ����� ����
		endPtr = node;										//��������� ������ ��������� �� ��������� ���� (�����������) 
	}
	size++;
}

void Deque::popBack()
{
	if (size == 0)								    //�������� �� ���������� ����� ���������� size
	{
		cout << "��� ����!" << endl;
		return;
	}
	int data = endPtr->data;                        //����� �������� ����
	if (endPtr->previousPtr == nullptr)             //���������, �������� �� ���� ���������
	{		
		delete endPtr;								//������� ��������� ����
		endPtr = nullptr;                           //��� ��������� ������ ��������� �� nullptr
		startPtr = nullptr;
	}
	else
	{
		endPtr = endPtr->previousPtr;                //��������� ������ ��������� �� ������������� ����
		delete endPtr->nextPtr;                      //������� ��������� ���� (����� ��������� �������������)
		endPtr->nextPtr = nullptr;                   //��������� ���� ��������� �� nullptr
	}
	size--;                                          //��������� �������� ���������� 
}

void Deque::pushFront(int data)
{
	if (size == 0)									 //�������� �� ���������� ����� ���������� size
	{
		Node* node = new Node(data, nullptr, nullptr);
		startPtr = node;
		endPtr = node;
	}
	else
	{
		Node* node = new Node(data, startPtr, nullptr);               //�������� ����� ���� (��������� �� ��������� ���� ����� ����������������)
		startPtr->previousPtr = node;								  //������ ���� ��������� �� ����� ����
		startPtr = node;											  //��������� ������ ��������� �� ������ ���� (�����������) 
	}
	size++;
}

void Deque::popFront()
{
	if (size == 0)                            //�������� �� ���������� ����� ���������� size
	{
		cout << "��� ����!" << endl;
		return;
	}
	int data = startPtr->data;							//����� �������� ����
	if (startPtr->nextPtr == nullptr)					//���������, �������� �� ���� ���������
	{
		delete startPtr;								//������� ��������� ����
		endPtr = nullptr;								//��� ��������� ������ ��������� �� nullptr
		startPtr = nullptr;
	}
	else
	{													  //��������� ������ ��������� �� ������ ���� �� ������
		startPtr = startPtr->nextPtr;					  //������� ������ ���� (����� ��������� ������ ����)
		delete startPtr->previousPtr;					  //������ ���� ��������� �� nullptr
		startPtr->previousPtr = nullptr;
	}													 
	size--;													//��������� �������� ���������� 
}

void Deque::show()
{
	if (size == 0)                           //�������� �� ���������� ����� ���������� size
	{
		cout << "����!";
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


void Deque::clear()                       //������� ����
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

int Deque::head()                             //������� ������ �������
{
	if (startPtr == nullptr)
		return 0;
	return startPtr->data;
}

int Deque::tail()                             //������� ������ �������
{
	if (endPtr == nullptr)
		return 0;
	return endPtr->data;
}

void Deque::fill(int count)                      //��������� ��� ���������� �����������
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