#pragma once

#include "SpriteNode.hpp"

namespace bas {

	struct Animation
	{
	public:
		Animation(std::string const& name, int xOffset, int yOffset, int frameWidth, int height, int frames, float duration, bool loop);
		std::string const&			getName() const;
		bool						getLoop() const;
		float						getDuration() const;
		int							getNumFrames() const;
		std::vector<sf::IntRect>	m_Frames;
	
	private:
		std::string					m_Name;
		bool						m_Loop;
		float						m_AnimDuration;
		int							m_NumFrames;
	};

	class DynamicNode : public SpriteNode
	{
	public:
		explicit		DynamicNode(const sf::Texture& texture);								// For defining a sprite as the whole texture
						~DynamicNode();
		Animation*		createAnimation(std::string const& name, int xOffset, int yOffset, int frameWidth, int height, int numFrames, float duration, bool loop = false);
		bool			setAnimation(std::string const& name);
		std::string		getCurrentAnimationName() const;

	protected:
		void						setAnimation(Animation* animation);
		/*override*/ virtual void	updateCurrent(sf::Time dt);

	private:
		Animation*					findAnimation(std::string const& name);

	private:
		std::vector<Animation>	m_AnimationList;
		Animation*				m_CurrentAnimation;
		std::string				m_CurrentAnimationName;
		float					m_CurrentAnimationTime;
	};

}