#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <stack>
#include <regex>
#include <gtest/gtest.h>
using namespace std;

class Assembler
{

public:
	string program;
	vector<string> command_lines;
	map<string, int> registers;
	map<string, int> labels;
	stack<int> call_position;
	Assembler(string in) :program(in)
	{}
	vector<string> Line_parser(string program, char const& spliter)
	{
		string individual;
		stringstream ss(program);
		vector<string> lines;
		while (getline(ss, individual, spliter))
		{
			if (individual != " ")
				lines.push_back(individual);
		}
		return lines;
	}
	void comment_eraser()
	{
		command_lines = Line_parser(program, '\n');
		for (int i = 0; i < command_lines.size(); i++)
		{
			size_t position = command_lines[i].find(";");
			if (position != std::string::npos)
			{
				command_lines[i].erase(position, command_lines[i].length() - position);
			}
			int last = command_lines[i].size() - 1;
			while (last >= 0 && command_lines[i][last] == ' ')
				--last;

			command_lines[i] = command_lines[i].substr(0, last + 1);
		}
	}


};
vector<string> split(const string& str, const string& separaters)
{
	vector<string> v;
	string::size_type start = 0;
	auto position = str.find_first_of(separaters, start);
	while (position != string::npos)
	{
		if (position != start)
			v.emplace_back(str, start, position - start);
		start = position + 1;
		position = str.find_first_of(separaters, start);
	}
	if (start < str.length())
		v.emplace_back(str, start, str.length() - start);
	return v;
}
string msg_form(string line)
{
	int spaces = 0;
	string form = line.substr(line.find('m') + 3);
	for (int i = 0; form.length(); i++)
	{
		if (isalpha(form[i]) || form[i] != ' ')
			break;
		if (form[i] == ' ')
			spaces++;
	}
	return form.substr(spaces, form.length());
}
string msg_parser(string msg_part, Assembler* instructions)
{

	string msg = "";
	for (int i = 0; i < msg_part.size(); i++)
	{
		if (msg_part[i] == 39)
		{
			size_t found = msg_part.find(39, i + 1);
			if (found != string::npos)
			{
				msg += msg_part.substr(i + 1, found - (i + 1));
				i = found;
				continue;
			}
		}
		if (msg_part[i] == ',')
		{
			size_t found_letter = SIZE_MAX;
			for (int j = i; j < msg_part.size(); j++)
			{
				if (isalpha(msg_part[j]))
				{
					found_letter = (size_t)j;
					break;
				}
			}
			size_t found_comma = msg_part.find(',', i + 1);
			if (found_comma != string::npos && found_letter < found_comma)
			{
				char letter = msg_part[found_letter];
				string value = "";
				value.push_back(letter);
				int num = instructions->registers[value];
				stringstream ss;
				ss << num;
				string str = ss.str();
				msg += str;
				i = found_comma;
				continue;
			}
		}
		if (isalpha(msg_part[i]))
		{
			char letter = msg_part[i];
			string value = "";
			value.push_back(letter);
			int num = instructions->registers[value];
			stringstream ss;
			ss << num;
			string str = ss.str();
			msg += str;
		}

	}
	return msg;
}
string assembler_interpreter(string program)
{
	Assembler* instructions = new Assembler(program);
	instructions->comment_eraser();
	double cmp_last = 0;
	string cmp_register;
	string massage = "";
	auto get_value = [&](string in)->int
	{
		return isalpha(in[0]) ? instructions->registers[in] : stoi(in);
	};
	for (int i = 0; i < instructions->command_lines.size(); i++)
	{
		for (int j = 0; j < instructions->command_lines[i].size(); j++)
		{
			if (instructions->command_lines[i][j] == ':')
			{
				instructions->labels[instructions->command_lines[i].substr(0, j)] = i;
			}
		}
	}
	for (auto it = instructions->labels.cbegin(); it != instructions->labels.cend(); ++it)
	{
		cout << it->first << " " << it->second << "\n=====================\n";
	}
	for (int i = 0; i < instructions->command_lines.size(); i++)
	{
		if (instructions->command_lines[i].empty())
			continue;
		vector<string> line = split(instructions->command_lines[i], ", ");
		string function = line[0];
		if (function == "msg")
		{
			string massage_part = msg_form(instructions->command_lines[i]);
			massage = msg_parser(massage_part, instructions);
		}
		if (function == "end")
		{
			return massage;
		}
		if (function == "mov")
		{
			cmp_register = line[1];
			instructions->registers[cmp_register] = get_value(line[2]);
		}
		if (function == "inc")
		{
			cmp_register = line[1];
			instructions->registers[cmp_register]++;
		}
		if (function == "dec")
		{
			cmp_register = line[1];
			instructions->registers[cmp_register]--;
		}
		if (function == "add")
		{
			cmp_register = line[1];
			instructions->registers[cmp_register] += get_value(line[2]);
		}
		if (function == "sub")
		{
			cmp_register = line[1];
			instructions->registers[cmp_register] -= get_value(line[2]);
		}
		if (function == "mul")
		{
			cmp_register = line[1];
			instructions->registers[cmp_register] *= get_value(line[2]);
		}
		if (function == "div")
		{
			cmp_register = line[1];
			instructions->registers[cmp_register] /= get_value(line[2]);
		}
		if (function == "call")
		{
			instructions->call_position.push(i);
			i = instructions->labels[line[1]];
		}
		if (function == "jmp")
		{
			i = instructions->labels[line[1]];
		}
		if (function == "jne" && cmp_last != 1)
		{
			i = instructions->labels[line[1]];
		}
		if (function == "je" && cmp_last == 1)
		{
			i = instructions->labels[line[1]];
		}
		if (function == "jge" && cmp_last >= 1)
		{
			i = instructions->labels[line[1]];
		}
		if (function == "jg" && cmp_last > 1)
		{
			i = instructions->labels[line[1]];
		}
		if (function == "jle" && cmp_last <= 1)
		{
			i = instructions->labels[line[1]];
		}
		if (function == "jl" && cmp_last < 1)
		{
			i = instructions->labels[line[1]];
		}
		if (function == "cmp")
		{
			if (get_value(line[2]) == 0)
				cmp_last = get_value(line[1]) - get_value(line[2]) + 1;
			else
				cmp_last = get_value(line[1]) / (double)get_value(line[2]);
		}
		if (function == "ret")
		{
			i = instructions->call_position.top();
			instructions->call_position.pop();
		}
	}
	return "-1";
}
TEST(FirstOF7, ShortOneFunctionTest) {
  string first_case= R"(
; My first program
mov  a, 5
inc  a
call function
msg  '(5+1)/2 = ', a    ; output message
end

function:
    div  a, 2
    ret)";
	EXPECT_EQ(assembler_interpreter(first_case),"(5+1)/2 = 3");
}
TEST(Second, DoubleFunctionLabel)
{
	string second_case= R"(
mov   a, 5
mov   b, a
mov   c, a
call  proc_fact
call  print
end

proc_fact:
    dec   b
    mul   c, b
    cmp   b, 1
    jne   proc_fact
    ret

print:
    msg   a, '! = ', c ; output text
    ret
)";
	EXPECT_EQ(assembler_interpreter(second_case), "5! = 120");
}
TEST(Third, ComplicatedWithRecursion )
{
	string third= R"(
mov   a, 8            ; value
mov   b, 0            ; next
mov   c, 0            ; counter
mov   d, 0            ; first
mov   e, 1            ; second
call  proc_fib
call  print
end

proc_fib:
    cmp   c, 2
    jl    func_0
    mov   b, d
    add   b, e
    mov   d, e
    mov   e, b
    inc   c
    cmp   c, a
    jle   proc_fib
    ret

func_0:
    mov   b, c
    inc   c
    jmp   proc_fib

print:
    msg   'Term ', a, ' of Fibonacci series is: ', b        ; output text
    ret)";
	EXPECT_EQ(assembler_interpreter(third), "Term 8 of Fibonacci series is: 21");
}
TEST(Fourth, DifficultMsgParser)
{
	string fourth= R"(
mov   a, 11           ; value1
mov   b, 3            ; value2
call  mod_func
msg   'mod(', a, ', ', b, ') = ', d        ; output
end

; Mod function
mod_func:
    mov   c, a        ; temp1
    div   c, b
    mul   c, b
    mov   d, a        ; temp2
    sub   d, c
    ret)";
	EXPECT_EQ(assembler_interpreter(fourth), "mod(11, 3) = 2");
}
TEST(Fifth, HardUnderEveryAspect)
{
	string fifth= R"(
mov   a, 81         ; value1
mov   b, 153        ; value2
call  init
call  proc_gcd
call  print
end

proc_gcd:
    cmp   c, d
    jne   loop
    ret

loop:
    cmp   c, d
    jg    a_bigger
    jmp   b_bigger

a_bigger:
    sub   c, d
    jmp   proc_gcd

b_bigger:
    sub   d, c
    jmp   proc_gcd

init:
    cmp   a, 0
    jl    a_abs
    cmp   b, 0
    jl    b_abs
    mov   c, a            ; temp1
    mov   d, b            ; temp2
    ret

a_abs:
    mul   a, -1
    jmp   init

b_abs:
    mul   b, -1
    jmp   init

print:
    msg   'gcd(', a, ', ', b, ') = ', c
    ret)";
	EXPECT_EQ(assembler_interpreter(fifth), "gcd(81, 153) = 9");
}
TEST(Sixth, CheckIfAlsoReturnsNotWorkingCode)
{
	string sixth= R"(
call  func1
call  print
end

func1:
    call  func2
    ret

func2:
    ret

print:
    msg 'This program should return -1')";
	EXPECT_EQ(assembler_interpreter(sixth), "-1");
}
TEST(Seventh, TestCheck)
{
	string seventh=R"(
mov   a, 2            ; value1
mov   b, 10           ; value2
mov   c, a            ; temp1
mov   d, b            ; temp2
call  proc_func
call  print
end

proc_func:
    cmp   d, 1
    je    continue
    mul   c, a
    dec   d
    call  proc_func

continue:
    ret

print:
    msg a, '^', b, ' = ', c
    ret)";
	EXPECT_EQ(assembler_interpreter(seventh), "2^10 = 1024");
}
