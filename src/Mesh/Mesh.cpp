#include "Mesh.h"

////////////////////////////////////////////////////////////
Mesh::Mesh(sf::Vector2f position, sf::Vector2i meshSize, unsigned cellSize)
	: m_positions{ position }, m_size{ meshSize }, m_cellSize{ cellSize }, m_quads{ sf::Quads }, m_lines{ sf::Lines }
{
	m_squareVec.resize(meshSize.x * meshSize.y);
	m_quads.resize(meshSize.x * meshSize.y * 4);
	m_lines.resize((meshSize.x + 1) * (meshSize.y + 1) * 2);

	for (int i = 0; i < meshSize.y; ++i)
	{
		sf::Vector2f cellPosition{ position.x,position.y + i * m_cellSize };
		for (int j = 0; j < meshSize.x; ++j)
		{
			int index = i * meshSize.x + j;
			// Positions
			m_quads[index * 4].position = cellPosition;
			m_quads[index * 4 + 1].position = sf::Vector2f{ cellPosition.x + m_cellSize,cellPosition.y };
			m_quads[index * 4 + 2].position = sf::Vector2f{ cellPosition.x + m_cellSize,cellPosition.y + m_cellSize };
			m_quads[index * 4 + 3].position = sf::Vector2f{ cellPosition.x,cellPosition.y + m_cellSize };
			// Colors
			m_quads[index * 4].color = sf::Color::White;
			m_quads[index * 4 + 1].color = sf::Color::White;
			m_quads[index * 4 + 2].color = sf::Color::White;
			m_quads[index * 4 + 3].color = sf::Color::White;
			// Offset
			cellPosition.x += m_cellSize;
		}
	}
	// Vertical lines
	for (int i = 0; i < meshSize.x + 1; ++i)
	{
		m_lines[i * 2].position = sf::Vector2f(position.x + i * m_cellSize, position.y);
		m_lines[i * 2 + 1].position = sf::Vector2f(position.x + i * m_cellSize, position.y + meshSize.y * m_cellSize);
		// Colors
		m_lines[i * 2].color = sf::Color::Black;
		m_lines[i * 2 + 1].color = sf::Color::Black;
	}
	// Horizontal lines
	for (int i = 0; i < meshSize.y + 1; ++i)
	{
		int index = meshSize.x + 1 + i;
		m_lines[index * 2].position = sf::Vector2f(position.x, position.y + i * m_cellSize);
		m_lines[index * 2 + 1].position = sf::Vector2f(position.x + meshSize.x * m_cellSize, position.y + i * m_cellSize);
		// Colors
		m_lines[index * 2].color = sf::Color::Black;
		m_lines[index * 2 + 1].color = sf::Color::Black;
	}
}

////////////////////////////////////////////////////////////
void Mesh::draw(sf::RenderTarget& target,bool drawSquares, bool drawLines)
{
	if (drawSquares)
	{
		target.draw(m_quads);
	}
	if (drawLines)
	{
		target.draw(m_lines);
	}
}

////////////////////////////////////////////////////////////
bool Mesh::isVisible(std::pair<sf::Vector2f, sf::Vector2f>& viewBox)
{
	auto& [top, boxSize] = viewBox;
	if (m_positions.x < top.x + boxSize.x 
		&& m_positions.x + m_size.x * m_cellSize > top.x 
		&& m_positions.y < top.y + boxSize.y 
		&& m_positions.y + m_size.y * m_cellSize > top.y)
	{
		return true;
	}
	return false;
}

bool Mesh::isInRange(sf::Vector2f mousePos)
{
	if (mousePos.x <= m_positions.x || mousePos.x >= m_positions.x + m_size.x * m_cellSize)
	{
		return false;
	}
	else if (mousePos.y <= m_positions.y || mousePos.y >= m_positions.y + m_size.y * m_cellSize)
	{
		return false;
	}
	return true;
}

void Mesh::activateCell(sf::Vector2f mousePos)
{
	int posX = static_cast<int>(mousePos.x - m_positions.x) / m_cellSize;
	int posY = static_cast<int>(mousePos.y - m_positions.y) / m_cellSize;
	int index = posY * m_size.x + posX;

	SquareType& sqType = m_squareVec[index];
	if (sqType == SquareType::EMPTY)
	{
		sqType = SquareType::FULL;
		setCellColor(SquareType::FULL, index);
	}
	else
	{
		sqType = SquareType::EMPTY;
		setCellColor(SquareType::EMPTY, index);
	}
}

void Mesh::setCellColor(SquareType sqType, int index)
{
	sf::Color color;
	if (sqType == SquareType::EMPTY)
	{
		color = sf::Color::White;
	}
	else
	{
		color = sf::Color::Green;
	}

	m_quads[index * 4].color = color;
	m_quads[index * 4 + 1].color = color;
	m_quads[index * 4 + 2].color = color;
	m_quads[index * 4 + 3].color = color;
}
