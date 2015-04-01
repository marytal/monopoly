#ifndef __GYM_H__
#define __GYM_H__

#include "ownable.h"
#include <string>

class Gym : public Ownable {
	private:
		std::string name;
		bool owned;
		int owner;
		Gym *otherGym;
	public:
		Gym(std::string name);
		int rent();
	
};

#endif

