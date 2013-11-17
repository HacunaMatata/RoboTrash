#ifndef VERSION_H
#define VERSION_H

namespace novaengine
{

	//Date Version Types
	static const char NOVAENGINE_DATE[] = "06";
	static const char NOVAENGINE_MONTH[] = "10";
	static const char NOVAENGINE_YEAR[] = "2013";
	static const char NOVAENGINE_UBUNTU_VERSION_STYLE[] =  "13.10";

	//Software Status
	static const char NOVAENGINE_STATUS[] =  "nightly";
	static const char NOVAENGINE_STATUS_SHORT[] =  "n";

	//Standard Version Type
	static const long NOVAENGINE_MAJOR  = 0;
	static const long NOVAENGINE_MINOR  = 3;
	static const long NOVAENGINE_BUILD  = 1;
	static const long NOVAENGINE_REVISION  = 3;

	//Miscellaneous Version Types
	static const long NOVAENGINE_BUILDS_COUNT  = 71;
	#define NOVAENGINE_RC_FILEVERSION 0,3,1,3
	#define NOVAENGINE_RC_FILEVERSION_STRING "0, 3, 1, 3\0"
	static const char NOVAENGINE_FULLVERSION_STRING [] = "0.3.1.3";

	//These values are to keep track of your versioning state, don't modify them.
	static const long NOVAENGINE_BUILD_HISTORY  = 4;
}
#endif //VERSION_H
