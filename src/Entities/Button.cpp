#include "Button.hpp"

namespace bas {

	Button::Button(const sf::Texture& texture, int width, int height)
		: DynamicNode(texture)
		, m_Width(width)
		, m_Height(height)
	{
		Initialize();
	}

	Button::~Button()
	{
		delete m_L;
		delete m_H;
		delete m_A;
	}

	void Button::Initialize()
	{
		m_L = createAnimation("low", 0 * m_Width, 0, m_Width, m_Height, 1, 1, false);
		m_H = createAnimation("highlighted", 1 * m_Width, 0, m_Width, m_Height, 1, 1, false);
		m_A = createAnimation("active", 2 * m_Width, 0, m_Width, m_Height, 1, 1, false);

		setAnimation(m_L);
	}

	void Button::updateCurrent(sf::Time dt)
	{
		
		
		DynamicNode::updateCurrent(dt);

	}

}