#pragma once
#include <vector>
#include "Mesh.h"

/// <summary>
/// Meshes manager
/// </summary>
class GridManager
{
public:
	/// <summary>
	/// Draw mehes
	/// </summary>
	/// <param name="target">Target to draw</param>
	/// <param name="viewBox">Current camera view</param>
	void draw(sf::RenderTarget& target, std::pair<sf::Vector2f, sf::Vector2f> viewBox);
	/// <summary>
	/// Add new mesh
	/// </summary>
	/// <param name="position">Mesh position</param>
	/// <param name="meshSize">Mesh size</param>
	void addMesh(sf::Vector2f position, sf::Vector2i meshSize,unsigned cellSize);
	/// <summary>
	/// Turn off square drawing
	/// </summary>
	void switchSquares() { drawSquares = !drawSquares; };
	/// <summary>
	/// Turn off line drawing
	/// </summary>
	void switchLines() { drawLines = !drawLines; };
	/// <summary>
	/// Handle mouse click
	/// </summary>
	/// <param name="mousePos">Mouse click position</param>
	void handleMouseClick(sf::Vector2f mousePos);
private:
	std::vector<Mesh> m_meshVec;		//!< Mesh vector
	bool drawSquares{ true };			//!< Square drawing flag
	bool drawLines{ true };				//!< Line drawing flag
};