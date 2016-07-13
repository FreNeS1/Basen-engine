#include "Logger.hpp"

namespace bas {
	namespace utils {

		FileLogger::FileLogger(const char *program_version, const char *fname)
			: m_NumWarnings(0U)
			, m_NumErrors(0U)
			, m_Clock()
		{
			m_File = fname;
			FileIO::setTarget(m_File.c_str());

			std::stringstream ss;
			ss << "Log file, program version " << program_version << std::endl << std::endl;
			ss << "[ " << FileLogger::getTime() << " ms ] (INFO): Log file created" << std::endl;
			FileIO::write(ss.str().c_str());
		}

		FileLogger::~FileLogger()
		{
			std::stringstream ss;

			ss << std::endl;
			ss << "Program finished on " << FileLogger::getTime() << " ms with:" << std::endl;
			ss << "- " << m_NumWarnings << " warnings" << std::endl;
			ss << "- " << m_NumErrors << " errors" << std::endl;

			FileIO::setTarget(m_File.c_str());
			FileIO::append(ss.str().c_str());
		}

		float FileLogger::getTime() {
			sf::Time currentTime = m_Clock.getElapsedTime();
			float time = currentTime.asMilliseconds();
			return time;
		}
	}
}