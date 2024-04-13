// Lab4_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include"ukrString.h"
#include<functional>
#include<crtdbg.h>
#include<fstream>
#include<vector>

namespace lab_funcs
{
	template<class Tout, class Tmsg>
	static Tout Input(const Tmsg& msg, std::function<Tout(std::string& str)> converter,
		std::function<bool(std::string& str, Tmsg& error)> validator = nullptr)
	{
		Tmsg error;

		std::string str;

		do
		{
			std::cout << msg << std::endl;

			std::getline(std::cin, str);

			if (!validator)
				break;

			if (validator(str, error))
				break;
			else
				std::cout << error << std::endl;

		} while (true);

		return converter(str);
	}
}

auto com_converter = [](std::string& str)->char
{
	return *str.c_str();
};

auto com_validator = [](std::string& str, strings::ukrString& error)->bool
{
	int res = 0;

	try
	{
		res = std::stoi(str);
	}
	catch (...)
	{
		error = "Невірний ввод!";
		return false;
	}

	if (res < 1 && res > 4)
	{
		error = "Невірний діапазон при введені команди!";
	}

	return true;
};

auto size_validator = [](std::string& str, strings::ukrString& error) ->bool
{
	int res = 0;
	try
	{
		res = std::stoi(str);
	}
	catch (...)
	{
		error = "Невірний ввод!";
		return false;
	}

	if (res <= 0)
	{
		error = "Кількість рядків не може бути 0 або від'ємним числом!";
		return false;
	}

	return true;
};

int main()
{
	using namespace lab_funcs;
    using namespace strings;
    using namespace std;

	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);

    cout << ukrString("Лабораторна робота номер 4") << endl;

	char path[] = "..\\Data\\data.txt";

	char key;

	for (; ;)
	{
		key = Input<char, ukrString>(ukrString("\n\nВиберіть опцію:\n \t-1 -> Виконати стандартне завдання. \n\t-2 -> Виконати завдання за варіантом. \n\t-3 -> Вийти з програмии. \n\t-4 -> Повторити цикл."),
			com_converter, com_validator);

		ifstream in_file_str;
		

		switch (key)
		{
		case '1':

			in_file_str.open(path);

			if (!in_file_str)
				cout << ukrString("Помилка при відкритті файлу!") << endl;
			else
			{
				vector<int> words_in_each_row;

				int rows = 0;
				
				strings::ukrString::wordSet word_array;

				char delim[] = { ' ' };

				//File read cycle
				while (!in_file_str.eof())
				{
					ukrString str;

					ukrString::getLine(in_file_str, str);

					ukrString::Split(str, word_array, delim);
					
					words_in_each_row.push_back(word_array.size());
					
					++rows;
				}

				cout << ukrString("Результат:") << endl;

				cout << ukrString("Число рядків: ") + ukrString(rows) << endl;

				cout << ukrString("Докладний аналіз: ") << endl;

				int size = words_in_each_row.size();

				for (size_t i = 0; i < size; i++)
				{
					cout << ukrString("В рядку номер ") + ukrString((int)i+1) + ukrString(" Виявлено: ") + ukrString(words_in_each_row[i]) + ukrString(" слова. ") << endl;
				}
			}

			break;
		case '2':
			break;					
		}

		if (key == '3') break;
	}

    return 0;
}


