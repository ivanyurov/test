#include"boolexpr.h"

long long StrToInt(std::string a)  //converts string to int
{
	try
	{
		if (((a[0] == '-') && ((a[1] >= '0') && (a[1] <= '9'))) || ((a[0] >= '0') && (a[0] <= '9')))
		{
			long long res = 0;
			int lengthCounter = 0;
			bool minus = 0;
			if (a[0] == '-')
			{
				++lengthCounter;
				minus = 1;
			}
			while (a[lengthCounter] >= '0' && a[lengthCounter] <= '9') { ++lengthCounter; }
			long long grade = 1;
			for (int i = lengthCounter; i > (int)minus; --i)
			{
				res += ((long long)a[i - 1] - (long long)'0') * grade;
				grade *= 10;
			}
			return ((minus == 1) ? -res : res);
		}
		else
		{
			throw 1;
			return 0;
		}
	}
	catch (int a)
	{
		std::cout << "Error with variables";
	}
}

void math(std::vector<bool_>& num_, std::vector<char>& operations_)  //supporting function for calculator
{
	try
	{
		bool_ a, b, c;
		a = num_.back();
		num_.pop_back();
		switch (operations_.back())
		{
		case'&':
			b = num_.back();
			num_.pop_back();
			c = a & b;
			num_.push_back(c);
			operations_.pop_back();
			break;
		case'v':
			b = num_.back();
			num_.pop_back();
			c = a - b;
			num_.push_back(c);
			operations_.pop_back();
			break;
		case'~':
			c = ~a;
			num_.push_back(c);
			operations_.pop_back();
			break;
		case'>':
			b = num_.back();
			num_.pop_back();
			c = a > b;
			num_.push_back(c);
			operations_.pop_back();
			break;
		case'<':
			b = num_.back();
			num_.pop_back();
			c = a < b;
			num_.push_back(c);
			operations_.pop_back();
			break;
		case'+':
			b = num_.back();
			num_.pop_back();
			c = a + b;
			num_.push_back(c);
			operations_.pop_back();
			break;
		case'|':
			b = num_.back();
			num_.pop_back();
			c = a | b;
			num_.push_back(c);
			operations_.pop_back();
			break;
		case'^':
			b = num_.back();
			num_.pop_back();
			c = a ^ b;
			num_.push_back(c);
			operations_.pop_back();
			break;
		case'=':
			b = num_.back();
			num_.pop_back();
			c.value_ = (a.value_ == b.value_);
			num_.push_back(c);
			operations_.pop_back();
			break;
		default:
			throw 1;
			break;
		}
	}
	catch (int a)
	{
		std::cout << "Wrong expression\n";
	}
}

bool_ boolCalculator(std::string x)  //returns value of bool expression with '0' and '1'
{

	std::vector<bool_> num;  //"stack" of numbers
	std::vector<char> operations;  //"stack" of operations
	char ch;
	int counter = 0;
	try
	{
		for (int i = 0; i < x.size(); ++i)
		{
			if (x[i] == '(') { ++counter; }
			if (x[i] == ')') { --counter; }
			if (counter < 0) { throw 1; }
		}
		if (counter > 0) { throw 1; }
	}
	catch (int a) { std::cout << "Wrong brackets\n"; }
	try
	{
		for (int i = 0; i < x.size(); ++i)
		{
			ch = x[i];
			if ((ch == '0') || (ch == '1'))
			{
				if (ch == '0') { num.push_back(0); }
				if (ch == '1') { num.push_back(1); }
				continue;
			}
			else if ((ch == '&') || (ch == 'v') || (ch == '~') || (ch == '>') || (ch == '<') || (ch == '+') ||
				(ch == '|') || (ch == '^') || (ch == '='))
			{
				if (operations.size() == 0)
				{
					operations.push_back(ch);
				}
				else if ((operations.size() != 0) && (priority(ch) <= priority(operations.back())))
				{
					operations.push_back(ch);
				}
				else if ((operations.size() != 0) && (priority(ch) > priority(operations.back())))
				{
					while ((operations.size() != 0) && (priority(ch) > priority(operations.back())))
					{
						math(num, operations);
					}
					operations.push_back(ch);
				}
				continue;
			}
			else if (ch == '(')
			{
				try
				{
					if ((x[i + 1] == '1') || (x[i + 1] == '0') || (x[i + 1] == '~'))
					{
						operations.push_back(ch);
						continue;
					}
					else { throw 1; }
				}
				catch (int a) { std::cout << "Wrong expression in brackets\n"; }
			}
			else if (ch == ')')
			{
				try
				{
					if ((x[i - 1] == '1') || (x[i - 1] == '0'))
					{
						while (operations.back() != '(')
						{
							math(num, operations);
						}
						operations.pop_back();
						continue;
					}
					else { throw 3; }
				}
				catch (int a) { std::cout << "Wrong expression in brackets\n"; }
			}
			else if (ch == ' ')
			{
				continue;
			}
			else
			{
				throw 1;
			}
		}
	}
	catch (int a) { std::cout << "Wrong sybmol\n"; }
	while (operations.size() != 0)
	{
		math(num, operations);
	}
	return num[0];
}

int priority(char x)  //returns priority of operations
{
	if (x == '~') { return 1; }
	if (x == '&') { return 2; }
	if ((x == 'v') || (x == '+') || (x == '|') || (x == '^')) { return 3; }
	if ((x == '>') || (x == '<') || (x == '=')) { return 4; }
}

bool isFullSystem(std::vector<BooleanExpression> x)  //checks if system of functions is full, using Post's criterion
{
	int flag = 0;
	for (int i = 0; i < x.size(); ++i)  //checks if functions keep 0
	{
		if (x[i].getValue(0).getValue() == 1) { ++flag; }
	}
	if (flag < 1) return 0;
	flag = 0;
	for (int i = 0; i < x.size(); ++i)  //checks if functions keep 1
	{
		if (x[i].getValue(x[i].getLength() - 1).getValue() == 0) { ++flag; }
	}
	if (flag < 1) return 0;
	for (int i = 0; i < x.size(); ++i)  //checks if functions are monotonous
	{
		for (int j = 0; j < x[i].getLength() - 1; ++j)
		{
			if (x[i].getValue(j + 1).getValue() < x[i].getValue(j).getValue()) { ++flag; }
		}
	}
	if (flag < 1) return 0;
	flag = 0;
	for (int i = 0; i < x.size(); ++i)  //checks if finctions are self-dual
	{
		for (int j = x[i].getLength() / 2 - 1; j >= 0; --j)
		{
			if (x[i].getValue(j).getValue() == x[i].getValue(x[i].getLength() - j - 1).getValue()) { ++flag; }
		}
	}
	if (flag < 1) return 0;
	flag = 0;
	for (int i = 0; i < x.size(); ++i)  //checks if functions are linear
	{
		bool s;
		x[i].zhegalkin(s);
		if (!s) ++flag;
	}
	if (flag < 1) return 0;
	return 1;
}


std::istream& operator>>(std::istream& in, bool_& x)
{
	bool tmp;
	std::cin >> tmp;
	x.value_ = tmp;
	return in;
}

std::ostream& operator<<(std::ostream& out, bool_& x)
{
	std::cout << x.value_;
	return out;
}

std::ofstream& operator<<(std::ofstream out, bool_& x)
{
	out << x.getValue();
	return out;
}

std::ostream& operator<<(std::ostream& out, BooleanExpression& x)
{
	for (int i = 0; i < x.getLength(); ++i)
	{
		bool_ tmp = x.getValue(i);
		std::cout << tmp << " ";
	}
	return out;
}