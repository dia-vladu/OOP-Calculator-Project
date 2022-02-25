#pragma once
#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;

class Calculator {
	char* expresie = nullptr;
	double rezultat;
	static int idCalculator;

public:
	//constructor default 
	Calculator() {
		expresie = nullptr;
		rezultat = 0;
	}

	//constructor cu parametrii 
	Calculator(const char* exp) {
		if (exp != nullptr) {
			expresie = new char[strlen(exp) + 1];
			strcpy_s(expresie, strlen(exp) + 1, exp);
		}
		rezultat = 0;
	}

	//setter expresie 
	void setExpresie(const char* exp) {
		if (exp != nullptr) {
			expresie = new char[strlen(exp) + 1];
			strcpy_s(expresie, strlen(exp) + 1, exp);
		}
	}

	//getter expresie 
	char* getExpresie() {
		return expresie;
	}

	//setter rezultat 
	void setRezultat(double rez) {
		rezultat = rez;
	}

	//getter rezultat 
	double getRezultat() {
		return rezultat;
	}

	//setter idCalculator 
	static void setid(int id) {
		Calculator::idCalculator = id;
	}

	//getter idCalculator 
	static int getid() {
		return idCalculator;
	}

	//metoda generica 
	bool corect(const char* s) {
		int roundOpen = 0;
		int roundClose = 0;
		int squareOpen = 0;
		int squareClose = 0;
		for (unsigned i = 0; i < strlen(s); i++) {
			switch (s[i])
			{
			case '(':
				roundOpen++;
				break;
			case ')':
				roundClose++;
				break;
			case '[':
				squareOpen++;
				break;
			case ']':
				squareClose++;
				break;
			default:
				break;
			}
		}
		if (roundOpen == roundClose && squareOpen == squareClose) {
			return true;
		}
		else {
			return false;
		}
	}

	//metoda generica 
	bool evaluate(const char* s) {
		unsigned i;
		for (i = 0; i < strlen(s); i++) {
			if (strchr("0123456789[](){}+-*/^#. ", s[i]) != NULL) {
				continue;
			}
			else {
				return false;
				break;
			}
		}
		if (i == strlen(s)) {
			if (corect(s) == true) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	//metoda generica 
	int countDigits(double input) {
		string aux = to_string(input);
		int nr = aux.length();
		for (int i = aux.length() - 1; i >= 0; i--) {
			if (aux[i] == '0') {
				nr--;
			}
			else {
				break;
			}
		}
		if (aux[0] == '-') {
			nr--;
		}
		int digits = --nr;
		return digits;
	}

	//metoda generica 
	void evaluatePostfix(const char* exp, double& no)
	{
		Stack stack(strlen(exp));
		int i;

		for (i = 0; exp[i]; ++i)
		{
			if (exp[i] == ' ') {
				continue;
			}
			else {
				if (isdigit(exp[i]))
				{
					double num = 0;
					string nr = "";
					while (exp[i] != ' ')
					{
						nr += exp[i];
						i++;
					}
					i--;
					num = stod(nr);
					stack.push(num);
				}
				else
				{
					double val1; stack.pop(val1);
					double val2; stack.pop(val2);

					switch (exp[i])
					{
					case '+': stack.push(val2 + val1); break;
					case '-': stack.push(val2 - val1); break;
					case '*': stack.push(val2 * val1); break;
					case '/':
						/*if (val1 == 0) {
							throw exception("Eroare: impartire la 0 !!!");
						}
						else {*/
						stack.push(val2 / val1); break;
						//}
					case '^': stack.push(pow(val2, val1)); break;
					case '#':
						/*if (val1 <= 0) {
							throw  exception("Eroare: ordinul radicalului invalid !!!");
						}
						else {*/
						stack.push(pow(val2, (1.0 / val1))); break;
						//}
					}
				}
			}
		}
		double num;
		stack.pop(num);
		no = num;
	}

	//operator relational 
	bool operator==(Calculator c) {
		return rezultat == c.rezultat;
	}

	//operator 
	Calculator operator!() {
		rezultat *= -1;
		return *this;
	}

	friend istream& operator>>(istream& in, Calculator& c);
	friend ostream& operator<<(ostream& out, Calculator c);
};
int Calculator::idCalculator = 333;

//operator citire 
istream& operator>>(istream& in, Calculator& c) {
	cout << "Dati expresie in postfix: ";
	string buffer;
	getline(in, buffer);
	c.setExpresie(buffer.c_str());
	double num;
	c.evaluatePostfix(buffer.c_str(), num);
	c.rezultat = num;
	return in;
}

//operator afisare 
ostream& operator<<(ostream& out, Calculator c) {
	if (c.expresie != nullptr) {
		out << "Expresia introdusa: " << c.expresie << endl;
	}
	else {
		out << "Expresia introdusa: " << endl;
	}
	out << "Rezultat: " << c.rezultat << endl;
	return out;
}
