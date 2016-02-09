#include "gym.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Gym::Gym(string name) : Ownable(name, 150) {}; // how much does a gym cost?

int Gym::rent(){
	cout << "Please roll again to determine your membership fees." << endl;
	string input;		
	cin >> input;		// Making the player feel like they're doing something.
	srand(time(NULL));
	int roll1 = rand() % 6 + 1;
	int roll2 = rand() % 6 + 1;
	cout << "You rolled: " << roll1 << " and " << roll2 << "." << endl;
	int roll = roll1 + roll2;

  if(otherGym->owner == owner){ // if both gyms are owned by the player
    return 10 * roll;
  } else {					// Actually returning the proper rent.
	return 4 * roll;
  }
}

void Gym::setOtherGym(Gym *oGym) {
	otherGym = oGym;				// Used in seeing if the player owns the other gym. 
}
