#include "../include/myfile.hh"
#include <iostream>
#include <fstream>
using namespace std;

myfile::stringvector myfile::read(const char filename[])
{
	stringvector out;
	ifstream in(filename);
	if(!in)
	{
		cout << "Cannot open input file.\n";
		throw;
	}
	string line;
	while(getline(in, line))
		out.push_back(line);
	return out;
}

void myfile::write(const char filename[], const char  content[])
{
	ofstream out;
	out.open (filename);
  if(!out)
	{
		cout << "Cannot open input file.\n";
		throw;
	}
	out << content << endl;
	out.close();
}
