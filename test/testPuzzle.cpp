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

	std::set<int> values;
	for(int i = 1; i <= Puzzle::PUZZLE_SIZE; ++i)
		values.insert(i);

	Puzzle puzzle;
	assert(puzzle.isSolved()==false && "A default puzzle is not solved?");
	assert(puzzle.getNumLeftToSolve() == Puzzle::NUM_SQUARES &&
			"A default puzzle does not have NUM_SQUARES left to solve?");

	for(int row  = 0; row < Puzzle::PUZZLE_SIZE; ++row) {
		for(int col = 0; col < Puzzle::PUZZLE_SIZE; ++col){
			const Square & square = puzzle(row, col);
			assert(square.getRow() == row && "Row not set correctly?");
			assert(square.getCol() == col && "Col not set correctly?");
			assert(square.isSet()==false &&	"A square was set?");
			assert(square.getPossibleValues()==values &&
					"Possible values not set correctly?");
		}
	}

	cout << "\n*** No problems!" << endl;
}



