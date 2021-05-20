#include "../Liczba.h"
#include "Misc.h"

int main()
{
	/*Liczba l1(INT_MAX,16);
	Liczba l2(500,7);
	testRel(l1, l2);
	cout << "INT_MAX + 500 : 0x" << l1 + l2 << endl;
	cout << "INT_MAX - 500 : 0x" << l1 - l2 << endl;
	cout << "INT_MAX / 500 : 0x" << l1 / l2 << endl;
	cout << "INT_MAX * 500 : 0x" << l1 * l2 << endl;
	
	l1 = -l1;
	cout << "-INT_MAX + 500 : 0x"  << l1 + l2 << endl;
	cout << "-INT_MAX - 500 : 0x" << l1 - l2 << endl;
	cout << "-INT_MAX / 500 : 0x" << l1 / l2 << endl;
	cout << "-INT_MAX * 500 : 0x" << l1 * l2 << endl;

	l2 = -l2;
	cout << "-INT_MAX + (-500) : 0x" << l1 + l2 << endl;
	cout << "-INT_MAX - (-500) : 0x" << l1 - l2 << endl;
	cout << "-INT_MAX / (-500) : 0x" << l1 / l2 << endl;
	cout << "-INT_MAX * (-500) : 0x" << l1 * l2 << endl;

	l1 = -l1;
	cout << "INT_MAX + (-500) : 0x" << l1 + l2 << endl;
	cout << "INT_MAX - (-500) : 0x" << l1 - l2 << endl;
	cout << "INT_MAX / (-500) : 0x" << l1 / l2 << endl;
	cout << "INT_MAX * (-500) : 0x" << l1 * l2 << endl;*/

	/*Liczba l3(4735);
	Liczba l4(l3);
	Liczba l5;
	cout << "a = " << l3 <<endl;
	cout << "a + a : " << l3 + l4 << endl;
	cout << "a - a : " << l3 - l4 << endl;
	cout << "a / a : " << l3 / l4 << endl;
	cout << "a * a : " << l3 * l4 << endl;
	testRel(l3, l4);

	l4=(-l3);
	cout <<endl <<"---------------"<<endl << "a = " << l3 << " b= -a "<<endl;
	cout << "a + b : " << l3 + l4 << endl;
	cout << "a - b : " << l3 - l4 << endl;
	cout << "a / b : " << l3 / l4 << endl;
	cout << "a * b : " << l3 * l4 << endl;
	testRel(l3, l4);*/

	/*Liczba l1(83554, 19);
	Liczba l2(68432);
	cout << l1 << " + " << l2;
	l1 += l2;
	cout << " = " << l1;
	l2 = Liczba(4874);
	cout << " / " << l2 << " = ";
	l1 /= l2;
	cout << l1 <<" * ";
	l2 = Liczba(92);
	cout << l2 << " = ";
	l1 *= l2;
	cout << l1;*/


	Liczba l1(3253, 60);
	cin >> l1;
	cout << l1 <<endl;
	l1.testWypisz();
	cout << endl;
	l1.testWypiszBw();

	/*Liczba l2(l1);
	Liczba l3(12, 16);
	cout << l3;
	Liczba l4(0, 16);
	while (l3 != l4)
		cout << --l3<<" ";
	l2 = l1 % l3;
	cout << l2;
	9235434*/
	/*l1.testWypisz();
	cout<<endl<<l1<< endl;
	l1.testWypiszBw();
	cout << endl;
	l2.testWypisz();
	cout << endl << l2 << endl;
	l2.testWypiszBw();
	cout << endl;
	l3.testWypisz();
	cout << endl << l3 << endl;
	l3.testWypiszBw();
	cout << endl;
	l4.testWypisz();
	cout << endl << l4 << endl;
	l4.testWypiszBw();*/
	

}