#include "ASXVAStateFilter.h"


CASXVAStateFilter::CASXVAStateFilter(void)
{
	m_dQ = 0.707;
	m_bTransposed = false;
	BLI2 = new CASXBilinearIntegrator();
	update();
}

void CASXVAStateFilter::init( int &sampleRate, double &Fc, double &Q, bool T )
{
	m_nSampleRate = sampleRate;
	m_dQ = Q;
	m_bTransposed = T;
	preWarpFc(Fc);
	update();
}

void CASXVAStateFilter::update()
{
	double R = 1/(2*m_dQ);
	double g = pi*m_dFrequency/m_nSampleRate;

	m_dA1 = 1 / ( 1 + 2*R*g + g*g );
	m_dB1 = 2*R + g;
	BLI->setGain(g);
	BLI2->setGain(g);
}

double CASXVAStateFilter::process( double &input )
{
	// Original Form
	if ( !m_bTransposed )
	{
		double HPFout = (input - (BLI->getZ()*m_dB1) - BLI2->getZ())*m_dA1;
		double BPFout = BLI->process(HPFout);
		double LPFout = BLI2->process(BPFout);
		return ( input*m_dD + LPFout*m_dE + HPFout*m_dF + BPFout*m_dG );
	}
	// Transposed Form
	else
	{
		double x = m_dA1*BLI->getZ() + input*m_dF;
		double HPFout = (input*m_dE - x);
		double BPFout = BLI2->process(HPFout);
		x = BPFout - x*m_dB1 + input*m_dG;
		double LPFout = BLI->process(x)*m_dA1;
		x = LPFout + input*m_dF;
		return ( input*m_dD + x );	
	}
}

CASXVAStateFilter::~CASXVAStateFilter(void)
{
	if(BLI2)
		delete BLI2;
}
