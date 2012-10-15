#ifndef VERSION_H
#define VERSION_H

	//Date Version Types
	static const char DATE[] = "31";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2010";
	static const double UBUNTU_VERSION_STYLE = 10.03;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 6;
	static const long BUILD = 624;
	static const long REVISION = 3396;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1081;
	#define RC_FILEVERSION 1,6,624,3396
	#define RC_FILEVERSION_STRING "1, 6, 624, 3396\0"
	static const char FULLVERSION_STRING[] = "1.6.624.3396";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 24;
	

#endif //VERSION_h
