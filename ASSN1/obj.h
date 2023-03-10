#ifndef OBJ_H
#define OBJ_H
#include <vector>

class RectObj {
private:
	;

protected:
	float x;
	float y;
	float w;
	float h;

public:
	RectObj();
	void set(float _x, float _y, float _w, float _h);
	void setX(float _x);
	void setY(float _y);
	float getX();
	float getY();
	float getW();
	float getH();
	void draw();
};

class User : public RectObj {
private:
	;

public:
	User();
	void draw();
};

class TerrainBlock : public RectObj {
private:
	bool exist;

public:
	TerrainBlock();
	void setExist(bool e);
	bool getExist();
	void draw();
};

class FireBall : public RectObj {
private:
	bool elev;

public:
	FireBall();
	void setElev(bool e);
	bool getElev();
	void draw();
};
#endif