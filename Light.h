//light source
#ifndef LIGHT_CLASS_H
#define	LIGHT_CLASS_H
#include<glad/glad.h>
#include <vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
using namespace std;
class Light
{
public:
	Light(glm::vec3 _pos , glm::vec4 _color);
	void Draw();
	glm::vec3 getPos();
	glm::vec4 getColor();
	glm::mat4 getModel();
private:
	glm::vec3 position;
	glm::vec4 color;
	glm::mat4 model;
};


#endif