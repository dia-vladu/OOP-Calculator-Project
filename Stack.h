#pragma once
#include <iostream>
#include <string>
using namespace std;

class Stack
{
	int top;
	unsigned capacity;
	double* array = nullptr;

public:
	//constructor implicit 
	Stack() {
		top = -1;
		capacity = 0;
		array = nullptr;
	}

	//constructor cu parametrii 
	Stack(int Top, unsigned Capacity, double* Array) {
		top = Top;
		capacity = Capacity;
		if (Array != nullptr) {
			array = new double[Capacity];
			for (unsigned i = 0; i < Capacity; i++) {
				array[i] = Array[i];
			}
		}
	}

	//constructor cu parametrii 
	Stack(unsigned Capacity) {
		top = -1;
		capacity = Capacity;
		array = new double[Capacity];
	}

	//destructor 
	~Stack() {
		if (array != nullptr) {
			delete[] array;
			array = nullptr;
		}
	}

	//constructor de copiere 
	Stack(const Stack& s) {
		top = s.top;
		capacity = s.capacity;
		if (s.array != nullptr) {
			array = new double[s.capacity];
			for (unsigned i = 0; i < s.capacity; i++) {
				array[i] = s.array[i];
			}
		}
	}

	//operator = 
	Stack operator=(const Stack& s) {
		if (this != &s) {
			if (s.array != nullptr) {
				if (array != nullptr) {
					delete[] array;
				}
				array = new double[s.capacity];
				for (unsigned i = 0; i < s.capacity; i++) {
					array[i] = s.array[i];
				}
			}
			top = s.top;
			capacity = s.capacity;
		}
		return *this;
	}

	//metoda generica 
	int isEmpty()
	{
		return (top == -1);
	}

	//metoda generica 
	double peek()
	{
		return array[top];
	}

	//metoda generica 
	void pop(double& num)
	{
		if (!isEmpty()) {
			num = array[top--];
		}
	}

	//metoda generica 
	void push(double op)
	{
		array[++top] = op;
	}

	//setter top 
	void setTop(int t) {
		if (t > -1) {
			top = t;
		}
	}

	//getter top 
	int getTop() {
		return top;
	}

	//setter capacity 
	void setCapacity(unsigned c) {
		if (c >= 0) {
			capacity = c;
		}
	}

	//getter capacity 
	unsigned getCapacity() {
		return capacity;
	}

	//setter array 
	void setArray(double* a, unsigned c) {
		if (a != nullptr) {
			if (array != nullptr) {
				delete[] array;
			}
			array = new double[c];
			for (int i = 0; i < c; i++) {
				array[i] = a[i];
			}
		}
	}

	//getter array 
	double* getArray() {
		return array;
	}

	//operator relational 
	bool operator> (Stack s) {
		return capacity > s.capacity;
	}

	//operator relational 
	bool operator< (Stack s) {
		return capacity < s.capacity;
	}

	friend istream& operator>>(istream& in, Stack& s);
	friend ostream& operator<<(ostream& out, Stack s);
};

//operator citire 
istream& operator>>(istream& in, Stack& s) {
	cout << "Dati capacitatea: ";
	in >> s.capacity;
	cout << "Dati top: ";
	in >> s.top;
	if (s.array != nullptr) {
		delete[] s.array;
	}
	s.array = new double[s.capacity];
	cout << "Dati elemente array: ";
	for (int i = 0; i < s.capacity; i++) {
		in >> s.array[i];
	}
	return in;
}

//operator afisare 
ostream& operator<<(ostream& out, Stack s) {
	out << "Top: " << s.top << endl;
	out << "Capacity: " << s.capacity << endl;
	if (s.array) {
		out << "Array: ";
		for (unsigned i = 0; i < s.capacity; i++) {
			cout << s.array[i] << endl;
		}
	}
	else {
		out << "Array: " << endl;
	}
	return out;
}
