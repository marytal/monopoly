#include "residence.h"

using namespace std;

Residence::Residence(string name) : Ownable(name, 200) {}; // how much do the residences cost?

int Residence::rent(){
	cout << "Made it to: Rent Function in Residences" << endl;
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

void Residence::setResidencies(Residence *rez1, Residence *rez2, Residence *rez3) {
	otherResidences[0] = rez1;
	otherResidences[1] = rez2;
	otherResidences[2] = rez3;
}
