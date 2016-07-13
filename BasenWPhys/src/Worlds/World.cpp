#include "World.hpp"

namespace bas {

	World::World(sf::RenderWindow* window, Input* input)
		: m_Window(window)
		, m_WorldView(window->getDefaultView())
		, m_Scene()
		, m_Input(input)
	{ }

	World::~World()
	{
		m_Input = nullptr;
	}

	void World::build()
	{
		loadResources();
		buildScene();
	}

	void World::loadResources() { }

	void World::buildScene() { }

	void World::draw()
	{
		m_Window->setView(m_WorldView);
		m_Window->draw(m_Scene);
		std::string s = "";
		if (m_Input->getInput((int)Action::UP))
			s = "Hi";
		m_Window->setTitle(s);
	}

	void World::update(sf::Time dt)
	{
		m_Scene.update(dt);
	}

}