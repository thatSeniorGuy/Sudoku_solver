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

class Square {
public:
	/*************************************************************************/
	/*********************** Constructors ************************************/
	/*************************************************************************/
	Square(int row, int col, int value);
	Square(int row = 0, int col = 0);
	Square(const Square & other);

	bool setValue(int newValue);

	bool getIsSet() const;
	int getValue() const;
	int getRow() const;
	int getCol() const;

	bool restrictValues(std::initializer_list<int> vals);

	Square & operator=(const Square & other);


private:
	bool isSet;
	int value;
	std::set<int> possibleValues;
	int row;
	int col;
};

#endif /* SQUARE_H_ */
