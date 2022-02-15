#include "stdafx.h"
#include "RC6algo.h"
#include "RC6.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;

// Konstruktor
RC6algo::RC6algo()
{
	this->cipherMode_ = CipherMode::ECB;
	this->keyLength_ = 32;
}

// Konstruktor tworzacy miejsce na klucz i ustawiajacy go
RC6algo::RC6algo(System::String^ key, int keyLength)
{
	this->keyLength_ = keyLength;
	this->key_ = gcnew array<System::Byte^>(this->keyLength_);
	for (int i = 0; i < key->Length; i++)
		this->key_[i] = ::Convert::ToByte(key[i]);
	this->cipherMode_ = CipherMode::ECB;
}

// Jak wyzej ale ustawia jeszcze wybrany przez uzytkownika 
// tryb szyfrowania
RC6algo::RC6algo(System::String^ key, int keyLength, CipherMode cipherMode)
{
	this->keyLength_ = keyLength;
	this->key_ = gcnew array<System::Byte^>(this->keyLength_);
	for (int i = 0; i < key->Length; i++)
		this->key_[i] = ::Convert::ToByte(key[i]);
	this->cipherMode_ = cipherMode;
}

// Szyfrowanie pliku
void RC6algo::Encrypt(System::String^ plik, System::String^ plikWyj)
{
	// Sprawdzamy czy plik istnieje
	::FileInfo^ fiPlik = gcnew FileInfo(plik);
	if (!fiPlik->Exists)
		return;
	// Wybor typu szyfrowania
	switch (this->cipherMode_)
	{
		case CipherMode::ECB:
		case CipherMode::CBC:
			Encrypt_ECB_CBC(plik, plikWyj); break;
		case CipherMode::CFB:
		case CipherMode::OFB:
			EncryptCFB_OFB(plik, plikWyj); break;

	}
}

// Deszyforwanie pliku
bool RC6algo::Decrypt(System::String^ plik, System::String^ plikWyj)
{
	// Sprawdzamy czy plik istnieje
	::FileInfo^ fiPlik = gcnew FileInfo(plik);
	if (!fiPlik->Exists)
		return false;
	// Wybor typu deszyfrowania
	switch (this->cipherMode_)
	{
		case CipherMode::ECB:
		case CipherMode::CBC:
			return (DecryptECB_CBC(plik, plikWyj)); break;
		case CipherMode::CFB:
		case CipherMode::OFB:
			return (Decrypt_CFB_OFB(plik, plikWyj)); break;
	}
}

// Metoda generuje klucz sesyjny
void RC6algo::GenerateSessionKey()
{
	// Inicjalizujemy zmienne
	Text::StringBuilder^ builder = gcnew Text::StringBuilder();
	// Inicjalizacja generatora liczb losownych na podstawie
	// aktualnej wartosci zegara systemowego (ilosc tick'ow)
	::Random^ random = gcnew Random(DateTime::Now.Ticks);
	unsigned char ch ;
	
	// Losujemy 32 znaki (dlugosc klucza) z przedzialu kodow
	// ASCII 33 do 126 (a zatem sa to cyfry, litery (male i duze) oraz
	// inne znaki alfanumeryczne
	for(int i = 0; i < this->keyLength_; i++)
	{
		ch = ::Convert::ToByte(random->Next(33, 126)) ;
		builder->Append(::Convert::ToChar(ch));
	}
	// Budujemy klucz
	System::String^ sess = builder->ToString();

	// Zapisujemy go w pamieci
	this->sessionKey_ = gcnew array<System::Byte^>(this->keyLength_);
	for (int i = 0; i < this->keyLength_; i++)
		this->sessionKey_[i] = ::Convert::ToByte(sess[i]);
}

void RC6algo::GenerateIV()
{
	Text::StringBuilder^ builder = gcnew Text::StringBuilder();
	// Inicjalizacja generatora liczb losownych na podstawie
	// aktualnej wartosci zegara systemowego (ilosc tick'ow)
	::Random^ random = gcnew Random(DateTime::Now.Ticks);
	unsigned char ch ;

	// Losujemy 16 znakow (dlugosc bloku) z przedzialu kodow
	// ASCII 33 do 126 (a zatem sa to cyfry, litery (male i duze) oraz
	// inne znaki alfanumeryczne
	for(int i = 0; i < 16; i++)
	{
		ch = ::Convert::ToByte(random->Next(33, 126)) ;		
		builder->Append(::Convert::ToChar(ch));
	}
	// Budujemy wektor
	System::String^ sess = builder->ToString();

	// Zapisujemy go w pamieci
	this->IV = gcnew array<System::Byte^>(32);
	for (int i = 0; i < 16; i++)
		this->IV[i] = ::Convert::ToByte(sess[i]);
}

