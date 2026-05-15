#pragma once

/**
 * @file Shader.h
 * @date 2026-05-14
 * @author Peter Young
 * 
 * @brief A basic struct to help organize and abstract GL shaders
 */

// // HEADERS //////////////////////////////////////////////////////////////////

#include <glad/glad.h>

// // NAMESPACE ////////////////////////////////////////////////////////////////

struct Shader
{

    GLuint id = 0;

    bool loadShaderProgramFromFile(
        const char *vertexShaderPath,
        const char* fragmentShaderPath
    );

    bool loadShaderFromData(
        const char *vertexShaderData,
        const char *fragmentShaderData
    );

    GLint createShaderFromData(
        const char* data,
        GLenum shaderType
    );

    void bind();

    void clear();

    GLint getUniformLocation(const char *name);

}; // end-struct Shader

// // EOF //////////////////////////////////////////////////////////////////////