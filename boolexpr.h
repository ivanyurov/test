#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>


class bool_  //class for easier work with variavles
{
public:
	bool value_;
	bool_(bool value = 1)
	{
		value_ = value;
	}
	bool_& operator&(const bool_& x)  // logical and
	{
		bool_ tmp;
		if ((this->getValue() == x.getValue()) && (x.getValue() == 1)) {}
		else { tmp.value_ = 0; }
		return tmp;
	}
	bool_& operator-(const bool_& x)  // logical or
	{
		bool_ tmp;
		if ((this->getValue() == x.getValue()) && (x.getValue() == 0)) { tmp.value_ = 0; }
		else {}
		return tmp;
	}
	bool_& operator~()  // logical not
	{
		this->value_ = !value_;
		return *this;
	}
	bool_& operator>(const bool_& x)  //implication
	{
		bool_ tmp;
		if (this->getValue() <= x.getValue()) {}
		else { tmp.value_ = 0; }
		return tmp;
	}
	bool_& operator<(const bool_& x)  //back implication
	{
		bool_ tmp;
		if (x.getValue() <= this->getValue()) {}
		else { tmp.value_ = 0; }
		return tmp;
	}
	bool_& operator+(const bool_& x)  // exclusive or
	{
		bool_ tmp;
		if (x.value_ != this->value_) {}
		else { tmp.value_ = 0; }
		return tmp;
	}
	bool_& operator|(const bool_& x)  //Scheffer's stroke
	{
		bool_ tmp;
		if ((this->value_ == x.value_) && (x.value_ == 0)) {}
		else { tmp.value_ = 0; }
		return tmp;
	}
	bool_& operator^(const bool_& x)  //Pierce arrow
	{
		bool_ tmp;
		if ((this->getValue() == x.getValue()) &&  (x.getValue() == 0)) {}
		else { tmp.value_ = 0; }
		return tmp;
	}
	bool getValue() const { return value_; }
};

std::istream& operator>>(std::istream& in, bool_& x);
std::ostream& operator<<(std::ostream& out, bool_& x);
std::ofstream& operator<<(std::ofstream out, bool_& x);

long long StrToInt(std::string a);
bool_ boolCalculator(std::string x);
void math(std::vector<bool_>& num_, std::vector<char>& operations_);
int priority(char x);


class BooleanExpression
{
	bool isConst_;
	int count_;
	int length_;
	std::string expr_;
	std::vector<bool_> function_;
public:
	BooleanExpression(const char* expr)
	{
		expr_ = expr;
		std::string tmp(expr);
		isConst_ = 1;
		int count = 0;  //number of variables
		for (int i = 0; i < tmp.size(); ++i)  //counts number of variables
		{
			if (tmp[i] == 'x')
			{
				int a = i + 1;
				std::string number;
				while ((a < tmp.size()) && (tmp[a] >= '0') && (tmp[a] <= '9'))
				{
					number.push_back(tmp[a]);
					++a;
				}
				a = StrToInt(number);
				if (a > count) { count = a; }
			}
		}
		if (count == 0)  //if function is simple const
		{
			std::vector<bool_> function(2);
			function[0] = boolCalculator(tmp);
			function[1] = boolCalculator(tmp);
			function_ = function;
			count_ = 1;
			length_ = 2;
			isConst_ = 1;
		}
		else
		{
			count_ = count;
			std::vector<std::vector<int>> pos(count);  //array that keep positions of every variable in expression string
			for (int i = 0; i < tmp.size(); ++i)  //checks positions of variables and change them to 0's in string
			{
				if (tmp[i] == 'x')
				{
					int a = i + 1;
					tmp[i] = '0';
					std::string number;
					while ((a < tmp.size()) && (tmp[a] >= '0') && (tmp[a] <= '9'))
					{
						number.push_back(tmp[a]);
						tmp.erase(a, 1);
					}
					a = StrToInt(number)-1;
					pos[a].push_back(i);
				}
			}
			int length = pow(2, count);  //length of function
			length_ = length;
			std::vector<bool_> function(length);
			bool* rank = new bool[count];  //array for enumeration of variables' values
			function[0] = boolCalculator(tmp);
			for (int i = 1; i < length; ++i)
			{
				for (int j = count - 1; j >= 0; --j)  //takes bytes from number to generate values of variables
				{
					rank[j] = i & (int)pow(2, (count - 1) - j);
				}
				for (int j = 0; j < count; ++j)  //substitutes the values of variables in function
				{
					for (int k = 0; k < pos[j].size(); ++k)
					{
						tmp[pos[j][k]] = '0' + rank[j];
					}
				}
				function[i] = boolCalculator(tmp);
			}
			delete[] rank;
			function_ = function;
			for (int i = 0; i < length_ - 1; ++i)  //checks if function is complex const
			{
				if (function_[i].getValue() != function_[i + 1].getValue()) isConst_ = 0;
			}
		}
	}

