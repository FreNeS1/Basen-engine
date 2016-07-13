#include "FileIO.hpp"

namespace bas {
	namespace utils {

		std::string FileIO::m_Target = "noTarget";

		void FileIO::setTarget(const char* target)
		{
			m_Target = target;
		}

		bool FileIO::write(const char* text)
		{
			std::ofstream os(m_Target);

			if (os)
			{
				os.write(text, strlen(text));
				if (!os)
				{
					// ERROR WRITING!
					return false;
				}
				os.close();
				return true;
			}
			// ERROR OPENING FILE!
			return false;
		}

		std::string FileIO::read()
		{
			std::ifstream is(m_Target);

			if (is) {
				is.seekg(0, is.end);
				int length = is.tellg();
				is.seekg(0, is.beg);

				char * buffer = new char[length];
				is.read(buffer, length);

				if (!is)
				{
					// ERROR READING!
				}
				is.close();
				std::string contents = buffer;
				delete[] buffer;
				return contents;
			}
			// ERROR OPENING FILE!
			return "";
		}

		bool FileIO::append(const char* text)
		{
			std::ofstream os(m_Target, std::ofstream::app);

			if (os)
			{
				os.write(text, strlen(text));
				if (!os)
				{
					// ERROR WRITING!
					return false;
				}
				os.close();
				return true;
			}
			// ERROR OPENING FILE!
			return false;
		}

		bool FileIO::write(int location, int length, const char* text)
		{
			std::ofstream os(m_Target);

			if (os)
			{
				os.seekp(location);
				os.write(text, length);

				if (!os)
				{
					// ERROR WRITING!
					return false;
				}

				os.close();
				return true;
			}
			// ERROR OPENING FILE!
			return false;
		}

		std::string FileIO::read(int location, int length)
		{
			std::ifstream is(m_Target);

			if (is) {
				char * buffer = new char[length];
				is.seekg(location);
				is.read(buffer, length);

				if (!is)
				{
					// ERROR READING!
				}

				is.close();
				std::string contents = buffer;
				delete[] buffer;
				return contents;
			}
			// ERROR OPENING FILE!
			return "";
		}
	}
}