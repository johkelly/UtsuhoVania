/*
 * TileScreen.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: jack
 */

#include <limits.h>
#include <algorithm>

#include "TileScreen.h"

TileScreen::TileScreen(Number worldScale, Number freq, int velIterations, int posIterations)
: PhysicsScreen(worldScale, freq, velIterations, posIterations)
{ /*Initialization list only */}

void TileScreen::addTile(Tile* t, unsigned int x, unsigned int y){
	Tile* tmp = getTile(x, y);
	if(tmp != NULL){
		removeChild(tmp);
		delete tmp;
	}
	tiles[x][y] = t;
	//t->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
	// workaround since POSITION_TOPLEFT seems to be broken with addCollisionChild
	t->setPosition(x*Tile::TILE_SIZE, y*Tile::TILE_SIZE);
	t->setHitbox(Tile::TILE_SIZE, Tile::TILE_SIZE, t->position.x-Tile::TILE_SIZE/2, t->position.y-Tile::TILE_SIZE/2);
	t->setScale(1,1);
	addChild(t);
}

Tile* TileScreen::removeTile(int x, int y){
	if(tiles.size() > x){
		if(tiles[x].size() > y){
			Tile* ret = getTile(x, y);
			tiles[x][y] = NULL;
			return ret;
		}
	}
	return NULL;
}

Tile* TileScreen::getTile(int x, int y){
	if(tiles.find(x) != tiles.end()){
		if(tiles[x].find(y) != tiles[x].end()){
			return tiles[x][y];
		}
	}
	return NULL;
}

void TileScreen::addTileActor(TileActor* a){
	actors.push_back(a);
	a->registerTo(this);
	addCollisionChild(a, Polycode::PhysicsScreenEntity::ENTITY_RECT);
}

void TileScreen::runMovement(Polycode::ScreenEntity* a, Number dx, Number dy){
	// Extract actor-backing entity
	// Cache current entity position
	Polycode::ScreenEntity* collBody = a;
	Polycode::Vector3 backPos = a->getPosition();

	// Attempt full horizontal movement
	collBody->Translate(dx, 0, 0);

	// If colliding, find collision entity and determine maximum non-colliding motion (put this in dx)
	for(bool redoTileCheck = true; redoTileCheck; ){
		// Determine y coordinates the collBody exists on (even partially)
		// Determine x coord, etc
		Polycode::Rectangle entityBox(collBody->position.x - collBody->width/2,
				collBody->position.y - collBody->height/2,
				collBody->width,
				collBody->height);
		int tileY = pixelToTile(entityBox.y);
		int tileX = pixelToTile(entityBox.x);
		int tileMaxY = pixelToTile(entityBox.y+entityBox.h);
		int tileMaxX = pixelToTile(entityBox.x+entityBox.w);
		// For each tile in the subgrid the actor occupies (x, y):
		// Determine the farthest that tile will allow the actor to move in the movement direction
		Number rewind = 0;
		for(int x = tileX; x <= tileMaxX; ++x){
			for(int y = tileY; y <= tileMaxY; ++y){
				// Collect the distance farthest opposite direction of travel (i.e. closest to original position)
				Tile* tile = getTile(x,y);
				if(tile == 0x0){
					continue;
				}
				Polycode::Rectangle tileBox = tile->getHitbox();
				Polycode::Rectangle collBox = entityBox.Clipped(tileBox);
				if(collBox.w * collBox.h != 0){
					/** Tile Interaction Logic **/
					Number tileRewind = collBox.w * (dx > 0 ? -1 : 1);
					rewind = (abs(rewind) > abs(tileRewind) ? rewind : tileRewind);
					/** End TIL **/
				}
			}
		}
		if(rewind == 0){
			redoTileCheck = false;
		}
		// Rewind movement
		collBody->Translate(rewind, 0, 0);
		// Repeat until not colliding after horizontal movement
	}

	// Attempt full vertical movement
	collBody->Translate(0, dy, 0);

	// If colliding, find collision entity and determine maximum non-colliding motion (put this in dx)
	for(bool redoTileCheck = true; redoTileCheck; ){
		// Assume the entity does not need to recheck its position
		redoTileCheck = false;
		// Determine y coordinates the collBody exists on (even partially)
		// Determine x coord, etc
		Polycode::Rectangle entityBox(collBody->position.x - collBody->width/2,
				collBody->position.y - collBody->height/2,
				collBody->width,
				collBody->height);
		int tileY = pixelToTile(entityBox.y);
		int tileX = pixelToTile(entityBox.x);
		int tileMaxY = pixelToTile(entityBox.y+entityBox.h);
		int tileMaxX = pixelToTile(entityBox.x+entityBox.w);
		// For each tile in the subgrid the actor occupies (x, y):
		// Determine the farthest that tile will allow the actor to move in the movement direction
		Number rewind = 0;
		for(int x = tileX; x <= tileMaxX; ++x){
			for(int y = tileY; y <= tileMaxY; ++y){
				// Collect the distance farthest opposite direction of travel (i.e. closest to original position)
				Tile* tile = getTile(x,y);
				if(tile == 0x0){
					continue;
				}
				Polycode::Rectangle tileBox = tile->getHitbox();
				Polycode::Rectangle collBox = entityBox.Clipped(tileBox);
				if(collBox.w * collBox.h != 0){
					/** Tile Interaction Logic **/
					Number tileRewind = collBox.h * (dy > 0 ? -1 : 1);
					rewind = (abs(rewind) > abs(tileRewind) ? rewind : tileRewind);
					/** End TIL **/
				}
			}
		}
		if(rewind == 0){
			redoTileCheck = false;
		}
		// Rewind movement
		collBody->Translate(0, rewind, 0);
		// Repeat until not colliding after vertical movement
	}

	// Done
}
