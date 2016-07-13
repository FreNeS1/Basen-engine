#include "DynamicNode.hpp"

namespace bas {

	Animation::Animation(std::string const& name, int xOffset, int yOffset, int frameWidth, int height, int frames, float duration, bool loop)
		: m_Name(name)
		, m_Frames()
		, m_Loop(loop)
		, m_AnimDuration(duration)
		, m_NumFrames(frames)
	{
		for (int i = 0; i < frames; i++)
		{
			m_Frames.push_back(sf::IntRect(xOffset + frameWidth * i, yOffset, frameWidth, height));
		}
	}

	std::string const& Animation::getName() const
	{
		return m_Name;
	}

	bool Animation::getLoop() const
	{
		return m_Loop;
	}

	float Animation::getDuration() const
	{
		return m_AnimDuration;
	}

	int Animation::getNumFrames() const
	{
		return m_NumFrames;
	}

	/***********************************/

	DynamicNode::DynamicNode(const sf::Texture& texture)
		: SpriteNode(texture)
		, m_AnimationList()
		, m_CurrentAnimationName()
		, m_CurrentAnimation(nullptr)
		, m_CurrentAnimationTime()
	{
		updateCurrent(sf::Time::Zero);
	}

	DynamicNode::~DynamicNode()
	{
		delete m_CurrentAnimation;
	}

	Animation* DynamicNode::createAnimation(std::string const& name, int xOffset, int yOffset, int frameWidth, int height, int numFrames, float duration, bool loop)
	{
		m_AnimationList.push_back(Animation(name, xOffset, yOffset, frameWidth, height, numFrames, duration, loop));

		return &m_AnimationList.back();
	}

	Animation* DynamicNode::findAnimation(std::string const& name)
	{
		for (auto item = m_AnimationList.begin(); item != m_AnimationList.end(); item++)
		{
			if (item->getName() == name)
				return &*item;				/* I have no idea what i'm doing here */
		}

		return nullptr;
	}

	bool DynamicNode::setAnimation(std::string const& name)
	{
		Animation* animation = findAnimation(name);

		if (animation != nullptr)
		{
			setAnimation(animation);
			return true;
		}

		return false;
	}

	void DynamicNode::setAnimation(Animation* animation)
	{
		m_CurrentAnimation = animation;
		m_CurrentAnimationName = animation->getName();
		m_CurrentAnimationTime = 0.0f;
	}

	std::string DynamicNode::getCurrentAnimationName() const
	{
		return m_CurrentAnimationName;
	}


	void DynamicNode::updateCurrent(sf::Time dt)
	{
		if (m_CurrentAnimation == nullptr)
			return;

		m_CurrentAnimationTime += dt.asSeconds();

		float animState = (m_CurrentAnimationTime / m_CurrentAnimation->getDuration()); /* 0 < animState < 1 */

		if (animState >= 1)
		{
			if (m_CurrentAnimation->getLoop())
			{
				animState = 0;
				m_CurrentAnimationTime = 0;
			}
			else
			{
				animState = 1;
				m_CurrentAnimationTime = m_CurrentAnimation->getDuration() * 1.2f;
			}
		}

		int currentFrame = (int)(animState * m_CurrentAnimation->getNumFrames());
		sf::IntRect& currentRect = m_CurrentAnimation->m_Frames[currentFrame];

		m_Sprite.setTextureRect(sf::IntRect(currentRect));
	}



	/*class DynamicNode : public SpriteNode
	{
	public:
		explicit		DynamicNode(const sf::Texture& texture);								// For defining a sprite as the whole texture
		void			createAnimation(std::string const& name, int xOffset, int yOffset, int frameWidth, int height, int frames, float duration, bool loop = false);
		void			createState(int ID, int xOffset, int yOffset, int width, int height);
		void			setAnimation(std::string const& name);
		std::string		getCurrentAnimationName();

	private:
		/*override*virtual void	updateCurrent(sf::Time dt);

	private:
		std::vector<Animation>	m_AnimationList;
		std::string				m_CurrentAnimationName;
		sf::Time				m_CurrentAnimationTime;
	};*/

}