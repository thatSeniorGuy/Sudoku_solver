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
