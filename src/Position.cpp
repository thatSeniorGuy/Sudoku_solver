/*
 * Position.cpp
 *
 *  Created on: 16 Sep 2014
 *      Author: Alexander Senior.
 */

#include "Position.h"

Position::Position(int row, int col) : row(row), col(col) {};

Position::Position(const Position & other) : row(other.row), col(other.col) {};

Position & Position::operator=(const Position & other){

	// Handle self-assignment.
	if(this==&other)
		return *this;

	row = other.row;
	col = other.col;
	return *this;
}



