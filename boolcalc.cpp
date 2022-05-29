#include<iostream>
#include<fstream>
#include<vector>
#include"boolexpr.h"



int main(int argc, const char* argv[])
{
	std::vector<BooleanExpression> exprSystem;
	std::string x;
	if ((argv[1][1] == 'c')&&(argv[1][2] == 'a')&&(argv[1][3] == 'l')&&(argv[1][4] == 'c'))
	{
		std::ifstream in(argv[2]);
		if (!in.is_open())
		{
			std::cout << "Input file open error\n";
			return 1;
		}
		std::ofstream out(argv[3]);
		if (!out.is_open())
		{
			std::cout << "Output file open error \n";
			return 1;
		}
		while (std::getline(in, x))
		{
			exprSystem.push_back(x);
		}
		for (int i = 0; i < exprSystem.size(); ++i)
		{
			for (int j = 0; j < exprSystem[i].getLength(); ++j)
			{
				std::cout<< exprSystem[i].getValue(j).getValue()<< ' ';
				out << exprSystem[i].getValue(j).getValue();
			}
			std::cout << '\n';
			out << "\n";
		}
		in.close();
		out.close();
	}
	else if ((argv[1][1] == 'c') && (argv[1][2] == 'n') && (argv[1][3] == 'f'))
	{
		std::ifstream in(argv[2]);
		if (!in.is_open())
		{
			std::cout << "Input file open error\n";
			return 1;
		}
		std::ofstream out(argv[3]);
		if (!out.is_open())
		{
			std::cout << "Output file open error \n";
			return 1;
		}
		while (std::getline(in, x))
		{
			exprSystem.push_back(x);
		}
		for (int i = 0; i < exprSystem.size(); ++i)
		{
			BooleanExpression x = exprSystem[i].cnf();
			out << x.getExpr() << '\n';
		}
		in.close();
		out.close();
	}
	else if ((argv[1][1] == 'd') && (argv[1][2] == 'n') && (argv[1][3] == 'f'))
	{
		std::ifstream in(argv[2]);
		if (!in.is_open())
		{
			std::cout << "Input file open error\n";
			return 1;
		}
		std::ofstream out(argv[3]);
		if (!out.is_open())
		{
			std::cout << "Output file open error \n";
			return 1;
		}
		while (std::getline(in, x))
		{
			exprSystem.push_back(x);
		}
		for (int i = 0; i < exprSystem.size(); ++i)
		{
			BooleanExpression x = exprSystem[i].dnf();
			out << x.getExpr()<<'\n';
		}
		in.close();
		out.close();
	}
	else if ((argv[1][1] == 'z') && (argv[1][2] == 'h'))
	{
		std::ifstream in(argv[2]);
		if (!in.is_open())
		{
			std::cout << "Input file open error\n";
			return 1;
		}
		std::ofstream out(argv[3]);
		if (!out.is_open())
		{
			std::cout << "Output file open error \n";
			return 1;
		}
		while (std::getline(in, x))
		{
			exprSystem.push_back(x);
		}
		for (int i = 0; i < exprSystem.size(); ++i)
		{
			BooleanExpression x = exprSystem[i].zhegalkin();
			out << x.getExpr() << '\n';
		}
		in.close();
		out.close();
	}
	else if ((argv[1][1] == 't') && (argv[1][2] == 'a') && (argv[1][3] == 'b') && (argv[1][4] == 'l') && (argv[1][5] == 'e'))
	{
		std::ifstream in(argv[2]);
		if (!in.is_open())
		{
			std::cout << "Input file open error\n";
			return 1;
		}
		while (std::getline(in, x))
		{
			exprSystem.push_back(x);
		}
		for (int i = 0; i < exprSystem.size(); ++i)
		{
			exprSystem[i].truthTable();
			std::cout << std::endl;
		}
		in.close();
	}
	else if ((argv[1][1] == 'i') && (argv[1][2] == 's') && (argv[1][3] == 'f') && (argv[1][4] == 'u') && (argv[1][5] == 'l') && (argv[1][6] == 'l'))
	{
		std::ifstream in(argv[2]);
		if (!in.is_open())
		{
			std::cout << "Input file open error\n";
			return 1;
		}
		std::ofstream out(argv[3]);
		if (!out.is_open())
		{
			std::cout << "Output file open error \n";
			return 1;
		}
		while (std::getline(in, x))
		{
			exprSystem.push_back(x);
		}
		if (isFullSystem(exprSystem))
		{
			out << "yes";
		}
		else
		{
			out << "no";
		}
		in.close();
		out.close();
	}
	else if ((argv[1][0] == '?') || (argv[1][1] == 'h'))
	{
	std::cout << "-calc input output - calculates values of expressions in file\n\n";
	std::cout << "-cnf input outp  ut - prints CNFs of expressions in file\n\n";
	std::cout << "-dnf input output - prints DNFs of expressions in file\n\n";
	std::cout << "-zh input output - prints zhegalkin's polynomials of expressions in file\n\n";
	std::cout << "-table input - prints truth tables of expressions in cmd\n\n";
	std::cout << "-isfull input output - prints yes in file if system is full, else prints no\n\n";
	}
	else
	{
		std::cout << "Wrong command\n";
	}
	system("pause");
	return 0;
}