// Metoda prywatna zapisujaca naglowek pliku.
void RC6algo::WriteHeader(System::String^ plikWyj)
{
	::BinaryWriter^ Zapis = gcnew BinaryWriter( File::Open( plikWyj, FileMode::Create ) );
	try
	{
	
	   // Obliczamy dlugosc naglowka - sa to 44 bajty w standardzie + musimy do nich
	   // dodac nasza dlugosc klucza - w ten sposob otrzymamy calkowita dlugosc naglowka.
		unsigned char dl = 44 + this->keyLength_;
		Zapis->Write(dl);       // Zapisujemy pole dlugosci naglowka

		dl = 8;                    // Jest to dlugosc sygnatury pliku
		Zapis->Write(dl);
		// Zapisujemy sygnature pliku (ciag po ktorym rozpoznajemy zaszyfrowany plik)
		// W naszym przypadku to RCRC6RC6
		Zapis->Write(Convert::ToByte('R'));
		Zapis->Write(Convert::ToByte('C'));
		Zapis->Write(Convert::ToByte('R'));
		Zapis->Write(Convert::ToByte('C'));
		Zapis->Write(Convert::ToByte('6'));
		Zapis->Write(Convert::ToByte('R'));
		Zapis->Write(Convert::ToByte('C'));
		Zapis->Write(Convert::ToByte('6'));

		// Dlugosc, prefiks i sam tryb szyfrowania
		// Okresla ilosc bajtow do zapisania
		dl = 5;
		Zapis->Write(dl);
		// Zapisujemy prefiks - w zasadzie wogole w specyfikacji prefiksy nie zostaly
		// okreslone wiec ich nie stosujemy bo nie ma takiej potrzeby - w programie
		// uzywany jest tylko jeden algorytm wiec prefiks nie ma zadnego zadania, 
		// zostal zaimplementowany tylko w celu zachowania zgodnosci z przeslanym
		// wzorem naglowka. W tym wypadku prefiks jest ciagiem RCRC
		Zapis->Write(Convert::ToByte('R'));
		Zapis->Write(Convert::ToByte('C'));
		Zapis->Write(Convert::ToByte('R'));
		Zapis->Write(Convert::ToByte('C'));
		// Zapisujemy sam tryb szyfrowania
		Zapis->Write(Convert::ToByte(static_cast<int>(this->cipherMode_))); // Typ szyfrowania

		// Dlugosc klucza, prefiks 
		rc6 algorytm;
		// Obliczamy ilosc bajtow do zapisania - jest to 5 (bo tyle wynosi kolejny
		// prefiks, ktory znow nam do niczego sie nie przyda :-) - wiec jest to
		// RCRC6 - stad tez 5 bajtow) i do tej piatki dodajemy dlugosc klucza
		// ktora moze byc jak wiadomo rozna.
		dl = 5 + this->keyLength_;
		Zapis->Write(dl);
		Zapis->Write(Convert::ToByte('R'));
		Zapis->Write(Convert::ToByte('C'));
		Zapis->Write(Convert::ToByte('R'));
		Zapis->Write(Convert::ToByte('C'));
		Zapis->Write(Convert::ToByte('6'));

		// Deklarujemy miejsce na bloki
		u1byte bufor_in[16];
		u1byte bufor_out[16];
		u1byte klucz_bufor[32];

		// Konwertujemy klucz do formatu wymaganego przez RC6
		for (int i = 0; i < this->keyLength_; i++)
			klucz_bufor[i] = Convert::ToByte(this->key_[i]);
		algorytm.set_key(klucz_bufor, this->keyLength_, dir_flag::both);

		// Szyfrujemy klucz sesyjny i zapisujemy go w pliku
		for (int i = 0; i < 16; i++)
			bufor_in[i] = Convert::ToByte(this->sessionKey_[i]);
		algorytm.encrypt(bufor_in, bufor_out);
		for (int j = 0; j < 16; j++)
			Zapis->Write(bufor_out[j]);
		// Jezeli klucz jest 32 bajtowy to musimy oczywiscie dopisac pozostale
		// 16 bajtow
       if (this->keyLength_ == 32)
		{
			for (int i = 16; i < 32; i++)
				bufor_in[i-16] = Convert::ToByte(this->sessionKey_[i]);
			algorytm.encrypt(bufor_in, bufor_out);
			for (int j = 0; j < 16; j++)
				Zapis->Write(bufor_out[j]);
		}
		
		// Dlugosc i prefiks wektora IV - tutaj mamy stala dlugosc tego bloku naglowka.
		// Kolejny raz mamy prefiks - uzywamy jako prefiksu RCRC6 - po czym 
		// nastepuje wektor IV (inicjalizujacy). Wektor ma stala dlugosc 16 bajtow,
		// bo dokladnie tyle wynosi dlugosc bloku na jakim operuje RC6. A 16 bajtow +
		// 5 bajtow prefiksu daje nam 21.
		dl = 21;
		Zapis->Write(dl);
		Zapis->Write(Convert::ToByte('R'));
		Zapis->Write(Convert::ToByte('C'));
		Zapis->Write(Convert::ToByte('R'));
		Zapis->Write(Convert::ToByte('C'));
		Zapis->Write(Convert::ToByte('6'));
		// Zapisujemy w pliku wektor poczatkowy
		for (int i = 0; i < 16; i++)
			Zapis->Write(Convert::ToByte(this->IV[i]));
		// Konczymy zapis.
		Zapis->Close();
	}
	catch (EndOfStreamException^ e)
	{
		Zapis->Close();
	}
}

