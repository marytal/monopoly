#ifndef __GYM_H__
#define __GYM_H__

#include "ownable.h"
#include <string>

class Gym : public Ownable {
	private:
		bool owned;
		// owner;
		Gym *otherGym;
	public:
		Gym(std::string name);
		int rent();
		void setOtherGym(Gym *otherGym);
};

#endif

