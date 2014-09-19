/*
 * Position.h
 *
 *  Created on: 16 Sep 2014
 *      Author: Alexander Senior.
 */

#ifndef POSITION_H_
#define POSITION_H_

/**
 * \class Position
 * \brief Convenience struct to represent a position in a Sudoku puzzle,
 * being a row and a column.
 */
struct Position{
public:
	/** \var row
	 *  \brief Row of the Sudoku puzzle.
	 */
	int row;

	/** \var col
	 *  \brief Column of the Sudoku puzzle.
	 */
	int col;
public:
	/**
	 * Constructions a Position with the given row and column. Row and column
	 * both default to 0.
	 */
	Position(int row = 0, int col = 0);

	/**
	 * Copy constructor.
	 */
	Position(const Position & other);

	/**
	 * Assignment operator; row and col will be copied from 'other'.
	 */
	Position & operator=(const Position & other);
};

#endif /* POSITION_H_ */
