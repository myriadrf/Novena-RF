#ifndef LMS_SUITE_VERSION_H
#define LMS_SUITE_VERSION_H

namespace lms_suite{
	
	//Date Version Types
	static const char DATE[] = "24";
	static const char MONTH[] = "11";
	static const char YEAR[] = "2014";
	static const char UBUNTU_VERSION_STYLE[] =  "14.11";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 26;
	static const long REVISION  = 125;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 108;
	#define RC_FILEVERSION 1,0,26,125
	#define RC_FILEVERSION_STRING "1, 0, 26, 125\0"
	static const char FULLVERSION_STRING [] = "1.0.26.125";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 26;
	

}
#endif //LMS_SUITE_VERSION_H
