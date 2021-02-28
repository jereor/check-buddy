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
	Ruutu lahtoruutu(alkuruutuX, alkuruutuY);
	Ruutu loppuruutu(loppuruutuX, loppuruutuY);
	Siirto siirto(lahtoruutu, loppuruutu);
	lista.push_back(siirto);
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtovari = asema->_lauta[lahtoruutuX][lahtoruutuY]->getVari();
	int loppuvari;

	// Tornin liike ylös

	for (int i = 1; i <= 8; i++) {
		if (lahtoruutuY + i <= 8) {
			// Siirto on OK, jos yläpuolella oleva ruutu on tyhjä
			if (asema->_lauta[lahtoruutuX][lahtoruutuY + i] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + i)));
			}
			else
			{
				// Siirto on OK, jos yläpuolella olevassa ruudussa on vastustajan nappula
				loppuvari = asema->_lauta[lahtoruutuX][lahtoruutuY + i]->getVari();
				if (lahtovari != loppuvari) {
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + i)));

					break;
				}
			}
		}
	}

	// Tornin liike alas
	for (int i = 8; i >= 0; i--) {
		if (lahtoruutuY - i >= 0) {
			// Siirto on OK, jos yläpuolella oleva ruutu on tyhjä
			if (asema->_lauta[lahtoruutuX][lahtoruutuY - i] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - i)));
			}
			else
			{
				// Siirto on OK, jos yläpuolella olevassa ruudussa on vastustajan nappula
				loppuvari = asema->_lauta[lahtoruutuX][lahtoruutuY - i]->getVari();
				if (lahtovari != loppuvari) {
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - i)));

					break;
				}
			}
		}
	}

	// Tornin liike oikealle
	for (int i = 1; i <= 8; i++) {
		if (lahtoruutuX + i <= 8) {
			// Siirto on OK, jos yläpuolella oleva ruutu on tyhjä
			if (asema->_lauta[lahtoruutuX + i][lahtoruutuY] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + i, lahtoruutuY)));
			}
			else
			{
				// Siirto on OK, jos yläpuolella olevassa ruudussa on vastustajan nappula
				loppuvari = asema->_lauta[lahtoruutuX + i][lahtoruutuY]->getVari();
				if (lahtovari != loppuvari) {
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + i, lahtoruutuY)));

					break;
				}
			}
		}
	}

	// Tornin liike vasemmalle
	for (int i = 8; i >= 0; i--) {
		if (lahtoruutuX - i >= 0) {
			// Siirto on OK, jos yläpuolella oleva ruutu on tyhjä
			if (asema->_lauta[lahtoruutuX - i][lahtoruutuY] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - i, lahtoruutuY)));
			}
			else
			{
				// Siirto on OK, jos yläpuolella olevassa ruudussa on vastustajan nappula
				loppuvari = asema->_lauta[lahtoruutuX - i][lahtoruutuY]->getVari();
				if (lahtovari != loppuvari) {
					lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - i, lahtoruutuY)));

					break;
				}
			}
		}
	}
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();
	Ruutu alkuRuutu = Ruutu(lahtoruutuX, lahtoruutuY);
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
		loppuRuutu = Ruutu(lahtoruutuX + liike[0], lahtoruutuY + liike[1]);
		siirto = Siirto(alkuRuutu, loppuRuutu);

		// wcout << alkuRuutu.getRivi() + liike[0] << " " << alkuRuutu.getSarake() + liike[1] << endl;

		// Katsotaan meneekö ratsu yli laudan
		if ((alkuRuutu.getRivi() + liike[0] > 7 || alkuRuutu.getRivi() + liike[0] < 0) || (alkuRuutu.getSarake() + liike[1] > 7 || alkuRuutu.getSarake() + liike[1] < 0))
		{
			laillinenSiirto = false;
		}
		// Katsotaan onko ruutu tyhjä
		if (laillinenSiirto == true)
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
			int uusi_x = ruutu->getSarake() + matka * mahdolliset_suunnat[suunta][0];
			int uusi_y = ruutu->getRivi() + matka * mahdolliset_suunnat[suunta][1];

			// Tarkistetaan mennäänkö reunan yli, jolloin lopetettaisiin suunnan tutkiminen
			if (uusi_x < 0 || uusi_x > 7 || uusi_y < 0 || uusi_y > 7)
				break;

			// Jos ruudussa oma nappula lopetetaan suunnan tutkiminen
			Nappula* nappula = asema->_lauta[uusi_y][uusi_x];
			if (nappula != NULL)
			{
				if (nappula->getVari() == vari)
					break;
				else
				{
					Ruutu alku(ruutu->getSarake(), ruutu->getRivi());
					Ruutu loppu(uusi_x, uusi_y);
					Siirto siirto(alku, loppu);
					lista.push_back(siirto);
					break;
				}
			}
			else
			{
				Ruutu alku(ruutu->getSarake(), ruutu->getRivi());
				Ruutu loppu(uusi_x, uusi_y);
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
	
	if (vari == 0) {
		// Eteenpäin
		if (ruutu->getRivi() + 1 < 8) {
			if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake()] == NULL
				|| asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake()]->getVari() != vari)
				lisaaListalle(ruutu->getRivi(), ruutu->getSarake(), ruutu->getRivi() + 1, ruutu->getSarake(), lista);
		}

		// Oikealle
		if (ruutu->getSarake() + 1 < 8) {
			if (asema->_lauta[ruutu->getRivi()][ruutu->getSarake() + 1] == NULL
				|| asema->_lauta[ruutu->getRivi()][ruutu->getSarake() + 1]->getVari() != vari) {
				lisaaListalle(ruutu->getRivi(), ruutu->getSarake(), ruutu->getRivi(), ruutu->getSarake() + 1, lista);
			}
		}

		// Taakse
		if (ruutu->getRivi() - 1 < 8) {
			if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake()] == NULL
				|| asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake()]->getVari() != vari) {
				lisaaListalle(ruutu->getRivi(), ruutu->getSarake(), ruutu->getRivi() - 1, ruutu->getSarake(), lista);
			}
		}

		// Vasemmalle
		if (ruutu->getSarake() - 1 < 8) {
			if (asema->_lauta[ruutu->getRivi()][ruutu->getSarake() - 1] == NULL
				|| asema->_lauta[ruutu->getRivi()][ruutu->getSarake() - 1]->getVari() != vari) {
				lisaaListalle(ruutu->getRivi(), ruutu->getSarake(), ruutu->getRivi(), ruutu->getSarake() - 1, lista);
			}
		}

		// Ylös oikealle
		if (ruutu->getRivi() + 1 < 8) {
			if (ruutu->getSarake() + 1 < 8) {
				if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + 1] == NULL
					|| asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() + 1]->getVari() != vari) {
					lisaaListalle(ruutu->getRivi(), ruutu->getSarake(), ruutu->getRivi() + 1, ruutu->getSarake() + 1, lista);
				}
			}
		}

		// Alas oikealle
		if (ruutu->getRivi() - 1 >= 0) {
			if (ruutu->getSarake() + 1 < 8) {
				if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() + 1] == NULL
					|| asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() + 1]->getVari() != vari) {
					lisaaListalle(ruutu->getRivi(), ruutu->getSarake(), ruutu->getRivi() - 1, ruutu->getSarake() + 1, lista);
				}
			}
		}

		// Alas vasemmalle
		if (ruutu->getRivi() - 1 >= 0) {
			if (ruutu->getSarake() - 1 >= 0) {
				if (asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() - 1] == NULL
					|| asema->_lauta[ruutu->getRivi() - 1][ruutu->getSarake() - 1]->getVari() != vari) {
					lisaaListalle(ruutu->getRivi(), ruutu->getSarake(), ruutu->getRivi() - 1, ruutu->getSarake() - 1, lista);
				}
			}
		}

		// Ylös vasemmalle
		if (ruutu->getRivi() + 1 < 8) {
			if (ruutu->getSarake() - 1 >= 0) {
				if (asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() - 1] == NULL
					|| asema->_lauta[ruutu->getRivi() + 1][ruutu->getSarake() - 1]->getVari() != vari) {
					lisaaListalle(ruutu->getRivi(), ruutu->getSarake(), ruutu->getRivi() + 1, ruutu->getSarake() - 1, lista);
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
					lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi - 2)));
			if (asema->_lauta[rivi - 1][sarake] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(sarake, rivi - 1)));
			}
		}

		// Onko ohestalyönti mahdollista?
		// Jos on, millä sarakkeella kaksoisaskel on tapahtunut?
		if (asema->kaksoisaskelSarakkeella != -1)
		{
			if (rivi == 3)
				if (asema->_lauta[3][asema->kaksoisaskelSarakkeella] && asema->_lauta[2][asema->kaksoisaskelSarakkeella] == NULL)
					lista.push_back(Siirto(*ruutu, Ruutu(asema->kaksoisaskelSarakkeella, 2)));
		}
	}
}



void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
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