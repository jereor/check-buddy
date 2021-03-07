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

void Nappula::lisaaListalle(int alkuY, int alkuX, int loppuY, int loppuX, list<Siirto>& lista) {
	int alkuruutuX = alkuX;
	int alkuruutuY = alkuY;
	int loppuruutuX = loppuX;
	int loppuruutuY = loppuY;

	Ruutu alkuruutu(alkuruutuY, alkuruutuX);
	Ruutu loppuruutu(loppuruutuY, loppuruutuX);

	Siirto siirto(alkuruutu, loppuruutu);
	lista.push_back(siirto);

	delete[] &alkuruutuX;
	delete[] &alkuruutuY;
	delete[] &loppuruutuX;
	delete[] &loppuruutuY;
	delete[] &alkuruutu;
	delete[] &loppuruutu;
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int alkuruutuY = ruutu->getRivi();
	int alkuruutuX = ruutu->getSarake();

	int lahtovari = asema->_lauta[alkuruutuY][alkuruutuX]->getVari();
	int loppuvari;

	// Tornin liike ylös
	for (int i = 1; i < 8; i++) {
		if (alkuruutuY + i < 8) {
			// Siirto on OK, jos yläpuolella oleva ruutu on tyhjä
			if (asema->_lauta[alkuruutuY + i][alkuruutuX] == NULL) {
				wcout << "Ylös: " << (alkuruutuY + i) << endl;
				lista.push_back(Siirto(*ruutu, Ruutu(alkuruutuY + 1, alkuruutuX)));
			}
			else
			{
				// Siirto on OK, jos yläpuolella olevassa ruudussa on vastustajan nappula
				loppuvari = asema->_lauta[alkuruutuY + 1][alkuruutuX]->getVari();
				if (lahtovari != loppuvari) {
					wcout << "Ylös: " << (alkuruutuY + i) << endl;
					lista.push_back(Siirto(*ruutu, Ruutu(alkuruutuY + i, alkuruutuX)));
					break;
				}
				else // Ruudussa on oma nappula, joten lopetetaan ylös laskenta
				{
					break;
				}
			}
		}
	}

	// Tornin liike alas
	for (int i = 1; i < 8; i++) {
		if (alkuruutuY - i >= 0) {
			// Siirto on OK, jos yläpuolella oleva ruutu on tyhjä
			if (asema->_lauta[alkuruutuY - i][alkuruutuX] == NULL) {
				wcout << "Alas: " << (alkuruutuY - i) << endl;
				lista.push_back(Siirto(*ruutu, Ruutu(alkuruutuY - i, alkuruutuX)));
			}
			else
			{
				// Siirto on OK, jos yläpuolella olevassa ruudussa on vastustajan nappula
				loppuvari = asema->_lauta[alkuruutuY - i][alkuruutuX]->getVari();
				if (lahtovari != loppuvari) {
					wcout << "Alas: " << (alkuruutuY - i) << endl;
					lista.push_back(Siirto(*ruutu, Ruutu(alkuruutuY - i, alkuruutuX)));
					break;
				}
				else // Ruudussa on oma nappula, joten lopetetaan alas laskenta
				{
					break;
				}
			}
		}
	}

	// Tornin liike oikealle
	for (int i = 1; i < 8; i++) {
		if (alkuruutuX + i < 8) {
			// Siirto on OK, jos yläpuolella oleva ruutu on tyhjä
			if (asema->_lauta[alkuruutuY][alkuruutuX + i] == NULL) {
				wcout << "Oikealle: " << (alkuruutuX + i) << endl;
				lista.push_back(Siirto(*ruutu, Ruutu(alkuruutuY, alkuruutuX + i)));
			}
			else
			{
				// Siirto on OK, jos yläpuolella olevassa ruudussa on vastustajan nappula
				loppuvari = asema->_lauta[alkuruutuY][alkuruutuX + i]->getVari();
				if (lahtovari != loppuvari) {
					wcout << "Oikealle: " << (alkuruutuX + i) << endl;
					lista.push_back(Siirto(*ruutu, Ruutu(alkuruutuY, alkuruutuX + i)));
					break;
				}
				else // Ruudussa on oma nappula, joten lopetetaan oikealle laskenta
				{
					break;
				}
			}
		}
	}

	// Tornin liike vasemmalle
	for (int i = 1; i < 8; i++) {
		if (alkuruutuX - i > 0) {
			// Siirto on OK, jos yläpuolella oleva ruutu on tyhjä
			if (asema->_lauta[alkuruutuY][alkuruutuX - i] == NULL) {
				wcout << "Vasemmalle: " << (alkuruutuX - i) << endl;
				lista.push_back(Siirto(*ruutu, Ruutu(alkuruutuY, alkuruutuX - i)));
			}
			else
			{
				// Siirto on OK, jos yläpuolella olevassa ruudussa on vastustajan nappula
				loppuvari = asema->_lauta[alkuruutuY][alkuruutuX - i]->getVari();
				if (lahtovari != loppuvari) {
					wcout << "Vasemmalle: " << (alkuruutuX - i) << endl;
					lista.push_back(Siirto(*ruutu, Ruutu(alkuruutuY, alkuruutuX - i)));
					break;
				}
				else // Ruudussa on oma nappula, joten lopetetaan vasemmalle laskenta
				{
					break;
				}
			}
		}
	}

	delete[] & alkuruutuX;
	delete[] & alkuruutuY;
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();
	Ruutu alkuRuutu = Ruutu(lahtoruutuY, lahtoruutuX);
	Ruutu loppuRuutu;
	Siirto siirto;

	bool laillinenSiirto;

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
		int loppuruutuX = lahtoruutuX + liike[0];
		int loppuruutuY = lahtoruutuY + liike[1];
		loppuRuutu = Ruutu(loppuruutuY, loppuruutuX);
		siirto = Siirto(alkuRuutu, loppuRuutu);

		// Katsotaan meneekö ratsu yli laudan
		if (loppuruutuY > 7 || loppuruutuY < 0 || loppuruutuX > 7 || loppuruutuX < 0)
		{
			laillinenSiirto = false;
		}
		// Katsotaan onko ruutu tyhjä
		if (laillinenSiirto == true && asema->_lauta[loppuruutuY][loppuruutuX] == NULL)
		{
			lista.push_back(siirto);
		}
	}
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int mahdolliset_suunnat[4][2] = { { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 } };

	// Tutkitaan lähetin kaikki neljä suuntaa
	for (int suunta = 0; suunta < 4; suunta++)
	{
		// Tutkitaan 1-7 ruutua tiettyyn suuntaan
		for (int matka = 1; matka <= 7; matka++)
		{
			int loppuruutuX = ruutu->getSarake() + matka * mahdolliset_suunnat[suunta][0];
			int loppuruutuY = ruutu->getRivi() + matka * mahdolliset_suunnat[suunta][1];

			// Tarkistetaan mennäänkö reunan yli, jolloin lopetettaisiin suunnan tutkiminen
			if (loppuruutuY > 7 || loppuruutuY < 0 || loppuruutuX > 7 || loppuruutuX < 0)
				break;

			// Jos ruudussa oma nappula, lopetetaan suunnan tutkiminen
			Nappula* nappula = asema->_lauta[loppuruutuY][loppuruutuX];
			if (nappula != NULL)
			{
				if (nappula->getVari() == vari)
					break;
				else
				{
					Ruutu alku(ruutu->getSarake(), ruutu->getRivi());
					Ruutu loppu(loppuruutuY, loppuruutuX);
					Siirto siirto(alku, loppu);
					lista.push_back(siirto);
					break;
				}
			}
			else
			{
				Ruutu alku(ruutu->getSarake(), ruutu->getRivi());
				Ruutu loppu(loppuruutuY, loppuruutuX);
				Siirto siirto(alku, loppu);
				lista.push_back(siirto);
			}
		}
	}
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	Torni::annaSiirrot(lista, ruutu, asema, vari);
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on että kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
	oman nappulan päälle ei voi mennä ja vastustajan nappulan voi syödä.

	Kaikki muu kuninkaaseen liittyvä tarkistus tehd��n eri paikassa*/
	
	int alkuruutuX = ruutu->getSarake();
	int alkuruutuY = ruutu->getRivi();

	if (vari == 0) {
		// Eteenpäin
		if (alkuruutuY + 1 <= 8) {
			if (asema->_lauta[alkuruutuY + 1][alkuruutuX] == NULL
				|| asema->_lauta[alkuruutuY + 1][alkuruutuX]->getVari() != vari)
				lisaaListalle(alkuruutuY, alkuruutuX, alkuruutuY + 1, alkuruutuX, lista);
		}

		// Oikealle
		if (alkuruutuX + 1 <= 8) {
			if (asema->_lauta[alkuruutuY][alkuruutuX + 1] == NULL
				|| asema->_lauta[alkuruutuY][alkuruutuX + 1]->getVari() != vari) {
				lisaaListalle(alkuruutuY, alkuruutuX, alkuruutuY, alkuruutuX + 1, lista);
			}
		}

		// Taakse
		if (alkuruutuY - 1 >= 0) {
			if (asema->_lauta[alkuruutuY - 1][alkuruutuX] == NULL
				|| asema->_lauta[alkuruutuY - 1][alkuruutuX]->getVari() != vari) {
				lisaaListalle(alkuruutuY, alkuruutuX, alkuruutuY - 1, alkuruutuX, lista);
			}
		}

		// Vasemmalle
		if (alkuruutuX - 1 >= 0) {
			if (asema->_lauta[alkuruutuY][alkuruutuX - 1] == NULL
				|| asema->_lauta[alkuruutuY][alkuruutuX - 1]->getVari() != vari) {
				lisaaListalle(alkuruutuY, alkuruutuX, alkuruutuY, alkuruutuX - 1, lista);
			}
		}

		// Ylös oikealle
		if (alkuruutuY + 1 <= 8) {
			if (alkuruutuX + 1 <= 8) {
				if (asema->_lauta[alkuruutuY + 1][alkuruutuX + 1] == NULL
					|| asema->_lauta[alkuruutuY + 1][alkuruutuX + 1]->getVari() != vari) {
					lisaaListalle(alkuruutuY, alkuruutuX, alkuruutuY + 1, alkuruutuX + 1, lista);
				}
			}
		}

		// Alas oikealle
		if (ruutu->getRivi() - 1 >= 0) {
			if (alkuruutuX + 1 <= 8) {
				if (asema->_lauta[alkuruutuY - 1][alkuruutuX + 1] == NULL
					|| asema->_lauta[alkuruutuY - 1][alkuruutuX + 1]->getVari() != vari) {
					lisaaListalle(alkuruutuY, alkuruutuX, alkuruutuY - 1, alkuruutuX + 1, lista);
				}
			}
		}

		// Alas vasemmalle
		if (alkuruutuY - 1 >= 0) {
			if (alkuruutuX - 1 >= 0) {
				if (asema->_lauta[alkuruutuY - 1][alkuruutuX - 1] == NULL
					|| asema->_lauta[alkuruutuY - 1][alkuruutuX - 1]->getVari() != vari) {
					lisaaListalle(alkuruutuY, alkuruutuX, alkuruutuY - 1, alkuruutuX - 1, lista);
				}
			}
		}

		// Ylös vasemmalle
		if (alkuruutuY + 1 <= 8) {
			if (alkuruutuX - 1 >= 0) {
				if (asema->_lauta[alkuruutuY + 1][alkuruutuX - 1] == NULL
					|| asema->_lauta[alkuruutuY + 1][alkuruutuX - 1]->getVari() != vari) {
					lisaaListalle(alkuruutuY, alkuruutuX, alkuruutuY + 1, alkuruutuX - 1, lista);
				}
			}
		}
	}
	
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int rivi = ruutu->getRivi();
	int sarake = ruutu->getSarake();

	// VALKOINEN
	if (vari == 0) {
		// Siirto suoraan eteenpäin
		if (rivi + 1 < 8) {
			if (rivi + 2 < 8)
				if (rivi == 1 && asema->_lauta[rivi + 2][sarake] == NULL) {
					lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi + 2)));
				}
			if (asema->_lauta[rivi + 1][sarake] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi + 1)));
			}
		}

		// Onko ohestalyönti mahdollista?
		// Jos on, millä sarakkeella kaksoisaskel on tapahtunut?
		if (asema->kaksoisaskelSarakkeella != -1)
		{
			if (rivi == 4)
				if (asema->_lauta[4][asema->kaksoisaskelSarakkeella] && asema->_lauta[5][asema->kaksoisaskelSarakkeella] == NULL)
					lista.push_back(Siirto(*ruutu, Ruutu(asema->kaksoisaskelSarakkeella, 5)));
		}
	}

	// MUSTA
	if (vari == 1) {
		// Siirto suoraan eteenpäin
		if (rivi - 1 >= 0) {
			if (rivi - 2 >= 0)
				if (rivi == 6 && asema->_lauta[rivi - 2][sarake] == NULL)
					lista.push_back(Siirto(*ruutu, Ruutu(rivi - 2, sarake)));
			if (asema->_lauta[rivi - 1][sarake] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake)));
			}
		}

		// Onko ohestalyönti mahdollista?
		// Jos on, millä sarakkeella kaksoisaskel on tapahtunut?
		if (asema->kaksoisaskelSarakkeella != -1)
		{
			if (rivi == 3)
				if (asema->_lauta[3][asema->kaksoisaskelSarakkeella] && asema->_lauta[2][asema->kaksoisaskelSarakkeella] == NULL)
					lista.push_back(Siirto(*ruutu, Ruutu(2, asema->kaksoisaskelSarakkeella)));
		}
	}
}



