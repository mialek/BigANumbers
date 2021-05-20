#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED
#include "../Liczba.h"

void testRel(Liczba l1, Liczba l2)
{
	if (l1 == l2)
		cout << l1 << " == " << l2 << endl;
	else
		cout << "~( " << l1 << " == " << l2 << " )" << endl;
	if (l1 != l2)
		cout << l1 << " != " << l2 << endl;
	else
		cout << "~( " << l1 << " != " << l2 << " )" << endl;
	if (l1 >= l2)
		cout << l1 << " >= " << l2 << endl;
	else
		cout << "~( " << l1 << " >= " << l2 << " )" << endl;
	if (l1 <= l2)
		cout << l1 << " <= " << l2 << endl;
	else
		cout << "~( " << l1 << " <= " << l2 << " )" << endl;
	if (l1 > l2)
		cout << l1 << " > " << l2 << endl;
	else
		cout << "~( " << l1 << " > " << l2 << " )" << endl;
	if (l1 < l2)
		cout << l1 << " < " << l2 << endl;
	else
		cout << "~( " << l1 << " < " << l2 << " )" << endl;
}

#endif
