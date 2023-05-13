#include "ExtendedTest.h"
#include "ShortTest.h"

#include "FixedCapBiMap.h"


#include <iostream>
using namespace std;


int main() {
	testAll();
	testAllExtended();
    FixedCapBiMap m(10);

    cout << "Add (1, 2) " << m.add(1, 2) << endl;
    cout << "Add (1, 4) " << m.add(1, 4) << endl;
    cout << "Add (2, 3) " << m.add(2, 3) << endl;
    cout << "Add (1, 2) " << m.add(1, 2) << endl;

    ValuePair res = m.search(1);
    cout << "Values assigned to 1: " << res.first << ", " << res.second << endl;
    res = m.search(2);
    cout << "Values assigned to 2: " << res.first << ", " << res.second << endl;


	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