	BooleanExpression(std::string expr)
	{
		expr_ = expr;
		std::string tmp(expr);
		isConst_ = 1;
		int count = 0;  //number of variables
		for (int i = 0; i < tmp.size(); ++i)  //counts number of variables
		{
			if (tmp[i] == 'x')
			{
				int a = i + 1;
				std::string number;
				while ((a < tmp.size()) && (tmp[a] >= '0') && (tmp[a] <= '9'))
				{
					number.push_back(tmp[a]);
					++a;
				}
				a = StrToInt(number);
				if (a > count) { count = a; }
			}
		}
		if (count == 0)  //if function is simple const
		{
			std::vector<bool_> function(2);
			function[0] = boolCalculator(tmp);
			function[1] = boolCalculator(tmp);
			function_ = function;
			count_ = 1;
			length_ = 2;
			isConst_ = 1;
		}
		else
		{
			count_ = count;
			std::vector<std::vector<int>> pos(count);  //array that keep positions of every variable in expression string
			for (int i = 0; i < tmp.size(); ++i)  //checks positions of variables and change them to 0's in string
			{
				if (tmp[i] == 'x')
				{
					int a = i + 1;
					tmp[i] = '0';
					std::string number;
					while ((a < tmp.size()) && (tmp[a] >= '0') && (tmp[a] <= '9'))
					{
						number.push_back(tmp[a]);
						tmp.erase(a, 1);
					}
					a = StrToInt(number) - 1;
					pos[a].push_back(i);
				}
			}
			int length = pow(2, count);  //length of function
			length_ = length;
			std::vector<bool_> function(length);
			bool* rank = new bool[count];  //array for enumeration of variables' values
			function[0] = boolCalculator(tmp);
			for (int i = 1; i < length; ++i)
			{
				for (int j = count - 1; j >= 0; --j)  //takes bytes from number to generate values of variables
				{
					rank[j] = i & (int)pow(2, (count - 1) - j);
				}
				for (int j = 0; j < count; ++j)  //substitutes the values of variables in function
				{
					for (int k = 0; k < pos[j].size(); ++k)
					{
						tmp[pos[j][k]] = '0' + rank[j];
					}
				}
				function[i] = boolCalculator(tmp);
			}
			delete[] rank;
			function_ = function;
			for (int i = 0; i < length_ - 1; ++i)  //checks if function is complex const
			{
				if (function_[i].getValue() != function_[i + 1].getValue()) isConst_ = 0;
			}
		}
	}

	BooleanExpression(const BooleanExpression& x)
	{
		count_ = x.count_;
		isConst_ = x.isConst_;
		length_ = x.length_;
		expr_ = x.expr_;
		function_ = x.function_;
	}

	BooleanExpression& operator=(BooleanExpression& x)
	{
		if (&x != this)
		{
			return x;
		}
	}

