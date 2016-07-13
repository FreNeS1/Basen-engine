#include "AnimationNode.hpp"

namespace bas {

	AnimationNode::AnimationNode(const sf::Texture& texture, int frameWidth, int height, int frames, float duration, bool loop)
		: SpriteNode(texture) /*Sprite is being set 2 times*/
		, m_ElapsedTime()
		, m_AnimDuration(duration)
		, m_Frames(frames)
		, m_FrameWidth(frameWidth)
		, m_Height(height)
		, m_Loop(loop)
	{
		updateCurrent(sf::Time::Zero);
	}

	void AnimationNode::updateCurrent(sf::Time dt)
	{
		m_ElapsedTime += dt.asSeconds();
		int animFrame = (int)((m_ElapsedTime / m_AnimDuration) * m_Frames) % m_Frames;

		if ((m_ElapsedTime / m_AnimDuration) >= 1)
		{
			if (m_Loop)
			{
				animFrame = 0;
				m_ElapsedTime = 0;
			}
			else
			{
				animFrame = m_Frames - 1;
				m_ElapsedTime = m_AnimDuration * 1.2f;
			}
		}

		m_Sprite.setTextureRect(sf::IntRect(animFrame * m_FrameWidth, 0, m_FrameWidth, m_Height));
	}
}