void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	wcout << "Lisätään sotilaan korotukset..." << endl;
	// Valkoisen korotus
	if (siirto->getLoppuruutu().getRivi() == 7)
	{
		Siirto daamiksi = *siirto;
		siirto->_miksikorotetaan = asema->vd;
		lista.push_back(daamiksi);

		Siirto torniksi = *siirto;
		torniksi._miksikorotetaan = asema->vt;
		lista.push_back(torniksi);

		Siirto lahetiksi = *siirto;
		lahetiksi._miksikorotetaan = asema->vl;
		lista.push_back(lahetiksi);

		Siirto ratsuksi = *siirto;
		ratsuksi._miksikorotetaan = asema->vr;
		lista.push_back(ratsuksi);
	}

	// Mustan korotus
	else if (siirto->getLoppuruutu().getRivi() == 0)
	{
		Siirto daamiksi = *siirto;
		siirto->_miksikorotetaan = asema->md;
		lista.push_back(daamiksi);

		Siirto torniksi = *siirto;
		torniksi._miksikorotetaan = asema->mt;
		lista.push_back(torniksi);

		Siirto lahetiksi = *siirto;
		lahetiksi._miksikorotetaan = asema->ml;
		lista.push_back(lahetiksi);

		Siirto ratsuksi = *siirto;
		ratsuksi._miksikorotetaan = asema->mr;
		lista.push_back(ratsuksi);
	}
}