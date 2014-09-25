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
#include <vector>
#include "Square.h"
#include <stdexcept>

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

	class PuzzleFileException : public std::runtime_error {
		//TODO here
		enum Reason{
			TOO_FEW_LINES,
			INVALID_LINE_LENGTH,
			INVALID_VALUE
		};
	public:
// Make static methods to construct exceptions.
		static PuzzleFileException tooFewLines(char * filename);
		static PuzzleFileException invalidLineLength(
				char * filename,
				char * line,
				int lineLength);
		static PuzzleFileException invalidValue(
				char * filename,
				char * line,
				char invalidValue);
		virtual ~PuzzleFileException() {};
		virtual const char * what();
	protected:
		PuzzleFileException(
				Reason reason,
				char * filename,
				char * line = NULL,
				int length = 0,
				char invalidValue = '?');

	protected:
		char whatMessage_[256];
		Reason reason_;
		char filename_[60];
		char line_;
		int length_;
		char invalidValue_;
	};

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

	/**
	 * \brief Copy constructor.
	 *
	 * The new puzzle is initialised to an exact copy of 'other', with its own
	 * set of Squares.
	 */
	Puzzle(const Puzzle & other);

	/**@}*/

	/**
	 * \brief Overload of assignment operator.
	 *
	 * This \ref Puzzle is set to be an exact copy for the 'other' Puzzle, with
	 * its own set of Square's initialised to a copy of other's set of Squares.
	 */
	Puzzle & operator=(const Puzzle & other);

private:
	std::vector<Square> squares_;
	bool solved_;
	int numLeftToSolve_;
};

#endif /* PUZZLE_H_ */
