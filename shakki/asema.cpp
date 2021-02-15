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

	_lauta[0][0] = vt; // Val. Torni
	_lauta[0][1] = vr; // Val. Ratsu
	_lauta[0][2] = vl; // Val. Lähetti
	_lauta[0][3] = vk; // Val. Kuningas
	_lauta[0][4] = vd; // Val. Daami
	_lauta[0][5] = vl; // Val. Lähetti
	_lauta[0][6] = vr; // Val. Ratsu
	_lauta[0][7] = vt; // Val. Torni
	_lauta[1][0] = vs; // Val. Sotilas
	_lauta[1][1] = vs; // Val. Sotilas
	_lauta[1][2] = vs; // Val. Sotilas
	_lauta[1][3] = vs; // Val. Sotilas
	_lauta[1][4] = vs; // Val. Sotilas
	_lauta[1][5] = vs; // Val. Sotilas
	_lauta[1][6] = vs; // Val. Sotilas
	_lauta[1][7] = vs; // Val. Sotilas

	_lauta[7][0] = mt; // Musta Torni
	_lauta[7][1] = mr; // Musta Ratsu
	_lauta[7][2] = ml; // Musta Lähetti
	_lauta[7][3] = mk; // Musta Kuningas
	_lauta[7][4] = md; // Musta Daami
	_lauta[7][5] = ml; // Musta Lähetti
	_lauta[7][6] = mr; // Musta Ratsu
	_lauta[7][7] = mt; // Musta Torni
	_lauta[6][0] = ms; // Musta Sotilas
	_lauta[6][1] = ms; // Musta Sotilas
	_lauta[6][2] = ms; // Musta Sotilas
	_lauta[6][3] = ms; // Musta Sotilas
	_lauta[6][4] = ms; // Musta Sotilas
	_lauta[6][5] = ms; // Musta Sotilas
	_lauta[6][6] = ms; // Musta Sotilas
	_lauta[6][7] = ms; // Musta Sotilas
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
		Nappula* nappula = _lauta[x1][y1]; // Voi olla että ei saa olla pointteri!!
		_lauta[x1][y1] = NULL;
		// Ja laittaa talteen otetun nappulan uuteen ruutuun
		_lauta[x2][y2] = nappula;

		if (nappula->getKoodi() == MK) {
			_onkoMustaKuningasLiikkunut = true;
		}
		if (nappula->getKoodi() == VK) {
			_onkoValkeaKuningasLiikkunut = true;
		}
		if (nappula->getKoodi() == VT && _lauta[0][0] == NULL) {
			_onkoValkeaDTliikkunut = true;
		}
		if (nappula->getKoodi() == VT && _lauta[0][7] == NULL) {
			_onkoValkeaKTliikkunut = true;
		}
		if (nappula->getKoodi() == MT && _lauta[7][0] == NULL) {
			_onkoMustaDTliikkunut = true;
		}
		if (nappula->getKoodi() == MT && _lauta[7][7] == NULL) {
			_onkoMustaKTliikkunut = true;
		}
		if (nappula->getKoodi() == MS && alkuruutu->getRivi() - loppuruutu->getRivi() == 2) {
			kaksoisaskelSarakkeella = loppuruutu->getSarake();
		}
		if (nappula->getKoodi() == VS && loppuruutu->getRivi() - alkuruutu->getRivi() == 2) {
			kaksoisaskelSarakkeella = loppuruutu->getSarake();
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

		if ((nappula->getKoodi() == VS || nappula->getKoodi() == MS) 
			&& (loppuruutu->getRivi() == 0 || loppuruutu->getRivi() == 7))
		{
			int korotus;
			do {
				wcout << "Miksi korotetaan? (1 = Daami, 2 = Torni, 3 = Lähetti, 4 = Ratsu)" << endl;
				wcin >> korotus;

				switch (korotus)
				{
				case 1:
					if (y2 == 7)
						_lauta[x2][y2] = vd;
					else if (y2 == 0)
						_lauta[x2][y2] = md;
					break;

				case 2:
					if (y2 == 7)
						_lauta[x2][y2] = vt;
					else if (y2 == 0)
						_lauta[x2][y2] = mt;
					break;
				
				case 3:
					if (y2 == 7)
						_lauta[x2][y2] = vl;
					else if (y2 == 0)
						_lauta[x2][y2] = ml;
					break;

				case 4:
					if (y2 == 7)
						_lauta[x2][y2] = vr;
					else if (y2 == 0)
						_lauta[x2][y2] = mr;
					break;
				}
				
			} while (korotus > 1 && korotus < 4);
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
	return this->_siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro) 
{
	this->_siirtovuoro = vuoro;
}


bool Asema::getOnkoValkeaKuningasLiikkunut() 
{
	return this->_onkoValkeaKuningasLiikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{
	return this->_onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	return this->_onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return this->_onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut() 
{
	return this->_onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return this->_onkoMustaKTliikkunut;
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
	//kertoimet asetettu sen takia että niiden avulla asioiden painoarvoa voidaan säätää helposti yhdestä paikasta
	
	//1. Nappuloiden arvo
	double nappuloidenArvo = laskeNappuloidenArvo(this->_siirtovuoro);
	
	//2. Kuningas turvassa

	
	//3. Arvosta keskustaa

	
	// 4. Arvosta linjoja
	
	return nappuloidenArvo;
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	double vArvo = 0;
	double mArvo = 0;
	
	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {

			int koodi = _lauta[x][y]->getKoodi();

			switch (koodi)
			{
			case 0: // Valkoinen torni
				vArvo += 5;
			case 1: // Valkoinen ratsu
				vArvo += 3;
			case 2: // Valkoinen lähetti
				vArvo += 3.25;
			case 3: // Valkoinen daami
				vArvo += 9;
			case 4: // Valkoinen kuningas
				vArvo += 0;
			case 5: // Valkoinen sotilas
				vArvo += 1;
			case 6: // Musta torni
				mArvo += 5;
			case 7: // Musta ratsu
				mArvo += 3;
			case 8: // Musta lähetti
				mArvo += 3.25;
			case 9: // Musta daami
				mArvo += 9;
			case 10: // Musta kuningas
				mArvo += 0;
			case 11: // Musta sotilas
				mArvo += 1;
			}
		}
	}

	if (vari == 0)
		return vArvo - mArvo;
	if (vari == 1)
		return mArvo - vArvo;

	return 0;
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	return 0;
	// Jos upseereita 3 tai vähemmän on loppupeli
	// mutta jos daami laudalla on loppupeli vasta kun kuin vain daami jäljellä
	
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


//MinMaxPaluu Asema::maxi(int syvyys) 
//{
//	MinMaxPaluu paluu;
//	double pisteet;
//
//	if (syvyys == 0)
//		return minimax(syvyys);
//	int max = -oo;
//
//	for (all moves) {
//		pisteet = mini(syvyys - 1, seuraaja);
//		if (pisteet > max)
//			max = score;
//	}
//
//	return paluu;
//}


//MinMaxPaluu Asema::mini(int syvyys) 
//{
//	MinMaxPaluu paluu;
//	double pisteet;
//
//	if (syvyys == 0)
//		return minimax(syvyys);
//	int min = +oo;
//
//	for (all moves) {
//		pisteet = maxi(syvyys - 1);
//		if (pisteet < min)
//			min = score;
//	}
//	return paluu;
//}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	std::list<Siirto> vastustajaSiirrotLista;
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			if (this->_lauta[i][j] == NULL)
				continue;
			if (this->_lauta[i][j]->getVari() == vastustajanVari)
				this->_lauta[i][j]->annaSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), this, vastustajanVari);
		}
	}

	// Käydään vastustajaSiirtoLista läpi ja jos sieltä löytyy tarkasteltava ruutu niin tiedetään sen olevan uhattu
	bool ruutuOK = true;
	for (auto siirto : vastustajaSiirrotLista)
	{
		if (ruutu->getSarake() == siirto.getLoppuruutu().getSarake() && ruutu->getRivi() == siirto.getLoppuruutu().getRivi()) {
			ruutuOK = false;
			break;
		}
	}

	return ruutuOK;
}

