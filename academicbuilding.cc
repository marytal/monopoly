#include "academicbuilding.h"

using namespace std;
/*
AcademicBuilding::AcademicBuilding(string name, int purchasePrice, int improvementPrice, string faculty, int rent[7]) : 
Ownable(name, false, -1, purchasePrice, false, purchasePrice), improvements(0), 
improvementPrice(improvementPrice), faculty(faculty), rent(rent) {};
*/
AcademicBuilding::AcademicBuilding(string name, int tileNum, int purchasePrice, int improvementPrice, string faculty, int rentbase, int rent1, int rent2, int rent3, int rent4, int rent5):
	tileNum(tileNum), Ownable(name, false, NULL, purchasePrice, false, purchasePrice), improvements(0), improvementPrice(improvementPrice), faculty(faculty) {
	rent_array[0] = rentbase;
	rent_array[1] = rentbase * 2;	// Getting around the problem
	rent_array[2] = rent1;			// of having to deal with giving 
	rent_array[3] = rent2;			// arrays in the MIL
	rent_array[4] = rent3;
	rent_array[5] = rent4;
	rent_array[6] = rent5;
}

void AcademicBuilding::addFaculty(AcademicBuilding *first, AcademicBuilding *second){
  facultyMembers[0] = first;	// Called to create the "monopolies"
  facultyMembers[1] = second;
}

void AcademicBuilding::improve(void) {	// Should make checks, 
	improvements++;						// but accordingly improves property
	totalPrice += improvementPrice;
}

void AcademicBuilding::unimprove(void) {
	improvements--;
	totalPrice -= improvementPrice;
}

int AcademicBuilding::getImprovementPrice(void) {		// A getter for Improvement Price
	return improvementPrice;
}

int AcademicBuilding::rent(void) {
	if(isMonopoly() && (improvements == 0)) {
		return rent_array[1];					// Calculates rent based on if owner owns all three
	} else if(isMonopoly()) {					// and then the number of improvements
		return rent_array[improvements + 1];
	} else { 
		return rent_array[0];
	}
}

bool AcademicBuilding::isMonopoly(){

	for(int i = 0; i < 2; i++){				// A check to see whether the owner of the property
		if(facultyMembers[i] == NULL){		// owns all of the faculty buildings
			return true;
		}
		if(facultyMembers[i]->owner != owner){
			return false;
		}
	}
	return true;
}