// Metoda prywatna, odczytujaca naglowek i ustawiajaca 
// odpowiednie pola w klasie
void RC6algo::ReadHeader(System::String^ plik)
{
	try
	{
		::BinaryReader^ Czytnik = gcnew BinaryReader( File::Open(plik, FileMode::Open));
		// Czytamy sygnature - jako ze pierwszych 15 bajtow nie daje nam zadnych
		// konkretnych informacji o pliku to mozemy je pominac. Po prostu przechodzimy
		// sobie po nich, nie przejmujac sie nimi.
		unsigned char buff;
		for (int i = 0; i < 15; i++)
			buff = Czytnik->ReadByte();
		// Odczytujemy typ szyfrowania, czyli 16 bajtw naszego naglowka. To pierwszy bajt
		// ktory nas interesuje w pliku wiec wczytujemy go do opdowiedniej zmiennej.
		this->cipherMode_ = static_cast<CipherMode> (Czytnik->ReadByte());
		// Wczytujemy teraz dlugosc prefiksu i klucza
		buff = Czytnik->ReadByte();
		// Konwertujemy wczytany bajt na liczbe.
		int dl = buff;
		// Musimy odjac od tej liczby 5 - jak widac bylo w zapisie naglowka, calu blok ma
		// dlugosc rowna dlugosci klucza z dodana dlugoscia prefiksu - prefiks to 5 bajtow
		// wiec po odjeciu piatki otrzymamy dlugosc klucza, jakim zaszyfrowano plik.
		dl -= 5;
		this->keyLength_ = dl;
		this->sessionKey_ = gcnew array<System::Byte^>(dl);

		u1byte bufor_in[16];
		u1byte bufor_out[16];
		rc6 algorytm;
		u1byte klucz_bufor[32];
		
		// Konwertujemy klucz do postaci akceptowanej przez RC6
		// i ustawiamy go
		for (int i = 0; i < this->keyLength_; i++)
			klucz_bufor[i] = Convert::ToByte(this->key_[i]);
		algorytm.set_key(klucz_bufor, this->keyLength_, dir_flag::both);
		
		// Czytamy 5 bajtow prefiksu klucza. Jako ze go nie uzywamy to po prostu
		// pomijamy te dane bez obrobki. Prefiks nie jest nam potrzebny.
		buff = Czytnik->ReadByte();
		buff = Czytnik->ReadByte();
		buff = Czytnik->ReadByte();
		buff = Czytnik->ReadByte();
		buff = Czytnik->ReadByte();
		// Zczytujemy i deszyfrujemy klucz sesyjny
		for (int i = 0; i < 16; i++)
			bufor_in[i] = Czytnik->ReadByte();
		algorytm.decrypt(bufor_in, bufor_out);
		for (int j = 0; j < 16; j++)
			this->sessionKey_[j] = bufor_out[j];
		// Jezeli klucz jest dluzszy niz 16 bajtow to musimy wczytac druga 
		// czesc klucza i ustawic jako sesyjny.
		if (this->keyLength_ > 16)
		{
			for (int i = 0; i < 16; i++)
				bufor_in[i] = Czytnik->ReadByte();
			algorytm.decrypt(bufor_in, bufor_out);
			for (int j = 16; j < this->keyLength_; j++)
				this->sessionKey_[j] = bufor_out[j-16];
		}
		
		// Czytamy 6 bajtow - czyli prefiks wektora IV. Ponownie, jak kazdy prefiks
		// pomijamy go - takze i w tym przypadku nie wykorzystujemy go do niczego wiec
		// wystarczy przeleciec te 6 bajtow i ustawic sie na odczyt wektora IV.
		for (int i = 0; i < 6; i++)
			buff = Czytnik->ReadByte();
		// Zczytujemy wektor poczatkowy - najpierw generujemy wektorek po to aby
		// uzyskac miejsce w pamieci na wczytanie tego wlasciwego.
		this->GenerateIV();
		// Czytamy 16 bajtow pliku, ktore zawieraja nasz wektor IV.
		for (int i = 0; i < 16; i++)
			this->IV[i] = Czytnik->ReadByte();
		Czytnik->Close();

	}
	catch (EndOfStreamException^ e)
	{

	}
	catch (...)
	{

	}

}

