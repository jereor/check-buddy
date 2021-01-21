#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}


void Kayttoliittyma::piirraLauta()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	char kirjaimet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			if (j == 0 && i == 7) {
				wcout << i+1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			if (j == 0 && i == 6) {
				wcout << i+1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
			}
			if (j == 0 && i == 5) {
				wcout << i+1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			if (j == 0 && i == 4) {
				wcout << i+1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
			}
			if (j == 0 && i == 3) {
				wcout << i+1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			if (j == 0 && i == 2) {
				wcout << i+1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
			}
			if (j == 0 && i == 1) {
				wcout << i+1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			if (j == 0 && i == 0) {
				wcout << i+1;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
			}

			if (i % 2 != 0) {
				if (j % 2 == 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
						BACKGROUND_GREEN | BACKGROUND_BLUE);
				} else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
			}
			else {
				if (j % 2 != 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
							BACKGROUND_GREEN | BACKGROUND_BLUE);
				} else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
			}

			if (_asema->_lauta[i][j] != NULL) {
				if (i == 1) // Mustat sotilaat
					wcout << " " << _asema->_lauta[i][j]->getUnicode();
				else
					wcout << " " << _asema->_lauta[i][j]->getUnicode() << " ";
			}	
			else
				wcout << "   ";
		}
		wcout << endl;

	}
	wcout << " ";
	for (int k = 0; k < 8; k++)
	{
		wcout << " " << kirjaimet[k] << " ";
	}
	wcout << endl;
}


/*
	Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	char kirjaimet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	wstring nappulatyyppi, alkuasema, loppuasema;

	_setmode(_fileno(stdout), _O_U16TEXT);

	while (true)
	{
		wstring input;
		wcout << "\nAnna siirto: ";
		wcin >> input;

		if (input == L"0")
		{
			break;
		}

		// Lyhyt ja pitkä linna
		if (input == L"0-0" || input == L"0-0-0")
		{
			if (input == L"0-0")
				return Siirto(true, false);
			else if (input == L"0-0-0")
				return Siirto(false, true);
		}

		if (input.find('K') != std::string::npos)
			nappulatyyppi = L"Kuningas";
		else if (input.find('D') != std::string::npos)
			nappulatyyppi = L"Daami";
		else if (input.find('L') != std::string::npos)
			nappulatyyppi = L"Lähetti";
		else if (input.find('R') != std::string::npos)
			nappulatyyppi = L"Ratsu";
		else if (input.find('T') != std::string::npos)
			nappulatyyppi = L"Torni";
		else
			wcout << "Virheellinen siirto. Anna siirto muodossa Rg1-f3" << endl;

		alkuasema = input.substr(1, 2);
		loppuasema = input.substr(4, 5);

		wcout << "Nappulatyyppi: " << nappulatyyppi << endl << "Nappula :" << alkuasema << " " << loppuasema << endl;

		int x1, y1, x2, y2;

		char c = alkuasema[0];
		for (int i = 0; i < sizeof(kirjaimet); i++) {
			if (c == kirjaimet[i])
				x1 = i;
		}
		try
		{
			y1 = std::stoi(alkuasema.substr(1, 2));
		}
		catch (...) {
			wcout << "\nFail!";
		}

		c = loppuasema[0];
		for (int i = 0; i < sizeof(kirjaimet); i++) {
			if (c == kirjaimet[i])
				x2 = i;
		}
		try
		{
			y2 = std::stoi(loppuasema.substr(1, 2));
		}
		catch (...) {
			wcout << "\nFail!";
		}

		wcout << x1 << " " << y1 << " " <<  x2 << " " << y2 << endl << endl;

		Ruutu alkuruutu(x1, y1);
		Ruutu loppuruutu(x2, y2);

		Siirto siirto(alkuruutu, loppuruutu);

		return siirto;
	}



}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
