#ifndef __AISD_LIST__
#define __AISD_LIST__

#include <iostream>
using namespace std;

template <class ValType>
class Node
{
public:
	ValType val;
	Node<ValType>* next;
	Node();
	Node(const ValType data);
	Node(const ValType &v, Node<ValType>* n);
	Node(const Node<ValType> &z);
	~Node() {}
	Node<ValType>& operator=(const Node<ValType>& z);
	friend ostream & operator<<(ostream &out, const Node<ValType> &mt)
	{
		out << mt.val;
		return out;
	}
};

template <class ValType>
class List
{
	Node<ValType>* head;
public:
	List() { head = NULL; }
	List(const Node<ValType> &z);
	List(const List<ValType>& list2);
	List<ValType>& operator=(const List<ValType>& list2);
	~List();

	void InsertToHead(const ValType& data); 
	void InsertToTail(const ValType& data); 
	void InsertToTail(const Node<ValType> &z);
	void InsertAfter(Node<ValType>* node, const ValType& data);
	void Delete(const ValType& data); 
	Node<ValType>* Search(const ValType& data);
	void Clean(); 
	int GetSize(); 

	Node<ValType>* GetHead() const { return head; } 
	bool operator==(const List<ValType> &l)const;
	bool operator!=(const List<ValType> &l)const;

	void Inverse(); 
	List<ValType> Merge(Node<ValType>* node, const List<ValType>& list2); // создать список3, добавив список2 в текущий список после указателя node  
	List<ValType> Merge(const List<ValType>& list2); // создать список3, добавив в конец текущего списка список2

	friend ostream & operator<<(ostream &out, const List<ValType> &mt)
	{
		Node<ValType> *t = mt.head;
		while (t != NULL)
		{
			out << t->val << " ";
			t = t->next;
		}
		return out;
	}
};

template<class ValType>
inline Node<ValType>::Node()
{
	next = NULL;
}

template<class ValType>
inline Node<ValType>::Node(const ValType data)
{
	val = data;
	next = NULL;
}

template<class ValType>
inline Node<ValType>::Node(const ValType & v, Node<ValType> * n)
{
	val = v;
	next = n;
}

template<class ValType>
inline Node<ValType>::Node(const Node & z)
{
	val = z.val;
	next = z.next;
}

template<class ValType>
inline Node<ValType>& Node<ValType>::operator=(const Node<ValType>& z)
{
	if (this != &z)
	{
		val = z.val;
		next = z.next;
	}
	return *this;
}

template<class ValType>
inline List<ValType>::List(const Node<ValType>& z)
{
	head = new Node<ValType>(z);
}

template<class ValType>
inline List<ValType>::List(const List<ValType> & list2)
{
	if (list2.head != NULL)
	{
		head = new Node<ValType>(list2.head->val);
		Node<ValType> *t = head;
		Node<ValType> *tt = list2.head->next;
		while (tt != NULL)
		{
			t->next = new Node<ValType>(tt->val);
			t = t->next;
			tt = tt->next;
		}
	}
	else
		head = NULL;
}

template<class ValType>
inline List<ValType> & List<ValType>::operator=(const List<ValType> & list2)
{
	if (this != &list2)
	{
		Clean();
		if (list2.head != NULL)
		{
			head = new Node<ValType>(list2.head->val);
			Node<ValType> *t = head;
			Node<ValType> *tt = list2.head->next;
			while (tt != NULL)
			{
				t->next = new Node<ValType>(tt->val);
				t = t->next;
				tt = tt->next;
			}
		}
	}
	return *this;
}

template<class ValType>
inline List<ValType>::~List()
{
	Node<ValType> *t = head;
	Node<ValType> *tt = head;
	if (t != NULL)
	{
		while (t->next != NULL)
		{
			tt = t->next;
			delete t;
			t = tt;
		}
		delete t;
	}
}

template<class ValType>
inline void List<ValType>::InsertToHead(const ValType & data)
{
	Node<ValType> *t = new Node<ValType>(data);
	t->next = head;
	head = t;
}

template<class ValType>
inline void List<ValType>::InsertToTail(const ValType & data)
{
	Node<ValType> *t = head;
	if (t != NULL)
	{
		while (t->next != NULL)
			t = t->next;
		t->next = new Node<ValType>(data);
	}
	else
		head = new Node<ValType>(data);
}

