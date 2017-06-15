#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;

template<typename T = int>
struct Element
{
	T value;
	Element<T>* next;
};

template<typename T = int>
class Stack
{
	Element<T>* front;
	int size = 0;

public:
	Stack();
	~Stack();
	Stack(const Stack& s);
	Stack& operator=(const Stack&);

	int getSize();
	bool isEmpty() const;

	void push(const T&);
	void pop(T& x);
	void clear();
	T top(T&);

	void print();

private:
	void destroy();
	void copy(const Stack& s);
};

template <typename T>
Stack<T>::Stack()
{
	front = NULL;

}

template <typename T>
Stack<T>::~Stack()
{
	destroy();
}

template <typename T>
Stack<T>::Stack(const Stack<T> &s)
{
	copy(s);
}

template <typename T>
Stack<T>&  Stack<T>::operator=(const Stack<T>& s)
{
	if (this != &s)
	{
		destroy();
		copy(s);
	}
	return *this;
}

template <typename T>
void Stack<T>::destroy()
{
	T value;
	while (!isEmpty())
	{
		pop(value);
	}
}

template <typename T>
void Stack<T>::copy(const Stack<T> &s)
{
	if (s.front){
		Element<T> * tmp = s.front, *q = NULL, *r = NULL;
		front = new Element<T>;
		assert(front != NULL);
		front->value = tmp->value;
		front->next = q;
		q = front;
		tmp = tmp->next;
		while (tmp)
		{
			r = new Element<T>;
			assert(r != NULL);
			r->value = tmp->value;
			q->next = r;
			q = r;
			tmp = tmp->next;
		}
		q->next = NULL;
	}
	else
		front = NULL;
}

template <typename T>
bool Stack<T>::isEmpty() const
{
	return (front == NULL);
}

template <typename T>
void Stack<T>::clear()
{
	destroy();
}

template <typename T>
int Stack<T>::getSize()
{
	return size;
}

template <typename T>
void Stack<T>::push(const T& value)
{
	Element<T>* el = new Element<T>;
	el->value = value;

	if (front)
	{
		el->next = front;

	}
	else
	{
		el->next = NULL;
	}
	front = el;

	size++;
}

template <typename T>
void Stack<T>::pop(T& value)
{
	if (front){
		Element<T>* tmp = front;
		value = tmp->value;
		front = front->next;
		delete tmp;
		size--;
	}
	else{
		cout << "Empty stack";
	}

}

template <typename T>
T Stack<T>::top(T &s)
{
	if (front)
	{
		s = front->value;
		return s;
	}
	else
		return NULL;
}

template <typename T>
void Stack<T>::print()
{
	T value;
	while (front){
		pop(value);
		cout << value << " ";
	}
	cout << endl;

}

template <typename T = int>
class Queue{

private:
	Stack<T> s1, s2;
	T size;

public:
	bool isEmpty() const;
	int getFront();
	int getBack();

	void push(const T& x);
	void pop(T& x);
	void print();
	int getSize();

};

template <typename T>
bool Queue<T>::isEmpty() const
{
	return (s1.isEmpty() && s2.isEmpty());
}

template <typename T>
int Queue<T>::getSize()
{
	return (s1.getSize() + s2.getSize());

}

template <typename T>
void Queue<T>::push(const T& x)
{
	s1.push(x);

}

template <typename T>
void Queue<T>::pop(T&x)
{
	if (s2.isEmpty()){
		while (!s1.isEmpty())
		{
			s1.pop(x);
			s2.push(x);
		}
	}
	s2.pop(x);
	cout << x << endl;
}

template <typename T>
int Queue<T>::getFront()
{
	T x;
	if (s2.isEmpty()){
		while (!s1.isEmpty())
		{
			s1.pop(x);
			s2.push(x);
		}
	}
	s2.top(x);
	return x;
}

template <typename T>
int Queue<T>::getBack()
{
	T x;
	if (s1.isEmpty())
	{
		while (!s2.isEmpty())
		{
			s2.pop(x);
			s1.push(x);
		}
	}
	s1.top(x);
	return x;
}

template <typename T>
void Queue<T>::print()
{
	if (!s2.isEmpty())
	{
		s2.print();
		if (!s1.isEmpty()){
			while (!s1.isEmpty())
			{
				T x;
				s1.pop(x);
				s2.push(x);
			}
			s2.print();
		}
	}
	else{
		if (!s1.isEmpty()){
			while (!s1.isEmpty())
			{
				T x;
				s1.pop(x);
				s2.push(x);
			}
			s2.print();
		}
	}
}

int main()
{
	system("pause");
	return 0;
}