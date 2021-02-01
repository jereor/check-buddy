#include <iostream>
#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
#include <fcntl.h>
#include <io.h>
using namespace std;


Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();
	Ruutu alkuRuutu = Ruutu(lahtoruutuX, lahtoruutuY);
	Ruutu loppuRuutu;
	Siirto siirto;

	bool laillinenSiirto;

	wcout << "Ratsu\n";

	// Lista siirroista
	int liikkeet[8][2]
	{
		{-2, 1},
		{-1, 2},
		{1, 2},
		{2, 1},
		{2, -1},
		{1, -2},
		{-1, -2},
		{-2, -1}
	};

	for (int* liike : liikkeet)
	{
		laillinenSiirto = true;
		loppuRuutu = Ruutu(lahtoruutuX + liike[0], lahtoruutuY + liike[1]);
		siirto = Siirto(alkuRuutu, loppuRuutu);

		wcout << alkuRuutu.getRivi() + liike[0] << " " << alkuRuutu.getSarake() + liike[1] << endl;

		// Katsotaan meneekö ratsu yli laudan
		if ((alkuRuutu.getRivi() + liike[0] > 7 || alkuRuutu.getRivi() + liike[0] < 0) || (alkuRuutu.getSarake() + liike[1] > 7 || alkuRuutu.getSarake() + liike[1] < 0))
		{
			if ((alkuRuutu.getRivi() + liike[0] > 7 && alkuRuutu.getSarake() + liike[1] > 7) || (alkuRuutu.getRivi() + liike[0] < 0 && alkuRuutu.getSarake() + liike[1] < 0))
			{
				wcout << "Laiton siirto" << endl;
					laillinenSiirto = false;
			}
			wcout << "Laiton siirto" << endl;
				laillinenSiirto = false;
		}
		// Katsotaan onko ruutu tyhjä
		if (laillinenSiirto == true)
		{
			wcout << "Lisätään siirto listaan" << endl;
			lista.push_back(siirto);
		}
	}
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int mahdolliset_suunnat[4][2] = { { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 } };
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on että kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
	oman nappulan päälle ei voi mennä ja vastustajan nappulan voi syödä.

	Kaikki muu kuninkaaseen liittyvä tarkistus tehd��n eri paikassa*/


	
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();

	int lahtoRuudunNappulanVari;
	int lahtoRuudunNappulanVari;


}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
