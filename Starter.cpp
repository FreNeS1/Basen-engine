#include "src/Basen.hpp"
#include "src/Utility/Logger.hpp"
#include <string>
#include <sstream>

int main()
{
	std::stringstream ss;
	std::string s;
	int lol;

	s = "ssss 1024222ssss";
	s = s.substr(4, 5);
	lol = strtol(s.c_str(), NULL, 0);

	ss << lol;

	bas::Basen game("Basen Test", ss.str().c_str(), "0.0.5");
	game.run();

	/*bas::utils::FileLogger log("0.0.1");

	log << bas::utils::FileLogger::LogType::LOG_INFO << "This is actually working";
	log << bas::utils::FileLogger::LogType::LOG_WARNING << "A new challenger is aproaching";
	log << bas::utils::FileLogger::LogType::LOG_ERROR << "h0i I'm Temmie, don forget mi friend bob!";

	std::string aux = "works!";

	bas::Basen game("Basen Test", aux.c_str(), "0.0.5");
	game.run();/**/

}