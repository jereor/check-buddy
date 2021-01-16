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
		nappulatyyppi = "Torni";
	else
		cout << "Virheellinen siirto. Anna siirto muodossa Rg1-f3" << endl;

	alkuasema = input.substr(1, 2);
	loppuasema = input.substr(4, 5);

	cout << "Nappulatyyppi: " << nappulatyyppi << "\nNappula :" << alkuasema << " " << loppuasema << endl;

	int x1, y1, x2, y2;
	if (alkuasema.substr(0, 1) == "a") x1 = a;
	if (alkuasema.substr(0, 1) == "b") x1 = b;
	if (alkuasema.substr(0, 1) == "c") x1 = c;
	if (alkuasema.substr(0, 1) == "d") x1 = d;
	if (alkuasema.substr(0, 1) == "e") x1 = e;
	if (alkuasema.substr(0, 1) == "f") x1 = f;
	if (alkuasema.substr(0, 1) == "g") x1 = g;
	if (alkuasema.substr(0, 1) == "h") x1 = h;

	if (loppuasema.substr(0, 1) == "a") x2 = a;
	if (loppuasema.substr(0, 1) == "b") x2 = b;
	if (loppuasema.substr(0, 1) == "c") x2 = c;
	if (loppuasema.substr(0, 1) == "d") x2 = d;
	if (loppuasema.substr(0, 1) == "e") x2 = e;
	if (loppuasema.substr(0, 1) == "f") x2 = f;
	if (loppuasema.substr(0, 1) == "g") x2 = g;
	if (loppuasema.substr(0, 1) == "h") x2 = h;

	y1 = std::stoi(alkuasema.substr(1, 2));
	y2 = std::stoi(loppuasema.substr(1, 2));
	cout << "Alkuasema - X1: " << x1 << " Y1: " << y1 << endl;
	cout << "Loppuasema - X2: " << x2 << " Y2: " << y2 << endl;

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
