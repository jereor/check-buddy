#include "peli.h"

using namespace std;


Peli::Peli(int ihmisenVari)
{
	if (ihmisenVari == 0) _koneenVari = 1;
	else if (ihmisenVari == 1) _koneenVari = 0;
}


int Peli::getKoneenVari(){
	return _koneenVari;
}
