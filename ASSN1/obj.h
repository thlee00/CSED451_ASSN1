#ifndef OBJ_H
#define OBJ_H
#include <vector>

class RectObj {
private:
	float w;
	float h;

protected:
	float x;
	float y;

public:
	RectObj();
	void set(float _x, float _y, float _w, float _h);
	void setX(float _x);
	void setY(float _y);
	float getX();
	float getY();
	void draw();
};

class User : public RectObj {
private:
	;
public:
	User();
	void draw();
};

class Block : public RectObj {
private:
	bool exist;

public:
	Block();
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