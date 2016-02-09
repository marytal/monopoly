#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__

#include "ownable.h"

#include <string>

class Residence : public Ownable {
	Residence *otherResidences[3];
	public:
	Residence(std::string name);
	int rent();
	void setResidencies(Residence *rez1, Residence *rez2, Residence *rez3);
};

#endif

