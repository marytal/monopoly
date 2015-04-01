#include "gym.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Gym::Gym(string name) : Ownable(name, 100) {}; // how much does a gym cost?

int Gym::rent(){
	cout << "Please roll again to determine your membership fees." << endl;
	string input;
	cin >> input;
	srand(time(NULL));
	int roll1 = rand() % 6 + 1;
	int roll2 = rand() % 6 + 1;
	cout << "You rolled: " << roll1 << " " << roll2 << "!" << endl;
	int roll = roll1 + roll2;

  if(otherGym->owner == owner){ // if both gyms are owned by the player
    return 10 * roll;
  } else {
    return 4 * roll;
  }

}
