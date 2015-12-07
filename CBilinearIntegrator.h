#pragma once

class CBilinearIntegrator
{
protected:
	double m_dGain;
	double m_dZ;
public:
	CBilinearIntegrator()				// constructor
	{
		m_dGain = 0.0;
		m_dZ = 0.0;
	}
	inline void init(double g)			// initialize
	{
		m_dGain = g;
		m_dZ = 0;
	}
	inline void reset()
	{
		m_dZ = 0;
	}
	inline void setGain(double g)			// set Gain
	{
		m_dGain = g;
	}
	inline double getZ()				// get Delay
	{
		return m_dZ;
	}
	inline double getGain()				// get Gain
	{
		return m_dGain;
	}
	inline double doIntegrate(double &input)	// Integrate
	{
		double v = input*m_dGain;		// process node v
		double output = v + m_dZ;		// process output
		m_dZ = v + output;			// process z
		return output;
	}
};
