#include "game3d.h"

game3d_context* game3d_init(const char *name, int window_width, int window_height, uint32_t flags)
{
    game3d_context *ctx = malloc(sizeof(*ctx));

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Failed to initialize SDL");
        return NULL;
    }

    // Setup OpenGL Attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Create Window
    SDL_Window *window = SDL_CreateWindow(name, 0, 0, window_width, window_height, flags);
    if(!window)
    {
        printf("Failed to create SDL window");
        return NULL;
    }
    ctx->window = window;

    // Create Context
    SDL_GLContext gl_ctx = SDL_GL_CreateContext(window);
    if(!gl_ctx)
    {
        printf("Failed to create context");
        return NULL;
    }
    ctx->gl_ctx = gl_ctx;

    // Make Current Context
    SDL_GL_MakeCurrent(window, gl_ctx);

    // Initialize GLAD
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("Failed to load GLAD");
        game3d_quit(ctx);
        return NULL;
    }

    // Create View Port
    glViewport(0, 0, window_width, window_height);

    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);

    // Turn Vsync on
    SDL_GL_SetSwapInterval(1);

    // Print OpenGL Version
    printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    init_render_objects(ctx);

    return ctx;
}

void game3d_quit(game3d_context *ctx)
{
    if(!ctx)
        return;

    SDL_GL_DeleteContext(ctx->gl_ctx);
    SDL_DestroyWindow(ctx->window);
    free(ctx);
    ctx = NULL;
    SDL_Quit();
}

void game3d_event_loop(int *state)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case(SDL_QUIT):
                *state = -1;
                break;
            case(SDL_MOUSEMOTION):
                //_input_manager.set_mouse_coords(event.motion.x, event.motion.y);
                break;
            case(SDL_KEYDOWN):
                //_input_manager.press_key(event.key.keysym.sym);
                break;
            case(SDL_KEYUP):
                //_input_manager.release_key(event.key.keysym.sym);
                break;
            case(SDL_MOUSEBUTTONDOWN):
                //_input_manager.press_key(event.button.button);
                break;
            case(SDL_MOUSEBUTTONUP):
                //_input_manager.release_key(event.button.button);
                break;
        }
    }
}