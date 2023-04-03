#include "AntManager.cuh"

void AntManager::setSettings(float maxSpeed, float maxForce, float wanderDistance, float wanderRadius, float2 simulationBound, unsigned agentNumber)
{
	// Set settings
	m_maxSpeed = maxSpeed;
	m_maxForce = maxForce;
	m_wanderDistance = wanderDistance;
	m_wanderRadius = wanderRadius;
	m_simulationBound = simulationBound;
	// Allocate memory for agents data
	m_positions.reserve(agentNumber);
	m_velocity.reserve(agentNumber);
	m_acceleration.reserve(agentNumber);
	m_angle.reserve(agentNumber);
}

void AntManager::addAnt(float2 positions, float angle)
{
	m_positions.push_back(positions);
	m_velocity.push_back({ 0.f,0.f });
	m_acceleration.push_back({ 0.f,0.f });
	m_angle.push_back(angle);
}