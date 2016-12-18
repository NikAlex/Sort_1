#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>

using namespace std;

struct man
{
	string name;
	string surname;
	short year;
	size_t size() const
	{
		size_t string_obj_size = sizeof(string);
		return string_obj_size * 2 + name.size() + surname.size() + sizeof(short);
	}
};

bool operator < (const man & m1, const man & m2)
{
	return (m1.name < m2.name);
}

bool operator >(const man & m1, const man & m2)
{
	return (m1.name > m2.name);
}

ostream & operator<<(ostream & output, man const & m)
{
	output << m.surname << " " << m.name << " " << m.year;
	return output;
}

istream & operator>>(istream & input, man & m)
{
	input >> m.surname >> m.name >> m.year;
	return input;
}

bool operator != (const man& m, const string& str)
{
	return (m.surname != str);
}

struct file_man
{
	man data;
	ifstream *f;
	file_man(const man& m_, ifstream* f_) : data(m_), f(f_){}
};

bool operator < (const file_man& mf1, const file_man& mf2)
{
	return (mf1.data > mf2.data);
}

void sorting(const string& input_name, const string& output_name, const size_t file_size)
{


	ifstream fin(input_name, ios::binary);
	if (!fin.is_open()) throw("file_not_open");
	ofstream fout(output_name, ios::binary);
	size_t n = 0;
	const size_t buffer_size = file_size * 1024 * 1024 * 0.6;
	while (!fin.eof())
	{
		vector<man> v; 
		man m;
		ofstream fout_(to_string(n + 1), ios::binary);
		unsigned long int size = 0;
		while ((size + 50) < buffer_size)
		{
			if ((fin >> m) && (m != ""))  v.push_back(m);
			size += m.size();
		}
		sort(v.begin(), v.end());
		for (auto i : v)
		{
			fout_ << i << endl;
		}
		++n;
		fout_.close();
	}
	fin.close();


	priority_queue<file_man> q;
	for (size_t i = 0; i < n; ++i)
	{
		ifstream* f_ = new ifstream(to_string(i + 1), ios::binary);
		man push_man;
		*f_ >> push_man;
		file_man fm(push_man, f_);
		q.push(fm);
	}
	while (!q.empty())
	{
		file_man mf_ = q.top();
		q.pop();
		fout << mf_.data << endl;
		if (!(*mf_.f).eof())
		{
			*mf_.f >> mf_.data;
			q.push(mf_);
		}
		else
		{
			(*(mf_.f)).close();
		}
	}
	for (size_t i = 0; i < n; ++i)
	{
		remove((to_string(i + 1)).c_str());
	}
	fout.close();
}
