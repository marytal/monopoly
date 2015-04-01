#include <iostream>
#include "textdisplay.h"
#include "unistd.h"
using namespace std;


int main(void) {
	TextDisplay td;

	cout << td << endl;

	for(int i = 0; i < 39; i++) {
		td.notify(i, '$');
		td.notify(i, 'G');
		td.notify(i, 'P');
		td.notify(i, 'D');
		td.notify(i, 'S');
		td.notify(i, 'B');
		td.notify(i, 'L');
		td.notify(i, 'T');
		td.improve(i);
		td.improve(i + 1);
		sleep(1);
		cout << td << endl;
	}
	return 0;
}
