#pragma once

#include "ASXVAFilter.h"

class CASXVAStateFilter : public CASXVAFilter
{
protected:
	CASXBilinearIntegrator * BLI2;
	double m_dQ;
	double m_dA1;
	double m_dB1;
	bool m_bTransposed;

	double m_dD;
	double m_dE;
	double m_dF;
	double m_dG;
public:
	CASXVAStateFilter(void);
	virtual ~CASXVAStateFilter(void);

	// Initialize
	void init( int &sampleRate, double &Fc, double &Q, bool T );

	// Setters
	inline void setQ( double &Q ) { m_dQ = Q; }
	inline void setTransposed( bool T ) { m_bTransposed = T; }
	inline void setD( double &D ) { m_dD = D; }
	inline void setE( double &E ) { m_dE = E; }
	inline void setF( double &F ) { m_dF = F; }
	inline void setG( double &G ) { m_dG = G; }

	// Update
	void update();

	// Process
	double process( double &input );
};