	void truthTable()  //writes truth table in console	
	{
		int count = this->getCount();
		int length = this->getLength();
		bool* rank = new bool[count];
		for (int i = 0; i < count; ++i)
		{
			std::cout << 'x' << i+1 << '\t';
		}
		std::cout << "F\n";
		for (int i = 0; i < length; ++i)
		{
			for (int j = count - 1; j >= 0; --j)  //takes bytes from number to generate values of variables
			{
				rank[j] = i & (int)pow(2, (count - 1) - j);
			}
			for (int j = 0; j < count; ++j)
			{
				std::cout << rank[j] << '\t';
			}
			bool_ a = this->getValue(i);
			std::cout << a << "\n";
		}
		delete[] rank;
	}

	BooleanExpression cnf()  //creates cnf from function
	{
		if (isConst_ == 1)
		{
			std::cout << "Function is constant\n";
			return *this;
		}
		int count = this->getCount();
		int length = this->getLength();
		bool* rank = new bool[count];
		std::string cnf;
		int zeros = 0;
		int counter = 0;
		for (int i = 0; i < length; ++i) { if (this->getValue(i).getValue() == 0) { ++zeros; } }
		for (int i = 0; i < length; ++i)
		{
			if (this->getValue(i).getValue() == 0)
			{
				++counter;
				cnf.push_back('(');
				for (int j = count - 1; j >= 0; --j)  //takes bytes from number to generate values of variables
				{
					rank[j] = i & (int)pow(2, (count - 1) - j);
				}
				for (int j = 0; j < count; ++j)
				{
					if (rank[j]==0) 
					{
						cnf.push_back('x');
						cnf += std::to_string(j+1);
						if (j < count - 1)
						{
							cnf.push_back('v');
						}
					}
					else
					{
						cnf.push_back('~');
						cnf.push_back('x');
						cnf += std::to_string(j+1);
						if (j < count - 1)
						{
							cnf.push_back('v');
						}
					}
				}
				cnf.push_back(')');
				if (counter < zeros)
				{
					cnf.push_back('&');
				}
			}
		}
		delete[] rank;
		BooleanExpression a(cnf);
		return a;
	}

	BooleanExpression dnf()  //creates dnf from function
	{
		if (isConst_ == 1)
		{
			std::cout << "Function is constant\n";
			return *this;
		}
		int count = this->getCount();
		int length = this->getLength();
		bool* rank = new bool[count];
		std::string dnf;
		int ones = 0;
		int counter = 0;
		for (int i = 0; i < length; ++i) { if (this->getValue(i).getValue() == 1) { ++ones; } }
		for (int i = 0; i < length; ++i)
		{
			if (this->getValue(i).getValue() == 1)
			{
				++counter;
				dnf.push_back('(');
				for (int j = count - 1; j >= 0; --j)  //takes bytes from number to generate values of variables
				{
					rank[j] = i & (int)pow(2, (count - 1) - j);
				}
				for (int j = 0; j < count; ++j)
				{
					if (rank[j] == 0)
					{
						dnf.push_back('~');
						dnf.push_back('x');
						dnf += std::to_string(j+1);
						if (j < count - 1)
						{
							dnf.push_back('&');
						}
					}
					else
					{
						dnf.push_back('x');
						dnf += std::to_string(j+1);
						if (j < count - 1)
						{
							dnf.push_back('&');
						}
					}
				}
				dnf.push_back(')');
				if (counter < ones)
				{
					dnf.push_back('v');
				}
			}
		}
		delete[] rank;
		BooleanExpression a(dnf);
		return a;
	}

