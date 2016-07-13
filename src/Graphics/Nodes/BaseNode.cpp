#include "BaseNode.hpp"

namespace bas {

	BaseNode::BaseNode()
		: m_Children()
		, m_Parent(nullptr)
	{ }

	void BaseNode::attachChild(Ptr newChild)
	{
		newChild->m_Parent = this;
		m_Children.push_back(std::move(newChild));
	}

	BaseNode::Ptr BaseNode::detachChild(const BaseNode& node)
	{
		auto found = std::find_if(m_Children.begin(), m_Children.end(),
			[&](Ptr& p) -> bool {return (&node == p.get()); });

		assert(found != m_Children.end());	// Never use unborn children for anything

		Ptr result = std::move(*found);
		result->m_Parent = nullptr;
		m_Children.erase(found);
		return result;
	}


	void BaseNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		drawCurrent(target, states);
		drawChildren(target, states);
	}

	void BaseNode::update(sf::Time dt)
	{
		updateCurrent(dt);
		updateChildren(dt);
	}


	void BaseNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const { }

	void BaseNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const Ptr& child : m_Children)
		{
			child->draw(target, states);
		}
	}


	void BaseNode::updateCurrent(sf::Time dt) { }

	void BaseNode::updateChildren(sf::Time dt)
	{
		for (const Ptr& child : m_Children)
		{
			child->update(dt);
		}
	}


	sf::Transform BaseNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;

		for (const BaseNode* node = this; node != nullptr; node = node->m_Parent)
			transform = node->getTransform() * transform;

		return transform;
	}

	sf::Vector2f BaseNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}

}