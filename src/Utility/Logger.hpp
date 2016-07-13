#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
* SOURCE: "https://github.com/SFML/SFML/wiki/Source:-Simple-File-Logger-(by-mateandmetal)"
*
* LICENSE:  This  program  is  free  software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published by
* the  Free Software Foundation; either version 3 of the License, or (at your
* option)  any later version. This program is distributed in the hope that it
* will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
* Public License for more details (copy included in program files).
*/

/*
* USAGE:
*
*	bas::utils::FileLogger log("<Version Number>", "<File Name>");
*	log << bas::utils::FileLogger::LogType::LOG_INFO << "This is actually working";
*	log << bas::utils::FileLogger::LogType::LOG_WARNING << "I'm warning you";
*	log << bas::utils::FileLogger::LogType::LOG_ERROR << "This is an error!";
*/

#include <SFML\System.hpp>
#include <sstream>
#include "FileIO.hpp"

namespace bas {
	namespace utils {

		class FileLogger : public sf::NonCopyable
		{

		public:
			enum class LogType
			{
				LOG_ERROR,
				LOG_WARNING,
				LOG_INFO
			};

			FileLogger(const char *program_version = "1.0", const char *fname = "Logger.log");
			~FileLogger();

			friend FileLogger &operator<< (FileLogger &logger, const LogType l_Type)
			{
				std::stringstream ss;

				switch (l_Type) {
				case FileLogger::LogType::LOG_ERROR:
					ss << "[ " << logger.getTime() << " ms ] ";
					ss << "(ERROR): ";
					logger.m_NumErrors++;
					break;

				case FileLogger::LogType::LOG_WARNING:
					ss << "[ " << logger.getTime() << " ms ] ";
					ss << "(WARNING): ";
					logger.m_NumWarnings++;
					break;

				default:
					ss << "[ " << logger.getTime() << " ms ] ";
					ss << "(INFO): ";
					break;
				}

				FileIO::setTarget(logger.m_File.c_str());
				FileIO::append(ss.str().c_str());

				return logger;
			};

			friend FileLogger &operator<< (FileLogger &logger, const char* text)
			{
				std::stringstream ss;
				ss << text << std::endl;

				FileIO::setTarget(logger.m_File.c_str());
				FileIO::append(ss.str().c_str());

				return logger;
			};

		private:
			float			getTime();

		private:
			std::string			m_File;
			sf::Clock			m_Clock;
			unsigned int		m_NumWarnings;
			unsigned int		m_NumErrors;
		};
	}
}