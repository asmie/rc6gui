// RC6.cpp : main project file.

#include "stdafx.h"
#include "frmGlowna.h"

using namespace RC6;

// Metoda main naszego programu.
// Od niej rozpoczyna sie wykonywanie calosci.
[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Ustawienie stylu wizualnego dla kontrolek
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Tworzymy okno glowne aplikacji
	Application::Run(gcnew frmGlowna());
	return 0;
}
