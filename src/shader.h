#ifndef SHADER_H
#define SHADER_H

#include "render/render.h"

//struct game3d_context;

extern int create_shaders(struct game3d_context *ctx,
                        const char *vert_shader_path,
                        const char *frag_shader_path);

extern int compile_shader(GLuint shader_id, const char *file_path);

extern int link_shaders(GLuint prog_id, GLuint vert_id, GLuint frag_id);

#endif //SHADER_H