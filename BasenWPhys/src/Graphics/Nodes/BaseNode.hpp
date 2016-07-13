#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>

namespace bas {

	class BaseNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
	{
	public:
		typedef std::unique_ptr<BaseNode> Ptr;					// This Ptr will be used a lot due to class relations with itself

	public:
							BaseNode();							// This will create an empty SceneNode with no children

		void				attachChild(Ptr newChild);			// This will attach a child and force the target to take this one as parent.
		Ptr					detachChild(const BaseNode& node);	// This will detach a child and focre the target to take (nullptr) as parent.

		void				update(sf::Time dt);				// This updates the node and all of its children calling uCurr and uChildr

		sf::Transform		getWorldTransform() const;			// Utility, this get's the world transform of the SceneNode 
		sf::Vector2f		getWorldPosition() const;			// Utility, this get's the world position of the SceneNode

	private:
		void				draw(sf::RenderTarget& target, sf::RenderStates states) const;			// This draws the node and all of its children calling dCurr and dChildr
		virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;	// Draws the current node. Classes created from this must declare a custom draw.
		void				drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;  // Calls draw() in all of the SceneNode's children

		virtual void		updateCurrent(sf::Time dt);			// Updates the current Node. Classes created from this must declare a custom update.
		void				updateChildren(sf::Time dt);		// Calls update(dt) in all of the SceneNode's children

	private:
		BaseNode*			m_Parent;		// This one's parent
		std::vector<Ptr>	m_Children;		// This one's children
	};

}