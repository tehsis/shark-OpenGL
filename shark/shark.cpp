#include "shark.h"
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int w, int h);


Shark::Shark(int width, int height, std::string title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == NULL) {
        throw "Could not create window";
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw "Failed to initialize GLAD";
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    init_triangle();

    std::string vertexCode, fragmentCode;
    std::ifstream vertexShaderFile, fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexShaderFile.open("shark/shaders/vertex.glsl");
        fragmentShaderFile.open("shark/shaders/fragment.glsl");
        std::stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    } catch (std::ifstream::failure e) {
        throw "Could not read shader files";
    }

    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infolog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infolog);
        std::stringstream response;
        response << "Could not compile Vertex shader: " << infolog << std::endl;
        throw response.str().c_str();
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success) {
         glGetShaderInfoLog(fragment, 512, NULL, infolog);
        std::stringstream response;
        response << "Could not compile Fragment shader: " << infolog << std::endl;
        throw response.str().c_str();
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infolog);
        std::stringstream response;
        response << "Could not link program: " << infolog << std::endl;
        throw response.str().c_str();
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glUseProgram(ID);

}

Shark::~Shark() {
    glfwTerminate();
    delete window;
}

void Shark::init_triangle() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int VBO;
    glGenVertexArrays(1, &VAO_TRIANGLE);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO_TRIANGLE);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Shark::Draw() {
    glfwSwapBuffers(window);
}


void Shark::Triangle(float x, float y) {
    int location = glGetUniformLocation(ID, "offset");
    glUniform2f(location, x, y);
    glBindVertexArray(VAO_TRIANGLE);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Shark::Color(COLORS color) {
    
    if (color == RED) {
        Color(1.0f, 0.0f, 0.0f);
    } else if (color == BLUE) {
        Color(0.0f, 1.0f, 0.0f);
    } else if (color == GREEN) {
        Color(0.0f, 0.0f, 1.0f);
    } else {
        Color(0.0f, 0.0f, 0.0f);
    }
}

void Shark::Color(float red, float green, float blue) {
    int location = glGetUniformLocation(ID, "color");
    glUniform3f(location, red, green, blue);

}

void Shark::BackgroundColor(COLORS color) {
    if (color == RED) {
      glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    } else {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // defaults to black
    }
    glClear(GL_COLOR_BUFFER_BIT);
}

void Shark::PollEvents() {
    return glfwPollEvents();
}

bool Shark::ShouldClose() {
    return glfwWindowShouldClose(this->window);
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);   
}


