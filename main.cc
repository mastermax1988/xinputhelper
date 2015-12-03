#include <iostream>
#include "include/command.hh"
#include "include/myfile.hh"
#include <regex>
using namespace std;
using namespace boost;

void manual()
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

}

void automatic()
{
  cout << "automatic" << endl;
  myfile::stringvector pointers=command::exec("xinput");
  for(int i=0;i<pointers.size();i++)
  {
    myfile::stringvector s;
    myfile::stringvector s2;
    split(s,pointers[i],is_any_of("="), token_compress_on);
    split(s2,s[1],is_any_of(" \t"), token_compress_on);
    int id=pointers[i].find("Wacom");
    if(id>0)
      command::exec(("xinput --map-to-output " + s2[0]+  " eDP1").c_str());
    
    id=pointers[i].find("maXTouch");
    if(id>0)
      command::exec(("xinput --map-to-output " + s2[0]+  " eDP1").c_str());
    id=pointers[i].find("EPSON");
    if(id>0)
      command::exec(("xinput --map-to-output " + s2[0]+  " DP2").c_str());
  }
}

void activate(bool b)
{
 cout << "(de)activate" << endl;
  myfile::stringvector pointers=command::exec("xinput");
  for(int i=0;i<pointers.size();i++)
  {
    myfile::stringvector s;
    myfile::stringvector s2;
    split(s,pointers[i],is_any_of("="), token_compress_on);
    split(s2,s[1],is_any_of(" \t"), token_compress_on);

    int id=pointers[i].find("maXTouch");
    if(id>0)
      if(b)
        command::exec(("xinput enable " + s2[0]).c_str());
      else
        command::exec(("xinput disable " + s2[0]).c_str());

  }

}
//main program
int main(int argc, char* argv[])
{
  if(argc==1)
    manual();
  else if(string(argv[1])=="a")
    automatic();
  else if(string(argv[1])=="e")
    activate(true);
  else if(string(argv[1])=="d")
    activate(false);;
  return 0;
}



