#pragma once

#include <list>
#include <string>
#include "minmaxpaluu.h"
#include "siirto.h"


// Ns. "forward declaration". Nyt Asema-luokassa voidaa esitellä Nappula-osoittimia ilman,
// että nappula.h -tiedostoa täytyy includoida.
class Nappula;


// Asema sisältää kaiken tarvittavan informaation pelitilanteen kuvaamiseksi
// (nappuloiden sijainti, siirtovuoro, linnoitusoikeudet jne.).
class Asema
{

public:
	// Pelilauta sisältää osoittimet kunkin ruudun nappula-olioon (nullptr/NULL/0 jos ruutu on tyhjä).
	// Public-määreellä, koska tätä käytetään paljon muualla.
	Nappula* _lauta[8][8];

	// Nappula-oliot. Huomaa, että samaa nappulaa voidaan käyttää useissa eri ruuduissa.
	// Määritelty static-määreellä, joten nappulat ovat kaikkien lauta-olioiden "yhteiskäytössä"
	// (suorituskyvyn vuoksi).
	static Nappula *vk, *vd, *vt, *vl, *vr, *vs;	// Valkeat nappulat.
	static Nappula *mk, *md, *mt, *ml, *mr, *ms;	// Mustat nappulat.

	// Ohestalyöntiä varten (-1 = sotilaan kaksoisaskelta ei tapahtunut edellisellä siirrolla).
	int kaksoisaskelSarakkeella = -1;


	Asema();												// Asettaa alkuaseman.
	void paivitaAsema(Siirto*);								// Päivittää aseman annetulla siirrolla.
	double evaluoi();										// Aseman numeerinen arviointi.
	MinMaxPaluu maxi(int syvyys);							// Minimax (max:n siirtovuoro).
	MinMaxPaluu mini(int syvyys);							// Minimax (min:n siirtovuoro).
	MinMaxPaluu minimax(int syvyys);						// Minimax-algoritmi.
	void annaLaillisetSiirrot(std::list<Siirto>& lista);	// Siirtogeneraattori.
	int getSiirtovuoro();									// Palauttaa siirtovuoron.
	void setSiirtovuoro(int);								// Asettaa siirtovuoron.
	bool getOnkoValkeaKuningasLiikkunut();					// Linnoittuminen mahdollista?
	bool getOnkoMustaKuningasLiikkunut();					// Linnoittuminen mahdollista?
	bool getOnkoValkeaDTliikkunut();						// Linnoittuminen mahdollista?
	bool getOnkoValkeaKTliikkunut();						// Linnoittuminen mahdollista?
	bool getOnkoMustaDTliikkunut();							// Linnoittuminen mahdollista?
	bool getOnkoMustaKTliikkunut();							// Linnoittuminen mahdollista?
	
private:

	// Lisäinformaatio pelitilanteesta.
	int _siirtovuoro;					// 0 = valkea, 1 = musta.
	bool _onkoValkeaKuningasLiikkunut;	// Linnoitus ei ole sallittu, jos kuningas on liikkunut.
	bool _onkoMustaKuningasLiikkunut;	// Linnoitus ei ole sallittu, jos kuningas on liikkunut.
	bool _onkoValkeaDTliikkunut;		// Linnoitus ei ole sallittu, jos daamisivustan torni on liikkunut.
	bool _onkoValkeaKTliikkunut;		// Linnoitus ei ole sallittu, jos kuningassivustan torni on liikkunut.
	bool _onkoMustaDTliikkunut;			// Linnoitus ei ole sallittu, jos daamisuvustan torni on liikkunut.	
	bool _onkoMustaKTliikkunut;			// Linnoitus ei ole sallittu, jos kuningassivustan torni on liikkunut.

	double laskeNappuloidenArvo(int);
	bool onkoAvausTaiKeskipeli(int);
	double nappuloitaKeskella(int);
	double linjat(int);
	bool onkoRuutuUhattu(Ruutu*, int vastustajanVari);
	void annaLinnoitusSiirrot(std::list<Siirto>& lista, int vari);

	// Karsii siirrot, jotka jättävät oman K:n shakkiin.
	void huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari); 
};