#include "gameengine.h"
#include <QtWidgets/QApplication>

void SetupConsoleWindow()
{
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;
}

int main(int argc, char *argv[])
{
	SetupConsoleWindow();

	cout<<"Successfully Loaded Console Window"<<endl;

	QApplication *a;
	a = new QApplication(argc, argv);
	GameEngine *w;
	w = new GameEngine();
	w->show();
	a->exec();

	SAFE_DELETE(a);
	SAFE_DELETE(w);

	system("pause");
	return 0;
}
