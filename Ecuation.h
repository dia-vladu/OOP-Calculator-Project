#pragma once
#include <iostream>
#include <string>
using namespace std;

class Ecuation {
	char* ecuation = nullptr;
	const int length;

public:
	//constructor default 
	Ecuation() : length(0) {
		ecuation = nullptr;
	}

	//constructor cu parametrii 
	Ecuation(const char* expresie, int Length) : length(Length) {
		if (expresie != nullptr) {
			if (ecuation != nullptr) {
				delete[] ecuation;
				ecuation = nullptr;
			}
			ecuation = new char[strlen(expresie) + 1];
			strcpy_s(ecuation, strlen(expresie) + 1, expresie);
		}
	}

	//constructor cu parametrii 
	Ecuation(const char* expresie) : length(strlen(expresie)) {
		if (expresie != nullptr) {
			if (ecuation != nullptr) {
				delete[] ecuation;
				ecuation = nullptr;
			}
			ecuation = new char[strlen(expresie) + 1];
			strcpy_s(ecuation, strlen(expresie) + 1, expresie);
		}
	}

	//destructor 
	~Ecuation() {
		if (ecuation != nullptr) {
			delete[] ecuation;
			ecuation = nullptr;
		}
	}

	//constructor de copiere 
	Ecuation(const Ecuation& ip) : length(ip.length) {
		if (ip.ecuation != nullptr) {
			if (ecuation != nullptr) {
				delete[] ecuation;
				ecuation = nullptr;
			}
			ecuation = new char[strlen(ip.ecuation) + 1];
			strcpy_s(ecuation, strlen(ip.ecuation) + 1, ip.ecuation);
		}
	}

	//operator = 
	Ecuation operator=(const Ecuation& ip) {
		if (this != &ip) {
			if (ip.ecuation != nullptr) {
				if (ecuation != nullptr) {
					delete[] ecuation;
					ecuation = nullptr;
				}
				ecuation = new char[strlen(ip.ecuation) + 1];
				strcpy_s(ecuation, strlen(ip.ecuation) + 1, ip.ecuation);
			}
		}
		return *this;
	}

	//metoda generica 
	string extractOperators(Ecuation e) {
		string op;
		for (int i = 0; i < strlen(e.ecuation); i++) {
			if (strchr("+-*/^#", e.ecuation[i]) != NULL) {
				op += e.ecuation[i];
			}
		}
		return op;
	}

	//metoda generica 
	int gradOperator(char op) {

		if (op == '^' || op == '#') {
			return 3;
		}
		if (op == '*' || op == '/') {
			return 2;
		}
		if (op == '+' || op == '-') {
			return 1;
		}
		return 0;
	}

	//metoda generica => generare ecuatie postfix 
	string infixToPostfix(string s) {
		string ops;
		string output;

		for (unsigned i = 0; i < s.length(); i++) {
			char c = s[i];
			if (c == ' ') {
				continue;
			}
			else {
				if (strchr("0123456789.", c) != NULL) {
					output += c;
				}
				else {
					if (c == '(' || c == '[') {
						ops += c;
					}
					else {
						if (c == ')') {
							while (ops[ops.length() - 1] != '(') {
								output += ' ';
								output += ops[ops.length() - 1];
								ops.erase(ops.begin() + ops.length() - 1);
							}
							ops.erase(ops.begin() + ops.length() - 1);
						}
						else {
							if (c == ']') {
								while (ops[ops.length() - 1] != '[') {
									output += ' ';
									output += ops[ops.length() - 1];
									ops.erase(ops.begin() + ops.length() - 1);
								}
								ops.erase(ops.begin() + ops.length() - 1);
							}
							else {
								while (!ops.empty() && gradOperator(c) <= gradOperator(ops[ops.length() - 1])) {
									output += ' ';
									output += ops[ops.length() - 1];
									ops.erase(ops.begin() + ops.length() - 1);
								}
								ops += c;
								output += ' ';
							}
						}
					}
				}
			}
		}
		while (!ops.empty()) {
			output += ' ';
			output += ops[ops.length() - 1];
			ops.erase(ops.begin() + ops.length() - 1);
		}
		return output;
	}

	//setter ecuation 
	void setEcuation(const char* _ecuation) {
		if (_ecuation != nullptr) {
			if (ecuation != nullptr) {
				delete[] ecuation;
			}
			ecuation = new char[strlen(_ecuation) + 1];
			strcpy_s(ecuation, strlen(_ecuation) + 1, _ecuation);
		}
	}

	//getter ecuation 
	char* getEcuation() {
		return ecuation;
	}

	//getter length 
	int getLength() {
		return length;
	}

	//metoda statica 
	static int nrTotalCalcule(Ecuation* ecuatii, int nrEcuatii) {
		int nr = 0;
		if (nrEcuatii > 0 && ecuatii != NULL) {
			for (int i = 0; i < nrEcuatii; i++) {
				if (strlen(ecuatii[i].ecuation) != 0) {
					for (int j = 0; j < strlen(ecuatii[i].ecuation); j++) {
						if (strchr("+-^#/*", ecuatii[i].ecuation[j])) {
							nr++;
						}
					}
				}
			}
		}
		return nr;
	}

	//operator cast explicit 
	explicit operator string() {
		return ecuation;
	}

	//operator indexare 
	char operator[](int index) {
		if (index >= 0 && index < strlen(ecuation)) {
			return ecuation[index];
		}
	}

	friend istream& operator>>(istream& in, Ecuation& ip);
	friend ostream& operator<<(ostream& out, Ecuation ip);
};

//operator citire 
istream& operator>>(istream& in, Ecuation& ip) {
	string buffer;
	cout << "Dati ecuatie: ";
	getline(in, buffer);
	ip.setEcuation(buffer.c_str());
	return in;
}

//operator afisare 
ostream& operator<<(ostream& out, Ecuation ip) {
	if (ip.ecuation != nullptr) {
		out << "Ecuatie: " << ip.ecuation << endl;
	}
	else {
		out << "Ecuatie: " << endl;
	}
	out << "Length: " << ip.length << endl;
	return out;
}
