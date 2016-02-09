#ifndef __ACADEMICBUILDING_H__
#define __ACADEMICBUILDING_H__

#include "ownable.h"
#include "textdisplay.h"
#include <string>


class AcademicBuilding : public Ownable {
	private:
//		int improvementPrice;
//		int purchasePrice;
		std::string faculty;
		int rent_array[7];
	public:
		int improvementPrice;
		int purchasePrice;
		int improvements;
		int tileNum;
		AcademicBuilding *facultyMembers[3];
		void notify(TextDisplay *td);
		bool isMonopoly();
//  AcademicBuilding(std::string name, int purchasePrice, int improvementPrice, std::string faculty, int rent[7]);
		AcademicBuilding(std::string name, int tileNum, int purchasePrice, int improvementPrice, std::string faculty, int rentBase, int rent1, int rent2, int rent3, int rent4, int rent5);
		int rent();
		void improve(void);
		void unimprove(void);
		int getImprovementPrice(void);
		void addFaculty(AcademicBuilding *first, AcademicBuilding *second);

};
#endif
