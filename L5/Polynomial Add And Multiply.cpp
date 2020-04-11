#include <iostream>

using namespace std;

class Polynomial
{
	public:
		int* coefficients;
		int terms;

		~Polynomial()
		{
			if (coefficients != nullptr)
			{
				delete coefficients;
			}
		}

		void getPolynomial()
		{
			cout << "No. of terms in the expression :";
			cin >> terms;
			coefficients = new int[terms];

			int exponent;
			int coefficient;

			for (int i = 0; i < terms; ++i)
			{
				cin >> coefficient;
				cin >> exponent;
				coefficients[exponent] = coefficient;
			}
			
		}

		void print()
		{
			for (int exponent = terms-1;  exponent >= 0; exponent--)
			{
				cout << coefficients[exponent] << "\t" << exponent << endl;
			}
		}
};

Polynomial* add (Polynomial* poly1, Polynomial* poly2)
{
	Polynomial *result = new Polynomial();
	Polynomial *greater = (poly1->terms > poly2->terms) ? poly1 : poly2;
	result->terms = greater->terms;
	result->coefficients = new int[result->terms];

	int addLength = (poly1->terms < poly2->terms) ? poly1->terms : poly2->terms;
	for (int i = 0; i < addLength; ++i)
	{
		result->coefficients[i] = poly1->coefficients[i] + poly2->coefficients[i];
	}

	for (int i = addLength; i < greater->terms ; ++i)
	{
		result->coefficients[i] = greater->coefficients[i];
	}
	return result;
}

Polynomial* mult(Polynomial* poly,int coeff,int power)
{
	Polynomial* result = new Polynomial();
	result->terms = poly->terms + power;
	result->coefficients = new int[result->terms];
	for (int i = result->terms - 1; i >= power; --i)
	{
		result->coefficients[i] = coeff * poly->coefficients[i-power];
	}

	for (int i = 0; i < power; ++i)
	{
		result->coefficients[i] = 0;
	}

	return result;
}

Polynomial* multiply(Polynomial* poly1, Polynomial* poly2)
{
	Polynomial* result = new Polynomial();
	result->terms = 0;

	for (int i = 0; i < poly2->terms; ++i)
	{
		Polynomial* temp;
		temp = mult(poly1,poly2->coefficients[i],i);
		Polynomial* tempresult = result;
		result = add(result,temp);
		delete temp;
		delete tempresult;
	}
	return result;
}


int main(void)
{
	cout << "Enter first Polynomial" << endl;
	Polynomial *p1 = new Polynomial();
	p1->getPolynomial();

	cout << "Enter second Polynomial" << endl;
	Polynomial *p2 = new Polynomial();
	p2->getPolynomial();

	Polynomial *p3;

	int option;
	while(true)
	{
		cout << "Enter 1 to add or 2 for multiply" << endl;
		cin >> option;
		if (option == 1)
		{
			p3 = add(p1,p2);
			p3->print();
		}
		else if (option == 2)
		{
			p3 = multiply(p1,p2);
			p3->print();
		}
		else
		{
			cout << "Exiting program" << endl;
			exit(0);
		}
		delete p3;
	}
	return 0;
}