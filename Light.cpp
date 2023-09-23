#include "Light.h"
Light::Light(glm::vec3 _pos , glm::vec4 _color) {
	this->position = _pos;
	this->color = _color;
	this->model = glm::mat4(1.0f);
	this->model = glm::translate(this->model, this->position);
}