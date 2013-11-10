/*
 * Tile.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: jack
 */

#include "Tile.h"

Tile::Tile(Polycode::String tilesheet, Polycode::String tile) : ScreenSprite(tilesheet, TILE_SIZE, TILE_SIZE), type(INVALID) {
	addAnimation("tile", tile, 1);
	playAnimation("tile", 0, false);
}

