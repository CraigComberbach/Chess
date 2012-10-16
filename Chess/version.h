#ifndef VERSION_H
#define VERSION_H

	//Date Version Types
	static const char DATE[] = "22";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.07";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 6;
	static const long BUILD = 615;
	static const long REVISION = 3335;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1073;
	#define RC_FILEVERSION 1,6,615,3335
	#define RC_FILEVERSION_STRING "1, 6, 615, 3335\0"
	static const char FULLVERSION_STRING[] = "1.6.615.3335";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 15;
	

#endif //VERSION_H
