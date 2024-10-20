#include "render/render.h"
#include "game3d.h"
#include "shader.h"

int init_render_objects(game3d_context *ctx)
{
    if(!ctx)
        return -1;

    GLuint vbo;
    GLuint vao;
    GLuint ebo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    ctx->vbo = vbo;
    ctx->vao = vao;
    ctx->ebo = ebo;

    return 0;
}

int create_shader_program(game3d_context *ctx, 
                        const char *vert_shader_path, 
                        const char *frag_shader_path)
{   
    return create_shaders(ctx, vert_shader_path, frag_shader_path);
}

// For now take nothing and draw square
// Will need to make Vertex object to hold all vertices, colour, texture data
// to pass in.
void game3d_draw(game3d_context *ctx)
{
    glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx->ebo);

    float vertices[] = {
    0.5f, 0.5f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f // top left
    };
    unsigned int indices[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void game3d_render(game3d_context *game_ctx)
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glBindVertexArray(game_ctx->vao);
    glUseProgram(game_ctx->program_id);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glUseProgram(0);

    glBindVertexArray(0);

    SDL_GL_SwapWindow(game_ctx->window);
}