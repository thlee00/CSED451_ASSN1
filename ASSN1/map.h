#ifndef MAP_H
#define MAP_H
#include "obj.h"
#include <deque>

using namespace std;

class Map {
private:
	int cnt_new_block;
	float block_x;

	User *user;
	deque<Block*> blocks;
	deque<FireBall*> fire_balls;

public:
	Map();
	void init();
	User* getUser();
	void drawUser();
	deque<Block*> getBlocks();
	void calTerrainBlock();
	void drawTerrainBlocks();
	deque<FireBall*> getFireBalls();
	void calFireBall();
	void drawFireBalls();
	
};
#endif