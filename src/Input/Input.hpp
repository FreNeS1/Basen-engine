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
* This first gets all the game class events as set(Type, code, value), flanks
* get stored in the m_flanks array, and input in the m_Input. For a set to be
* considered a valid option, m_Triggers for that action has to have that code
* in the array.
*/

#include <SFML/Window/Event.hpp>

namespace bas {

#define NUM_TRIGGERS 3

	enum class Type /* This sets the basic offset of the input code */
	{
		Keyboard = 0,
		Mouse = sf::Keyboard::KeyCount,
		Controller = sf::Keyboard::KeyCount + sf::Mouse::ButtonCount,
	};

	enum class Action
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ATTACK,
		DEFEND,
		JUMP,
		ACTION,
		TOTAL
	};

	namespace config {
		static int config1[(int)Action::TOTAL][NUM_TRIGGERS] =
		{
			/* UP */	{ sf::Keyboard::W ,		-2, -2 },
			/* DOWN */	{ sf::Keyboard::S ,		-2, -2 },
			/* LEFT */	{ sf::Keyboard::A,		-2, -2 },
			/* RIGHT */	{ sf::Keyboard::D,		-2, -2 },
			/* ATTACK */{ sf::Keyboard::Q ,		-2, -2 },
			/* DEFEND */{ sf::Keyboard::E ,		-2, -2 },
			/* JUMP */	{ sf::Keyboard::Space,	-2, -2 },
			/* ACTION */{ sf::Keyboard::F,		-2, -2 }
		};
	}

	class Input {

	public:
				Input();
		void	load();

		void	set(Type type, int code, bool value);
		void	set2D(Type type, int dx, int dy);

		bool	getInput(int k);
		bool	getPress(int k);
		bool	getRelease(int k);
		void	clear();
		
	private:
		int		getCode(Type type, int k);

	private:
		int 	m_Triggers[(int)Action::TOTAL][NUM_TRIGGERS];

		bool	m_Input[(int)Action::TOTAL];
		int		m_Flank[(int)Action::TOTAL];

		int		m_Dx;
		int		m_Dy;
	};

}