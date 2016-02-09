#ifndef __TIMS_H__
#define __TIMS_H__

class TimsCup {
	static TimsCup instance1;
	static TimsCup instance2;
	static TimsCup instance3;
	static TimsCup instance4;
	static int instances;

	TimsCup(void);
	static void cleanup();
	
	public:
		static TimsCup *getInstance();
		void useCup();
};
