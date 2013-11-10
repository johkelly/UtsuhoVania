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
		delete tmp;
	}
	tiles[x][y] = t;
	//t->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
	// workaround since POSITION_TOPLEFT seems to be broken with addCollisionChild
	t->setPosition(x*Tile::TILE_SIZE+Tile::TILE_SIZE/2, y*Tile::TILE_SIZE+Tile::TILE_SIZE/2);
	t->setScale(1,1);
	addCollisionChild(tiles[x][y], Polycode::PhysicsScreenEntity::ENTITY_RECT);
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

void TileScreen::runMovement(Polycode::ScreenEntity* a, int& dx, int& dy){
	// TODO

	// Extract actor-backing entity
	// Cache current entity position
	Polycode::ScreenEntity* collBody = a;
	Polycode::Vector3 backPos = a->getPosition();

	// Attempt full horizontal movement
	collBody->Translate(dx, 0, 0);
	Update();

	// If colliding, find collision entity and determine maximum non-colliding motion (put this in dx)
	while(isEntityColliding(collBody)){
		// Determine y coordinates the collBody exists on (even partially)
		// Determine x coord, etc
		int pixY = collBody->getPosition().y - (collBody->getPositionMode() == Polycode::ScreenEntity::POSITION_CENTER ? collBody->height/2 : 0);
		int pixX = collBody->getPosition().x - (collBody->getPositionMode() == Polycode::ScreenEntity::POSITION_CENTER ? collBody->width/2 : 0);
		int pixMaxY = pixY + collBody->height;
		int pixMaxX = pixX + collBody->width;
		int tileY = pixelToTile(pixY);
		int tileX = pixelToTile(pixX);
		int tileMaxY = pixelToTile(pixMaxY);
		int tileMaxX = pixelToTile(pixMaxX);
		// For each tile in the subgrid the actor occupies (x, y):
		// Determine the farthest that tile will allow the actor to move in the movement direction
		int rewindTo = backPos.x;
		for(int x = tileX; x <= tileMaxX; ++x){
			for(int y = tileY; y <= tileMaxY; ++y){
				// Collect the distance farthest opposite direction of travel (i.e. closest to original position)
				Tile* tile = getTile(x,y);
				if(tile == NULL){
					continue;
				}
				int tileRewind = tile->getPosition().x
						// Adjust based on tile positioning mode
						+ (tile->getPositionMode() == Polycode::ScreenEntity::POSITION_CENTER ? tile->getPosition().x : 0)
						// Adjust based on direction of travel
						+ (dx > 0 ? tile->width : 0);
				rewindTo = (tileRewind-backPos.x < rewindTo-backPos.x ? tileRewind : rewindTo);
			}
		}
		// Undo movement, reduce dx to minimum collected allowable
		collBody->Translate(-dx, 0, 0);
		dx = rewindTo;
		// Translate collBody again
		collBody->Translate(dx, 0, 0);
		Update();
		// Repeat last two steps until not colliding after horizontal movement
	}

	// Attempt full vertical movement
	collBody->Translate(0, dy, 0);
	Update();

	while(isEntityColliding(collBody)){
		// Determine y coordinates the collBody exists on (even partially)
		// Determine x coord, etc
		int pixY = collBody->getPosition().y - (collBody->getPositionMode() == Polycode::ScreenEntity::POSITION_CENTER ? collBody->height/2 : 0);
		int pixX = collBody->getPosition().x - (collBody->getPositionMode() == Polycode::ScreenEntity::POSITION_CENTER ? collBody->width/2 : 0);
		int pixMaxY = pixY + collBody->height;
		int pixMaxX = pixX + collBody->width;
		int tileY = pixelToTile(pixY);
		int tileX = pixelToTile(pixX);
		int tileMaxY = pixelToTile(pixMaxY);
		int tileMaxX = pixelToTile(pixMaxX);
		// For each tile in the subgrid the actor occupies (x, y):
		// Determine the farthest that tile will allow the actor to move in the movement direction
		int rewindTo = backPos.y;
		for(int x = tileX; x <= tileMaxX; ++x){
			for(int y = tileY; y <= tileMaxY; ++y){
				// Collect the distance farthest opposite direction of travel (i.e. closest to original position)
				Tile* tile = getTile(x,y);
				if(tile == NULL){
					continue;
				}
				int tileRewind = tile->getPosition().x
						// Adjust based on tile positioning mode
						+ (tile->getPositionMode() == Polycode::ScreenEntity::POSITION_CENTER ? tile->getPosition().x : 0)
						// Adjust based on direction of travel
						+ (dx > 0 ? tile->width : 0);
				rewindTo = (tileRewind-backPos.y < rewindTo-backPos.y ? tileRewind : rewindTo);
			}
		}
		// Undo movement, reduce dx to minimum collected allowable
		collBody->Translate(0, -dy, 0);
		dy = rewindTo;
		// Translate collBody again
		collBody->Translate(0, dy, 0);
		Update();
		// Repeat last two steps until not colliding after horizontal movement
	}

	// Done
}