template<class ValType>
inline void List<ValType>::InsertToTail(const Node<ValType>& z)
{
	Node<ValType> *t = head;
	if (t != NULL)
	{
		while (t->next != NULL)
			t = t->next;
		t->next = new Node<ValType>(z);
	}
	else
		head = new Node<ValType>(z);
}

template<class ValType>
inline void List<ValType>::InsertAfter(Node<ValType>* node, const ValType & data)
{
	if (head == NULL)
		throw "Head null";
	if (node != NULL)
	{
		Node<ValType> *t = new Node<ValType>(data, node->next);
		node->next = t;
	}
}

template<class ValType>
inline void List<ValType>::Delete(const ValType & data)
{
	Node<ValType> *t = head;
	Node<ValType> *tt = head;
	if (t != NULL)
	{
		while ((t->next != NULL) && (t->val != data))
		{
			tt = t;
			t = t->next;
		}
		if (t->val == data)
		{
			tt->next = t->next;
			if (t == head)
				head = head->next;
			delete t;
		}
	}
}

template<class ValType>
inline Node<ValType> * List<ValType>::Search(const ValType & data)
{
	Node<ValType> *t = head;
	if (t != NULL)
	{
		while ((t->next != NULL) && (t->val != data))
		{
			t = t->next;
		}
		if (t->val == data)
			return t;
		else
			return NULL;
	}
	else
		return NULL;
}

template<class ValType>
inline void List<ValType>::Clean()
{
	Node<ValType> *t = head;
	Node<ValType> *tt = head;
	if (t != NULL)
	{
		while (t->next != NULL)
		{
			tt = t->next;
			delete t;
			t = tt;
		}
		delete t;
		head = NULL;
	}
}

template<class ValType>
inline int List<ValType>::GetSize()
{
	int i = 0;
	Node<ValType> *t = head;
	while (t != NULL)
	{
		i++;
		t = t->next;
	}
	return i;
}

template<class ValType>
inline bool List<ValType>::operator==(const List<ValType> &l) const
{
	Node<ValType> *t = head;
	Node<ValType> *tt = l.head;
	bool f = true;
	while ((t != NULL) && (tt != NULL) && (f))
	{
		if (t->val != tt->val)
			f = false;
		t = t->next;
		tt = tt->next;
	}
	if ((t != NULL) || (tt != NULL))
		f = false;
	return f;
}

template<class ValType>
inline bool List<ValType>::operator!=(const List<ValType>& l) const
{
	return !(*this == l);
}

template<class ValType>
inline void List<ValType>::Inverse()
{
	if (head != NULL)
	{
		Node<ValType> *t = head;
		Node<ValType> *tt = NULL;
		Node<ValType> *ttt = head->next;
		if ((t != NULL) && (t->next != NULL))
		{
			do
			{
				ttt = t->next;
				t->next = tt;
				tt = t;
				t = ttt;
			} while (t != NULL);
			head = tt;
		}
	}
}

template<class ValType>
inline List<ValType> List<ValType>::Merge(Node<ValType>* node, const List<ValType> & list2)
{
	if (head != NULL)
	{
		List<ValType> l(head->val);
		Node<ValType>* t = l.head;
		Node<ValType>* tt = head;
		while ((tt->next != NULL) && (tt != node))
		{
			t->next = new Node<ValType>(tt->next->val);
			t = t->next;
			tt = tt->next;
		}
		if (node != NULL)
		{
			Node<ValType>* ttt = list2.head;
			while (ttt != NULL)
			{
				t->next = new Node<ValType>(ttt->val);
				t = t->next;
				ttt = ttt->next;
			}
			while (tt->next != NULL)
			{
				t->next = new Node<ValType>(tt->next->val);
				t = t->next;
				tt = tt->next;
			}
		}
		return l;
	}
	else
	{
		List<ValType> l;
		return l;
	}
}

template<class ValType>
inline List<ValType> List<ValType>::Merge(const List<ValType>& list2)
{
	if (head != NULL)
	{
		List<ValType> l(head->val);
		Node<ValType> *t = head->next;
		Node<ValType> *tt = l.head;
		while (t != NULL)
		{
			tt->next = new Node<ValType>(t->val);
			t = t->next;
			tt = tt->next;
		}
		t = list2.head;
		while (t != NULL)
		{
			tt->next = new Node<ValType>(t->val);
			t = t->next;
			tt = tt->next;
		}
		return l;
	}
	else
	{
		List<ValType> l(list2);
		return l;
	}
}

#endif