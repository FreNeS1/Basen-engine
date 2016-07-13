#pragma once 

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../Graphics/Nodes/BaseNode.hpp"
#include "../Graphics/Nodes/TextNode.hpp" 
#include "../Resources/ResourceHolder.hpp"
#include "../Resources/ResourceHolderNames.hpp"
#include "../Input/Input.hpp"

namespace bas {

	class World : private sf::NonCopyable
	{
	public:
											World(sf::RenderWindow* window, Input* input);	// Default constructor								// Default destructor ?
											~World();

		void								build();										// Builds and places the world
		void								update(sf::Time dt);							// Update method
		void								draw();											// Draw method

	private:
		virtual void						buildScene();		// At the start of the world, we create and position all nodes
		virtual void						loadResources();	// At the start of the world, we load it's resources

	protected:
		sf::RenderWindow*					m_Window;		// The window
		sf::View							m_WorldView;	// The camera
		
		Input*								m_Input;		// Input to the world
		BaseNode							m_Scene;		// Main world node
	};

}