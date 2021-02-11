#pragma once

#include <list>
#include <string>
#include "asema.h"
#include "siirto.h"
using namespace std;


// Vakioarvot nappulatyypeille.
enum
{
	VT,VR,VL,VD,VK,VS,
	MT,MR,ML,MD,MK,MS
};


// Yliluokka shakkinappuloille.
class Nappula
{

private:
	std::wstring	_unicode;	// nappulaa vastaava unicode-merkki
	int				_vari;		// valkea = 0, musta = 1
	int				_koodi;		// VT, VR, MT tms.

public:
	Nappula(std::wstring, int, int);
	Nappula() {}

	// Siirtojen generointi. Puhdas virtuaalifunktio, eli aliluokat toteuttavat tämän
	// omalla tavallaan.
	virtual void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari) = 0;

	void setUnicode(std::wstring unicode)	{ _unicode = unicode;			}
	std::wstring getUnicode()				{ return _unicode;				}
	void setVari(int vari)					{ _vari = vari;					}
	int getVari()							{ return _vari;					}
	int getKoodi()							{ return _koodi;				}
	void setKoodi(int koodi)				{ _koodi = koodi;				}
	void lisaaListalle(int, int, int, int, list<Siirto>&);
};

// Torni-aliluokka. Virtuaalinen perintä tarkoittaa, ett� kantaluokka peritään moniperinnässä vain kerran
// (koska daami perii sekä tornin että lähetin).
class Torni : public virtual Nappula {
public:
	Torni(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Ratsu-aliluokka.
class Ratsu : public Nappula {
public:
	Ratsu(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Lähetti-aliluokka. Virtuaalinen perintä tarkoittaa, että kantaluokka peritän moniperinnässä vain kerran
// (koska daami perii sekä tornin että lähetin).
class Lahetti : public virtual Nappula {
public:
	Lahetti(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Daami-aliluokka. Perii sekä lähetin että tornin.
class Daami : public Lahetti, public Torni {
public:
	Daami(std::wstring unicode, int vari, int koodi) : 
		Nappula(unicode, vari, koodi), Lahetti(unicode, vari, koodi), Torni(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Kuningas-aliluokka.
class Kuningas : public Nappula {
public:
	Kuningas(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
};

// Sotilas-aliluokka.
class Sotilas : public Nappula {
public:
	Sotilas(std::wstring unicode, int vari, int koodi) : Nappula(unicode, vari, koodi) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
private:
	void lisaaSotilaanKorotukset(Siirto*, std::list<Siirto>& lista, Asema*);
};


