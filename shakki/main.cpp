#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"

using namespace std;

enum
{
	a, b, c, d, e, f, g, h
};

int main()
{
	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	std::list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();

	Siirto siirto;
	string nappulatyyppi, alkuasema, loppuasema;
	bool onTorni = false;
	bool lyhytLinna = false;
	bool pitkaLinna = false;
	char kirjaimet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

	string input;
	cout << "Anna siirto: ";
	cin >> input;

	if (input.find('K') != std::string::npos)
		nappulatyyppi = "Kuningas";
	else if (input.find('D') != std::string::npos)
		nappulatyyppi = "Daami";
	else if (input.find('L') != std::string::npos)
		nappulatyyppi = "Lähetti";
	else if (input.find('R') != std::string::npos)
		nappulatyyppi = "Ratsu";
	else if (input.find('T') != std::string::npos)
	{
		nappulatyyppi = "Torni";
		onTorni = true;
	}
	else
		cout << "Virheellinen siirto. Anna siirto muodossa Rg1-f3" << endl;

	if (onTorni && alkuasema.substr(1, 2) == "O" && alkuasema.substr(3, 4) == "O")
	{
		// Lyhyt linna
		lyhytLinna = true;
		Siirto siirto(lyhytLinna, pitkaLinna);
	}
	else if (onTorni && alkuasema.substr(0, 1) == "O" && alkuasema.substr(3, 4) == "O" && alkuasema.substr(5, 6) == "O")
	{
		// Pitkä linna
		pitkaLinna = true;
		Siirto siirto(lyhytLinna, pitkaLinna);
	}
	else
	{
		alkuasema = input.substr(1, 2);
		loppuasema = input.substr(4, 5);

		int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		for (int i = 0; i < sizeof(kirjaimet); i++) {
			char c = alkuasema[0];
			if (c == kirjaimet[i])
				x1 = i;
		}
		y1 = std::stoi(alkuasema.substr(1, 2));
		cout << y1 << endl;

		for (int i = 0; i < sizeof(kirjaimet); i++) {
			char c = loppuasema[0];
			if (c == kirjaimet[i])
				x2 = i;
		}
		y2 = std::stoi(loppuasema.substr(1, 2));

		cout << "Alkuasema - X1: " << x1 << " Y1: " << y1 << endl;
		cout << "Loppuasema - X2: " << x2 << " Y2: " << y2 << endl;
	}

	/*
	while (lopetus != 0) {
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		if (lista.size() == 0) {
			lopetus = 0;
			std::wcout << "Peli loppui";
			continue;
		}
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			MinMaxPaluu paluu;
			if (koneenVari == 0) {
				paluu = asema.maxi(3);
			}
			else {
				paluu = asema.mini(3);
			}
			siirto = paluu._parasSiirto;
		}
		else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
		}
		asema.paivitaAsema(&siirto);
	}
	*/
	
	return 0;
}
