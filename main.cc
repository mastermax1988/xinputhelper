#include <iostream>
#include "include/command.hh"
#include "include/myfile.hh"
#include <regex>
using namespace std;
using namespace boost;

//main program
int main()
{
  myfile::stringvector settings=myfile::read("config");
  const char* xrandrset=settings[0].c_str();
  command::exec(xrandrset);
  myfile::stringvector pointers=command::exec("xinput");
  for(int i=1;i<settings.size();i++)
    cout << i << ": " << settings[i] << "   ";
  cout << endl; 
  for(int i=0;i<pointers.size();i++)
  {
    myfile::stringvector s;
    myfile::stringvector s2;
    split(s,pointers[i],is_any_of("="), token_compress_on);
    split(s2,s[1],is_any_of(" \t"), token_compress_on);
    cout << pointers[i] << endl;
    string in;
    int num=-1;
    getline(cin,in);
    stringstream mystream(in);
    mystream >> num;
    if(num<settings.size() && num>0)
      command::exec(("xinput --map-to-output " + s2[0] +  " " + settings[num]).c_str()); 
  }
  return 0;
}


