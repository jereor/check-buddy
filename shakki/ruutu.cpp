#include "ruutu.h"

Ruutu::Ruutu(int sarake, int rivi)
{
	setRivi(rivi);
	setSarake(sarake);
}

Ruutu::Ruutu()
{
	setRivi(0);
	setSarake(0);
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