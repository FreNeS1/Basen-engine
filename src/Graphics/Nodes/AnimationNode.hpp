#pragma once

#include "SpriteNode.hpp"

namespace bas {

	class AnimationNode : public SpriteNode
	{
	public:
		explicit		AnimationNode(const sf::Texture& texture, int frameWidth, int height, int frames, float duration, bool loop = true);								// For defining a sprite as the whole texture

	private:
		/*override*/ virtual void	updateCurrent(sf::Time dt);

	private:
		float		m_ElapsedTime;
		float		m_AnimDuration;
		bool		m_Loop;
		int			m_Frames;
		int			m_FrameWidth;
		int			m_Height;
	};
	
}