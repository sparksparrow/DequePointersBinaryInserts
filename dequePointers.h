#pragma once

class Deque
{
private:
	int size;	                      //������ ����
	
	struct Node                       //���� ����
	{
		int data;                      //���������� ����
		Node* nextPtr;                 //��������� �� ��������� �������
		Node* previousPtr;             //��������� �� ���������� �������

		Node(int data, Node* nextPtr, Node* previousPtr);    //����������� ����
	};

	Node* startPtr;                     //��������� �� ������ ������� ����
	Node* endPtr;                       //��������� �� ��������� ������� ����

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