	BooleanExpression zhegalkin(bool& isSimple)  //calculates zhegalkin's polynomial using the pascal method (check if function is linear)
	{
		isSimple = 1;
		if (isConst_ == 1)
		{
			std::string x;
			if (function_[0].getValue() == 1)
			{
				x = "1";
			}
			else
			{
				x = "1+1";
			}
			BooleanExpression a(x);
			return a;
		}
		bool_** table = new bool_ * [this->count_ + 1];
		for (int i = 0; i <= this->count_; ++i)
		{
			table[i] = new bool_[this->length_];
		}
		for (int i = 0; i < this->length_; ++i)
		{
			table[0][i] = this->getValue(i);
		}
		for (int i = 0; i < this->count_; ++i)  
		{
			int flag = 1;
			for (int j = 0; j < this->length_; ++j)
			{
				if (flag % 2 == 1)
				{
					table[i + 1][j] = table[i][j];
				}
				else
				{
					table[i + 1][j] = table[i][j] + table[i][j - (int)pow(2, i)];
				}
				if ((j+1) % (int)pow(2, i)==0)
				{
					++flag;
				}
			}
		
		}
		bool* rank = new bool[count_];
		std::string zhegalkin;
		if (function_[0].getValue() == 1)
		{
			zhegalkin += "1+";
		}
		for (int i = 1; i < length_; ++i)
		{
			if (table[count_][i].getValue() == 1)
			{
				for (int j = count_ - 1; j >= 0; --j)  //takes bytes from number to generate values of variables
				{
					rank[j] = i & (int)pow(2, (count_ - 1) - j);
				}
				int counter = 0;
				for (int j = 0; j < count_; ++j)
				{
					if (rank[j] == 1)
					{
						++counter;
						zhegalkin += 'x' + std::to_string(j+1) + '&';
					}
				}
				if (counter > 1)
				{
					isSimple = 0;
				}
				zhegalkin.pop_back();
				zhegalkin += '+';
			}
		}
		delete[] rank;
		for (int i = 0; i <= this->count_; ++i)
		{
			delete[] table[i];
		}
		delete[] table;
		zhegalkin.pop_back();
		BooleanExpression a(zhegalkin);
		return a;
	}

	BooleanExpression zhegalkin()  //calculates zhegalkin's polynomial using the pascal method (does not check if function is linear)
	{
		if (isConst_ == 1)
		{
			std::string x;
			if (function_[0].getValue() == 1)
			{
				x = "1";
			}
			else
			{
				x = "1+1";
			}
			BooleanExpression a(x);
			return a;
		}
		bool_** table = new bool_ * [this->count_ + 1];
		for (int i = 0; i <= this->count_; ++i)
		{
			table[i] = new bool_[this->length_];
		}
		for (int i = 0; i < this->length_; ++i)
		{
			table[0][i] = this->getValue(i);
		}
		for (int i = 0; i < this->count_; ++i)
		{
			int flag = 1;
			for (int j = 0; j < this->length_; ++j)
			{
				if (flag % 2 == 1)
				{
					table[i + 1][j] = table[i][j];
				}
				else
				{
					table[i + 1][j] = table[i][j] + table[i][j - (int)pow(2, i)];
				}
				if ((j + 1) % (int)pow(2, i) == 0)
				{
					++flag;
				}
			}

		}
		bool* rank = new bool[count_];
		std::string zhegalkin;
		if (function_[0].getValue() == 1)
		{
			zhegalkin += "1+";
		}
		for (int i = 1; i < length_; ++i)
		{
			if (table[count_][i].getValue() == 1)
			{
				for (int j = count_ - 1; j >= 0; --j)  //takes bytes from number to generate values of variables
				{
					rank[j] = i & (int)pow(2, (count_ - 1) - j);
				}
				for (int j = 0; j < count_; ++j)
				{
					if (rank[j] == 1)
					{
						zhegalkin += 'x' + std::to_string(j+1) + '&';
					}
				}
				zhegalkin.pop_back();
				zhegalkin += '+';
			}
		}
		delete[] rank;
		for (int i = 0; i <= this->count_; ++i)
		{
			delete[] table[i];
		}
		delete[] table;
		zhegalkin.pop_back();
		BooleanExpression a(zhegalkin);
		return a;
	}

	operator std::string() const { return this->expr_; }  //return expression as string

	bool_ getValue(int x) const { return function_[x]; }
	int getLength() const { return length_; }
	int getCount() const { return count_; }
	std::string getExpr() const { return expr_; }
	std::vector<bool_> getFunction() const { return function_; }
};

bool isFullSystem(std::vector<BooleanExpression> x);

std::ostream& operator<<(std::ostream& out, BooleanExpression& x);
