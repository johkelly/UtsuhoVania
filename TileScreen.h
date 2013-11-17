/*
 * TileScreen.h
 *
 *  Created on: Nov 6, 2013
 *      Author: jack
 */

#ifndef TILESCREEN_H_
#define TILESCREEN_H_

#include <PolyPhysicsScreen.h>
#include <PolyPhysicsScreenEntity.h>

#include <vector>
#include <map>

#include "Tile.h"
#include "TileActor.h"

class TileScreen: public Polycode::PhysicsScreen, TileActorMediator {
public:
	// Constructs a new TileScreen
	// TODO: Since we're only using collision data, the last three args may be unnecessary
	TileScreen(Number worldScale, Number freq, int velIterations=10, int posIterations=10);

	// TileScreen takes ownership of pointers passed to it

	// Adds a tile at the specified coordinate
	// Existing Tile* at the coordinate is delete'd
	// Coordinates are on the tile grid, not in the simulation coordinate space
	void addTile(Tile* t, unsigned int x, unsigned int y);
	// Removes a tile at the specified coordinate
	// Returns: Pointer to the tile removed if a tile was stored at the coordinate, NULL otherwise
	// TileScreen no longer owns the Tile pointer
	Tile* removeTile(int x, int y);
	// Returns: Pointer to a tile at the specified coordinates if a tile existed there, NULL otherwise
	// TileScreen maintains ownership of the tile pointed to
	Tile* getTile(int x, int y);

	void addTileActor(TileActor* a);

	// dx and dy are passed in as desired movement
	// dx and dy are populated after call as actual allowable movement
	// Precondition: *a has been added as an actor to this screen
	// If Violated: dx and dy will be unchanged
	virtual void runMovement(Polycode::ScreenEntity* a, Number dx, Number dy);
private:
	// Tile*'s are laid out in a 2D array structure, with a mapping to their underlying collision entities
	std::map<int, std::map<int, Tile* > > tiles;
	// TileActor*'s are mapped to underlying ScreenEntities
	// All TilerActor classes and subclasses must validate their movement with the TileScreen to prevent desyncs!
	std::vector<TileActor*> actors;
	// Convert from pixel coordinates to tile coordinates and vice versa
	int pixelToTile(Number p) { return floor((p+Tile::TILE_SIZE/2) / Tile::TILE_SIZE); }
	int tileToPixel(Number t) { return t * Tile::TILE_SIZE-Tile::TILE_SIZE/2; }
};

#endif /* TILESCREEN_H_ */
