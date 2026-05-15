// // HEADERS //////////////////////////////////////////////////////////////////

#include "Shader.h"

#include "utilities.h"

// // NAMESPACE ////////////////////////////////////////////////////////////////

/// @brief Load a shader from the appropriate GLSL files
/// @param vertexShaderPath the vertex shader filepath
/// @param fragmentShaderPath the fragment shader filepath
/// @return 
bool Shader::loadShaderProgramFromFile(
    const char* vertexShaderPath,
    const char* fragmentShaderPath)
{
    char *vertexData = readFileContents(vertexShaderPath);
    char *fragmentData = readFileContents(fragmentShaderPath);

    if (vertexData == nullptr || fragmentData == nullptr)
    {
        delete[] vertexData;
        delete[] fragmentData;
        return 0;
    }

    bool rez = loadShaderFromData(vertexData, fragmentData);
    delete[] vertexData;
    delete[] fragmentData;

    return rez;

} // end-loadShaderProgramFromFile


/// @brief Load the shader from the appropriate data
/// @param vertexShaderData the vertex shader data (from GLSL file)
/// @param fragmentShaderData the fragment shader data (from GLSL file)
/// @return 
bool Shader::loadShaderFromData(
    const char *vertexShaderData,
    const char *fragmentShaderData)
{
    auto vertexID = createShaderFromData(
        vertexShaderData, GL_VERTEX_SHADER);
    if (vertexID == 0) return 0;

    auto fragmentID = createShaderFromData(
        fragmentShaderData, GL_FRAGMENT_SHADER);
    if (fragmentID == 0) {
        glDeleteShader(vertexID);
        return 0;
    }

    id = glCreateProgram();

    glAttachShader(id, vertexID);
    glAttachShader(id, fragmentID);

    glLinkProgram(id);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    GLint info = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &info);
    if (info != GL_TRUE)
    {
        char *message = 0;
        int l = 0;

        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &l);

        message = new char[l];
        glGetShaderInfoLog(id, l, &l, message);
        message[l-1] = 0;
        std::cout << "Link error: " << message << "\n";
        delete[] message;

        glDeleteProgram(id);
        id = 0;
        return false;
    }

    glValidateProgram(id);

    return true;
} // end-loadShaderProgramFromData


/// @brief Create a shader from the given data
/// @param data the shader data
/// @param shaderType the shader type (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
/// @return 
GLint Shader::createShaderFromData(const char *data, GLenum shaderType)
{

    GLuint shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &data, nullptr);
    glCompileShader(shaderID);

    GLint result = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        char *message = 0;
        int l = 0;

        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &l);

        if (l)
        {
            message = new char[l];
            glGetShaderInfoLog(shaderID, l, &l, message);
            message[l-1] = 0;
            std::cout << data << ":\n" << message << "\n";
            delete[] message;
        }
        else
            std::cout << data << ":\n" << "unknown error\n";

        glDeleteShader(shaderID);
        shaderID = 0;
    }

    return shaderID;

} // end-createShaderFromData


void Shader::bind() { glUseProgram(id); }
void Shader::clear() {
    glDeleteProgram(id);
    *this = {};
}


// // EOF //////////////////////////////////////////////////////////////////////