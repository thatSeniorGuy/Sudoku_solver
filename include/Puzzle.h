/**
 * \file Puzzle.h
 *
 * \brief Defines the class Puzzle and functions for interfacing with it.
 *
 *  Created on: 20 Sep 2014
 *      Author: Alexander Senior.
 */

#ifndef PUZZLE_H_
#define PUZZLE_H_

#include <iostream>
#include <string>
#include "Square.h"

/** \class Puzzle
 * //TODO
 *
 */
class Puzzle {
public:
	/** \var puzzle_size
	 *  \brief The size of the Sudoku puzzle.
	 *
	 */
	static const int puzzle_size = 9;
public:

	/** @name Constructors and destructors */
	/**@{*/
	/**
	 * \brief Default constructor for the class.
	 *
	 * This creates an empty Puzzle, with all of its Squares unset, solved_ set
	 * to false and numLeftToSolve_ set to \ref puzzle_size * \ref puzzle_size.
	 */
	Puzzle();

	Puzzle(std::string filename);

	Puzzle(const Puzzle & other);




	/**
	 * \brief Deletes all the Squares created in either constructor.
	 */
	~Puzzle();
	/**@}*/

	Puzzle & operator=(const Puzzle & other);




private:
	Square * squares_;
	bool solved_;
	int numLeftToSolve_;
};

#endif /* PUZZLE_H_ */