void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) 
{ 
	// paivitaAsema(listan alkio); TESTATAAN SIIRTO
	// onkoRuutuUhattu(kuninkaan ruutu); KATSOTAAN ONKO KUNINGAS UHATTU
	// paivitaAsema(listan alkion vastakohta); PERUUTETAAN SIIRTO
}

void Asema::annaLinnoitusSiirrot(std::list<Siirto>& lista, int vari)
{
	// Linnoituksien huomioiminen
	// 1. Kuningas ei saa olla liikkunut
	// 2. Torni ei saa olla liikkunut
	// 3. Kuningas ei saa olla shakattuna
	// 4. Ruutujen pitää olla tyhjät
	// 5. Ruudut eivät saa olla uhattuja

	// VALKOINEN
	if (vari == 0)
	{
		// Lyhyt
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaKTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 0), !vari) && this->onkoRuutuUhattu(&Ruutu(5, 0), !vari) && this->onkoRuutuUhattu(&Ruutu(6, 0), !vari)
			&& this->_lauta[5][0] == NULL && this->_lauta[6][0] == NULL)
		{
			lista.push_back(Siirto(true, false));
		}
		// Pitkä
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 0), !vari) && this->onkoRuutuUhattu(&Ruutu(3, 0), !vari) && this->onkoRuutuUhattu(&Ruutu(2, 0), !vari)
			&& this->_lauta[3][0] == NULL && this->_lauta[2][0] == NULL)
		{
			lista.push_back(Siirto(false, true));
		}
	}

	// MUSTA
	if (vari == 1)
	{
		// Lyhyt
		if (!this->getOnkoMustaKuningasLiikkunut() && !this->getOnkoMustaKTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 7), !vari) && this->onkoRuutuUhattu(&Ruutu(5, 7), !vari) && this->onkoRuutuUhattu(&Ruutu(6, 7), !vari)
			&& this->_lauta[5][7] == NULL && this->_lauta[6][7] == NULL)
		{
			lista.push_back(Siirto(true, false));
		}
		// Pitkä
		if (!this->getOnkoValkeaKuningasLiikkunut() && !this->getOnkoValkeaDTliikkunut()
			&& this->onkoRuutuUhattu(&Ruutu(4, 7), !vari) && this->onkoRuutuUhattu(&Ruutu(3, 7), !vari) && this->onkoRuutuUhattu(&Ruutu(2, 7), !vari)
			&& this->_lauta[3][7] == NULL && this->_lauta[2][7] == NULL)
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