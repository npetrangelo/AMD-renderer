#include <stdio.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

typedef struct {
    // Handle to a program object
    GLuint programObject;
} UserData;

GLbyte* read_shader_file(const char *filename) {
    GLbyte* buffer = NULL;
    long length;
    FILE *f = fopen(filename, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(sizeof(GLbyte) * length);
        if (buffer) {
            fread(buffer, 1, length, f);
        }
        fclose (f);
    }

    return buffer;
}

/**
* Create a shader object, load the shader source, and compile the shader.
*/
GLuint LoadShader(const char *shaderSrc, GLenum type) {
    GLint compiled;

    // Create the shader object
    GLuint shader = glCreateShader(type);

    if(shader == 0)
        return 0;
    
    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if(!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1) {
            char* infoLog = malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            printf("Error compiling shader:\n%s\n", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

/**
* Initialize the shader and program object
*/
int Init(ESContext *esContext) {
    UserData* userData = esContext->userData;
    GLbyte* vShaderStr = read_shader_file("helloShaderVert.glsl");
    GLbyte* fShaderStr = read_shader_file("helloShaderFrag.glsl");

    // Load the vertex/fragment shaders
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);

    // Create the program object programObject = glCreateProgram();
    if(programObject == 0)
        return 0;

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    // Bind vPosition to attribute 0
    glBindAttribLocation(programObject, 0, "vPosition");

    // Link the program
    GLuint programObject;
    glLinkProgram(programObject);

    // Check the link status
    GLint linked;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if(!linked) {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1) {
            char* infoLog = malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            printf("Error linking program:\n%s\n", infoLog);
            free(infoLog);
        }
        glDeleteProgram(programObject);
        return FALSE;
    }

    // Store the program object userData->programObject = programObject;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    return TRUE;
}

/*
* Draw a triangle using the shader pair created in Init()
*/
void Draw(ESContext *esContext) {
    UserData *userData = esContext->userData;
    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                          -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f};
    // Set the viewport
    glViewport(0, 0, esContext->width, esContext->height);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    glUseProgram(userData->programObject);

    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

int main(int argc, char *argv[]) {
    ESContext esContext;
    UserData userData;
    esInitialize(&esContext);
    esContext.userData = &userData;
    esCreateWindow(&esContext, "Hello Triangle", 320, 240, ES_WINDOW_RGB);
    if(!Init(&esContext))
        return 0;
    esRegisterDrawFunc(&esContext, Draw);
    esMainLoop(&esContext);
}