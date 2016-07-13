#pragma once



#include "World.hpp"
#include "../Graphics/Nodes/TextNode.hpp"

namespace bas {

	class DebugWorld : public World
	{
	public:
				DebugWorld(sf::RenderWindow* window, Input* input);
		void	sendMessage(std::string message);
		void	updateState();
		void	tickUps();
		void	tickFps();
		
	private:
		/*overload*/ void	loadResources();
		/*overload*/ void	buildScene();
		std::string			format(int n);

	private:		
		int			m_Fps;
		int			m_Ups;
		
		TextNode*	m_StateText;
		TextNode*	m_MessageText;
		sf::Clock	m_Timer;
		FontHolder	m_Fonts;
	};

}