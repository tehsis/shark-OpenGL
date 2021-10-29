#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum COLORS {
    RED,
    GREEN,
    BLUE,
    BLACK
};


class Shark {

    public:
    Shark(int width, int height, std::string title);
    ~Shark();
    bool ShouldClose();
    void PollEvents();
    void Color(COLORS color);
    void Color(float red, float green, float blue);
    void Triangle(float x, float y);
    void Square(float x, float y);
    void BackgroundColor(COLORS color);
    void Draw();

    private:
    GLFWwindow* window;
    unsigned int ID;
    unsigned int VAO_TRIANGLE;
    unsigned int VAO_SQUARE;
    void init_triangle();
    void init_square();
};