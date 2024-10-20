#include "shader.h"
#include "game3d.h"
#include <stdio.h>

int create_shaders(game3d_context *ctx,
                    const char *vert_shader_path,
                    const char *frag_shader_path)
{
    GLuint program_id = glCreateProgram();
    GLuint vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
    if(!vert_shader_id)
        return -1;
    GLuint frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    if(!frag_shader_id)
        return -1;
    
    int ret = 0;
    ret = compile_shader(vert_shader_id, vert_shader_path);
    if(ret < 0)
        return ret;
    
    ret = compile_shader(frag_shader_id, frag_shader_path);
    if(ret < 0)
        return ret;

    ret = link_shaders(program_id, vert_shader_id, frag_shader_id);
    if(ret < 0)
        return ret;

    ctx->program_id = program_id;

    return ret;
}

int compile_shader(GLuint shader_id, const char *file_path)
{
    FILE *f = fopen(file_path, "rb");
    if(!f) {
        printf("failed to open file %s\n", file_path);
        return -1;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = malloc((length + 1) * sizeof(char));
    if(!buf) {
        printf("failed to initialize buffer\n");
        return -1;
    }
    fread(buf, 1, length, f);
    buf[length + 1] = '\0';

    fclose(f);

    glShaderSource(shader_id, 1, (const char *const *)&buf, NULL);
    glCompileShader(shader_id);

    free(buf);

    GLint success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
        GLint max_buffer = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_buffer);
        char *error = malloc(max_buffer * sizeof(char));
        if(!error) {
            printf("failed to allocate error buffer\n");
            return -1;
        }
        glGetShaderInfoLog(shader_id, max_buffer, &max_buffer, error);

        glDeleteShader(shader_id);

        free(error);

        printf("Unable to compile shader %s due to: %s\n", file_path, error);
        return -1;
    }

    return 0;
}

int link_shaders(GLuint prog_id, GLuint vert_id, GLuint frag_id)
{
    // Attach shaders
    glAttachShader(prog_id, vert_id);
    glAttachShader(prog_id, frag_id);

    // Link the program
    glLinkProgram(prog_id);

    // Error checking/handling
    GLint is_linked = 0;
    glGetProgramiv(prog_id, GL_LINK_STATUS, (int*)&is_linked);
    if(is_linked == GL_FALSE)
    {
        GLint max_buffer = 0;
        glGetProgramiv(prog_id, GL_INFO_LOG_LENGTH, &max_buffer);
        char error[max_buffer];
        glGetProgramInfoLog(prog_id, max_buffer, &max_buffer, error);

        // Delete program and shaders
        glDeleteProgram(prog_id);
        glDeleteShader(vert_id);
        glDeleteShader(frag_id);

        return -1;
    }

    // Detach shaders after successful link
    glDetachShader(prog_id, vert_id);
    glDetachShader(prog_id, frag_id);

    return 0;
}