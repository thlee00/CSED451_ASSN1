#ifndef MAP_H
#define MAP_H
#include "obj.h"
#include <deque>

using namespace std;

class Map {
private:
	float cnt_jmp;
	int cnt_new_tb;
	int cnt_new_fb;
	float block_x;
	float fb_x;

	User *user;
	deque<TerrainBlock*> terrain_blocks;
	deque<FireBall*> fire_balls;
	deque<Coin*> coins;

public:
	Map();
	void init();
	User* getUser();
	void drawUser();
	void findLRTerrainBlocks(TerrainBlock** left_tb, TerrainBlock** right_tb);
	void calUserPosition(bool* up, bool* down);
	deque<TerrainBlock*> getTerrainBlocks();
	void newTerrainBlock();
	void drawTerrainBlocks();
	deque<FireBall*> getFireBalls();
	void newFireBall();
	void drawFireBalls();
	bool checkFireBall();
	bool checkEndCondition();
	deque<Coin*> getCoins();
	void calCoin();
	void drawCoins();
	bool EatCoin();
	bool calEndCondition();
};
#endif