// Metoda prywatna szyfrujaca w trybach ECB lub CBC
// Uzyta zostala jedna metoda, ze wzgledu na niewielkie roznice
// implementacyjne w obu tych metodach.
void RC6algo::Encrypt_ECB_CBC(System::String^ plik, System::String^ plikWyj)
{
	try
	{
		// Generujemy klucz sesyjny i wektor poczatkowy (uzyteczny tylko w CBC)
		this->GenerateSessionKey();
		this->GenerateIV();

		this->WriteHeader(plikWyj);

		// Pobieramy informacje o pliku
		// Otwieramy oba pliki (wejsciowy i wyjsciowy) w trybie
		// binarnym, aby moc obslugiwac rowniez pliki w tym formacie
		::FileInfo^ fiPlik = gcnew FileInfo(plik);
		::BinaryReader^ Czytnik = gcnew BinaryReader( File::Open(plik, FileMode::Open));
		::BinaryWriter^ Zapis = gcnew BinaryWriter( File::Open( plikWyj, FileMode::Append) );

	
		// Pobieramy dlugosc pliku
		__int64 dlugosc = fiPlik->Length;
		Zapis->Write(dlugosc);
		// Tworzymy obiekt algorytmu z implementacji z Internetu
		rc6 algorytm;

		// Deklarujemy miejsce na bloki
		u1byte bufor_in[16];
		u1byte bufor_out[16];
		u1byte klucz_bufor[32];

		// Ustawiamy jako klucz szyfrujacy klucz sesyjny
		for (int i = 0; i < this->keyLength_; i++)
			klucz_bufor[i] = Convert::ToByte(this->sessionKey_[i]);
		algorytm.set_key(klucz_bufor, this->keyLength_, dir_flag::both);

		// Szyfrujemy caly plik w blokach po 16 bajtow (rozmiar
		// bloku dla RC6).
		for (int i = 0; i < (int)(dlugosc / 16); i++)
		{
			// Czytamy po 16 bajtow
			for (int j = 0; j < 16; j++)
			{
				bufor_in[j] = Czytnik->ReadByte();
				// Jezeli jest to tryb CBC od razu
				// xorujemy z zaszyfrowana wartoscia poprzedniego
				// bloku
				if (this->cipherMode_ == CipherMode::CBC)
					bufor_in[j] ^= Convert::ToByte(this->IV[j]);
			}
			// Szyfrujemy obecny blok
			algorytm.encrypt(bufor_in, bufor_out);
			// Zapisujemy wynik do pliku
			for (int j = 0; j < 16; j++)
			{
				Zapis->Write(bufor_out[j]);
				// Jesli CBC to zapamietujemy obecny szyfrogram
				// do pozniejszego xorowania
				if (this->cipherMode_ == CipherMode::CBC)
					this->IV[j] = bufor_out[j];
			}
		}
		// Czytamy ostatni ciag bajtow
		for (int i = 0; i < (dlugosc - (int)(dlugosc / 16) * 16); i++)
		{
			bufor_in[i] = Czytnik->ReadByte();
			if (this->cipherMode_ == CipherMode::CBC)
				bufor_in[i] ^= Convert::ToByte(this->IV[i]);
		}
		// Jezeli dlugosc ostatniego bloku w pliku nie wynosi
		// 16 to dopelniamy zerami do 16stu bajtow
		for (int j = (dlugosc - (int)(dlugosc / 16) * 16); j < 16; j++)
		{
			bufor_in[j] = 0;
			// Jesli CBC to od razu xorujemy
			if (this->cipherMode_ == CipherMode::CBC)
				bufor_in[j] ^= Convert::ToByte(this->IV[j]);
		}
		// Szyfrujemy ostatni blok
		algorytm.encrypt(bufor_in, bufor_out);
		// Zapis ostatniego bloku
		for (int j = 0; j < 16; j++)
				Zapis->Write(bufor_out[j]);
		// Zamykamy pliki
		Czytnik->Close();
		Zapis->Close();

	}
	catch ( EndOfStreamException^ e)
	{

	}
	catch (...)
	{

	}
}

