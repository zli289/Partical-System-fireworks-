#ifndef __GWU_Ball__
#define __GWU_Ball__

class Ball
{
public:
	vec3 velocity, position, a;
	GLfloat matrix[16];
	GLfloat size;

	Ball();
	Ball(vec3 velocity, vec3 position,GLfloat size=0.2f);
	~Ball();
	void updateM();
	void gravity(GLfloat t);
	void split(std::vector<Ball> particles);
};

Ball::Ball()
{
	velocity=vec3(RandomFloat(-1,1),RandomFloat(4,8),RandomFloat(-1,1));
	position=vec3(RandomFloat(-0.5,0.5),RandomFloat(-0.5,0.5),RandomFloat(-0.5,0.5));
	size=0.05f;
}
Ball::~Ball(){}

Ball::Ball(vec3 velocity, vec3 position,GLfloat size)
{
	this->velocity=velocity;
	this->position=position;
	this->size=size;
	a=vec3(0,-2.0f,0);

	for(int i=0;i< 4;i++)
		matrix[i*5]=1.0f;
	updateM();
}

void Ball::updateM()
{
	matrix[12]=position[0];
	matrix[13]=position[1];
	matrix[14]=position[2];
}

void Ball::gravity(GLfloat t)
{
	velocity += a*t;
	position+= velocity*t;
	updateM();
}

void Ball::split(std::vector<Ball> particles)
{
	
}

#endif