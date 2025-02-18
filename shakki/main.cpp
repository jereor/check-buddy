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

	while (lopetus != 0)
	{
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";

		asema.annaLaillisetSiirrot(lista);

		if (lista.size() == 0) {
			lopetus = 0;
			wcout << "\nPeli loppui";
			continue;
		}

		siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
		asema.paivitaAsema(&siirto);
	}

	while (lopetus != 0) {
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";
		// Tarkasta onko peli loppu?

		asema.annaLaillisetSiirrot(lista);
		
		if (lista.size() == 0) {
			lopetus = 0;
			std::wcout << "\nPeli loppui";
			continue;
		}

		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
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
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
		}
		Kayttoliittyma::getInstance()->annaVastustajanSiirto();
		asema.paivitaAsema(&siirto);
	}
	
	return 0;
}
