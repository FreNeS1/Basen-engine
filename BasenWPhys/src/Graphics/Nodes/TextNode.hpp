#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "BaseNode.hpp"

namespace bas {

	class TextNode : public BaseNode
	{
	public:
		explicit			TextNode(const sf::Font& font, unsigned int size, sf::Color color = sf::Color::White, sf::Uint32 style = 0);
		void				setText(std::string const& text);
		std::string			getText() const;

	private:
		/*override*/ virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		sf::Text		m_Text;
	};

}