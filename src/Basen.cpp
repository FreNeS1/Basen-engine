#include "Basen.hpp"

namespace bas {

	Basen::Basen(const char* name, const char* title, const char* version)
		: m_IsFocused(true)
		, m_Name(name)
		, m_Options("Options.stg")
		, m_Logger("Logger.log")
		, m_Input()
	{
		/* First, we have to handle the settings */
		if (m_Options.loadOptions())
			m_Logger << utils::FileLogger::LogType::LOG_INFO << "Options file loaded";
		else
			m_Logger << utils::FileLogger::LogType::LOG_WARNING << "Options file corrupt, back to defaults";

		/* Then, we create the window and load the default world */
		m_Window = new sf::RenderWindow();
		if (m_Options.getFullscreen())
			m_Window->create(sf::VideoMode(m_Options.getWidth(), m_Options.getHeight()), title, sf::Style::Fullscreen);
		else
			m_Window->create(sf::VideoMode(m_Options.getWidth(), m_Options.getHeight()), title, sf::Style::Default);
		m_Logger << utils::FileLogger::LogType::LOG_INFO << "Window created";

		/* Now we only need to load the current world and request focus for the game*/
		m_CurrentWorld = new World(m_Window, &m_Input);
		m_CurrentWorld->build();
		m_Window->requestFocus();

#if B_DEBUG
		/* If the debug screen is active, we create the debug window with the debug world */
		m_DebugWindow = new sf::RenderWindow();
		m_DebugWindow->create(sf::VideoMode(640, 480), "Debug Console", sf::Style::Titlebar);
		m_DebugWindow->setPosition(sf::Vector2i(0, 0));
		m_DebugWorld = new DebugWorld(m_DebugWindow, &m_Input);
		m_DebugWorld->build();
		m_Window->requestFocus();
#endif
	}

	Basen::~Basen()
	{
		/* Delete all the stuff i was using */
		delete m_CurrentWorld;
		delete m_DebugWorld;
		delete m_Window;
		delete m_DebugWindow;
	}

	void Basen::run()
	{
		/* We create a clock and if the time is set, we limit the render() and update()
		*  functions. If we have a debug window we do update and render there too */

		sf::Clock clock;

		sf::Time fpsTimer = sf::Time::Zero;
		sf::Time upsTimer = sf::Time::Zero;
#if B_DEBUG
		sf::Time debugTimer = sf::Time::Zero;
#endif
		sf::Time fpsStep = sf::seconds(1.0f / CONSTANT_FPS);
		sf::Time upsStep = sf::seconds(1.0f / CONSTANT_UPS);

		/* Main program loop */
		while (m_Window->isOpen())
		{
			sf::Time timeElapsed = clock.restart();
			fpsTimer += timeElapsed;
			upsTimer += timeElapsed;

#if B_DEBUG
			debugTimer += timeElapsed;

			if (debugTimer > sf::seconds(1.0f))
			{
				debugTimer -= sf::seconds(1.0f);
				m_DebugWorld->updateState();
			}
#endif

			if (FIXED_FPS)
			{
				if (fpsTimer > fpsStep)
				{
#if B_DEBUG
					m_DebugWorld->tickFps();
#endif
					fpsTimer -= fpsStep;
					render();
				}
			}
			else
			{
				render();
#if B_DEBUG
				m_DebugWorld->tickFps();
#endif
			}

			if (FIXED_UPS)
			{
				if (upsTimer > upsStep)
				{
					upsTimer -= upsStep;
					update(upsStep);
#if B_DEBUG
					m_DebugWorld->tickUps();
#endif
				}
			}
			else
			{
				update(timeElapsed);
#if B_DEBUG
				m_DebugWorld->tickUps();
#endif
			}

			processEvents();
		}
	}

	void Basen::processEvents()
	{
		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				handleInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handleInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				m_Window->close();
				break;
			case sf::Event::GainedFocus:
				m_IsFocused = true;
				break;
			case sf::Event::LostFocus:
				m_IsFocused = false;
				break;
			}
		}
	}

	void Basen::update(sf::Time deltaTime)
	{
		if (m_IsFocused)
		{
			m_CurrentWorld->update(deltaTime);
			m_Input.clear();
		}

#if B_DEBUG
		m_DebugWorld->update(deltaTime);
#endif
	}

	void Basen::render()
	{
		m_Window->clear(sf::Color::Black);
		m_CurrentWorld->draw();
		m_Window->display();

#if B_DEBUG
		m_DebugWindow->clear(sf::Color::Black);
		m_DebugWorld->draw();
		m_DebugWindow->display();
#endif
	}

	void Basen::handleInput(sf::Keyboard::Key key, bool isPressed)
	{
		m_Input.set(Type::Keyboard, key, isPressed);
	}
}

/*
#include "Game.hpp"
#include <iostream>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close)
	, mWorld(mWindow)
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsFocused(true)
{
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	std::cout << "PLS";
	sf::Clock clock;
	sf::Time lastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time timeElapsed = clock.restart();
		lastUpdate += timeElapsed;
		while (lastUpdate > TimePerFrame)
		{
			lastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(timeElapsed);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::GainedFocus:
			mIsFocused = true;
			break;
		case sf::Event::LostFocus:
			mIsFocused = false;
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	if (mIsFocused)
		mWorld.update(deltaTime);
}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string((mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames)) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key,
	bool isPressed)
{
}*/