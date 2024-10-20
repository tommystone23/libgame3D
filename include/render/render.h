#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <SDL2/SDL.h>

struct game3d_context;

// typedef struct render_context_s {
//     GLuint vbo;
//     GLuint vao;
//     GLuint ebo;  
//     GLuint program_id;
// } render_context;

extern int init_render_objects(struct game3d_context *ctx);

extern int create_shader_program(struct game3d_context *ctx, 
                                const char *vert_shader_path, 
                                const char *frag_shader_path);

extern void game3d_draw(struct game3d_context *ctx);
extern void game3d_render(struct game3d_context *ctx);

#endif // RENDER_H