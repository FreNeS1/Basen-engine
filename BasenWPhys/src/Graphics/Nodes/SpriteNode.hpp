#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "BaseNode.hpp"

namespace bas {

	class SpriteNode : public BaseNode
	{
	public:
		explicit		SpriteNode(const sf::Texture& texture);								// For defining a sprite as the whole texture
						SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);	// If we need the position of the sprite within the texture

	private:
		/*override*/ virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;	// Draws the node onscreen

	protected:
		sf::Sprite		m_Sprite;
	};

}