#include <iostream>
#include <cstddef>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);

Asema::Asema()
{
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa
	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			_lauta[x][y] = NULL;
		}
	}

	// Asetetaan alkuaseman mukaisesti nappulat ruuduille

	_lauta[0][0] = mt; // Musta Torni
	_lauta[0][1] = mr; // Musta Ratsu
	_lauta[0][2] = ml; // Musta Lähetti
	_lauta[0][3] = mk; // Musta Kuningas
	_lauta[0][4] = md; // Musta Daami
	_lauta[0][5] = ml; // Musta Lähetti
	_lauta[0][6] = mr; // Musta Ratsu
	_lauta[0][7] = mt; // Musta Torni
	_lauta[1][0] = ms; // Musta Sotilas
	_lauta[1][1] = ms; // Musta Sotilas
	_lauta[1][2] = ms; // Musta Sotilas
	_lauta[1][3] = ms; // Musta Sotilas
	_lauta[1][4] = ms; // Musta Sotilas
	_lauta[1][5] = ms; // Musta Sotilas
	_lauta[1][6] = ms; // Musta Sotilas
	_lauta[1][7] = ms; // Musta Sotilas

	_lauta[7][0] = vt; // Val. Torni
	_lauta[7][1] = vr; // Val. Ratsu
	_lauta[7][2] = vl; // Val. Lähetti
	_lauta[7][3] = vk; // Val. Kuningas
	_lauta[7][4] = vd; // Val. Daami
	_lauta[7][5] = vl; // Val. Lähetti
	_lauta[7][6] = vr; // Val. Ratsu
	_lauta[7][7] = vt; // Val. Torni
	_lauta[6][0] = vs; // Val. Sotilas
	_lauta[6][1] = vs; // Val. Sotilas
	_lauta[6][2] = vs; // Val. Sotilas
	_lauta[6][3] = vs; // Val. Sotilas
	_lauta[6][4] = vs; // Val. Sotilas
	_lauta[6][5] = vs; // Val. Sotilas
	_lauta[6][6] = vs; // Val. Sotilas
	_lauta[6][7] = vs; // Val. Sotilas
}


void Asema::paivitaAsema(Siirto *siirto)
{
	// Kaksoisaskel-lippu on oletusarvoisesti pois päältä.
	// Asetetaan myöhemmin, jos tarvii.
	kaksoisaskelSarakkeella = -1;


	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna())
	{
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL; // kuninkaan paikka tyhjä
			_lauta[6][0] = vk; // kuninkaan uusi paikka
			_lauta[7][0] = NULL; // tornin paikka tyhjä
			_lauta[5][0] = vt; // tornin uusi paikka
		}
		if (_siirtovuoro == 1) {
			_lauta[4][7] = NULL; // kuninkaan paikka tyhjä
			_lauta[6][7] = mk; // kuninkaan uusi paikka
			_lauta[7][7] = NULL; // tornin paikka tyhjä
			_lauta[5][7] = mt; // tornin uusi paikka
		}
	}

	// Onko pitkä linna
	if (siirto->onkoPitkalinna())
	{
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL; // kuninkaan paikka tyhjä
			_lauta[2][0] = vk; // kuninkaan uusi paikka
			_lauta[0][0] = NULL; // tornin paikka tyhjä
			_lauta[3][0] = vt; // tornin uusi paikka
		}
		if (_siirtovuoro == 1) {
			_lauta[4][7] = NULL; // kuninkaan paikka tyhjä
			_lauta[2][7] = mk; // kuninkaan uusi paikka
			_lauta[0][7] = NULL; // tornin paikka tyhjä
			_lauta[3][7] = mt; // tornin uusi paikka
		}
	}

	else
	{
		// Kaikki muut siirrot

		Ruutu* alkuruutu = &siirto->getAlkuruutu();
		Ruutu* loppuruutu = &siirto->getLoppuruutu();

		// Ottaa siirron alkuruudussa olleen nappulan talteen 
		int x1 = alkuruutu->getSarake();
		int y1 = alkuruutu->getRivi();
		int x2 = loppuruutu->getSarake();
		int y2 = loppuruutu->getRivi();
		Nappula* nappula = _lauta[x1][y1];
		_lauta[x1][y1] = NULL;
		// Ja laittaa talteen otetun nappulan uuteen ruutuun
		_lauta[x2][y2] = nappula;

		if (_lauta[x2][y2]->getKoodi() == MK) {
			_onkoMustaKuningasLiikkunut = true;
		}
		if (_lauta[x2][y2]->getKoodi() == VK) {
			_onkoValkeaKuningasLiikkunut = true;
		}
		if (_lauta[x2][y2]->getKoodi() == VT && _lauta[0][0] == NULL) {
			_onkoValkeaDTliikkunut = true;
		}
		if (_lauta[x2][y2]->getKoodi() == VT && _lauta[0][7] == NULL) {
			_onkoValkeaKTliikkunut = true;
		}
		if (_lauta[x2][y2]->getKoodi() == MT && _lauta[7][0] == NULL) {
			_onkoMustaDTliikkunut = true;
		}
		if (_lauta[x2][y2]->getKoodi() == MK && _lauta[7][7] == NULL) {
			_onkoMustaKTliikkunut = true;
		}
		if (_lauta[x2][y2]->getKoodi() == MS && alkuruutu->getRivi() - loppuruutu->getRivi() == 2) {
			kaksoisaskelSarakkeella = 1;
		}
		if (_lauta[x2][y2]->getKoodi() == VS && loppuruutu->getRivi() - alkuruutu->getRivi() == 2) {
			kaksoisaskelSarakkeella = 1;
		}

		// Ohestalyönti on tyhjään ruutuun. Vieressä oleva (sotilas) poistetaan.
		if (kaksoisaskelSarakkeella != -1) {
			
			// Valkoinen
			if (_siirtovuoro == 0) {
				if (_lauta[x2][y2]->getKoodi() == VS
					&& _lauta[x2][y2 - 1]->getKoodi() == MS)
				{
					_lauta[x2][y2 - 1] = NULL; // Valkoinen söi mustan
				}
			}

			// Musta
			else if (_siirtovuoro == 1) {
				if (_lauta[x2][y2]->getKoodi() == MS
					&& _lauta[x2][y2 + 1]->getKoodi() == VS)
				{
					_lauta[x2][y2 + 1] = NULL; // Musta söi valkoisen
				}
			}
		}

		//// Katsotaan jos nappula on sotilas ja rivi on päätyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittymän laittama nappula


		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l�htenyt nappula

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille väreille)

		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille väreille ja molemmille torneille)

		// päivitetään _siirtovuoro
		if (getSiirtovuoro() == 0) setSiirtovuoro(1);
		else setSiirtovuoro(0);
	}

}



