/** \file Square.h
 *
 * \brief Defines the Square class and functions for interacting with it.
 *
 *  Created on: 16 Sep 2014
 *      Author: Alexander Senior.
 */

#ifndef SQUARE_H_
#define SQUARE_H_

#include <set>
#include <initializer_list>
#include <iostream>
#include <string>
#include "Position.h"

/**
 * \class Square
 * \brief Atomic piece of a Sudoku puzzle.
 *
 * This class represents the smallest part of a Sudoku puzzle, the square (of
 * which there are 81 in a standard puzzle). A square can either be set and have
 * a value between 1 and \ref puzzle_size, or it can be unset and have many
 * possible values. Squares also have a row and a column, which must both be
 * between 0 and \ref puzzle_size. For now, \ref puzzle_size is set to 9.
 */
class Square {
public:
	/**
	 * \var puzzle_size
	 * \brief The size of the Sudoku puzzle.
	 */
	static const int puzzle_size = 9;

public:
	/** @name Constructors */
	/**@{*/

	/**
	 * \brief Default 'unset' constructor.
	 *
	 * This creates an unset \ref Square; the \ref Square's row and column are
	 * set to the supplied values, isSet_ is set to false, and possibleValues_
	 * will contain all the integers from 1 to \ref puzzle_size.
	 *
	 * \param row The neq Square's row. If this is not between 0 and \ref
	 * puzzle_size - 1, then a std::out_of_range exception will be thrown.
	 * Defaults to 0.
	 *
	 * \param col The Square's new col. If this is not between 0 and \ref
	 * puzzle_size - 1, then a std::out_of_range exception will be thrown.
	 * Defaults to 0.
	 */

	Square(int row = 0, int col = 0);

	/**
	 * \brief 'Set' constructor.
	 *
	 * This creates a set \ref Square, with its value set to the given parameter.
	 * isSet_ will be set to true, and possibleValues_ will contain only the
	 * given value. The \ref Square will have its row and column set
	 * accordingly.
	 *
	 * \param row The new Square's row. If this is not between 0 and \ref
	 * puzzle_size - 1, then a std::out_of_range exception will be thrown.
	 *
	 * \param col The new Square's col. If this is not between 0 and \ref
	 * puzzle_size - 1, then a std::out_of_range exception will be thrown.
	 *
	 * \param value The new \ref Square's value. If this is not between 1 and
	 * \ref puzzle_size, then a std::out_of_range exception will be thrown.
	 */
	Square(int row, int col, int value);

	/**
	 * \brief Copy constructor.
	 *
	 * The new \ref Square will be set to an exact copy of other.
	 */
	Square(const Square & other);

	/**@}*/ //Constructors.

	/** @name Mutators */
	/**@{*/

	/**
	 * \brief Sets the value of the \ref Square.
	 *
	 * Attempts to set the Square's value to the specified parameter. The given
	 * value must be in the Square's list of possible values, and the square
	 * must not be set already; if so, then this Square's value_ will be set to
	 * newValue, isSet_ will be set to true, and possibleValues_ will be
	 * cleared to only contain the new value.
	 *
	 * \param newValue The value for the Square. If this is not between 1 and
	 * \ref puzzle_size, a std::out_of_range exception will be thrown.
	 *
	 * \returns Returns true if the Square was set successfully, or false if
	 * the Square was already set, or the given value was not in the Square's
	 * list of possible values.
	 */
	bool setValue(int newValue);

	/**
	 * \brief Changes the Square's row.
	 *
	 * Tries to change the Square's row to the new specified value. If the new
	 * co-ordinate is not between 0 and puzzle_size - 1, a std::out_of_range
	 * exception will be thrown.
	 */
	void setRow(int newRow);

	/**
	 * \brief Changes the Square's col.
	 *
	 * Tries to change the Square's col to the new specified value. If the new
	 * co-ordinate is not between 0 and puzzle_size - 1, a std::out_of_range
	 * exception will be thrown.
	 */
	void setCol(int newCol);

	/**@}*/ // Mutators

	/** @name Inspectors */
	/**@{*/

	/** \brief Returns the Square's row. */
	int getRow() const;

	/** \brief Returns the Square's col. */
	int getCol() const;

	/** \brief Returns the Square's \ref Position. */
	Position getPosition() const;

	/** \brief Returns whether the Square is set or not. */
	bool isSet() const;

	/** \brief Returns the Square's value. If this Square is not set, then a
	 * std::logic_error will be thrown. */
	int getValue() const;

	/** \brief Returns a set::set<int> of this Square's possible values. */
	std::set<int> getPossibleValues() const;
	/**@}*/

	/** @name Miscellaneous. */
	/**@{*/

	/**
	 * \brief Restrict the possible values of this Square.
	 *
	 * This method attempts to restrict the values that this Square could
	 * possibly have. If at any point there is only one possible value that
	 * this Square could have, then it will be set to that value.
	 *
	 * \param vals The list of values to take away from this Square's list of
	 * possible values. If any of them are less than one or greater than
	 * puzzle_size, a std::out_of_range exception will be thrown.
	 *
	 * \returns This method will return false is this Square is already set
	 * then it is called, or if all values are processed then this Square has
	 * at least two possible values. Return's true if by the end of this
	 * method, the Square is set.
	 */
	bool restrictValues(std::set<int> vals);

	/**
	 * \brief Assignment operator.
	 *
	 * This Square will be set to an exact copy of the other square.
	 */
	Square & operator=(const Square & other);

	/**
	 * \brief Validates the given co-ordinate (either a row or a col).
	 *
	 * Utility function to validate whether a given row or col is valid; that
	 * is, between 0 and \ref puzzle_size - 1. If it is not, false is returned;
	 * otherwise true is returned.
	 */
	static bool validateCoordinate(int coord);

	/**
	 * \brief Validates the given \ref Position.
	 *
	 * Utility function to validate whether a \ref Position is valid; that
	 * is, whether its row and col attributes are between 0 and \ref
	 * puzzle_size - 1. If they are not, then false is returned; otherwise true
	 * is returned.
	 */
	static bool validatePosition(const Position & pos);

	/**
	 * \brief Returns a string representation of the Square.
	 *
	 * If the Square is set, then the returned std::string will contain its
	 * value; otherwise, the string will contain the # symbol.
	 */
	std::string toString() const;


	/**@}*/ // Miscellaneous.

private:
	/**
	 * \var row_
	 * \brief Row that this Square is located in the Sudoku puzzle.
	 */
	int row_;

	/**
	 * \var col_
	 * \brief Column that this Square is located in the Sudoku puzzle.
	 */
	int col_;

	/**
	 * \var isSet_
	 * \brief Holds whether this Square is set or not.
	 */
	bool isSet_;

	/**
	 * \var value_
	 * \brief Holds the value of this Square; if it is not set, then this value
	 * is rubbish.
	 */
	int value_;

	/**
	 * \var possibleValues_
	 * \brief Holds all the values that this Square could be. If this Square is
	 * set, then it will only have its value.
	 */
	std::set<int> possibleValues_;
};

/**
 * \brief Overloads the << operator for printing a \ref Square to a
 * std::ostream.
 *
 * Prints the \ref Square to the ostream, then returns the ostream. The string
 * representation of a Square is either its value if it is set, or a # symbol
 * if it is not.
 */
std::ostream & operator<<(std::ostream & ostream, const Square & square);

#endif /* SQUARE_H_ */
