#include <cmath> // Include this header for M_PI
#include <vector>
#include <glm/glm.hpp> // For basic GLM types like glm::vec3
#include <glm/gtc/matrix_transform.hpp> // For transformations like glm::normalize


using namespace std;

class Shape {
public:
    Shape(const std::vector<float>& coordinates) : coordinates_(coordinates) {}

protected:
    std::vector<float> coordinates_;
};

class Sphere{
public:
    Sphere(float _radius, const std::vector<float>& colors, const glm::vec3& position,int staks = 40, int slices = 40)
        : radius(_radius) , NUM_STACKS(staks) , NUM_SLICES(slices)
    {
        r = colors[0];
        g = colors[1];
        b = colors[2];
        generateVerticesAndIndices();
        generateModelMatrix(position);
    }
    vector<float> getVertices() {
        return vertices;
    }
    vector<unsigned int> getIndices() {
        return indices;
    }
    glm::mat4 getModel() {
        return this->Model;
    }
private:
    // Generate a set of vertices for the sphere
    int NUM_STACKS;
    int NUM_SLICES;
    float radius;
    vector<float> vertices;
    vector<unsigned int> indices;;
    float r,g,b;
    glm::mat4 Model = glm::mat4(1.0f);


    void generateVerticesAndIndices() {
        float PI = acos(-1.0f);
        //generate vertices
        for (int i = 0; i < NUM_STACKS; i++) {
            for (int j = 0; j < NUM_SLICES; j++) {
                double theta = 2 * PI * i / (NUM_STACKS - 1);
                double phi = PI * j / (NUM_SLICES - 1);

                float x = cos(theta) * sin(phi) * radius;
                float y = sin(theta) * sin(phi) * radius;
                float z = cos(phi) * radius;
                float u = (theta + 0.5) / (2 * PI);
                float v = (phi + 0.5) / PI;

                // Calculate the normal and normalize it
                glm::vec3 normal(x, y, z);
                normal = glm::normalize(normal);

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                vertices.push_back(r);
                vertices.push_back(g);
                vertices.push_back(b);
                vertices.push_back(u);
                vertices.push_back(v);
                vertices.push_back(normal.x); // Add the normalized normal components
                vertices.push_back(normal.y);
                vertices.push_back(normal.z);
            }
        }
        //generate indices
        for (int i = 0; i < NUM_STACKS - 1; i++) {
            for (int j = 0; j < NUM_SLICES - 1; j++) {
                indices.push_back(i * NUM_SLICES + j);
                indices.push_back(i * NUM_SLICES + j + 1);
                indices.push_back((i + 1) * NUM_SLICES + j + 1);

                indices.push_back(i * NUM_SLICES + j);
                indices.push_back((i + 1) * NUM_SLICES + j + 1);
                indices.push_back((i + 1) * NUM_SLICES + j);
            }
        }
    }
    void generateModelMatrix(const glm::vec3& position) {
        this->Model = glm::translate(Model,position);
    }
};

