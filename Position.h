/*
 * Position.h
 *
 *  Created on: 16 Sep 2014
 *      Author: alex
 */

#ifndef POSITION_H_
#define POSITION_H_

struct Position{
public:
	int row;
	int col;
public:
	Position(int row = 0, int col = 0);
	Position(const Position & other);
	Position & operator=(const Position & other);
};

#endif /* POSITION_H_ */
