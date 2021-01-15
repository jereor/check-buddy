#include "ruutu.h"

Ruutu::Ruutu(int sarake, int rivi)
{
	setRivi(rivi);
	setSarake(sarake);
}


int Ruutu::getRivi()
{
	return 0;
}


int Ruutu::getSarake()
{
	return 0;
}


void Ruutu::setRivi(int rivi) 
{
	this->_rivi = rivi;
}


void Ruutu::setSarake(int sarake) 
{
	this->_sarake = sarake;
}