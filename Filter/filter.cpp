#include"filter.h"

Filter::Filter():
english(false), 
russian(false),
numbers(false),
punctuation(false),
replacement(1U),
str(nullptr)
{
	loadSystem();
}

Filter::~Filter()
{
	delete str;
}

void Filter::menu()
{
	int code = 0;
	while (true)
	{
		// цыкл меню
		cout << "Filters: " 
			<< "\nEnglish - " << (english ? "on" : "off")
			<< "\nRussian - " << (russian ? "on" : "off")
			<< "\nNumbers - " << (numbers ? "on" : "off")
			<< "\nPunctuation - " << (punctuation ? "on" : "off")
			<< endl << endl;

		print();
		cout << "1 - button English"
			<< "\n2 - button Russian"
			<< "\n3 - button Numbers"
			<< "\n4 - button Punctuation"
			<< "\n5 - Enter your sentense"
			<< "\n6 - button load user sentense"
			<< "\n7 - button load system sentense"
			<< "\nEsc - button Exit" 
			<< "\nPress button: ";
			
		code = _getch();

		if (code == 27) // ESC = 27
		{
			system("cls");
			break;
		}
		else if (code >= 49 && code <= 52)	//49 = 1, 52 = 4  
		{
			system("cls");

			if (code == 49) 		// 1
				english ? english = false : english = true;
			else if (code == 50)	// 2
				russian ? russian = false : russian = true;
			else if (code == 51)	// 3
				numbers ? numbers = false : numbers = true;
			else if (code == 52)	// 4
				punctuation ? punctuation = false : punctuation = true;
		}
		else if (code == 53)	// 53 = 5  
		{
			char buff[400] = {};
			cout << "\n\nEnter your sentence: ";		
			cin.getline(buff,sizeof(buff));
			*str = buff;
			system("cls");
			save();
		}
		else if (code == 54 || code == 55)	// 54 = 6, 55 = 7 
		{
			system("cls");
			code == 54 ? loadUser() : loadSystem();
		}
		else system("cls");
	} 
}
void Filter::save()const
{
	ofstream out("user.txt");
	// Если файл удалось открыть.
	if (out.is_open())
	{
		out << *str;
		// Закрытие файлового потока.
		out.close();
	}
}
void Filter::loadUser()
{
	ifstream in("user.txt");

	if (str != nullptr) delete str;
	str = new string;

	// Если файл удалось открыть.
	if (in.is_open())
	{
		const int size = 300;
		do
		{
			char buffer[size] = {};
			in.getline(buffer, size);
			*str += buffer;
			*str += '\n';
		} while (in); // Цикл продолжается до тех пор, пока не наступит конец файла.

		// Закрытие файлового потока.
		in.close();
	}
	else  cout << "Could not open the file\n";
}
void Filter::loadSystem()
{
	ifstream in("system.txt");

	if (str != nullptr) delete str;
	str = new string;

	// Если файл удалось открыть.
	if (in.is_open())
	{
		const int size = 300;
		do
		{
			char buffer[size] = {};
			in.getline(buffer, size);
			*str += buffer;
			*str += '\n';
		} while (in); // Цикл продолжается до тех пор, пока не наступит конец файла.

		// Закрытие файлового потока.
		in.close();
	}
	else  cout << "Could not open the file\n";
}
void Filter::print() const
{
	bool was = false;
	unsigned int size = (*str).length();
	for (unsigned int i = 0U; i < size; ++i)
	{
		was = false;
		
		if (english && (((*str)[i] >= 65 && (*str)[i] <= 90) || ((*str)[i] >= 97 && (*str)[i] <= 122))) // 65 to 90 big letters, // 97 to 122 small letters 	
			was = true;
		else if (russian && ((*str)[i] >= char(192) && (*str)[i] <= char(255))) 
			was = true;
		else if (numbers && ((*str)[i] >= 48 && (*str)[i] <= 57)) 
			was = true;
		else if (punctuation && ((*str)[i] == 44 || (*str)[i] == 45 || (*str)[i] == 46 || (*str)[i] == 58 || (*str)[i] == 59)) // . , - ; :
			was = true;
			
		was ? cout << replacement : cout << (*str)[i];
	}
	cout << endl;
}