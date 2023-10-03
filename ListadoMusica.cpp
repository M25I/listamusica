using namespace System;
using namespace System::Windows::Forms;
#include "ListadoMusica.h"


[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ListadoMusica::ListadoMusica form;
	Application::Run(% form);
	return 0;
}