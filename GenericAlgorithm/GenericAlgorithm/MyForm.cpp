#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace std;

[STAThreadAttribute]

int main()
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();

	GenericAlgorithm::MyForm  form;

	Application::Run(% form);


}