#include <vector>
#include <cmath> // Include this header for M_PI
#include <glad/glad.h>

class Shape {
public:
    Shape(const std::vector<float>& coordinates) : coordinates_(coordinates) {}

protected:
    std::vector<float> coordinates_;
};

class Sphere : public Shape {
public:
    std::vector<unsigned int> indices_;
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
    float r,g,b;

    void generateVerticesAndIndices() {
        const float PI = acos(-1.0f);
        // Create vertices and indices for a sphere
        const int slices = 36;  // Number of horizontal slices
        const int stacks = 28;  // Number of vertical stacks
        float sectorStep = 2 * PI / slices;
        float stackStep = PI / stacks;
        float sectorAngle, stackAngle;

        for (int i = 0; i <= stacks; ++i) {
            stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
            float xy = radius_ * cosf(stackAngle);             // r * cos(u)
            float z = radius_ * sinf(stackAngle);              // r * sin(u)
            for (int j = 0; j <= slices; ++j) {
                float theta = static_cast<float>(j) / static_cast<float>(slices) * static_cast<float>(2 * PI);

                sectorAngle = j * sectorStep;           // starting from 0 to 2pi

                // vertex position
                float x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
                float y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

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
            }
        }
        //create the indices:
        //  k1--k1+1
        //  |  / |
        //  | /  |
        //  k2--k2+1
        unsigned int k1, k2;
        for (int i = 0; i <= stacks; ++i) {
            k1 = i * (slices + 1);     // beginning of current stack
            k2 = k1 + slices + 1;      // beginning of next stack
            for (int j = 0; j < slices; ++j, ++k1, ++k2) {
                if (i != 0)
                {
                    indices_.push_back(k1);
                    indices_.push_back(k2);
                    indices_.push_back( k1 + 1);   // k1---k2---k1+1
                }

                if (i != (stacks - 1))
                {
                    indices_.push_back(k1+1);
                    indices_.push_back(k2);
                    indices_.push_back(k2 + 1);   // k1---k2---k1+1
                }

            }
        }
    }
};

