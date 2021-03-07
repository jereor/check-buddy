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

int main()
{
	std::wcout << "HeippariShakki\n";
	std::wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema; 
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->kysyVastustajanVari());
	std::list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();

	while (lopetus != 0) {
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		std::wcout << "\n";
		
		std::wcout << "Generoidaan siirtoja..." << endl;
		// Uusi kierros, uudet siirrot
		asema.annaLaillisetSiirrot(lista);
		std::wcout << "Siirrot generoitu." << endl;
		
		// Jos siirtolista on tyhjä, peli on päättynyt.
		if (lista.size() == 0) {
			lopetus = 0;
			std::wcout << "\nPeli loppui";
			continue;
		}

		// Muuten, jatketaan laskemaan paras siirto
		Siirto siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
		if (asema.getSiirtovuoro() == koneenVari) {
			wcout << "Lasketaan paras siirto" << endl;
			MinMaxPaluu paluu;
			if (koneenVari == 0) {
				paluu = asema.maxi(4);
			}
			else {
				paluu = asema.mini(4);
			}
			siirto = paluu._parasSiirto;
		}
		else {
			siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
		}
		asema.paivitaAsema(&siirto);
	}
	
	return 0;
}
