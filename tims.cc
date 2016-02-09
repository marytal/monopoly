#include "tims.h"
#include <cstdlib>
#include <iostream>

using namespace std;

TimsCup *TimsCup::instance = 0;

TimsCup *TimsCup::getInstance() {
	if(instances == 4) {
		return NULL;
	} else if(!instance1) {
		instance1 = new TimsCup;
		atexit(cleanup);
		instances++;
		return instance1;
	} else if(!instance2) {
		instance2 = new TimsCup;
		atexit(cleanup);
		instances++;
		return instance2;
	} else if(!instance3) {
		instance3 = new TimsCup;
		atexit(cleanup);
		instances++;
		return instance3;
	} else if(!instance4) {
		instance4 = new TimsCup;
		atexit(cleanup);
		instances++;
		return instance4;
	}
}

void TimsCup::useCup(void) {
	if
