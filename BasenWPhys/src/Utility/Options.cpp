#include "Options.hpp"

namespace bas {
	namespace utils {

		bool toBool(int s) 
		{
			return s == 1;
		}

		Options::Options(const char* file)
			: m_File(file)
		{ }

		bool Options::loadOptions()
		{
			if (!getFromFile())
			{
				repairOptions();
				return false;
			}
			return true;
		}

		bool Options::getFromFile()
		{
			FileIO::setTarget(m_File);
			std::string contents = FileIO::read();
			std::string s;

			if (getContents(&contents))		// MANUALLY HANDLE EACH ONE
			{
				start = m_Indeces[WIDTH_LOCATION * 2];
				end = m_Indeces[(WIDTH_LOCATION * 2) + 1];
				s = contents.substr(start, end - start);
				m_Width = strtol(s.c_str(), NULL, 0);

				if (m_Width < 200 || m_Width > 10000)
				{
					return false;
				}

				start = m_Indeces[HEIGHT_LOCATION * 2];
				end = m_Indeces[(HEIGHT_LOCATION * 2) + 1];
				s = contents.substr(start, end - start);
				m_Height = strtol(s.c_str(), NULL, 0);

				if (m_Height < 200 || m_Height > 10000)
				{
					return false;
				}

				start = m_Indeces[FULLSCREEN_LOCATION * 2];
				end = m_Indeces[(FULLSCREEN_LOCATION * 2) + 1];
				s = contents.substr(start, end - start);
				int i = strtol(s.c_str(), NULL, 0);
				m_Fullscreen = toBool(i);
				return true;
			}
			return false;
		}

		bool Options::getContents(std::string *contents)
		{
			FileIO::setTarget(m_File);

			if (*contents == "")
			{
				return false;
			}
			else
			{
				std::size_t found = 1;
				std::size_t prev = 0;
				int i = 0;

				while (prev != std::string::npos)
				{
					found = contents->find("=", prev + 1);
					m_Indeces[i] = found + 1;
					found = contents->find(";", found);
					m_Indeces[i + 1] = found;

					i += 2;
					prev = found;
				}

				return true;
			}
		}

		void Options::repairOptions()
		{
			m_Width = atoi(WIDTH_DEFAULT);
			m_Height = atoi(HEIGHT_DEFAULT);
			m_Fullscreen = toBool(FULLSCREEN_DEFAULT);

			std::stringstream ss;

			ss << "Options file. Modify values at your onw risk." << std::endl << std::endl;
			ss << "Width = " << WIDTH_DEFAULT << ";" << std::endl;
			ss << "Height = " << HEIGHT_DEFAULT << ";" << std::endl;
			ss << "Fullscreen = " << FULLSCREEN_DEFAULT << ";" << std::endl;

			FileIO::setTarget(m_File);
			FileIO::write(ss.str().c_str());
		}

		int Options::getWidth()
		{
			return m_Width;
		}

		int Options::getHeight()
		{
			return m_Height;
		}

		bool Options::getFullscreen()
		{
			return m_Fullscreen;
		}

	}
}