// Metoda prywatna deszyfrujaca w trybach ECB lub CBC
// Uzyta zostala jedna metoda, ze wzgledu na niewielkie roznice
// implementacyjne w obu tych metodach.
bool RC6algo::DecryptECB_CBC(System::String^ plik, System::String^ plikWyj)
{

	try
	{
		this->ReadHeader(plik);
			// Otwieramy pliki
		::FileInfo^ fiPlik = gcnew FileInfo(plik);
		::BinaryReader^ Czytnik = gcnew BinaryReader( File::Open(plik, FileMode::Open));
		::BinaryWriter^ Zapis = gcnew BinaryWriter( File::Open( plikWyj, FileMode::Create ) );

		// Obliczamy dlugosc bloku danych (rozmiar pliku - naglowek)
		int dlugosc = fiPlik->Length - (52 + this->keyLength_);
		// Pomijamy juz wczytany naglowek
		unsigned char buff;
		for (int i = 0; i < 44+this->keyLength_; i++)
			buff = Czytnik->ReadByte();

		// Jezeli nie zgadza sie z tym wybranym przez uzytkownika
		// to zapisujemy rozpoznany tryb i wracamy do wyboru
		// metody szyfrujacej
		if (this->cipherMode_ != CipherMode::CBC && this->cipherMode_ != CipherMode::ECB)
		{
			Czytnik->Close();
			Zapis->Close();
			this->Decrypt(plik, plikWyj);
			return true;
		}

		// Deklarujemy zmienne
		
		u1byte bufor_in[16];
		u1byte bufor_out[16];
		rc6 algorytm;
		u1byte klucz_bufor[32];

		// Zczytujemy dlugosc oryginalu
		__int64 dlugosc_orig = Czytnik->ReadInt64();

		// Konwertujemy klucz sesyjny i ustawiamy go do deszyfracji
		for (int i = 0; i < this->keyLength_; i++)
			klucz_bufor[i] = Convert::ToByte(this->sessionKey_[i]);
		algorytm.set_key(klucz_bufor, this->keyLength_, dir_flag::both);

		// Deszyfrujemy plik w blokach o dlugosc 16
		for (int i = 0; i < (int)(dlugosc / 16)-1; i++)
		{
			// Czytamy blok 16 bajtow
			for (int j = 0; j < 16; j++)
				bufor_in[j] = Czytnik->ReadByte();
			// Deszyfrujemy go
			algorytm.decrypt(bufor_in, bufor_out);
			for (int j = 0; j < 16; j++)
			{
				// Jesli jest to tryb CBC to wykonujemy xora
				// i zapamietujemy obecny szyfrogram jako kolejny
				// do operacji xor
				if (this->cipherMode_ == CipherMode::CBC)
				{
					bufor_out[j] ^= Convert::ToByte(this->IV[j]);
					this->IV[j] = bufor_in[j];
				}
				// Zapisujemy
				Zapis->Write(bufor_out[j]);
				
			}
		}
		// Czytamy ostatnie 16 bajtow pliku
		for (int j = 0; j < 16; j++)
				bufor_in[j] = Czytnik->ReadByte();
		// Deszyfrujemy je
		algorytm.decrypt(bufor_in, bufor_out);
		// Zapisujemy w pliku tylko tyle bajtow ile mial miec oryginal
		for (int j = 0; j < (int)dlugosc_orig - (int)(dlugosc_orig / 16) * 16; j++)
		{
				// Oczywiscie w przypadku CBC jeszcze xorujemy
				if (this->cipherMode_ == CipherMode::CBC)
					bufor_out[j] ^= Convert::ToByte(this->IV[j]);
				Zapis->Write(bufor_out[j]);
		}
		// Zamykamy pliki 
		Czytnik->Close();
		Zapis->Close();
		return true;
	}
	catch ( EndOfStreamException^ e)
	{

	}
	catch (...)
	{

	}

}

