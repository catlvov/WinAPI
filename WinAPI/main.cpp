
#include <windows.h>

INT WINAPI WinMain(HINSTANCE hinstance, HINSTANCE HPrevInst, LPSTR IpCmdLine, INT nCmsShow)
{
	MessageBox(NULL, "Привет мир!", "Hello!!",
		MB_YESNOCANCEL |
		MB_HELP |
		MB_ICONINFORMATION |
		MB_DEFBUTTON3 |
		MB_SYSTEMMODAL
	);
	return 0;
}