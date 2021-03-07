#pragma once
#include "ruutu.h"

// Ns. "forward declaration". Nyt Asema-luokassa voidaa esitell� Nappula-osoittimia ilman,
// että nappula.h -tiedostoa täytyy includoida.
class Nappula; 


// Siirto kuvaa nappulan siirtymisen ruudusta toiseen, mukaanlukien erikoissiirrot
// (linnoitus ja ohestalyönti).
class Siirto
{
public:
	Siirto(Ruutu, Ruutu);
	Siirto(){}
	Siirto(bool, bool); // Linnoitus lyhesti (K-siipi) tai pitk�sti (D-siipi?
	Ruutu getAlkuruutu();
	Ruutu getLoppuruutu();
	bool onkoLyhytLinna();
	bool onkoPitkalinna();
	Nappula* _miksikorotetaan = 0; 

private:
	Ruutu _alkuRuutu;
	Ruutu _loppuRuutu;
	bool _lyhytLinna = false;
	bool _pitkaLinna = false;
};