// Metoda prywatna szyfrujaca w trybach CFB lub OFB
// Uzyta zostala jedna metoda, ze wzgledu na niewielkie roznice
// implementacyjne w obu tych metodach.
void RC6algo::EncryptCFB_OFB(System::String^ plik, System::String^ plikWyj)
{
	try
	{
		// Generujemy potrzebne dane
		this->GenerateSessionKey();
		this->GenerateIV();

		this->WriteHeader(plikWyj);

		// Otwieramy pliki
		::FileInfo^ fiPlik = gcnew FileInfo(plik);
		::BinaryReader^ Czytnik = gcnew BinaryReader( File::Open(plik, FileMode::Open));
		::BinaryWriter^ Zapis = gcnew BinaryWriter( File::Open( plikWyj, FileMode::Append ) );

		__int64 dlugosc = fiPlik->Length;
		Zapis->Write(dlugosc);

		rc6 algorytm;

		// Deklaracja danych
		u1byte bufor_in[16];
		u1byte bufor_out[16];
		u1byte klucz_bufor[32];

		// Ustawiamy klucz sesyjny jako nasz klucz szyfrujacy
		for (int i = 0; i < this->keyLength_; i++)
			klucz_bufor[i] = Convert::ToByte(this->sessionKey_[i]);
		algorytm.set_key(klucz_bufor, this->keyLength_, dir_flag::both);

		// Szyfrujemy dane
		for (int i = 0; i < (int)(dlugosc / 16); i++)
		{
			// Ustawiamy wynik poprzedniej operacji lub
			// wektor poczatkowy gdy i = 0
			for (int j = 0; j < 16; j++)
				bufor_in[j] = Convert::ToByte(this->IV[j]);
			// Szyfrujemy
			algorytm.encrypt(bufor_in, bufor_out);

			// Czytamy bloki po 16 bajtow i xorujemy je z 
			// zaszyfrowanymi danymi
			for (int j = 0; j < 16; j++)
			{
				bufor_in[j] = Czytnik->ReadByte();
				bufor_in[j] ^= bufor_out[j];
			}
			// Zapisujemy dane
			for (int j = 0; j < 16; j++)
			{
				Zapis->Write(bufor_in[j]);
				// W trybie CFB zaszyfrowane dane sa poddawane 
				// dalszej obrobce (tj. szyfrowania i xorowaniu)
				if ( this->cipherMode_ == CipherMode::CFB)
					this->IV[j] = bufor_in[j];
				// W trybie OFB, szyfrowac ponownie bedziemy 
				// juz zaszyfrowany wektor poczatkowy
				else
					this->IV[j] = bufor_out[j];
			}
		}
		// Ustawiamy wynik poprzedniej operacji
		for (int j = 0; j < 16; j++)
			bufor_in[j] = Convert::ToByte(this->IV[j]);
		// Szyfrujemy
		algorytm.encrypt(bufor_in, bufor_out);
		// Zajmujemy sie ostatnim blokiem podobnie jak w ECB i CBC
		for (int i = 0; i < (dlugosc - (int)(dlugosc / 16) * 16); i++)
		{
			bufor_in[i] = Czytnik->ReadByte();
			bufor_in[i] ^= bufor_out[i];
		}
		for (int j = (dlugosc - (int)(dlugosc / 16) * 16); j < 16; j++)
		{
			bufor_in[j] = 0;
			bufor_in[j] ^= bufor_out[j];
		}
		// Zapisujemy ostatni blok danych
		for (int j = 0; j < 16; j++)
				Zapis->Write(bufor_in[j]);
		Czytnik->Close();
		Zapis->Close();
	}
	catch ( EndOfStreamException^ e)
	{

	}

}

