/*
 * Sudoku_solver.cpp
 *
 *  Created on: 16 Sep 2014
 *      Author: alex
 */
#include <iostream>
#include <string>

extern void testSquare();
extern void testPuzzle();

int main(int argc, char * argv[]){

	if(argc==2 && std::string(argv[1])=="testSquare")
		testSquare();
	else if(argc == 2 && std::string(argv[1])=="testPuzzle")
		testPuzzle();
	else
		std::cout << "Nothing to see yet!" << std::endl;

	return 0;
}



