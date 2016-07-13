#pragma once

#include "../Graphics/Nodes/DynamicNode.hpp"

namespace bas {

	class Button : public DynamicNode
	{
	public:
		explicit	Button(const sf::Texture& texture, int width, int height);
					~Button();
	private:
		void		Initialize();
		void		updateCurrent(sf::Time dt);

	private:
		int			m_Width;
		int			m_Height;

		Animation*	m_L;
		Animation*	m_H;
		Animation*	m_A;

	};

}
