#include <iostream>
#include "include/command.hh"
#include "include/myfile.hh"
#include "include/myclass.hh"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <boost/lexical_cast.hpp>
#include "include/board.hh"

using namespace std;
using namespace boost;

//main program
int main()
{
	myfile::stringvector wholefile = myfile::read("../level1-1.in");
	//command::printoutput(result);
	myfile::stringvector inputvector;
	split( inputvector , wholefile[0] , is_any_of(" "));
	int iNrOfTests = lexical_cast<int>(inputvector[0]);
	int iBoardIndex = 0;
	board *theBoards[iNrOfTests];
	theBoards[0] = new board(lexical_cast<int>(inputvector[1]), lexical_cast<int>(inputvector[2]), lexical_cast<int>(inputvector[3]));
	for(int i = 4; i < inputvector.size(); i++)
	{
		if(lexical_cast<int>(inputvector[i]) == 0)
			continue;
		if(lexical_cast<int>(inputvector[i - 1]) == 0)
		{
			//new board
			iBoardIndex++;
			theBoards[iBoardIndex] = new board(lexical_cast<int>(inputvector[i]), lexical_cast<int>(inputvector[i + 1]), lexical_cast<int>(inputvector[i + 2]));
			i += 2;
			continue;
		}

		theBoards[iBoardIndex]->addPoint(lexical_cast<int>(inputvector[i]), lexical_cast<int>(inputvector[i + 1]), true);
		i++;
	}
	theBoards[0]->solveBoard();
	for (int i = 0; i < iNrOfTests; i++)
		delete theBoards[i];
}


