#include "Console.h"

void Console::displayError(string errorMsg)
{
	out(errorMsg.c_str(), COLOR::RED);
}

void Console::displaySuccess(string successMsg)
{
	out(successMsg.c_str(), COLOR::GREEN);
}

void Console::newLine()
{
	cout << endl;
}

void Console::pause()
{
	out("Aby kontynuowaÊ, naciúnij dowolny klawisz...\n", COLOR::YELLOW);
	cin.get();
}

#ifdef _WIN32
void Console::out(const char * text, COLOR color)
{
	SetConsoleTextAttribute(hConsole, color);
	string result;
	for (; *text; text++)
		switch (*text)
		{
		case 'π': result += static_cast < char >(0xa5); break;
		case 'Ê': result += static_cast < char >(0x86); break;
		case 'Í': result += static_cast < char >(0xa9); break;
		case '≥': result += static_cast < char >(0x88); break;
		case 'Ò': result += static_cast < char >(0xe4); break;
		case 'Û': result += static_cast < char >(0xa2); break;
		case 'ú': result += static_cast < char >(0x98); break;
		case 'ø': result += static_cast < char >(0xbe); break;
		case 'ü': result += static_cast < char >(0xab); break;
		case '•': result += static_cast < char >(0xa4); break;
		case '∆': result += static_cast < char >(0x8f); break;
		case ' ': result += static_cast < char >(0xa8); break;
		case '£': result += static_cast < char >(0x9d); break;
		case '—': result += static_cast < char >(0xe3); break;
		case '”': result += static_cast < char >(0xe0); break;
		case 'å': result += static_cast < char >(0x97); break;
		case 'Ø': result += static_cast < char >(0xbd); break;
		case 'è': result += static_cast < char >(0x8d); break;
		default: result += *text; break;
		}
	cout << result;
}

void Console::clear()
{
	system("cls");
}
#elif __linux__
void Console::out(const char * text, COLOR color)
{
	string result;
	for (; *text; text++)
		switch (*text)
		{
		case 'π': result += static_cast < char >(0xa5); break;
		case 'Ê': result += static_cast < char >(0x86); break;
		case 'Í': result += static_cast < char >(0xa9); break;
		case '≥': result += static_cast < char >(0x88); break;
		case 'Ò': result += static_cast < char >(0xe4); break;
		case 'Û': result += static_cast < char >(0xa2); break;
		case 'ú': result += static_cast < char >(0x98); break;
		case 'ø': result += static_cast < char >(0xbe); break;
		case 'ü': result += static_cast < char >(0xab); break;
		case '•': result += static_cast < char >(0xa4); break;
		case '∆': result += static_cast < char >(0x8f); break;
		case ' ': result += static_cast < char >(0xa8); break;
		case '£': result += static_cast < char >(0x9d); break;
		case '—': result += static_cast < char >(0xe3); break;
		case '”': result += static_cast < char >(0xe0); break;
		case 'å': result += static_cast < char >(0x97); break;
		case 'Ø': result += static_cast < char >(0xbd); break;
		case 'è': result += static_cast < char >(0x8d); break;
		default: result += *text; break;
		}
	cout << "\033[" << color << "m" << result;
}

void Console::clear()
{
	system("clear");
}
#elif __APPLE__
void Console::out(const char * text, COLOR color)
{
	string result;
	for (; *text; text++)
		switch (*text)
		{
		case 'π': result += static_cast < char >(0xa5); break;
		case 'Ê': result += static_cast < char >(0x86); break;
		case 'Í': result += static_cast < char >(0xa9); break;
		case '≥': result += static_cast < char >(0x88); break;
		case 'Ò': result += static_cast < char >(0xe4); break;
		case 'Û': result += static_cast < char >(0xa2); break;
		case 'ú': result += static_cast < char >(0x98); break;
		case 'ø': result += static_cast < char >(0xbe); break;
		case 'ü': result += static_cast < char >(0xab); break;
		case '•': result += static_cast < char >(0xa4); break;
		case '∆': result += static_cast < char >(0x8f); break;
		case ' ': result += static_cast < char >(0xa8); break;
		case '£': result += static_cast < char >(0x9d); break;
		case '—': result += static_cast < char >(0xe3); break;
		case '”': result += static_cast < char >(0xe0); break;
		case 'å': result += static_cast < char >(0x97); break;
		case 'Ø': result += static_cast < char >(0xbd); break;
		case 'è': result += static_cast < char >(0x8d); break;
		default: result += *text; break;
		}
	cout << "\x1b[" << color << "m" << result;
}

void Console::clear()
{
	system("clear");
}
#endif
