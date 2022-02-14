// Implementacja klasy opakowujacej algorytm RC6
#include "aes_defs.h"

// Stale okreslajace tryb pracy
const unsigned char TRYB_ECB = 1;
const unsigned char TRYB_CBC = 2;
const unsigned char TRYB_CFB = 3;
const unsigned char TRYB_OFB = 4;

ref class RC6algo
{
public:
	// Konstruktor domyslny
	RC6algo();
	// Konstruktory z parametrami
	RC6algo(System::String^ s_klucz, int Dl_klucza);
	RC6algo(System::String^ s_klucz, int Dl_klucza, int typ_szyfrowania);

	// Szyfrowanie i deszyfrowanie
	void Szyfruj(System::String^ plik, System::String^ plikWyj);
	bool Deszyfruj(System::String^ plik, System::String^ plikWyj);

private:
	// Zmienne prywatne klasy:
	// klucz, klucz sesyjny, wektor poczatkowy oraz tryb szyfrowania
	array<System::Byte^>^ klucz;
	array<System::Byte^>^ sesyjny;
	array<System::Byte^>^ IV;
	unsigned char TypSzyfrowania; 
	unsigned char DlugoscKlucza;

	// Metody generujace dane
	void GenerujKluczSesyjny(void);
	void GenerujIV(void);

	// Metody obs³ugi nag³ówka
	void ZapiszNaglowek(System::String^ plikWyj);
	void WczytajNaglowek(System::String^ plik);

	// Metody prywatne szyfrujace
	void SzyfrujECB_CBC(System::String^ plik, System::String^ plikWyj);
	bool DeszyfrujECB_CBC(System::String^ plik, System::String^ plikWyj);
	void SzyfrujCFB_OFB(System::String^ plik, System::String^ plikWyj);
	bool DeszyfrujCFB_OFB(System::String^ plik, System::String^ plikWyj);
};