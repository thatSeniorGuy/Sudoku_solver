/*
 * Puzzle.cpp
 *
 *  Created on: 20 Sep 2014
 *      Author: alex
 */

#include "Puzzle.h"

Puzzle::Puzzle() : squares_(nullptr), solved_(false),
	numLeftToSolve_(puzzle_size*puzzle_size) {

	squares_ = new Square[puzzle_size*puzzle_size];

	try{
		for(int i = 0; i < puzzle_size*puzzle_size; i++){
			squares_[i].setRow(i/puzzle_size);
			squares_[i].setCol(i%puzzle_size);
		}
	}
	catch (std::out_of_range & e) {
		// The for loop above shouldn't throw any exceptions, but ...
		delete[] squares_;
		throw e;
	}

}

Puzzle::~Puzzle() {
	delete[] squares_;
}

