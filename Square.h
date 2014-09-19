/*
 * Square.h
 *
 *  Created on: 16 Sep 2014
 *      Author: alex
 */

#ifndef SQUARE_H_
#define SQUARE_H_

#include <set>
#include <initializer_list>
#include "Position.h"

/**
 * Atomic piece of a Sudoku puzzle.
 *
 * This class represents the smallest part of a Sudoku puzzle, the square (of
 * which there are 81 in a standard puzzle). A square can either be set and have
 * a value between 1 and 'puzzle_size', or it can be unset and have many
 * 'possibleValues'. Squares also have a row and a column, both between 0 and
 * 'puzzle_size'. For now, 'puzzle_size' is set to 9.
 */
class Square {
public:
	static const int puzzle_size = 9;

public:
	/*************************************************************************/
	/*********************** Constructors ************************************/
	/*************************************************************************/
	Square(int row, int col, int value);
	Square(int row = 0, int col = 0);
	Square(const Square & other);

	/*************************************************************************/
	/************************ Mutators ***************************************/
	/*************************************************************************/
	bool setValue(int newValue);

	/*************************************************************************/
	/************************ Inspectors *************************************/
	/*************************************************************************/

	int getRow() const;
	int getCol() const;
	Position getPosition() const;
	bool isSet() const;
	int getValue() const;
	std::set<int> getPossibleValues() const;

	/*************************************************************************/
	/************************ Misc *******************************************/
	/*************************************************************************/

	/* Return true if all but one of the Square's possible values erased, so
	 * this square can have only one possible value. */
	bool restrictValues(std::initializer_list<int> vals);

	Square & operator=(const Square & other);

	static void validatePosition(int row, int col);
	static void validatePosition(const Position & pos);


private:
	int row_;
	int col_;
	bool isSet_;
	int value_;
	std::set<int> possibleValues_;
};

#endif /* SQUARE_H_ */
