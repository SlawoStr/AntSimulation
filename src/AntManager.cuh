#pragma once
#include "Utility/VectorMathHelper.h"
#include <thrust/universal_vector.h>
#include <thrust/host_vector.h>

class AntManager
{
public:
	/// <summary>
	///  Set ants configurations
	/// </summary>
	/// <param name="maxSpeed">Maximum speed</param>
	/// <param name="maxForce">Maximum force</param>
	/// <param name="wanderDistance">Wander distance ( randomMovement setting )</param>
	/// <param name="wanderRadius">Wander radius (randomMovement setting )</param>
	/// <param name="simulationBound">Simulation bounds</param>
	/// <param name="agentNumber">Number of agents to reserve memory for</param>
	void setSettings(float maxSpeed, float maxForce, float wanderDistance, float wanderRadius, float2 simulationBound, unsigned agentNumber);
	/// <summary>
	/// Add new ant
	/// </summary>
	/// <param name="positions">Ant position</param>
	/// <param name="angle">Ant angle</param>
	void addAnt(float2 positions, float angle);
	/// <summary>
	/// Get array of agent positions
	/// </summary>
	/// <returns>Array of positions</returns>
	thrust::host_vector<float2> getPositions() { return m_positions; }
	/// <summary>
	/// Get array of agent angles
	/// </summary>
	/// <returns>Array of angles</returns>
	thrust::host_vector<float> getAngles() { return m_angle; }
private:
	// Agent settings
	float m_maxSpeed;				//!< Maximum speed
	float m_maxForce;				//!< Maximum turning force
	float m_wanderDistance;			//!< Distance from agent to 'wander' circle
	float m_wanderRadius;			//!< Radius of 'wander' circle
	// Other
	float2 m_simulationBound;		//!< Simulation bounds
	// Agent data
	thrust::universal_vector<float2> m_positions;
	thrust::universal_vector<float2> m_velocity;
	thrust::universal_vector<float2> m_acceleration;
	thrust::universal_vector<float>  m_angle;
};