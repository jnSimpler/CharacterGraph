#include "MyForm.h"
#include "ImageVSText.h"
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"main\"" )
//define entry point

using namespace ImageVSText;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew MyForm());

	return 0;
}