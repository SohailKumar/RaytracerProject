#include <memory>
#include <tuple>
#include <cmath>
#include <print>

#include "Material.h"
#include "Light.h"

Material::Material() {
	this->radianceValues = glm::vec3(0.0f, 0.0f, 0.0f);

	this->diffuseColor = glm::vec3(1.0f, 0.0f, 0.0f);
	this->specularColor = glm::vec3(0.0f, 0.0f, 0.0f);
	this->ambient_k = 1.0f;
	this->diffuse_k = 1.0f;
	this->specular_k = 1.0f;
	this->shiny_exp = 2.0f;
}

Material::Material(glm::vec3 values, glm::vec3 diffuseColor, glm::vec3 specularColor, float ambient_k, float diffuse_k, float specular_k, float shiny_exp) {
	this->radianceValues = values;

	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
	this->ambient_k = ambient_k;
	this->diffuse_k = diffuse_k;
	this->specular_k = specular_k;
	this->shiny_exp = shiny_exp;
}

std::tuple<glm::vec3, glm::vec3> Material::CalculateRadiance(glm::vec3 point, glm::vec3 normal, glm::vec3 incoming, glm::vec3 reflection, glm::vec3 viewDir, const Light* light)
{
	/*if (glm::dot(incoming, normal) < 0) {
		std::println("DOT1 = {}, {}", glm::dot(incoming, normal), glm::clamp(glm::dot(incoming, normal), 0.0f, 1.0f));
	}*/
	//std::println("viewDir = {}, {}, {}", viewDir[0], viewDir[1], viewDir[2]);
	//if (glm::dot(reflection, viewDir) < 0) {
	//	std::println("DOT2 = {}", glm::dot(reflection, viewDir), glm::clamp(glm::dot(reflection, viewDir), 0.0f, 1.0f));
	//}
	glm::vec3 diffuse = light->color * this->diffuseColor * (glm::clamp(glm::dot(incoming, normal), 0.0f, 1.0f));
	glm::vec3 specular = light->color * this->specularColor * std::pow(glm::clamp(glm::dot((reflection), viewDir), 0.0f, 1.0f), shiny_exp);
	//TODO: Fix reflection to be 
	return {diffuse, specular};
}
