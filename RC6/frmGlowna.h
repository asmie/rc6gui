// Kod generowany autmatycznie przez Visual C++
// Koniec autmatycznego kodu jest oznaczony

#pragma once
#include "RC6algo.h"
#include "aboutBox.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace RC6 {

	/// <summary>
	/// Summary for frmGlowna
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class frmGlowna : public System::Windows::Forms::Form
	{
	public:
		frmGlowna(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmGlowna()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  plikToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  zako?czToolStripMenuItem;




	private: System::Windows::Forms::ToolStripMenuItem^  pomocToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  oProgramieToolStripMenuItem;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txtPlikWejsciowy;
	private: System::Windows::Forms::Button^  btnPrzegladaj;
	private: System::Windows::Forms::TextBox^  txtPlikWyjsciowy;
	private: System::Windows::Forms::Button^  btnPrzegladajWyj;
	private: System::Windows::Forms::OpenFileDialog^  dlgWejscie;
	private: System::Windows::Forms::SaveFileDialog^  dlgWyjscie;
	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::Button^  btnWykonaj;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  rDeszyfruj;

	private: System::Windows::Forms::RadioButton^  rSzyfruj;

	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  klucz;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  klucz2;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::ComboBox^  wyborTrybu;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::ComboBox^  dlugosc_Klucza;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->plikToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zako?czToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pomocToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->oProgramieToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtPlikWejsciowy = (gcnew System::Windows::Forms::TextBox());
			this->btnPrzegladaj = (gcnew System::Windows::Forms::Button());
			this->txtPlikWyjsciowy = (gcnew System::Windows::Forms::TextBox());
			this->btnPrzegladajWyj = (gcnew System::Windows::Forms::Button());
			this->dlgWejscie = (gcnew System::Windows::Forms::OpenFileDialog());
			this->dlgWyjscie = (gcnew System::Windows::Forms::SaveFileDialog());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btnWykonaj = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->rDeszyfruj = (gcnew System::Windows::Forms::RadioButton());
			this->rSzyfruj = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->klucz = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->klucz2 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->wyborTrybu = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->dlugosc_Klucza = (gcnew System::Windows::Forms::ComboBox());
			this->menuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->plikToolStripMenuItem,
					this->pomocToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(695, 30);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// plikToolStripMenuItem
			// 
			this->plikToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->zako?czToolStripMenuItem });
			this->plikToolStripMenuItem->Name = L"plikToolStripMenuItem";
			this->plikToolStripMenuItem->Size = System::Drawing::Size(46, 26);
			this->plikToolStripMenuItem->Text = L"&File";
			// 
			// zako?czToolStripMenuItem
			// 
			this->zako?czToolStripMenuItem->Name = L"zako?czToolStripMenuItem";
			this->zako?czToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->zako?czToolStripMenuItem->Text = L"&Quit";
			this->zako?czToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmGlowna::zako?czToolStripMenuItem_Click);
			// 
			// pomocToolStripMenuItem
			// 
			this->pomocToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->oProgramieToolStripMenuItem });
			this->pomocToolStripMenuItem->Name = L"pomocToolStripMenuItem";
			this->pomocToolStripMenuItem->Size = System::Drawing::Size(55, 26);
			this->pomocToolStripMenuItem->Text = L"&Help";
			// 
			// oProgramieToolStripMenuItem
			// 
			this->oProgramieToolStripMenuItem->Name = L"oProgramieToolStripMenuItem";
			this->oProgramieToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->oProgramieToolStripMenuItem->Text = L"&About";
			this->oProgramieToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmGlowna::oProgramieToolStripMenuItem_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 45);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Input file:";
			// 
			// txtPlikWejsciowy
			// 
			this->txtPlikWejsciowy->Enabled = false;
			this->txtPlikWejsciowy->Location = System::Drawing::Point(16, 65);
			this->txtPlikWejsciowy->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtPlikWejsciowy->Name = L"txtPlikWejsciowy";
			this->txtPlikWejsciowy->Size = System::Drawing::Size(520, 22);
			this->txtPlikWejsciowy->TabIndex = 2;
			// 
			// btnPrzegladaj
			// 
			this->btnPrzegladaj->Location = System::Drawing::Point(559, 60);
			this->btnPrzegladaj->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnPrzegladaj->Name = L"btnPrzegladaj";
			this->btnPrzegladaj->Size = System::Drawing::Size(120, 33);
			this->btnPrzegladaj->TabIndex = 3;
			this->btnPrzegladaj->Text = L"Browse";
			this->btnPrzegladaj->UseVisualStyleBackColor = true;
			this->btnPrzegladaj->Click += gcnew System::EventHandler(this, &frmGlowna::btnPrzegladaj_Click);
			// 
			// txtPlikWyjsciowy
			// 
			this->txtPlikWyjsciowy->Enabled = false;
			this->txtPlikWyjsciowy->Location = System::Drawing::Point(16, 138);
			this->txtPlikWyjsciowy->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtPlikWyjsciowy->Name = L"txtPlikWyjsciowy";
			this->txtPlikWyjsciowy->Size = System::Drawing::Size(520, 22);
			this->txtPlikWyjsciowy->TabIndex = 4;
			// 
			// btnPrzegladajWyj
			// 
			this->btnPrzegladajWyj->Location = System::Drawing::Point(559, 133);
			this->btnPrzegladajWyj->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnPrzegladajWyj->Name = L"btnPrzegladajWyj";
			this->btnPrzegladajWyj->Size = System::Drawing::Size(120, 33);
			this->btnPrzegladajWyj->TabIndex = 5;
			this->btnPrzegladajWyj->Text = L"Browse";
			this->btnPrzegladajWyj->UseVisualStyleBackColor = true;
			this->btnPrzegladajWyj->Click += gcnew System::EventHandler(this, &frmGlowna::btnPrzegladajWyj_Click);
			// 
			// dlgWejscie
			// 
			this->dlgWejscie->FileName = L"openFileDialog1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 118);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(68, 16);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Output file:";
			// 
			// btnWykonaj
			// 
			this->btnWykonaj->Location = System::Drawing::Point(552, 335);
			this->btnWykonaj->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnWykonaj->Name = L"btnWykonaj";
			this->btnWykonaj->Size = System::Drawing::Size(121, 37);
			this->btnWykonaj->TabIndex = 8;
			this->btnWykonaj->Text = L"Execute";
			this->btnWykonaj->UseVisualStyleBackColor = true;
			this->btnWykonaj->Click += gcnew System::EventHandler(this, &frmGlowna::btnWykonaj_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rDeszyfruj);
			this->groupBox1->Controls->Add(this->rSzyfruj);
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Location = System::Drawing::Point(20, 212);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->groupBox1->Size = System::Drawing::Size(276, 119);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Operation type";
			// 
			// rDeszyfruj
			// 
			this->rDeszyfruj->AutoSize = true;
			this->rDeszyfruj->Enabled = false;
			this->rDeszyfruj->Location = System::Drawing::Point(8, 85);
			this->rDeszyfruj->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->rDeszyfruj->Name = L"rDeszyfruj";
			this->rDeszyfruj->Size = System::Drawing::Size(75, 20);
			this->rDeszyfruj->TabIndex = 2;
			this->rDeszyfruj->TabStop = true;
			this->rDeszyfruj->Text = L"Decrypt";
			this->rDeszyfruj->UseVisualStyleBackColor = true;
			// 
			// rSzyfruj
			// 
			this->rSzyfruj->AutoSize = true;
			this->rSzyfruj->Enabled = false;
			this->rSzyfruj->Location = System::Drawing::Point(8, 57);
			this->rSzyfruj->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->rSzyfruj->Name = L"rSzyfruj";
			this->rSzyfruj->Size = System::Drawing::Size(73, 20);
			this->rSzyfruj->TabIndex = 1;
			this->rSzyfruj->TabStop = true;
			this->rSzyfruj->Text = L"Encrypt";
			this->rSzyfruj->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(11, 25);
			this->checkBox1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(150, 20);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = L"Detect automatically";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &frmGlowna::checkBox1_CheckedChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->ForeColor = System::Drawing::Color::Red;
			this->label4->Location = System::Drawing::Point(376, 220);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(66, 16);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Enter key:";
			this->label4->Visible = false;
			// 
			// klucz
			// 
			this->klucz->Location = System::Drawing::Point(380, 240);
			this->klucz->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->klucz->MaxLength = 32;
			this->klucz->Name = L"klucz";
			this->klucz->Size = System::Drawing::Size(292, 22);
			this->klucz->TabIndex = 11;
			this->klucz->UseSystemPasswordChar = true;
			this->klucz->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->ForeColor = System::Drawing::Color::Red;
			this->label5->Location = System::Drawing::Point(376, 268);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(103, 16);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Enter key again:";
			this->label5->Visible = false;
			// 
			// klucz2
			// 
			this->klucz2->Location = System::Drawing::Point(380, 293);
			this->klucz2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->klucz2->MaxLength = 32;
			this->klucz2->Name = L"klucz2";
			this->klucz2->Size = System::Drawing::Size(296, 22);
			this->klucz2->TabIndex = 13;
			this->klucz2->UseSystemPasswordChar = true;
			this->klucz2->Visible = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(19, 173);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(45, 16);
			this->label6->TabIndex = 14;
			this->label6->Text = L"Mode:";
			// 
			// wyborTrybu
			// 
			this->wyborTrybu->FormattingEnabled = true;
			this->wyborTrybu->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"ECB", L"CBC", L"CFB", L"OFB" });
			this->wyborTrybu->Location = System::Drawing::Point(68, 170);
			this->wyborTrybu->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->wyborTrybu->Name = L"wyborTrybu";
			this->wyborTrybu->Size = System::Drawing::Size(151, 24);
			this->wyborTrybu->TabIndex = 15;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(380, 335);
			this->button1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(121, 37);
			this->button1->TabIndex = 16;
			this->button1->Text = L"Cancel";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &frmGlowna::button1_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(271, 175);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(72, 16);
			this->label7->TabIndex = 17;
			this->label7->Text = L"Key length:";
			// 
			// dlugosc_Klucza
			// 
			this->dlugosc_Klucza->FormattingEnabled = true;
			this->dlugosc_Klucza->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"16", L"32" });
			this->dlugosc_Klucza->Location = System::Drawing::Point(351, 170);
			this->dlugosc_Klucza->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->dlugosc_Klucza->Name = L"dlugosc_Klucza";
			this->dlugosc_Klucza->Size = System::Drawing::Size(185, 24);
			this->dlugosc_Klucza->TabIndex = 18;
			// 
			// frmGlowna
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(695, 387);
			this->Controls->Add(this->dlugosc_Klucza);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->wyborTrybu);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->klucz2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->klucz);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->btnWykonaj);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btnPrzegladajWyj);
			this->Controls->Add(this->txtPlikWyjsciowy);
			this->Controls->Add(this->btnPrzegladaj);
			this->Controls->Add(this->txtPlikWejsciowy);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->MaximizeBox = false;
			this->Name = L"frmGlowna";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"RC6GUI";
			this->Load += gcnew System::EventHandler(this, &frmGlowna::frmGlowna_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


// KONIEC kodu generowanego autmatycznie

		// Obsluga przycisku zakoncz z menu gornego - pytamy sie uzytkownika czy 
		// chce zakonczyc program, jesli tak to wylaczamy aplikacje
		private: System::Void zako?czToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			Windows::Forms::DialogResult res = MessageBox::Show("Confirm exit?", "RC6", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
			if (res == ::DialogResult::Yes)
				Application::Exit();
		}
	
		 // Obsluga ladowania glownego okna
		private: System::Void frmGlowna_Load(System::Object^  sender, System::EventArgs^  e) 
		{
			wyborTrybu->SelectedIndex = 0;		
			dlugosc_Klucza->SelectedIndex = 1;
		}

		// Obsluga zmiany rozpoznawania automatycznego
		private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			if (checkBox1->Checked)
			{
				rSzyfruj->Enabled = false;
				rDeszyfruj->Enabled = false;
			}
			else
			{
				rSzyfruj->Enabled = true;
				rDeszyfruj->Enabled = true;
				rSzyfruj->Checked = true;
			}
		}

		// Obsluga przycisku przegladania i wyboru pliku
		// Ustawiamy odpowiednie opcje oraz wyswietlamy standardowe okienko
		// Windows sluzace do wyboru pliku do otwarcia.
		private: System::Void btnPrzegladaj_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			dlgWejscie->CheckFileExists = true;
			dlgWejscie->CheckPathExists = true;
			dlgWejscie->Multiselect = false;
			dlgWejscie->RestoreDirectory = true;
			dlgWejscie->Filter = "RC6 files (*.rc6)|*.rc6|All files (*.*)|*.*";
			dlgWejscie->FilterIndex = 2;
			::DialogResult res = dlgWejscie->ShowDialog(this);
			if (res == ::DialogResult::OK)
			{
				txtPlikWejsciowy->Text =  dlgWejscie->FileName;
			}
		}

		// Obsluga przycisku przegladania i wyboru pliku
		// Ustawiamy odpowiednie opcje oraz wyswietlamy standardowe okienko
		// Windows sluzace do wyboru pliku tym razem do zapisu.
		private: System::Void btnPrzegladajWyj_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			dlgWyjscie->Filter = "RC6 files (*.rc6)|*.rc6|All files (*.*)|*.*";
			dlgWyjscie->FilterIndex = 2;
			dlgWyjscie->RestoreDirectory = true;
			if (dlgWyjscie->ShowDialog(this) == ::DialogResult::OK)
			{
				txtPlikWyjsciowy->Text = dlgWyjscie->FileName;
			}
		}

	    // Obsluga przycisku wykonaj
		private: System::Void btnWykonaj_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			// Sprawdzamy czy ustawiono pliki
			if (txtPlikWejsciowy->Text->Equals("") || txtPlikWyjsciowy->Text->Equals(""))
			{
				MessageBox::Show("You have to choose files!", "RC6", Windows::Forms::MessageBoxButtons::OK, Windows::Forms::MessageBoxIcon::Error);
				return;
			}

			// Jesli obslugujemy guzik De/Szyfruj to sprawdzamy czy
			// haslo jest wpisane oraz posiada wymagana dlugosc.
			if (btnWykonaj->Text->Equals("De/Szyfruj"))
			{
				if (klucz->Text->Equals("") || klucz->Text->IsNullOrEmpty(klucz->Text) || klucz->Text->Length < 8)
				{
					MessageBox::Show("Key has to be at least 8 chars long!", "RC6", Windows::Forms::MessageBoxButtons::OK, Windows::Forms::MessageBoxIcon::Error);
					return;
				}

				if (klucz2->Visible == true && !(klucz->Text->Equals(klucz2->Text)))
				{
					MessageBox::Show("Given keys are not the same!", "RC6", Windows::Forms::MessageBoxButtons::OK, Windows::Forms::MessageBoxIcon::Error);
					return;
				}

			}

			// Zmienna okreslajaca czy plik ma byc szyfrowany czy deszyfrowany
			bool CzySzyfrowac = true;

			// Sprawdzenie rozszerzenie - pliki rc6 raczej deszyfrujemy
			if (txtPlikWejsciowy->Text->EndsWith(".rc6", System::StringComparison::CurrentCultureIgnoreCase))
			{
				CzySzyfrowac = false;
			}
			else
			{
				// Sprawdzamy format pliku - jezeli pierwsze 5 bajtow
				// to RCRC6 to plik przeznaczamy do deszyfrowania
				::FileInfo^ fiPlik = gcnew FileInfo(txtPlikWejsciowy->Text);
				if (fiPlik->Length > 5)
				{
					unsigned char buff;
					::BinaryReader^ Czytnik = gcnew BinaryReader( File::Open(txtPlikWejsciowy->Text, FileMode::Open));
					String^ ID;
					buff = Czytnik->ReadByte();
					buff = Czytnik->ReadByte();
					buff = Czytnik->ReadByte();
					ID += ::Convert::ToChar(buff);
					buff = Czytnik->ReadByte();
					ID += ::Convert::ToChar(buff);
					buff = Czytnik->ReadByte();
					ID += ::Convert::ToChar(buff);
					buff = Czytnik->ReadByte();
					ID += ::Convert::ToChar(buff);
					buff = Czytnik->ReadByte();
					ID += ::Convert::ToChar(buff);
					Czytnik->Close();
					if (ID->Equals("RCRC6"))
						CzySzyfrowac = false;
				}
			}

			// Jezeli automatyczne rozpoznawanie jest wylaczone 
			// to wykonujemy opcje zaznaczona przez uzytkownika
			if (!checkBox1->Checked)
			{
				if (rSzyfruj->Checked)
					CzySzyfrowac = true;
				else
					CzySzyfrowac = false;
			}

			bool Wykonano = false;
			bool CzyDobrze = true;
			// W przypadku szyfrowania
			if (CzySzyfrowac)
			{
				label4->Visible = true;
				klucz->Visible = true;
				label5->Visible = true;
				klucz2->Visible = true;
				button1->Visible = true;
				btnPrzegladaj->Enabled = false;
				btnPrzegladajWyj->Enabled = false;
				if (btnWykonaj->Text->Equals("En/Decrypt"))
				{
					// Gdy klucz jest za krotki dodajemy znaki
					String^ sklucz;
					sklucz = klucz->Text;
					int dlugosc;
					dlugosc = System::Convert::ToInt32(dlugosc_Klucza->SelectedItem->ToString());
					for (int i = sklucz->Length; i <dlugosc; i++)
					{
						sklucz += "A";
					}

					// Szyfrujemy
					RC6algo^ obiekt = gcnew RC6algo(sklucz, dlugosc, static_cast<CipherMode>(wyborTrybu->SelectedIndex + 1));
					obiekt->Encrypt(txtPlikWejsciowy->Text, txtPlikWyjsciowy->Text);
					Wykonano = true;
				}
				btnWykonaj->Text = "En/Decrypt";
			}
			else
			{
				label4->Visible = true;
				klucz->Visible = true;
				button1->Visible = true;
				btnPrzegladaj->Enabled = false;
				btnPrzegladajWyj->Enabled = false;
				if (btnWykonaj->Text->Equals("En/Decrypt"))
				{
					// Gdy klucz jest za krotki dodajemy znaki
					String^ sklucz;
					sklucz = klucz->Text;
					for (int i = sklucz->Length; i <32; i++)
						sklucz += "A";

					// Deszyfrujemy
					RC6algo^ obiekt = gcnew RC6algo(sklucz,32, static_cast<CipherMode>(wyborTrybu->SelectedIndex + 1));
					CzyDobrze = obiekt->Decrypt(txtPlikWejsciowy->Text, txtPlikWyjsciowy->Text);
					Wykonano = true;
				}
				btnWykonaj->Text = "En/Decrypt";
			}

			// Jesli wykonano, ustawiamy formatke do pierwotnego wygladu

			if (btnWykonaj->Text->Equals("En/Decrypt") && Wykonano == true)
			{
				label4->Visible = false;
				klucz->Visible = false;
				label5->Visible = false;
				klucz2->Visible = false;
				btnPrzegladaj->Enabled = true;
				btnPrzegladajWyj->Enabled = true;
				klucz->Text = "";
				klucz2->Text = "";
				btnWykonaj->Text = "Execute";
				button1->Visible = false;
				if (CzyDobrze)
					MessageBox::Show("Operation has been executed correctly!", "RC6", Windows::Forms::MessageBoxButtons::OK, Windows::Forms::MessageBoxIcon::Information);
				else
					MessageBox::Show("Opeartion has been not executed due to the errors!", "RC6", Windows::Forms::MessageBoxButtons::OK, Windows::Forms::MessageBoxIcon::Error);

			}
		}

		// Obsluga guzika Anuluj, przywraca formatke do pierwotnego
		// widoku.
		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
		{
				label4->Visible = false;
				klucz->Visible = false;
				label5->Visible = false;
				klucz2->Visible = false;
				btnPrzegladaj->Enabled = true;
				btnPrzegladajWyj->Enabled = true;
				klucz->Text = "";
				klucz2->Text = "";
				btnWykonaj->Text = "Execute";
				button1->Visible = false;
		}

	    // Ladowanie formatki "O programie"
		private: System::Void oProgramieToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			RC6::aboutBox^ frmOprogramie = gcnew aboutBox();
			frmOprogramie->ShowDialog(this);
		}
};

}
