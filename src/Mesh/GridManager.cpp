#include "GridManager.h"
#include <iostream>

////////////////////////////////////////////////////////////
void GridManager::draw(sf::RenderTarget& target, std::pair<sf::Vector2f, sf::Vector2f> viewBox)
{
	for (auto& mesh : m_meshVec)
	{
		if (mesh.isVisible(viewBox))
		{
			mesh.draw(target, drawSquares, drawLines);
		}
	}
}

////////////////////////////////////////////////////////////
void GridManager::addMesh(sf::Vector2f position, sf::Vector2i meshSize, unsigned cellSize)
{
	m_meshVec.emplace_back(position, meshSize, cellSize);
}

void GridManager::handleMouseClick(sf::Vector2f mousePos)
{
	for (auto& mesh : m_meshVec)
	{
		if (mesh.isInRange(mousePos))
		{
			mesh.activateCell(mousePos);
			return;
		}
	}
	std::cout << "Not handled" << std::endl;
}
