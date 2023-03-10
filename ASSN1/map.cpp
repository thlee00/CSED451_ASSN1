#include "map.h"

Map::Map() {
	cnt_new_block = 0;
	block_x = 1.3;
}

/* Initialize all things */
void Map::init() {
	user = new User();
	user->set(0.1, 0.2, 0.1, 0.3);
}

User* Map::getUser() { return user; }
void Map::drawUser() {
	user->draw();
}

deque<Block*> Map::getBlocks() { return blocks; }
void Map::calTerrainBlock() {
	cnt_new_block++;

	if (cnt_new_block == 30) {
		Block* tmp = new Block();
		block_x += 0.3;
		tmp->setX(block_x);

		if (!blocks.empty() && !blocks.back()->getExist())
			tmp->setExist(true);
		else
			tmp->setExist(rand() % 2);

		cnt_new_block = 0;
		blocks.push_back(tmp);
		if (blocks.size() > 5) {
			Block* rmv = blocks.front();
			blocks.pop_front();
			delete rmv;
		}
	}
}

void Map::drawTerrainBlocks() {
	for (int i = 0; i < blocks.size(); i++)
		blocks[i]->draw();
}

deque<FireBall*> Map::getFireBalls() { return fire_balls; }
void Map::calFireBall() {
	deque<FireBall*>::iterator iter = fire_balls.begin();
	while (!fire_balls.empty() && iter != fire_balls.end()) {
		FireBall* fb = *iter;
		float fb_x = fb->getX();
		fb->setX(fb_x -0.005);
		if (fb_x < user->getX() - 0.2) {
			FireBall* rmv = *iter;
			iter++;
			fire_balls.pop_front();
			delete rmv;
		}
		else
			iter++;
	}

	if (rand() / (double)RAND_MAX * 100.0 < 1.0) {
		FireBall* fb = new FireBall();
		fb->setX(user->getX() + 0.9);

		if (!blocks.empty() && ((blocks.back()->getX() >= fb->getX() && !blocks.back()->getExist())))
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

