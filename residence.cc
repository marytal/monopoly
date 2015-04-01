#include "residence.h"

using namespace std;

Residence::Residence(string name) : Ownable(name) {};

int Residence::rent(){
	//. do stuff
	int count = 0;
	int rent = 25;

	for(int i = 0; i < 3; i++){
		if(owner == otherResidences[i]->owner){
			count++;
			rent *= 2;
		}
	}

	return rent;
}