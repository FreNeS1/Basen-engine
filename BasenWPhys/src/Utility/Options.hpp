#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
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
* USAGE: This generates an option file, that holds the options you can save.
* Options are handled manually, and if the values are wrong, it resets the
* whole file. You can also reset the whole file using repairOptions.
* For loading the options, you only need to call loadOptions.
*
*/

#include <sstream>
#include "FileIO.hpp"
#include "Logger.hpp"

namespace bas {
	namespace utils {

		class Options
		{
		public:

					Options(const char* file);
			bool	loadOptions();

			int		getWidth();
			int		getHeight();
			bool	getFullscreen();
			void	repairOptions();

		private:
			bool	getFromFile();
			bool	getContents(std::string *contents);

		private:
			const char* m_File;
			std::size_t m_Indeces[50];
			std::size_t start;
			std::size_t end;

			int			m_Height;
			int			m_Width;
			bool		m_Fullscreen;

			const int	WIDTH_LOCATION = 0;
			const int	HEIGHT_LOCATION = 1;
			const int	FULLSCREEN_LOCATION = 2;

			const char*	WIDTH_DEFAULT = "1024";
			const char*	HEIGHT_DEFAULT = "720";
			const int	FULLSCREEN_DEFAULT = 0;
		};

	}
}