// Metoda prywatna deszyfrujaca w trybach CFB lub OFB
// Uzyta zostala jedna metoda, ze wzgledu na niewielkie roznice
// implementacyjne w obu tych metodach.
bool RC6algo::Decrypt_CFB_OFB(System::String^ plik, System::String^ plikWyj)
{
	try
	{
		this->ReadHeader(plik);

		// Otwieramy pliki
		::FileInfo^ fiPlik = gcnew FileInfo(plik);
		::BinaryReader^ Czytnik = gcnew BinaryReader( File::Open(plik, FileMode::Open));
		::BinaryWriter^ Zapis = gcnew BinaryWriter( File::Open( plikWyj, FileMode::Create ) );

		// Liczymy dlugosc pliku
		int dlugosc = fiPlik->Length - (52 + this->keyLength_);
		// Pomijamy juz wczytany naglowek
		unsigned char buff;
		for (int i = 0; i < 44+this->keyLength_; i++)
			buff = Czytnik->ReadByte();
		// Jesli pobrany jest inny niz ten ustawiony przez 
		// uzytkownika to wracamy do wyboru funkcji deszyfrujacej
		if (this->cipherMode_ != CipherMode::CFB && this->cipherMode_ != CipherMode::OFB)
		{
			Czytnik->Close();
			Zapis->Close();
			return this->Decrypt(plik, plikWyj);;
		}
		
		u1byte bufor_in[16];
		u1byte bufor_out[16];
		rc6 algorytm;
		u1byte klucz_bufor[32];

		// Czytamy oryginalna dlugosc pliku
		__int64 dlugosc_orig = Czytnik->ReadInt64();

		// Konwertujemy i ustawiamy klucz sesyjny
		for (int i = 0; i < this->keyLength_; i++)
			klucz_bufor[i] = Convert::ToByte(this->sessionKey_[i]);
		algorytm.set_key(klucz_bufor, this->keyLength_, dir_flag::both);

		// Deszyfrujemy plik
		for (int i = 0; i < (int)(dlugosc / 16)-1; i++)
		{
			// Szyfrujemy kolejny ciag strumienia szyfrujacego
			for (int j = 0; j < 16; j++)
				bufor_in[j] = Convert::ToByte(this->IV[j]);
			algorytm.encrypt(bufor_in, bufor_out);

			// Czytamy blok 16 bajtow
			for (int j = 0; j < 16; j++)
			{
				bufor_in[j] = Czytnik->ReadByte();
				// W trybie CFB nastepnym ciagiem strumienia szyfrujacego
				// jest wlasnie wczytany szyfrogram
				if (this->cipherMode_ == CipherMode::CFB)
					this->IV[j] = bufor_in[j];
				else
				// W trybie OFB jest nim zaszyfrowany ponownie wektor IV
					this->IV[j] = bufor_out[j];
				// xorujemy dane ze strumieniem
				bufor_in[j] ^= bufor_out[j];
			}
			// Zapisujemy wynik do pliku
			for (int j = 0; j < 16; j++)
			{
				Zapis->Write(bufor_in[j]);
			}
		}
		// Obsluga ostatniego bloku pliku (jak w ECB)

		for (int j = 0; j < 16; j++)
			bufor_in[j] = Convert::ToByte(this->IV[j]);
		algorytm.encrypt(bufor_in, bufor_out);
		for (int j = 0; j < 16; j++)
		{
				bufor_in[j] = Czytnik->ReadByte();
				bufor_in[j] ^= bufor_out[j];
		}	

		for (int j = 0; j < (int)dlugosc_orig - (int)(dlugosc_orig / 16) * 16; j++)
				Zapis->Write(bufor_in[j]);
		
		// Zamykamy pliki
		Czytnik->Close();
		Zapis->Close();
		return true;
	}
	catch ( EndOfStreamException^ e)
	{

		return false;
	}
	catch ( ... )
	{

	}
}
