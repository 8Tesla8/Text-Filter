#include <iostream>
#include <string>
#include <fstream>
#include <conio.h> //getch here
using namespace std;

class Filter
{
	bool english;
	bool russian;
	bool numbers;
	bool punctuation;
	char replacement;
	string *str;

	void loadSystem();
	void loadUser();
	void save() const;
	void print() const;

public:
	Filter();
	~Filter();
	void menu();
};