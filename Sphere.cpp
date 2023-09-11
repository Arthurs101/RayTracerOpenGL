#include <vector>
#include <cmath> // Include this header for M_PI
#include <glad/glad.h>
#define PI 3.1416
class Shape {
public:
    Shape(const std::vector<float>& coordinates) : coordinates_(coordinates) {}

protected:
    std::vector<float> coordinates_;
};

class Sphere : public Shape {
public:
    Sphere(float radius, const std::vector<float>& centerCoordinates, const std::vector<float>& colors)
        : Shape(centerCoordinates), radius_(radius) 
    {
        r = colors[0];
        g = colors[1];
        b = colors[2];
        generateVerticesAndIndices();
    }

    GLfloat* getVertices() {
        return vertices_.data();
    }

     GLuint* getIndices()  {
        return indices_.data();
    }
    
    GLsizeiptr getVerticesSize()  {
        return vertices_.size();
    }

    GLsizeiptr getIndicesSize()  {
        return indices_.size();
    }

private:
    float radius_;
    std::vector<float> vertices_;
    std::vector<unsigned int> indices_;
    float r,g,b;

    void generateVerticesAndIndices() {
        // Create vertices and indices for a sphere
        const int slices = 20;  // Number of horizontal slices
        const int stacks = 20;  // Number of vertical stacks

        for (int i = 0; i <= stacks; ++i) {
            float phi = static_cast<float>(i) / static_cast<float>(stacks) * static_cast<float>(PI);
            for (int j = 0; j <= slices; ++j) {
                float theta = static_cast<float>(j) / static_cast<float>(slices) * static_cast<float>(2 * PI);

                float x = radius_ * std::sin(phi) * std::cos(theta) + coordinates_[0];
                float y = radius_ * std::sin(phi) * std::sin(theta) + coordinates_[1];
                float z = radius_ * std::cos(phi) + coordinates_[2];

                // Calculate texture coordinates based on phi and theta
                float u = static_cast<float>(j) / static_cast<float>(slices);
                float v = static_cast<float>(i) / static_cast<float>(stacks);

                // Add colors (you can change these values)
                vertices_.push_back(x);
                vertices_.push_back(y);
                vertices_.push_back(z);
                vertices_.push_back(r);
                vertices_.push_back(g);
                vertices_.push_back(b);
                vertices_.push_back(u);
                vertices_.push_back(v);

                if (i < stacks && j < slices) {
                    int currRow = i;
                    int nextRow = i + 1;
                    int nextCol = j + 1;

                    indices_.push_back(currRow * (slices + 1) + j);
                    indices_.push_back(nextRow * (slices + 1) + j);
                    indices_.push_back(currRow * (slices + 1) + nextCol);

                    indices_.push_back(currRow * (slices + 1) + nextCol);
                    indices_.push_back(nextRow * (slices + 1) + j);
                    indices_.push_back(nextRow * (slices + 1) + nextCol);
                }
            }
        }
    }
};

