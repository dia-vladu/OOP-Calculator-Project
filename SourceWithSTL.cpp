#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <fstream>
#include <iomanip>
using namespace std;

//------------------ INTERFATA AFISABIL -------------------
class Afisabil {
public:
	//metoda virtuala pura
	virtual void afisare() = 0;
};

//------------------ CLASA STACK --------------------------

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

//----------------------------- CLASA CALCULATOR -----------------------------------------

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
	//aici am folosit containerul STL - stack
	bool corect(char* s) {
		stack<char> st;
		char x;
		for (int i = 0; i < strlen(s); i++) {
			if (s[i] == '(' || s[i] == '[') {
				st.push(s[i]);
				continue;
			}
			switch (s[i]) {
			case ')':
				x = st.top();
				st.pop();
				if (x == '[') {
					return false;
				}
				break;
			case ']':
				x = st.top();
				st.pop();
				if (x == '(') {
					return false;
				}
				break;
			}
		}
		return (st.empty());
	}

	//metoda generica 
	bool evaluate(char* s) {
		unsigned i;
		int x = 0;
		for (i = 0; i < strlen(s); i++) {
			if (strchr("0123456789[](){}+-*/^#. ", s[i]) != NULL) {
				if (strchr("+-*/^#", s[i]) != NULL) {
					x++;
				}
				continue;
			}
			else {
				return false;
				break;
			}
		}
		if (x == 0) {
			return false;
		}
		else {
			if (i == strlen(s)) {
				if (corect(s) == true) {
					return true;
				}
				else {
					return false;
				}
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
					int count = 0;
					for (int i = 0; i < nr.length(); i++) {
						if (nr[i] == '.') {
							count++;
						}
					}
					if (count <= 1) {
						num = stod(nr);
						stack.push(num);
					}
					else {
						//throw exception("Numar invalid !!!");
					}
				}
				else
				{
					double val1; stack.pop(val1);
					double val2; stack.pop(val2);

					switch (exp[i])
					{
					case '+': stack.push(val2 + val1); break;
					case '-': stack.push(val2 - val1); break;
					case '*':
						if (val1 == 0 || val2 == 0) {
							stack.push(0); break;
						}
						else {
							stack.push(val2 * val1); break;
						}
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

	//operator de negatie
	Calculator operator!() {
		rezultat *= -1;
		return *this;
	}

	//metoda virtuala
	virtual long rotunjire(double r) {
		cout << "Ca sa poti rotunji valoarea rezultatului, trebuie sa folosesti un Calculator Destept !" << endl;
		return 0;
	}

	//metoda virtuala
	virtual double trunchiere(double r) {
		cout << "Ca sa poti trunchia valoarea rezultatului, trebuie sa folosesti un Calculator Destept !" << endl;
		return 0;
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

//----------------------------CLASA DERIVATA - CALCULATOR DESTEPT ------------------------

class CalculatorDestept : public Calculator, public Afisabil {
	double rezultat;

public:
	CalculatorDestept() {
		rezultat = 0;
	}

	CalculatorDestept(double rez) {
		rezultat = rez;
	}

	void afisare() override {
		cout << "Rezultatul ecuatiei: " << getExpresie() << "este: " << getRezultat() << endl;
	}

	long rotunjire(double r) override {
		return (r > 0.0) ? (r + 0.5) : (r - 0.5);
	}

	double trunchiere(double r) override {
		return trunc(r);
	}
};

//----------------------------- CLASA ECUATION --------------------------------------------  

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
istream& operator>>(istream& in, Ecuation& e) {
	string buffer;
	cout << "Dati ecuatie: ";
	getline(in, buffer);
	e.setEcuation(buffer.c_str());
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

//----------------------------- MAIN ----------------------------------------

int main(/*int argc, char* argv[]*/) {

	cout << "MENIU:" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Variante citire ecuatii: " << endl;
	cout << "\t1 - prin consola" << endl;
	cout << "\t2 - din fisier" << endl;
	cout << "Alegeti varianta pentru citire: ";
	int varCit;
	cin >> varCit;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Variante afisare rezultate: " << endl;
	cout << "\t1 - afisare la consola" << endl;
	cout << "\t2 - afisare in fisier" << endl;
	cout << "Alegeti varianta pentru afisare: ";
	int varAfis;
	cin >> varAfis;
	cout << "------------------------------------------------------------------" << endl;
	cout << "Ati ales: " << endl;
	cout << "Citire: ";
	string citire;
	string afisare;
	if (varCit == 1) {
		cout << "consola" << endl;
	}
	else {
		cout << "fisier" << endl;
		cout << "Dati nume fisier pentru citire: ";
		cin >> citire;
	}
	cout << "Afisare: ";
	if (varAfis == 1) {
		cout << "consola" << endl;
	}
	else {
		cout << "fisier" << endl;
		cout << "Dati nume fisier pentru afisare: ";
		cin >> afisare;
	}
	cout << "-----------------------------------------------------------------" << endl;
	if (varAfis == 2) {
		ofstream afis(afisare);
		if (varCit == 1) {
			string ecuatie;
			int nr = 1;
			while (nr) {
				cout << "Dati ecuatie: ";
				cin >> ws;
				getline(cin, ecuatie);
				if (ecuatie == "exit") {
					nr = 0;
				}
				else {
					Ecuation ecuation(ecuatie.c_str());
					string postfix = ecuation.infixToPostfix(ecuatie);
					Calculator calcul(postfix.c_str());
					if (calcul.evaluate(calcul.getExpresie())) {
						double rez;
						calcul.evaluatePostfix(calcul.getExpresie(), rez);
						calcul.setRezultat(rez);
						int digits = calcul.countDigits(calcul.getRezultat());
						string s;
						s = "Rezultatul ecuatiei " + ecuatie + " este: ";
						afis << s;
						if (to_string(calcul.getRezultat()) == "inf" || to_string(calcul.getRezultat()) == "-inf") {
							afis << "Erorr !!!" << endl;
						}
						else {
							afis << setprecision(digits) << calcul.getRezultat() << endl;
						}
					}
					else {
						cout << "Ecuatie invalida!" << endl;
						cout << endl;
					}
				}
			}
		}
		else {
			ifstream cit(citire);
			string ecuatie;
			while (getline(cit, ecuatie)) {
				cout << "Ecuatia citita: ";
				cout << ecuatie << endl;
				Ecuation ecuation(ecuatie.c_str());
				string postfix = ecuation.infixToPostfix(ecuatie);
				Calculator calcul(postfix.c_str());
				if (calcul.evaluate(calcul.getExpresie())) {
					double rez;
					calcul.evaluatePostfix(calcul.getExpresie(), rez);
					calcul.setRezultat(rez);
					int digits = calcul.countDigits(calcul.getRezultat());
					string s;
					s = "Rezultatul ecuatiei " + ecuatie + " este: ";
					afis << s;
					if (to_string(calcul.getRezultat()) == "inf" || to_string(calcul.getRezultat()) == "-inf") {
						afis << "Erorr !!!" << endl;
					}
					else {
						afis << setprecision(digits) << calcul.getRezultat() << endl;
					}
				}
				else {
					cout << "Ecuatie invalida!" << endl;
					cout << endl;
				}
			}
			cit.close();
		}
		afis.close();
	}
	else {
		if (varCit == 1) {
			string ecuatie;
			int nr = 1;
			while (nr) {
				cout << "Dati ecuatie: ";
				cin >> ws;
				getline(cin, ecuatie);
				if (ecuatie == "exit") {
					nr = 0;
				}
				else {
					Ecuation ecuation(ecuatie.c_str());
					string postfix = ecuation.infixToPostfix(ecuatie);
					Calculator calcul(postfix.c_str());
					if (calcul.evaluate(calcul.getExpresie())) {
						double rez;
						calcul.evaluatePostfix(calcul.getExpresie(), rez);
						calcul.setRezultat(rez);
						int digits = calcul.countDigits(calcul.getRezultat());
						cout.precision(digits);
						//try {
						//	//nu stiu ce sa scriu aici ca sa functioneze
						//}
						//catch (exception& e) {
						//	cout << e.what() << endl;
						//}
						//catch (...) {
						//	cout << "eroare generala";
						//}
						if (to_string(calcul.getRezultat()) == "inf" || to_string(calcul.getRezultat()) == "-inf") {
							cout << "Erorr !!!" << endl;
							cout << endl;
						}
						else {
							cout << "Rezultat: " << calcul.getRezultat() << endl;
							cout << endl;
							/*CalculatorDestept c(rez);
							cout << "Rezultat rotunjit: " << c.rotunjire(rez) << endl;
							cout << "Rezultat trunchiat: " << c.trunchiere(rez) << endl;*/
						}
					}
					else {
						cout << "Ecuatie invalida!" << endl;
						cout << endl;
					}
				}
			}
		}
		else {
			ifstream cit(citire);
			string ecuatie;
			while (getline(cit, ecuatie)) {
				cout << "Ecuatia citita: ";
				cout << ecuatie << endl;
				Ecuation ecuation(ecuatie.c_str());
				string postfix = ecuation.infixToPostfix(ecuatie);
				Calculator calcul(postfix.c_str());
				if (calcul.evaluate(calcul.getExpresie())) {
					double rez;
					calcul.evaluatePostfix(calcul.getExpresie(), rez);
					calcul.setRezultat(rez);
					int digits = calcul.countDigits(calcul.getRezultat());
					cout.precision(digits);
					if (to_string(calcul.getRezultat()) == "inf" || to_string(calcul.getRezultat()) == "-inf") {
						cout << "Erorr !!!" << endl;
						cout << endl;
					}
					else {
						cout << "Rezultat: " << calcul.getRezultat() << endl;
						cout << endl;
					}
				}
				else {
					cout << "Ecuatie invalida!" << endl;
					cout << endl;
				}
			}
			cit.close();
		}
	}
}