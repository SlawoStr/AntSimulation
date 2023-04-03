#pragma once
#include <SFML/Graphics.hpp>

enum class SquareType
{
	EMPTY,
	FULL
};

class Mesh
{
public:
	/// <summary>
	/// Create mesh 
	/// </summary>
	/// <param name="position">Mesh position on world map</param>
	/// <param name="meshSize">Number of cells (X,Y)</param>
	/// <param name="squareSize">Size of each square</param>
	Mesh(sf::Vector2f position, sf::Vector2i meshSize, unsigned cellSize);
	/// <summary>
	/// Draw mesh
	/// </summary>
	/// <param name="target">Target to draw</param>
	void draw(sf::RenderTarget& target, bool drawSquares, bool drawLines);
	/// <summary>
	/// Check if mesh is visible in current view
	/// </summary>
	/// <param name="viewBox">View box containig left top point and size of current view</param>
	/// <returns>Is visisble in view</returns>
	bool isVisible(std::pair<sf::Vector2f, sf::Vector2f>& viewBox);
	/// <summary>
	/// Check if mouse position is inside mesh
	/// </summary>
	/// <param name="mousePos">Mouse position</param>
	/// <returns>Is in range</returns>
	bool isInRange(sf::Vector2f mousePos);
	/// <summary>
	/// Activate cell
	/// </summary>
	/// <param name="mousePos">Position of cell to activate (mouse click pos)</param>
	void activateCell(sf::Vector2f mousePos);
private:
	/// <summary>
	/// Change color of a cell with index
	/// </summary>
	/// <param name="sqType">New type of cell</param>
	/// <param name="index">Index of cell</param>
	void setCellColor(SquareType sqType, int index);
private:
	sf::Vector2f m_positions;				//!< Mesh position in world
	sf::Vector2i m_size;					//!< Number of cells in mesh
	std::vector<SquareType>	m_squareVec;	//!< Vector of square types (for drawing)
	unsigned m_cellSize;					//!< Size of each cell (square)
	// Drawing
	sf::VertexArray m_quads;				//!< Vertex array of quads for cell drawing
	sf::VertexArray m_lines;				//!< Vertex array of lines for inMesh line drawing
};