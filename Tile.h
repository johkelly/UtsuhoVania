/*
 * Tile.h
 *
 *  Created on: Nov 6, 2013
 *      Author: jack
 */

#ifndef TILE_H_
#define TILE_H_

#include <PolyScreenSprite.h>
#include <PolyString.h>

class Tile : public Polycode::ScreenSprite{
public:
	const static Number TILE_SIZE = 17;
	enum TileType{
		INVALID,
		EMPTY,
		WATER,
		SLOPE,
		SOLID
	};

	TileType type;

	Tile(Polycode::String tilesheet, Polycode::String tile);
private:
};

#endif /* TILE_H_ */
