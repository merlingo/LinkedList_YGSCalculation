#include <iostream>
#include <ostream>
#define LinkedList_h

using namespace std;

template <class T>
struct Node
{
	T data;
	Node <T> *link;
};

template <class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	void destroyList();
	bool emptyList();
	int length();
	Node <T> * search(T& item) const;
	void insertFirst(T& item);
	void insertLast(T item);
	void deleteNode(T& item);

	Node <T> *head;
	Node <T> *last;
	int count;

	std::ostream &operator <<(LinkedList<T> &L)
	{
		std::ostream &os;
		Node <T> *q;
		q = L.head;
		while (q != NULL)
		{
			os << q->data;
			os << endl;
			q = q->link;
		}
		return os;
	};
};
template <class T>
LinkedList<T>::LinkedList()
{
	head = last = NULL;
	count = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	destroyList();
}

template <class T>
void LinkedList<T>::destroyList()
{
	Node <T> *p;
	while (head != NULL)
	{
		p = head;
		head = head->link;
		delete p;
	}
	last = NULL;
	count = 0;
}

template <class T>
bool LinkedList<T>::emptyList()
{
	return head == NULL;
}

template <class T>
int LinkedList<T>::length()
{
	return count;
}

template <class T>
Node <T> * LinkedList<T>::search(T& item) const
{
	Node <T> *p = head;
	bool found = false;
	//node in the list
	while (p != NULL && !found) //search the list
	{
		if (p->data == item)
			found = true;
		else
			p = p->link;
	}
	return p;
}//end search

template <class T>
void LinkedList<T>::insertFirst(T& item)
{
	Node <T> *p = new Node<T>; //create the new node
	p->data = item;
	p->link = head;
	head = p; //make head point to the actual first node
	if (last == NULL)
		last = p;
	count++; //increment count
}//end insertFirst

template <class T>
void LinkedList<T>::insertLast(T item)
{
	Node<T> *p = new Node <T>; //create the new node
	p->data = item;
	p->link = NULL;
	if (head != NULL)
	{
		last->link = p;
		last = p;
	}
	else
	{
		head = last = p;
	}
	count++; //increment count
}//end insertLast

template <class T>
void LinkedList<T>::deleteNode(T& item)
{
	Node <T> *p, *q;
	bool found = false;
	if (head == NULL)
		cout << "Cannot delete from an empty list." << endl;
	else
	{
		if (head->data == item)
		{
			p = head;
			head = head->link;
			count--;
			if (head == NULL)
				last = NULL;
			delete p;
		}
		else //search the list for the node with the given info
		{
			found = false;
			p = head;
			q = head->link;

			while (q != NULL && !found)
			{
				if (q->data == item)
				{
					found = true;
				}
				else
				{
					p = q;
					q = q->link;
				}
			}//end while
			if (found)
			{
				p->link = q->link;
				if (last == q) //node to be deleted was the last node
					last = p; //update the value of last
				count--;
				delete q; //delete the node from the list
			}
			else
				cout << "The item to be deleted is not in " << "the list." << endl;
		}//end else
	}//end else
}//end deleteNode


