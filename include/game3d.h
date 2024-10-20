#ifndef GAME3D_H
#define GAME3D_H

#include "render/render.h"

typedef struct game3d_context {
    SDL_GLContext *gl_ctx;
    SDL_Window *window;
    GLuint vbo;
    GLuint vao;
    GLuint ebo;  
    GLuint program_id;
} game3d_context;

extern game3d_context* game3d_init(const char *name, int window_width, int window_height, uint32_t flags);

extern void game3d_quit(game3d_context *ctx);

extern void game3d_event_loop(int *state);

#endif //GAME3D_H