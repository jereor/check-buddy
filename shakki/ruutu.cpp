#include "ruutu.h"

Ruutu::Ruutu(int rivi, int sarake)
{
	setSarake(sarake);
	setRivi(rivi);
}

Ruutu::Ruutu()
{
	setSarake(0);
	setRivi(0);
}


int Ruutu::getRivi()
{
	return _rivi;
}


int Ruutu::getSarake()
{
	return _sarake;
}


void Ruutu::setRivi(int rivi) 
{
	this->_rivi = rivi;
}


void Ruutu::setSarake(int sarake) 
{
	this->_sarake = sarake;
}