#include "SpriteNode.hpp"

namespace bas {

	SpriteNode::SpriteNode(const sf::Texture& texture)
		: m_Sprite(texture)
	{ }

	SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
		: m_Sprite(texture, textureRect)
	{ }

	void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Sprite, states);
	}

}