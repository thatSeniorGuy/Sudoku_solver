/**
 * \file testPuzzle.cpp
 *
 *  Created on: 3 Oct 2014
 *      Author: Alexander Senior.
 */

#include "Puzzle.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

void testPuzzle();
static void testDefaultCtor();

void testPuzzle(){
	cout << "***Testing class Puzzle. ***\n" << endl;

	testDefaultCtor();



	cout << "\n***All done!***" << endl;
}

void testDefaultCtor(){
	cout << "***Testing default c'tor.***\n" << endl;

	Puzzle puzzle;
	assert(puzzle.isSolved()==false && "A default puzzle is not solved?");
	assert(puzzle.getNumLeftToSolve() == Puzzle::NUM_SQUARES &&
			"A default puzzle does not have NUM_SQUARES left to solve?");


	cout << "\n*** No problems!" << endl;
}



