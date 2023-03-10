#include "map.h"

Map::Map() {
	cnt_jmp = 0.0;
	cnt_new_tb = 0;
	cnt_new_fb = 0;
	block_x = 0.0;
	fb_x = 1.0;
}

void Map::init() {
	user = new User();
	for (int i = 0; i < 5; i++) {
		TerrainBlock* tb = new TerrainBlock();
		block_x += 0.3;
		tb->setX(block_x);
		terrain_blocks.push_back(tb);
	}
}

User* Map::getUser() { return user; }

void Map::drawUser() {
	user->draw();
}

void Map::calUserPosition(bool* up, bool* down) {
	user->setX(user->getX() + 0.01);
	
	for (int i = 0; i < terrain_blocks.size(); i++) {
		TerrainBlock* cur_tb = terrain_blocks[i];
		if (!cur_tb->getExist() && (cur_tb->getX() - 0.3 <= user->getX() && user->getX() + user->getW() <= cur_tb->getX())) {
			user->setY(user->getY() - 0.01);
			break;
		}
	}
	

	if (*up == true) {
		if (cnt_jmp < 0.35) {
			user->setY(user->getY() + 0.01);
			cnt_jmp += 0.01;
		}
		else {
			*up = false;
			*down = true;
			cnt_jmp = 0.0;
		}
	}
	else if (*down == true) {
		if (cnt_jmp < 0.35) { //점프력 상향
			user->setY(user->getY() - 0.01);
			if (user->getY() < 0.2) {
				for (int i = 0; i < terrain_blocks.size(); i++) {
					TerrainBlock* cur_tb = terrain_blocks[i];
					if (cur_tb->getExist() && (cur_tb->getX() - 0.3 <= user->getX() && user->getX() + user->getW() <= cur_tb->getX())) {
						user->setY(0.2);
						break;
					}
				}
			}
			cnt_jmp += 0.01;
		}
		else {
			cnt_jmp = 0.0;
			*down = false;
		}
	}
	else {
		for (int i = 0; i < terrain_blocks.size(); i++) {
			TerrainBlock* cur_tb = terrain_blocks[i];
			if (!cur_tb->getExist() && (cur_tb->getX() - 0.3 <= user->getX() && user->getX() + user->getW() <= cur_tb->getX())) {
				user->setY(user->getY() - 0.01);
				break;
			}
		}
	}
}

deque<TerrainBlock*> Map::getTerrainBlocks() { return terrain_blocks; }

void Map::calTerrainBlock() {
	cnt_new_tb++;

	if (cnt_new_tb == 30) {
		TerrainBlock* tb = new TerrainBlock();
		block_x += 0.3;
		tb->setX(block_x);

		if (!terrain_blocks.empty() && !terrain_blocks.back()->getExist())
			tb->setExist(true);
		else
			if(rand() % 4 >= 1) tb->setExist(true);
			else tb->setExist(false);
			//블럭 없어질 확률을 1/4로 하향

		cnt_new_tb = 0;
		terrain_blocks.push_back(tb);
		if (terrain_blocks.size() > 5) {
			TerrainBlock* rmv = terrain_blocks.front();
			terrain_blocks.pop_front();
			delete rmv;
		}
	}
}

void Map::drawTerrainBlocks() {
	for (int i = 0; i < terrain_blocks.size(); i++)
		terrain_blocks[i]->draw();
}

deque<FireBall*> Map::getFireBalls() { return fire_balls; }

void Map::calFireBall() {
	deque<FireBall*>::iterator iter = fire_balls.begin();
	while (!fire_balls.empty() && iter != fire_balls.end()) {
		FireBall* fb = *iter;
		float fb_x = fb->getX();
		fb->setX(fb_x - 0.005);
		if (fb_x < user->getX() - 0.2) {
			FireBall* rmv = *iter;
			iter++;
			fire_balls.pop_front();
			delete rmv;
		}
		else
			iter++;
	}

	if (rand() / (double)RAND_MAX * 100.0 < 0.2) { //파이어볼 생성 확률 하향
		FireBall* fb = new FireBall();
		fb->setX(user->getX() + 0.9);

		if (!terrain_blocks.empty() && ((terrain_blocks.back()->getX() >= fb->getX() && !terrain_blocks.back()->getExist())))
			fb->setElev(false);
		else if (!fire_balls.empty() && !fire_balls.back()->getElev())
			fb->setElev(true);
		else
			fb->setElev(rand() % 2);
		fb->setY(fb->getElev() ? 0.53 : 0.3);
		fire_balls.push_back(fb);
	}
}

void Map::drawFireBalls() {
	for (int i = 0; i < fire_balls.size(); i++)
		fire_balls[i]->draw();
}


deque<Coin*> Map::getCoins() { return coins; }

void Map::calCoin() {
	deque<Coin*>::iterator iter = coins.begin();
	while (!coins.empty() && iter != coins.end()) {
		Coin* c = *iter;
		float c_x = c->getX();
		if (c_x < user->getX() - 0.2) {
			Coin* rmv = *iter;
			iter++;
			coins.pop_front();
			delete rmv;
		}
		else
			iter++;
	}

	if (rand() / (double)RAND_MAX * 100.0 < 1 && coins.size() < 10) {
		Coin* c = new Coin();
		c->setX(user->getX() + 0.9);
		if(rand() % 3 == 0) c->setY(c->getY() + 0);
		else if (rand() % 3 == 1) c->setY(c->getY() + 0.25);
		else c->setY(c->getY() + 0.45);
		//Set 3 kinds of height where coins to be placed
		coins.push_back(c);
	}
}

void Map::drawCoins() {
	for (int i = 0; i < coins.size(); i++)
		coins[i]->draw();
}

bool Map::EatCoin() { //Check whether user contacts with coin or not, and erase the eaten coin
	deque<Coin*>::iterator iter = coins.begin();
	int count = 0;
	while (!coins.empty() && iter != coins.end()) {
		Coin* c = *iter;
		float c_x = c->getX();
		float c_y = c->getY();
		if (c_x >= user->getX() && c_x <= user->getX() + user->getW()) {
			if (c_y >= user->getY() && c_y <= user->getY() + user->getH()) {
				coins.erase(coins.begin() + count);
				return true;
			}
		}
		c_x += c->getH();
		if (c_x >= user->getX() && c_x <= user->getX() + user->getW()) {
			if (c_y >= user->getY() && c_y <= user->getY() + user->getH()) {
				coins.erase(coins.begin() + count);
				return true;
			}
		}
		c_x = c->getX();
		c_y += c->getH();
		if (c_x >= user->getX() && c_x <= user->getX() + user->getW()) {
			if (c_y >= user->getY() && c_y <= user->getY() + user->getH()) {
				coins.erase(coins.begin() + count);
				return true;
			}
		}
		c_x += c->getH();
		if (c_x >= user->getX() && c_x <= user->getX() + user->getW()) {
			if (c_y >= user->getY() && c_y <= user->getY() + user->getH()) {
				coins.erase(coins.begin() + count);
				return true;
			}
		}
		iter++;
		count++;
	}
	return false;
}

bool Map::calEndCondition() {
	///if()
	return false;
}