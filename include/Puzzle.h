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

	/**
	 * \class PuzzleFileException
	 *
	 * \brief Exception thrown by the file constructor for \ref Puzzle when it
	 * encounters an invalid file.
	 *
	 * The enum Reason contains the reason why this exception was thrown, and
	 * the exception itself contains more information on how the file is
	 * invalid. The class uses named constructors for users to create
	 * PuzzleFileExceptions.
	 */
	class PuzzleFileException : public std::runtime_error {
		/**
		 * \enum Reason
		 * \brief Details why the PuzzleFileException was thrown.
		 *
		 * TOO_FEW_LINES: the file contained too few lines to construct a full
		 * Sudoku puzzle.
		 * INVALID_LINE_LENGTH: one of the lines in the file was either too
		 * large or too small.
		 * INVALID_VALUE: one of the lines in the file contained an invalid
		 * value.
		 */
		enum Reason{
			TOO_FEW_LINES,
			INVALID_LINE_LENGTH,
			INVALID_VALUE
		};
	public:
		/** @name Named constructors.*/
		/**@{*/
		/**
		 * \brief Creates a PuzzleFileException with its reason set to
		 * TOO_FEW_LINES, for the given file.
		 *
		 * \param filename Char pointer to the offending file. If the string is
		 * larger than 59 characters, it will be restricted to 59 characters.
		 * If a nullptr is passed, the filename will be noted as invalid.
		 */
		static PuzzleFileException tooFewLines(const char * filename);
		static PuzzleFileException invalidLineLength(
				const char * filename,
				const char * line,
				int lineLength);
		static PuzzleFileException invalidValue(
				const char * filename,
				const char * line,
				char invalidValue);
		/**@}*/

		virtual ~PuzzleFileException() throw () {} ;
		virtual const char * what();
		Reason getReason() const;

		PuzzleFileException(const PuzzleFileException & other);
		PuzzleFileException & operator=(const PuzzleFileException & other);

	protected:
		PuzzleFileException(
				Reason reason,
				const char * filename,
				const char * line = NULL,
				int length = 0,
				char invalidValue = '?');

	protected:
		const static int STR_LEN = 60;
		char whatMessage_[256];
		Reason reason_;
		char filename_[STR_LEN];
		char line_[STR_LEN];
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
	Square squares_[puzzle_size * puzzle_size];
	bool solved_;
	int numLeftToSolve_;
};

#endif /* PUZZLE_H_ */
