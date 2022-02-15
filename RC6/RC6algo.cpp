#include "stdafx.h"
#include "RC6algo.h"
#include "RC6.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;


RC6algo::RC6algo()
{
	this->cipherMode_ = CipherMode::ECB;
	this->keyLength_ = 32;
}


RC6algo::RC6algo(System::String^ key, int keyLength)
{
	this->keyLength_ = keyLength;
	this->key_ = gcnew array<System::Byte^>(this->keyLength_);
	for (int i = 0; i < key->Length; i++)
		this->key_[i] = ::Convert::ToByte(key[i]);
	this->cipherMode_ = CipherMode::ECB;
}


RC6algo::RC6algo(System::String^ key, int keyLength, CipherMode cipherMode)
{
	this->keyLength_ = keyLength;
	this->key_ = gcnew array<System::Byte^>(this->keyLength_);
	for (int i = 0; i < key->Length; i++)
		this->key_[i] = ::Convert::ToByte(key[i]);
	this->cipherMode_ = cipherMode;
}


void RC6algo::Encrypt(System::String^ fileIn, System::String^ fileOut)
{
	::FileInfo^ inputFileInfo = gcnew FileInfo(fileIn);
	if (!inputFileInfo->Exists)
		return;
	
	switch (this->cipherMode_)
	{
		case CipherMode::ECB:
		case CipherMode::CBC:
			Encrypt_ECB_CBC(fileIn, fileOut); break;
		case CipherMode::CFB:
		case CipherMode::OFB:
			EncryptCFB_OFB(fileIn, fileOut); break;
	}
}


bool RC6algo::Decrypt(System::String^ fileIn, System::String^ fileOut)
{
	::FileInfo^ inputFileInfo = gcnew FileInfo(fileIn);
	if (!inputFileInfo->Exists)
		return false;

	switch (this->cipherMode_)
	{
		case CipherMode::ECB:
		case CipherMode::CBC:
			return (DecryptECB_CBC(fileIn, fileOut)); break;
		case CipherMode::CFB:
		case CipherMode::OFB:
			return (Decrypt_CFB_OFB(fileIn, fileOut)); break;
		default:
			return false;
	}
}


