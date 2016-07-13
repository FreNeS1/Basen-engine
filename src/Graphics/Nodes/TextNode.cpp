#include "TextNode.hpp"

namespace bas {

	TextNode::TextNode(const sf::Font& font, unsigned int size, sf::Color color, sf::Uint32 style)
		: m_Text()
	{
		m_Text.setFont(font);
		m_Text.setCharacterSize(size);
		m_Text.setColor(color);
		m_Text.setStyle(style);
	}

	void TextNode::setText(std::string const& text)
	{
		m_Text.setString(text);
	}

	std::string TextNode::getText() const
	{
		return m_Text.getString();
	}

	void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Text, states);
	}

}