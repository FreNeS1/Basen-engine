#include "DebugWorld.hpp"

namespace bas {

	DebugWorld::DebugWorld(sf::RenderWindow* window, Input* input)
		: World(window, input)
		, m_StateText()
		, m_MessageText()
		, m_Fonts()
		, m_Timer()
	{ }

	void DebugWorld::loadResources()
	{
		m_Fonts.load(Fonts::Debug1, "res/Fonts/Debug.ttf");
	}

	void DebugWorld::buildScene()
	{
		sf::Font& debugFont = m_Fonts.get(Fonts::Debug1);

		std::unique_ptr<TextNode> stateText(new TextNode(debugFont, 20));
		m_StateText = stateText.get();
		m_StateText->setPosition(410.0f, 0.0f);
		updateState();
		m_Scene.attachChild(std::move(stateText));

		std::unique_ptr<TextNode> messageText(new TextNode(debugFont, 20));
		m_MessageText = messageText.get();
		m_MessageText->setText("[" + std::to_string(m_Timer.getElapsedTime().asMilliseconds()) + "] ms - Debug window created.");
		m_Scene.attachChild(std::move(messageText));
	}

	std::string DebugWorld::format(int n)
	{
		int in = n;
		std::string sn;

		if (in < 10)
			sn = "000" + std::to_string(in);
		else if (in < 100)
			sn = "00" + std::to_string(in);
		else if (in < 1000)
			sn = "0" + std::to_string(in);
		else
			sn = std::to_string(in);

		return sn;
	}

	void DebugWorld::updateState() /* TO BE CALLED ONCE PER SECOND */
	{
		std::string sfps = format(m_Fps);
		std::string sups = format(m_Ups);

		m_StateText->setText("FPS: " + sfps + " / UPS: " + sups);

		m_Scene.update(sf::Time::Zero);
		m_Window->draw(m_Scene);

		m_Fps = 0;
		m_Ups = 0;
	}

	void DebugWorld::sendMessage(std::string message)
	{
		std::string text = m_MessageText->getText();
		text = text + "\n[" + std::to_string(m_Timer.getElapsedTime().asMilliseconds()) + "] ms - " + message;
		m_MessageText->setText(text);

		m_Scene.update(sf::Time::Zero);
		m_Window->draw(m_Scene);
	}

	void DebugWorld::tickFps()
	{
		m_Fps++;
	}
	
	void DebugWorld::tickUps()
	{
		m_Ups++;
	}
}