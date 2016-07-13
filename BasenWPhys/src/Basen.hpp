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

#include "Includes.hpp"

namespace bas {

	class Basen
	{
	public:
				Basen(const char* name, const char* title, const char* version);
				~Basen();
		void	run();

	private:
		void	processEvents();
		void	updateStatistics();
		void	handleInput(sf::Keyboard::Key key, bool isPressed);
		void	update(sf::Time dt);
		void	render();

	private:
		sf::RenderWindow*	m_Window;
		sf::RenderWindow*	m_DebugWindow;

		World*				m_CurrentWorld;
		DebugWorld*			m_DebugWorld;

		utils::Options		m_Options;
		utils::FileLogger	m_Logger;
		Input				m_Input;

		const char*			m_Name;
		bool				m_IsFocused;
	};
}