int Asema::getSiirtovuoro() 
{
	return 0;
}


void Asema::setSiirtovuoro(int vuoro) 
{
	
}


bool Asema::getOnkoValkeaKuningasLiikkunut() 
{
	return false;
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{
	return false;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	return false;
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return false;
}


bool Asema::getOnkoMustaDTliikkunut() 
{
	return false;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return false;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
Lähetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyvä että kunigas g1 tai b1/c1
Loppupelissä vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla estämässä vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitkiä linjoja daami, torni ja lähetti
*/
double Asema::evaluoi() 
{
	return 0;

	//kertoimet asetettu sen takia että niiden avulla asioiden painoarvoa voidaan säätää helposti yhdestä paikasta
	
	//1. Nappuloiden arvo
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	// 4. Arvosta linjoja
	
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	return 0;
	
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	return 0;
	// Jos upseereita 3 tai vähemmän on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami jäljellä
	
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	

}


double Asema::nappuloitaKeskella(int vari) 
{
	return 0;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa
	
	//valkeille ydinkeskusta

	
	
	//valkeille laitakeskusta
	


	//mustille ydinkeskusta
	
	//mustille laitakeskusta
	
}


double Asema::linjat(int vari) 
{
	return 0;
	
	//valkoiset
	
	//mustat
	
}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lisäsin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	
	// Rekursion kantatapaus 1: peli on loppu
	
	// Rekursion kantatapaus 2: katkaisusyvyydessä
	
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{

	return false;
}

void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) 
{ 
	
}

void Asema::annaLinnoitusSiirrot(std::list<Siirto>& lista, int vari)
{
	if (vari == 0)
	{
		// Lyhyt
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaKTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(0, 4), !vari) && this->onkoRuutuUhattu(&Ruutu(0, 5), !vari) && this->onkoRuutuUhattu(&Ruutu(0, 6), !vari)
			&& this->_lauta[0][5] == NULL && this->_lauta[6][0] == NULL)
		{
			lista.push_back(Siirto(true, false));
		}
		// Pitkä
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(0, 4), !vari) && this->onkoRuutuUhattu(&Ruutu(0, 3), !vari) && this->onkoRuutuUhattu(&Ruutu(0, 3), !vari)
			&& this->_lauta[0][3] == NULL && this->_lauta[2][0] == NULL)
		{
			lista.push_back(Siirto(false, true));
		}
	}
}

void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) 
{
	int vari = this->getSiirtovuoro();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			// Ei kysele tyhjiltä ruuduilta nappulan nimeä
			if (this->_lauta[i][j] == NULL) {
				continue;
			}
			if (this->_lauta[i][j]->getVari() != vari) {
				continue;
			}
			this->_lauta[i][j]->annaSiirrot(lista, &Ruutu(i, j), this, vari); // Myöhäinen sidonta
		}
	}
	this->annaLinnoitusSiirrot(lista, vari);
	this->huolehdiKuninkaanShakeista(lista, vari);
}
