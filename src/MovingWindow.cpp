#include <iostream>
#include "MovingWindow.h"
#include "Utility/Timer.h"
#include "Utility/RNGGenerator.h"
#include <math.h>

#define PI 3.14159265

float radians(float a)
{
	return 0.017453292f * a;
}

float degree(float a)
{
	return static_cast<float>(a * (180 / PI));
}

bool isRight(float2 a, float2 b, float2 c)
{
	return((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) > 0;
}

float getDistance(float2 fp, float2 sp)
{
	return sqrtf(powf(sp.x - fp.x, 2) + powf(sp.y - fp.y, 2));
}

////////////////////////////////////////////////////////////
MovingWindow::MovingWindow(unsigned windowWidth, unsigned windowHeight, std::string windowTitle, unsigned framerate) : m_camera(m_window)
{
	m_window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle);
	m_window.setFramerateLimit(framerate);

	m_gridManger.addMesh(sf::Vector2f(0.0f, 0.0f), sf::Vector2i(10, 10), 150);
}

////////////////////////////////////////////////////////////
void MovingWindow::run()
{
	Timer t;
	while (m_window.isOpen())
	{
		t.start();
		if (!m_pause)
		{
			update();
		}
		m_window.clear(sf::Color(128, 128, 128));
		draw();
		m_window.display();
		pollEvent();
		t.stop();
		double elapsedTime = t.measure();
		std::cout << "Frame time: " << elapsedTime * 1000 << std::endl;
	}
}

////////////////////////////////////////////////////////////
void MovingWindow::pollEvent()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		if (m_camera.handleEvent(e))
		{
			break;
		}
		switch (e.type)
		{
			case sf::Event::Closed:
			{
				m_window.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (e.key.code == sf::Keyboard::Escape)
				{
					m_window.close();
				}
				else if (e.key.code == sf::Keyboard::P)
				{
					m_pause = !m_pause;
				}
				else if (e.key.code == sf::Keyboard::Z)
				{
					m_gridManger.switchSquares();
				}
				else if (e.key.code == sf::Keyboard::X)
				{
					m_gridManger.switchLines();
				}
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (e.key.code == sf::Mouse::Button::Left)
				{
					//m_gridManger.handleMouseClick(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
					sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

					for (int i = 0; i < 10'000; i++)
					{
						m_antManager.addAnt({ RNGGenerator::randFloat(0.0f,1500.0f),RNGGenerator::randFloat(0.0f,1500.0f) }, RNGGenerator::randFloat(0.0f, 6.2831f));
					}
				}
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////
void MovingWindow::update()
{
}

////////////////////////////////////////////////////////////
void MovingWindow::draw()
{
	auto res = m_camera.getViewBox();
	m_gridManger.draw(m_window, m_camera.getViewBox());

	auto agentPositions = m_antManager.getPositions();
	auto agentAngles = m_antManager.getAngles();

	// Body
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Red);
	shape.setSize({ 5.0f,5.0f });
	shape.setOrigin(2.5f, 2.5f);
	// Vision
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(10, 10),sf::Color::Red),
		sf::Vertex(sf::Vector2f(150, 150),sf::Color::Red),
		sf::Vertex(sf::Vector2f(10, 10),sf::Color::Red),
		sf::Vertex(sf::Vector2f(150, 150),sf::Color::Red)
	};

	sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	int counter{};
	int spotCounter{};
	for (const auto& pos : agentPositions)
	{
		shape.setPosition({ pos.x,pos.y });
		m_window.draw(shape);

		
		line[0].position.x = pos.x;
		line[0].position.y = pos.y;

		line[1].position.x = pos.x + 50 * cos(agentAngles[counter] - radians(30));
		line[1].position.y = pos.y + 50 * sin(agentAngles[counter] - radians(30));
		
		line[2].position.x = pos.x;
		line[2].position.y = pos.y;

		line[3].position.x = pos.x + 50 * cos(agentAngles[counter] + radians(30));
		line[3].position.y = pos.y + 50 * sin(agentAngles[counter] + radians(30));
		
		/*
		bool rightTest = isRight(pos, { line[3].position.x,line[3].position.y }, { mousePos.x,mousePos.y });
		bool leftTest = isRight(pos, { line[1].position.x,line[1].position.y }, { mousePos.x,mousePos.y });

		if (leftTest && !rightTest)
		{
			line[0].color = sf::Color::Blue;
			line[1].color = sf::Color::Blue;
			line[2].color = sf::Color::Blue;
			line[3].color = sf::Color::Blue;
		}
		else
		{
			line[0].color = sf::Color::Red;
			line[1].color = sf::Color::Red;
			line[2].color = sf::Color::Red;
			line[3].color = sf::Color::Red;
		}
		*/
		float degreeBetween = atan2f(mousePos.y - pos.y, mousePos.x - pos.x);
		float result = fmod((degree(agentAngles[counter] - degreeBetween) + 180.0f + 360.0f), 360.0f) - 180.0f;
		if (result <= 30 && result >= -30)
		{
			spotCounter++;
		}
		//std::cout << "Result degree: " << result << std::endl;
		
		if (result <= 30 && result >= -30)
		{
			line[0].color = sf::Color::Blue;
			line[1].color = sf::Color::Blue;
			line[2].color = sf::Color::Blue;
			line[3].color = sf::Color::Blue;
		}
		else
		{
			line[0].color = sf::Color::Red;
			line[1].color = sf::Color::Red;
			line[2].color = sf::Color::Red;
			line[3].color = sf::Color::Red;
		}
		m_window.draw(line, 4, sf::Lines);
		counter++;
	}
	std::cout << "Spot counter: " << spotCounter << std::endl;
}