void RC6algo::GenerateSessionKey()
{
	Text::StringBuilder^ builder = gcnew Text::StringBuilder();
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


void RC6algo::WriteHeader(System::String^ fileOut)
{
	::BinaryWriter^ fWriter = gcnew BinaryWriter( File::Open( fileOut, FileMode::Create ) );
	try
	{
	
	   // Obliczamy dlugosc naglowka - sa to 44 bajty w standardzie + musimy do nich
	   // dodac nasza dlugosc klucza - w ten sposob otrzymamy calkowita dlugosc naglowka.
		unsigned char len = 44 + this->keyLength_;
		fWriter->Write(len);       // Zapisujemy pole dlugosci naglowka

		len = 8;                    // Jest to dlugosc sygnatury pliku
		fWriter->Write(len);
		// Zapisujemy sygnature pliku (ciag po ktorym rozpoznajemy zaszyfrowany plik)
		// W naszym przypadku to RCRC6RC6
		fWriter->Write(Convert::ToByte('R'));
		fWriter->Write(Convert::ToByte('C'));
		fWriter->Write(Convert::ToByte('R'));
		fWriter->Write(Convert::ToByte('C'));
		fWriter->Write(Convert::ToByte('6'));
		fWriter->Write(Convert::ToByte('R'));
		fWriter->Write(Convert::ToByte('C'));
		fWriter->Write(Convert::ToByte('6'));

		// Dlugosc, prefiks i sam tryb szyfrowania
		// Okresla ilosc bajtow do zapisania
		len = 5;
		fWriter->Write(len);
		// Zapisujemy prefiks - w zasadzie wogole w specyfikacji prefiksy nie zostaly
		// okreslone wiec ich nie stosujemy bo nie ma takiej potrzeby - w programie
		// uzywany jest tylko jeden algorytm wiec prefiks nie ma zadnego zadania, 
		// zostal zaimplementowany tylko w celu zachowania zgodnosci z przeslanym
		// wzorem naglowka. W tym wypadku prefiks jest ciagiem RCRC
		fWriter->Write(Convert::ToByte('R'));
		fWriter->Write(Convert::ToByte('C'));
		fWriter->Write(Convert::ToByte('R'));
		fWriter->Write(Convert::ToByte('C'));
		// Zapisujemy sam tryb szyfrowania
		fWriter->Write(Convert::ToByte(static_cast<int>(this->cipherMode_))); // Typ szyfrowania

		// Dlugosc klucza, prefiks 
		rc6 algorithm;
		// Obliczamy ilosc bajtow do zapisania - jest to 5 (bo tyle wynosi kolejny
		// prefiks, ktory znow nam do niczego sie nie przyda :-) - wiec jest to
		// RCRC6 - stad tez 5 bajtow) i do tej piatki dodajemy dlugosc klucza
		// ktora moze byc jak wiadomo rozna.
		len = 5 + this->keyLength_;
		fWriter->Write(len);
		fWriter->Write(Convert::ToByte('R'));
		fWriter->Write(Convert::ToByte('C'));
		fWriter->Write(Convert::ToByte('R'));
		fWriter->Write(Convert::ToByte('C'));
		fWriter->Write(Convert::ToByte('6'));

		// Deklarujemy miejsce na bloki
		u1byte inBuffer[16];
		u1byte outBuffer[16];
		u1byte keyBuffer[32];

		// Konwertujemy klucz do formatu wymaganego przez RC6
		for (int i = 0; i < this->keyLength_; i++)
			keyBuffer[i] = Convert::ToByte(this->key_[i]);
		algorithm.set_key(keyBuffer, this->keyLength_, dir_flag::both);

		// Szyfrujemy klucz sesyjny i zapisujemy go w pliku
		for (int i = 0; i < 16; i++)
			inBuffer[i] = Convert::ToByte(this->sessionKey_[i]);
		algorithm.encrypt(inBuffer, outBuffer);
		for (int j = 0; j < 16; j++)
			fWriter->Write(outBuffer[j]);
		// Jezeli klucz jest 32 bajtowy to musimy oczywiscie dopisac pozostale
		// 16 bajtow
       if (this->keyLength_ == 32)
		{
			for (int i = 16; i < 32; i++)
				inBuffer[i-16] = Convert::ToByte(this->sessionKey_[i]);
			algorithm.encrypt(inBuffer, outBuffer);
			for (int j = 0; j < 16; j++)
				fWriter->Write(outBuffer[j]);
		}
		
		// Dlugosc i prefiks wektora IV - tutaj mamy stala dlugosc tego bloku naglowka.
		// Kolejny raz mamy prefiks - uzywamy jako prefiksu RCRC6 - po czym 
		// nastepuje wektor IV (inicjalizujacy). Wektor ma stala dlugosc 16 bajtow,
		// bo dokladnie tyle wynosi dlugosc bloku na jakim operuje RC6. A 16 bajtow +
		// 5 bajtow prefiksu daje nam 21.
		len = 21;
		fWriter->Write(len);
		fWriter->Write(Convert::ToByte('R'));
		fWriter->Write(Convert::ToByte('C'));
		fWriter->Write(Convert::ToByte('R'));
		fWriter->Write(Convert::ToByte('C'));
		fWriter->Write(Convert::ToByte('6'));
		// Zapisujemy w pliku wektor poczatkowy
		for (int i = 0; i < 16; i++)
			fWriter->Write(Convert::ToByte(this->IV[i]));
		// Konczymy zapis.
		fWriter->Close();
	}
	catch (EndOfStreamException^)
	{
		fWriter->Close();
	}
}


void RC6algo::ReadHeader(System::String^ fileIn)
{
	::BinaryReader^ fReader = gcnew BinaryReader(File::Open(fileIn, FileMode::Open));

	try
	{	
		// Czytamy sygnature - jako ze pierwszych 15 bajtow nie daje nam zadnych
		// konkretnych informacji o pliku to mozemy je pominac. Po prostu przechodzimy
		// sobie po nich, nie przejmujac sie nimi.
		unsigned char buff;
		for (int i = 0; i < 15; i++)
			buff = fReader->ReadByte();
		// Odczytujemy typ szyfrowania, czyli 16 bajtw naszego naglowka. To pierwszy bajt
		// ktory nas interesuje w pliku wiec wczytujemy go do opdowiedniej zmiennej.
		this->cipherMode_ = static_cast<CipherMode> (fReader->ReadByte());
		// Wczytujemy teraz dlugosc prefiksu i klucza
		buff = fReader->ReadByte();
		// Konwertujemy wczytany bajt na liczbe.
		int dl = buff;
		// Musimy odjac od tej liczby 5 - jak widac bylo w zapisie naglowka, calu blok ma
		// dlugosc rowna dlugosci klucza z dodana dlugoscia prefiksu - prefiks to 5 bajtow
		// wiec po odjeciu piatki otrzymamy dlugosc klucza, jakim zaszyfrowano plik.
		dl -= 5;
		this->keyLength_ = dl;
		this->sessionKey_ = gcnew array<System::Byte^>(dl);

		u1byte inBuffer[16];
		u1byte outBuffer[16];
		rc6 algorithm;
		u1byte keyBuffer[32];
		
		// Konwertujemy klucz do postaci akceptowanej przez RC6
		// i ustawiamy go
		for (int i = 0; i < this->keyLength_; i++)
			keyBuffer[i] = Convert::ToByte(this->key_[i]);
		algorithm.set_key(keyBuffer, this->keyLength_, dir_flag::both);
		
		// Czytamy 5 bajtow prefiksu klucza. Jako ze go nie uzywamy to po prostu
		// pomijamy te dane bez obrobki. Prefiks nie jest nam potrzebny.
		buff = fReader->ReadByte();
		buff = fReader->ReadByte();
		buff = fReader->ReadByte();
		buff = fReader->ReadByte();
		buff = fReader->ReadByte();
		// Zczytujemy i deszyfrujemy klucz sesyjny
		for (int i = 0; i < 16; i++)
			inBuffer[i] = fReader->ReadByte();
		algorithm.decrypt(inBuffer, outBuffer);
		for (int j = 0; j < 16; j++)
			this->sessionKey_[j] = outBuffer[j];
		// Jezeli klucz jest dluzszy niz 16 bajtow to musimy wczytac druga 
		// czesc klucza i ustawic jako sesyjny.
		if (this->keyLength_ > 16)
		{
			for (int i = 0; i < 16; i++)
				inBuffer[i] = fReader->ReadByte();
			algorithm.decrypt(inBuffer, outBuffer);
			for (int j = 16; j < this->keyLength_; j++)
				this->sessionKey_[j] = outBuffer[j-16];
		}
		
		// Czytamy 6 bajtow - czyli prefiks wektora IV. Ponownie, jak kazdy prefiks
		// pomijamy go - takze i w tym przypadku nie wykorzystujemy go do niczego wiec
		// wystarczy przeleciec te 6 bajtow i ustawic sie na odczyt wektora IV.
		for (int i = 0; i < 6; i++)
			buff = fReader->ReadByte();
		// Zczytujemy wektor poczatkowy - najpierw generujemy wektorek po to aby
		// uzyskac miejsce w pamieci na wczytanie tego wlasciwego.
		this->GenerateIV();
		// Czytamy 16 bajtow pliku, ktore zawieraja nasz wektor IV.
		for (int i = 0; i < 16; i++)
			this->IV[i] = fReader->ReadByte();
		fReader->Close();

	}
	catch (EndOfStreamException^)
	{
		fReader->Close();
	}
	catch (...)
	{

	}
}


void RC6algo::Encrypt_ECB_CBC(System::String^ fileIn, System::String^ fileOut)
{
	try
	{
		// Generujemy klucz sesyjny i wektor poczatkowy (uzyteczny tylko w CBC)
		this->GenerateSessionKey();
		this->GenerateIV();

		this->WriteHeader(fileOut);

		// Pobieramy informacje o pliku
		// Otwieramy oba pliki (wejsciowy i wyjsciowy) w trybie
		// binarnym, aby moc obslugiwac rowniez pliki w tym formacie
		::FileInfo^ inputFileInfo = gcnew FileInfo(fileIn);
		::BinaryReader^ fReader = gcnew BinaryReader( File::Open(fileIn, FileMode::Open));
		::BinaryWriter^ fWriter = gcnew BinaryWriter( File::Open(fileOut, FileMode::Append));

	
		// Pobieramy dlugosc pliku
		__int64 length = inputFileInfo->Length;
		fWriter->Write(length);
		// Tworzymy obiekt algorytmu z implementacji z Internetu
		rc6 algorithm;

		// Deklarujemy miejsce na bloki
		u1byte inBuffer[16];
		u1byte outBuffer[16];
		u1byte keyBuffer[32];

		// Ustawiamy jako klucz szyfrujacy klucz sesyjny
		for (int i = 0; i < this->keyLength_; i++)
			keyBuffer[i] = Convert::ToByte(this->sessionKey_[i]);
		algorithm.set_key(keyBuffer, this->keyLength_, dir_flag::both);

		// Szyfrujemy caly plik w blokach po 16 bajtow (rozmiar
		// bloku dla RC6).
		for (int i = 0; i < (int)(length / 16); i++)
		{
			// Czytamy po 16 bajtow
			for (int j = 0; j < 16; j++)
			{
				inBuffer[j] = fReader->ReadByte();
				// Jezeli jest to tryb CBC od razu
				// xorujemy z zaszyfrowana wartoscia poprzedniego
				// bloku
				if (this->cipherMode_ == CipherMode::CBC)
					inBuffer[j] ^= Convert::ToByte(this->IV[j]);
			}
			// Szyfrujemy obecny blok
			algorithm.encrypt(inBuffer, outBuffer);
			// Zapisujemy wynik do pliku
			for (int j = 0; j < 16; j++)
			{
				fWriter->Write(outBuffer[j]);
				// Jesli CBC to zapamietujemy obecny szyfrogram
				// do pozniejszego xorowania
				if (this->cipherMode_ == CipherMode::CBC)
					this->IV[j] = outBuffer[j];
			}
		}
		// Czytamy ostatni ciag bajtow
		for (int i = 0; i < (length - (int)(length / 16) * 16); i++)
		{
			inBuffer[i] = fReader->ReadByte();
			if (this->cipherMode_ == CipherMode::CBC)
				inBuffer[i] ^= Convert::ToByte(this->IV[i]);
		}
		// Jezeli dlugosc ostatniego bloku w pliku nie wynosi
		// 16 to dopelniamy zerami do 16stu bajtow
		for (auto j = (length - (int)(length / 16) * 16); j < 16; j++)
		{
			inBuffer[j] = 0;
			// Jesli CBC to od razu xorujemy
			if (this->cipherMode_ == CipherMode::CBC)
				inBuffer[j] ^= Convert::ToByte(this->IV[j]);
		}
		// Szyfrujemy ostatni blok
		algorithm.encrypt(inBuffer, outBuffer);
		// Zapis ostatniego bloku
		for (int j = 0; j < 16; j++)
				fWriter->Write(outBuffer[j]);
		// Zamykamy pliki
		fReader->Close();
		fWriter->Close();

	}
	catch ( EndOfStreamException^ )
	{

	}
	catch (...)
	{

	}
}


bool RC6algo::DecryptECB_CBC(System::String^ fileIn, System::String^ fileOut)
{
	try
	{
		this->ReadHeader(fileIn);
			// Otwieramy pliki
		::FileInfo^ inputFileInfo = gcnew FileInfo(fileIn);
		::BinaryReader^ fReader = gcnew BinaryReader( File::Open(fileIn, FileMode::Open));
		::BinaryWriter^ fWriter = gcnew BinaryWriter( File::Open( fileOut, FileMode::Create ) );

		// Obliczamy dlugosc bloku danych (rozmiar pliku - naglowek)
		auto length = inputFileInfo->Length - (52 + this->keyLength_);
		// Pomijamy juz wczytany naglowek
		unsigned char buff;
		for (int i = 0; i < 44+this->keyLength_; i++)
			buff = fReader->ReadByte();

		// Jezeli nie zgadza sie z tym wybranym przez uzytkownika
		// to zapisujemy rozpoznany tryb i wracamy do wyboru
		// metody szyfrujacej
		if (this->cipherMode_ != CipherMode::CBC && this->cipherMode_ != CipherMode::ECB)
		{
			fReader->Close();
			fWriter->Close();
			this->Decrypt(fileIn, fileOut);
			return true;
		}

		// Deklarujemy zmienne
		
		u1byte inBuffer[16];
		u1byte outBuffer[16];
		rc6 algorithm;
		u1byte keyBuffer[32];

		// Zczytujemy dlugosc oryginalu
		__int64 originalLength = fReader->ReadInt64();

		// Konwertujemy klucz sesyjny i ustawiamy go do deszyfracji
		for (int i = 0; i < this->keyLength_; i++)
			keyBuffer[i] = Convert::ToByte(this->sessionKey_[i]);
		algorithm.set_key(keyBuffer, this->keyLength_, dir_flag::both);

		// Deszyfrujemy plik w blokach o dlugosc 16
		for (int i = 0; i < (int)(length / 16)-1; i++)
		{
			// Czytamy blok 16 bajtow
			for (int j = 0; j < 16; j++)
				inBuffer[j] = fReader->ReadByte();
			// Deszyfrujemy go
			algorithm.decrypt(inBuffer, outBuffer);
			for (int j = 0; j < 16; j++)
			{
				// Jesli jest to tryb CBC to wykonujemy xora
				// i zapamietujemy obecny szyfrogram jako kolejny
				// do operacji xor
				if (this->cipherMode_ == CipherMode::CBC)
				{
					outBuffer[j] ^= Convert::ToByte(this->IV[j]);
					this->IV[j] = inBuffer[j];
				}
				// Zapisujemy
				fWriter->Write(outBuffer[j]);
				
			}
		}
		// Czytamy ostatnie 16 bajtow pliku
		for (int j = 0; j < 16; j++)
				inBuffer[j] = fReader->ReadByte();
		// Deszyfrujemy je
		algorithm.decrypt(inBuffer, outBuffer);
		// Zapisujemy w pliku tylko tyle bajtow ile mial miec oryginal
		for (int j = 0; j < (int)originalLength - (int)(originalLength / 16) * 16; j++)
		{
				// Oczywiscie w przypadku CBC jeszcze xorujemy
				if (this->cipherMode_ == CipherMode::CBC)
					outBuffer[j] ^= Convert::ToByte(this->IV[j]);
				fWriter->Write(outBuffer[j]);
		}
		// Zamykamy pliki 
		fReader->Close();
		fWriter->Close();
		return true;
	}
	catch ( EndOfStreamException^)
	{
		return false;
	}
	catch (...)
	{
		return false;
	}

}


void RC6algo::EncryptCFB_OFB(System::String^ fileIn, System::String^ fileOut)
{
	try
	{
		// Generujemy potrzebne dane
		this->GenerateSessionKey();
		this->GenerateIV();

		this->WriteHeader(fileOut);

		// Otwieramy pliki
		::FileInfo^ inputFileInfo = gcnew FileInfo(fileIn);
		::BinaryReader^ fReader = gcnew BinaryReader( File::Open(fileIn, FileMode::Open));
		::BinaryWriter^ fWriter = gcnew BinaryWriter( File::Open( fileOut, FileMode::Append ) );

		__int64 length = inputFileInfo->Length;
		fWriter->Write(length);

		rc6 algorithm;

		// Deklaracja danych
		u1byte inBuffer[16];
		u1byte outBuffer[16];
		u1byte keyBuffer[32];

		// Ustawiamy klucz sesyjny jako nasz klucz szyfrujacy
		for (int i = 0; i < this->keyLength_; i++)
			keyBuffer[i] = Convert::ToByte(this->sessionKey_[i]);
		algorithm.set_key(keyBuffer, this->keyLength_, dir_flag::both);

		// Szyfrujemy dane
		for (int i = 0; i < (int)(length / 16); i++)
		{
			// Ustawiamy wynik poprzedniej operacji lub
			// wektor poczatkowy gdy i = 0
			for (int j = 0; j < 16; j++)
				inBuffer[j] = Convert::ToByte(this->IV[j]);
			// Szyfrujemy
			algorithm.encrypt(inBuffer, outBuffer);

			// Czytamy bloki po 16 bajtow i xorujemy je z 
			// zaszyfrowanymi danymi
			for (int j = 0; j < 16; j++)
			{
				inBuffer[j] = fReader->ReadByte();
				inBuffer[j] ^= outBuffer[j];
			}
			// Zapisujemy dane
			for (int j = 0; j < 16; j++)
			{
				fWriter->Write(inBuffer[j]);
				// W trybie CFB zaszyfrowane dane sa poddawane 
				// dalszej obrobce (tj. szyfrowania i xorowaniu)
				if ( this->cipherMode_ == CipherMode::CFB)
					this->IV[j] = inBuffer[j];
				// W trybie OFB, szyfrowac ponownie bedziemy 
				// juz zaszyfrowany wektor poczatkowy
				else
					this->IV[j] = outBuffer[j];
			}
		}
		// Ustawiamy wynik poprzedniej operacji
		for (int j = 0; j < 16; j++)
			inBuffer[j] = Convert::ToByte(this->IV[j]);
		// Szyfrujemy
		algorithm.encrypt(inBuffer, outBuffer);
		// Zajmujemy sie ostatnim blokiem podobnie jak w ECB i CBC
		for (int i = 0; i < (length - (int)(length / 16) * 16); i++)
		{
			inBuffer[i] = fReader->ReadByte();
			inBuffer[i] ^= outBuffer[i];
		}
		for (auto j = (length - (int)(length / 16) * 16); j < 16; j++)
		{
			inBuffer[j] = 0;
			inBuffer[j] ^= outBuffer[j];
		}
		// Zapisujemy ostatni blok danych
		for (int j = 0; j < 16; j++)
				fWriter->Write(inBuffer[j]);
		fReader->Close();
		fWriter->Close();
	}
	catch ( EndOfStreamException^)
	{

	}

}


bool RC6algo::Decrypt_CFB_OFB(System::String^ fileIn, System::String^ fileOut)
{
	try
	{
		this->ReadHeader(fileIn);

		// Otwieramy pliki
		::FileInfo^ inputFileInfo = gcnew FileInfo(fileIn);
		::BinaryReader^ fReader = gcnew BinaryReader( File::Open(fileIn, FileMode::Open));
		::BinaryWriter^ fWriter = gcnew BinaryWriter( File::Open( fileOut, FileMode::Create ) );

		// Liczymy dlugosc pliku
		auto length = inputFileInfo->Length - (52 + this->keyLength_);
		// Pomijamy juz wczytany naglowek
		unsigned char buff;
		for (int i = 0; i < 44+this->keyLength_; i++)
			buff = fReader->ReadByte();
		// Jesli pobrany jest inny niz ten ustawiony przez 
		// uzytkownika to wracamy do wyboru funkcji deszyfrujacej
		if (this->cipherMode_ != CipherMode::CFB && this->cipherMode_ != CipherMode::OFB)
		{
			fReader->Close();
			fWriter->Close();
			return this->Decrypt(fileIn, fileOut);;
		}
		
		u1byte inBuffer[16];
		u1byte outBuffer[16];
		rc6 algorithm;
		u1byte keyBuffer[32];

		// Czytamy oryginalna dlugosc pliku
		__int64 originalLength = fReader->ReadInt64();

		// Konwertujemy i ustawiamy klucz sesyjny
		for (int i = 0; i < this->keyLength_; i++)
			keyBuffer[i] = Convert::ToByte(this->sessionKey_[i]);
		algorithm.set_key(keyBuffer, this->keyLength_, dir_flag::both);

		// Deszyfrujemy plik
		for (int i = 0; i < (int)(length / 16)-1; i++)
		{
			// Szyfrujemy kolejny ciag strumienia szyfrujacego
			for (int j = 0; j < 16; j++)
				inBuffer[j] = Convert::ToByte(this->IV[j]);
			algorithm.encrypt(inBuffer, outBuffer);

			// Czytamy blok 16 bajtow
			for (int j = 0; j < 16; j++)
			{
				inBuffer[j] = fReader->ReadByte();
				// W trybie CFB nastepnym ciagiem strumienia szyfrujacego
				// jest wlasnie wczytany szyfrogram
				if (this->cipherMode_ == CipherMode::CFB)
					this->IV[j] = inBuffer[j];
				else
				// W trybie OFB jest nim zaszyfrowany ponownie wektor IV
					this->IV[j] = outBuffer[j];
				// xorujemy dane ze strumieniem
				inBuffer[j] ^= outBuffer[j];
			}
			// Zapisujemy wynik do pliku
			for (int j = 0; j < 16; j++)
			{
				fWriter->Write(inBuffer[j]);
			}
		}
		// Obsluga ostatniego bloku pliku (jak w ECB)

		for (int j = 0; j < 16; j++)
			inBuffer[j] = Convert::ToByte(this->IV[j]);
		algorithm.encrypt(inBuffer, outBuffer);
		for (int j = 0; j < 16; j++)
		{
				inBuffer[j] = fReader->ReadByte();
				inBuffer[j] ^= outBuffer[j];
		}	

		for (int j = 0; j < (int)originalLength - (int)(originalLength / 16) * 16; j++)
				fWriter->Write(inBuffer[j]);
		
		// Zamykamy pliki
		fReader->Close();
		fWriter->Close();
		return true;
	}
	catch ( EndOfStreamException^)
	{

		return false;
	}
	catch ( ... )
	{
		return false;
	}
}
