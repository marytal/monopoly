#include "academicbuilding.h"

using namespace std;
/*
AcademicBuilding::AcademicBuilding(string name, int purchasePrice, int improvementPrice, string faculty, int rent[7]) : 
Ownable(name, false, -1, purchasePrice, false, purchasePrice), improvements(0), 
improvementPrice(improvementPrice), faculty(faculty), rent(rent) {};
*/
AcademicBuilding::AcademicBuilding(string name, int purchasePrice, int improvementPrice, string faculty, int rentbase, int rent1, int rent2, int rent3, int rent4, int rent5):
	Ownable(name, false, NULL, purchasePrice, false, purchasePrice), improvements(0), improvementPrice(improvementPrice), faculty(faculty) {
	rent_array[0] = rentbase;
	rent_array[1] = rentbase * 2;
	rent_array[2] = rent1;
	rent_array[3] = rent2;
	rent_array[4] = rent3;
	rent_array[5] = rent4;
	rent_array[6] = rent5;
}

void AcademicBuilding::improve(void) {
	improvements++;
	totalPrice += improvementPrice;
}

void AcademicBuilding::unimprove(void) {
	improvements--;
	totalPrice -= improvementPrice;
}

int AcademicBuilding::getImprovementPrice(void) {
	return improvementPrice;
}

int AcademicBuilding::rent(void) {
	return rent_array[improvements];
}

bool AcademicBuilding::isMonopoly(){

	// for(int i = 0; i < 3; i++){
	// 	if(facultyMembers[i]->owner != owner){
	// 		return false;
	// 	}
	// }
	return false;
}