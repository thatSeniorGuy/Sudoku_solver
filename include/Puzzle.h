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
 * //TODO last comment this.
 *
 */
class Puzzle {
public:
	/** \var PUZZLE_SIZE
	 *  \brief The size of the Sudoku puzzle.
	 */
	static const int PUZZLE_SIZE = 9;

	/**
	 * \var NUM_SQUARES
	 * \brief The number of Squares in the Sudoku puzzle.
	 */
	static const int NUM_SQUARES = PUZZLE_SIZE * PUZZLE_SIZE;

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

		/**
		 * \brief Creates a PuzzleFileException with its reason set to
		 * INVALID_LINE_LENGTH, for the given file.
		 *
		 * \param filename Char pointer to the offending file. If the string is
		 * larger than 59 characters, it will be restricted to 59 characters.
		 * If a nullptr is passed, the filename will be noted as invalid.
		 *
		 * \param line Char pointer to the offending line. If the string is
		 * larger than 59 characters, it will be restricted to 59. If a nullptr
		 * is passed, the line will be noted as invalid.
		 *
		 * \param lineLength The length of the offending line.
		 */
		static PuzzleFileException invalidLineLength(
				const char * filename,
				const char * line,
				int lineLength);

		/**
		 * \brief Creates a PuzzleFileException with its reason set to
		 * INVALID_VALUE, for the given file.
		 *
		 * \param filename Char pointer to the offending file. If the string is
		 * larger than 59 characters, it will be restricted to 59 characters.
		 * If a nullptr is passed, the filename will be noted as invalid.
		 *
		 * \param line Char pointer to the offending line. If the string is
		 * larger than 59 characters, it will be restricted to 59. If a nullptr
		 * is passed, the line will be noted as invalid.
		 *
		 * \param invalidValue The offending value in the line.
		 */
		static PuzzleFileException invalidValue(
				const char * filename,
				const char * line,
				char invalidValue);
		/**@}*/

		/**
		 * \brief Trivial destructor for the class.
		 */
		virtual ~PuzzleFileException() throw () {} ;

		/**
		 * \brief Returns a string detailing the reasons why this exception was
		 * thrown.
		 *
		 * Returns the reason why this exception was thrown.
		 * If the reason was TOO_FEW_LINE, this is stated.
		 * If the reason was INVALID_LINE_LENGTH, then the line and its length
		 * is given.
		 * If the reason was INVALID_VALUE, then the value and the line it was
		 * in is returned.
		 */
		virtual const char * what();

		/** @name Getters. */
		/**@{*/

		/**
		 * \brief Returns the reason for why this exception was returned.
		 */
		Reason getReason() const;

		/**
		 * \brief Returns the name of the file that caused this exception to be
		 * thrown.
		 */
		const char * getFilename() const;

		/**
		 * \brief Returns the offending line of the file that caused this
		 * exception to be thrown, if this exception was thrown because of
		 * INVALID_LINE_LENGTH or INVALID_VALUE.
		 *
		 * Note that if the reason for this exception was _not_
		 * INVALID_LINE_LENGTH or INVALID_VALUE, this string will be empty.
		 */
		const char * getLine() const;

		/**
		 * \brief Returns the length of the line of the file that caused this
		 * exception to be thrown, if this exception was thrown because of
		 * INVALID_LINE_LENGTH.
		 *
		 * Note that if the Reason for this exception was not
		 * INVALID_LINE_LENGTH, this will be zero.
		 */
		int getLength() const;

		/**
		 * \brief Returns the character that caused this exception to be
		 * thrown, if this exception was thrown because of INVALID_VALUE.
		 *
		 * Note that if the Reason of this exception was not INVALID_VALUE,
		 * then what is returned will be garbage.
		 */
		char getInvalidValue() const;

		/**@}*/

		/**
		 * \brief Copy constructor; the new PuzzleFileException is set to an
		 * exact copy of other, with its own copy of other's string members.
		 */
		PuzzleFileException(const PuzzleFileException & other);

		/**
		 * \brief Overloaded assignment operator; this exception is set to be
		 * a copy of other, with its own copy of other's string members.
		 */
		PuzzleFileException & operator=(const PuzzleFileException & other);

	protected:
		/**
		 * \brief Protected constructor for the class.
		 *
		 * This constructor is not meant to be called from outside this class,
		 * due to the slight complexity of its required arguments. Creates a
		 * PuzzleFileException with the given Reason, filename of the
		 * offending file, and other relevant information (depending on the
		 * Reason of the exception).
		 *
		 * \param reason Reason for this exception being thrown. Used for
		 * all three types of exception.
		 *
		 * \param filename Name of the file that is invalid for a Reason.
		 * Used for all three types of exception.
		 *
		 * \param line The line in the offending file that caused this
		 * exception to be thrown. Used for the Reasons INVALID_LINE_LENGTH
		 * and INVALID_VALUE.
		 *
		 * \param length Length of an invalid line, used when the reason is
		 * INVALID_LINE_LENGTHs.
		 *
		 * \param invalidValue The invalid value that causes a INVALID_VALUE exception
		 * to be thrown.
		 */
		PuzzleFileException(
				Reason reason,
				const char * filename,
				const char * line = NULL,
				int length = 0,
				char invalidValue = '?');

	protected:
		/**
		 *  \brief Length of the smaller strings used by this class.
		 */
		const static int STR_LEN = 60;

		/**
		 * \brief String that explains why this exception was thrown; created
		 * when what() is called.
		 */
		char whatMessage_[256];

		/**
		 * \brief The reason why this exception was thrown.
		 */
		Reason reason_;

		/**
		 * \brief The name of the file that caused this exception to be thrown.
		 */
		char filename_[STR_LEN];

		/**
		 * \brief When the reason is INVALID_LINE_LENGTH or INVALID_VALUE, this
		 * contains the offending line or the line that contained the offending
		 * value.
		 */
		char line_[STR_LEN];

		/**
		 * \brief When the reason is INVALID_LINE_LENGTH, this contains the
		 * length of the offending line.
		 */
		int length_;

		/**
		 * \brief When the reason is INVALID_VALUE, this contains the invalid
		 * value.
		 */
		char invalidValue_;
	};

public:

	/** @name Constructors and destructors */
	/**@{*/
	/**
	 * \brief Default constructor for the class.
	 *
	 * This creates an empty Puzzle, with all of its Squares unset, solved_ set
	 * to false and numLeftToSolve_ set to \ref PUZZLE_SIZE * \ref PUZZLE_SIZE.
	 */
	Puzzle();

	//TODO 2 test this and default constructor out.
	//TODO 3 comment.
	Puzzle(const std::string & filename);

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
	Square squares_[NUM_SQUARES];
	bool solved_;
	int numLeftToSolve_;
};

#endif /* PUZZLE_H_ */
