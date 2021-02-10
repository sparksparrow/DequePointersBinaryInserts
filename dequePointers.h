#pragma once

class Deque
{
private:
	int size;	                      //размер дека
	
	struct Node                       //нода дека
	{
		int data;                      //переменная дека
		Node* nextPtr;                 //указатель на следующий элемент
		Node* previousPtr;             //указатель на предыдущий элемент

		Node(int data, Node* nextPtr, Node* previousPtr);    //конструктор ноды
	};

	Node* startPtr;                     //указатель на первый элемент дека
	Node* endPtr;                       //указатель на последний элемент дека

public:	
	Deque();
	int getSize();
	int& operator[] (const int index);
	void pushBack(int data);
	void popBack();
	void pushFront(int data);
	void popFront();
	bool isEmpty();	
	void show();
	void clear();
	int head();
	int tail();
	void fill(int count);	
	
	~Deque();
};