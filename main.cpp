// // HEADERS //////////////////////////////////////////////////////////////////

#include <iostream>

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "Shader.h"

// // GLOBAL VARIABLES /////////////////////////////////////////////////////////

float triangleData[] = 
{
    // Positions        Colors
    // x y z            r g b
    0, 1, 0,            1, 0, 0,    // Vertex 1
    -1, -1, 0,          0, 1, 0,    // Vertex 2
    1, -1, 0,           0, 0, 1     // Vertex 3
};

// // MAIN LOOP ////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    std::cout << "Hello, world!" << std::endl;

    // INITIALIZE SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // CREATE A WINDOW
    SDL_Window *window = SDL_CreateWindow("Hello SDL", 100, 100, 680, 480,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window == nullptr)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

    // CREATE AN OpenGL CONTEXT
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
	{
		std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

    // LOAD OpenGL FUNCTIONS USING glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

    // CREATE THE BUFFER
    GLuint buffer = 0;
    glGenBuffers(1, &buffer);   // 1 = only making 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);  // Make sure we're
                                            // binding it as a 
                                            // vertex buffer.

    glBufferData(GL_ARRAY_BUFFER,   // Vertex buffer
        sizeof(triangleData),       // Size
        triangleData,               // The data itself
        GL_STATIC_DRAW              // A hint that this data
                                    // won't get updated
    );

    // SET THE ATTRIBUTES.
    // NOTE: OpenGL REQUIRES THAT ALL GPUs THAT USE IT
    // HAVE A MINIMUM OF 16 ATTRIBUTES SO YOU'RE ALWAYS
    // GUARANTEED SPACE FOR 16 OF THEM.
    // NOTE: The attributes we set here could be swapped
    // but we've set them in this order. Just make sure
    // everything matches properly.
    glEnableVertexAttribArray(0);   // POSITION = slot 0
    glVertexAttribPointer(
        0,      // attribute's number
        3,      // # of components
        GL_FLOAT, // component type
        GL_FALSE, // whether these floats should be sent as ints
        sizeof(float) * 6, // how big a vertex row is
        0       // where in the row to start reading
    );

    glEnableVertexAttribArray(1);   // COLOR = slot 1
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 6,
        (void*)(sizeof(float)*3)    // Legacy code reason for formatting
    );

    Shader shader;
    shader.loadShaderProgramFromFile(
        "resources/myshader.vert",
        "resources/myshader.frag"
    );
    shader.bind();

    // DO THE MAIN LOOP
    bool running = true;
    bool doLegacyTriangleRender = false;
    while (running)
    {
        int w = 0, h = 0;
        SDL_GetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);

        // PROCESS ALL THE PROPER EVENTS
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}

			if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_CLOSE && 
					event.window.windowID == SDL_GetWindowID(window))
				{
					running = false;
				}
			}
		}

        // HANDLE THE RENDERING
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

        /// NOTE: This is just kept here for my own edification.
        if (doLegacyTriangleRender)
        {
            glBegin(GL_TRIANGLES);
            glVertex2f(0, 1);
            glColor3f(1, 0, 0);

            glVertex2f(-1, -1);
            glColor3f(0, 1, 0);

            glVertex2f(1, -1);
            glColor3f(0, 0, 1);

            glEnd();
        }
        else
        {
            // Start at 0th vertex and draw 3
            // If a shader is not loaded, this will either
            // not show, or you will see a white triangle.
            // Some implement a default shader.
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        SDL_GL_SwapWindow(window);

    } // end-main while loop

    glDeleteBuffers(1, &buffer);

    return 0;
}