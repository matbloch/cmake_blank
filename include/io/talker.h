#ifndef IO__talker
#define IO__talker

#include <string>

namespace io
{
	class Talker {
		public:
		Talker();
		void talk();
		void say(std::string sentence);
	};
};

#endif