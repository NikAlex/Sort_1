#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>

using namespace std;

struct stroka
{
	string name;
	string surname;
	short year;
	size_t size() const
	{
		size_t sz = sizeof(string);
		return (sz + name.size() + sz + surname.size() + sizeof(short));
	}
};

bool operator < (const stroka & s1, const stroka& s2)
{
	return (s1.name < s2.name);
}

bool operator >(const stroka & s1, const stroka& s2)
{
	return (s1.name > s2.name);
}

ostream & operator<<(ostream & output, stroka const & str)
{
	output << str.surname << " " << str.name << " " << str.year;
	return output;
}

istream & operator>>(istream & input, stroka & str)
{
	input >> str.surname >> str.name >> str.year;
	return input;
}

bool operator != (const stroka& s, const string& str)
{
	return (s.surname != str);
}

struct s_i
{
	stroka s;
	ifstream *f;
	s_i(const stroka& s_, ifstream* f_) : s(s_), f(f_){}
};

bool operator < (const s_i& s_i1, const s_i& s_i2)
{
	return (s_i1.s > s_i2.s);
}

void sort_it(const string input_name, const string output_name, const short mem_size)
{
	ifstream fin(input_name, ios::binary);
	if (!fin.is_open()) throw("file_not_open");
	ofstream fout(output_name, ios::binary);
	short k = 0;
	const size_t ms = mem_size * 1024 * 1024 * 0.63;
	while (!fin.eof())
	{
		vector<stroka> v; stroka s;
		ofstream fout_(to_string(k + 1), ios::binary);
		for (unsigned long int size = 0; (size + 50) < ms;)
		{
			if (!fin.eof() && (fin >> s) && (s != ""))  v.push_back(s);
			size += s.size();
		}
		sort(v.begin(), v.end());
		for (auto i : v)
		{
			if (i != "") fout_ << i << endl;
		}
		++k;
		fout_.close();
	}
	fin.close();
	priority_queue<s_i> pq;
	for (size_t i = 0; i < k; ++i)
	{
		ifstream* f_ = new ifstream(to_string(i + 1), ios::binary);
		stroka str;
		*f_ >> str;
		s_i si(str, f_);
		pq.push(si);
	}
	while (!pq.empty())
	{
		s_i si = pq.top();
		pq.pop();
		if (si.s != "") fout << si.s << endl;
		if (!(*si.f).eof() && (*si.f >> si.s))
		{
			pq.push(si);
		}
		else
		{
			(*(si.f)).close();
		}
	}
	for (size_t i = 0; i < k; ++i)
	{
		remove((to_string(i + 1)).c_str());
	}
	fout.close();
}
