#include <iostream>
#include <string>
#include <cmath>
#include "Stack.h"
#include "Calculator.h"
#include "Ecuation.h"
using namespace std;

//----------------------------- MAIN ----------------------------------------

int main() {

	string ecuatie = "";
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
				cout << "Rezultat: ";
				//try {
				//	//nu stiu ce sa scriu aici ca sa functioneze
				//}
				//catch (exception& e) {
				//	cout << e.what() << endl;
				//}
				if (to_string(calcul.getRezultat()) == "inf") {
					cout << "Erorr !!!" << endl;
				}
				else {
					cout << calcul.getRezultat() << endl;
				}
			}
		}
	}
}
