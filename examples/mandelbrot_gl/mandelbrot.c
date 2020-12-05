/* compiae with
-- Windows
  cl /I. /I../../ /O2 mandelbrot.c /link /out:mandelbrot.exe kernel32.lib user32.lib gdi32.lib opengl32.lib shell32.lib
  clang -I. -I../../ -O2 mandelbrot.c -o mandelbrot.exe -lkernel32 -luser32 -lgdi32 -lshell32 -lopengl32
  gcc -I. -I../../ -O2 mandelbrot.c -o mandelbrot.exe -lkernel32 -luser32 -lgdi32 -lshell32 -lopengl32

-- Mac OS X --
  gcc -I. -I../../ -O2 mandelbrot.c -o mandelbrot -framework Cocoa -framework Quartz -framework Carbon -framework OpenGL

-- Linux --
  gcc -I../../ -O2 mandelbrot.c -o mandelbrot -lX11 -lm -lGL
*/

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define UNICODE
#endif

#define GLEW_NO_GLU
#define GLEW_STATIC
#include "GL/glew.c"

#define WUHOO_OPENGL_ENABLE
#define WUHOO_IMPLEMENTATION
#include "wuhoo.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

GLuint
mandelbrot_program_create(const char * rsrc_path, const char * vert_file, const char * frag_file) {
  GLuint vert;
  GLuint frag;
  GLuint prog;
  char* vert_src;
  char* frag_src;
  size_t vert_src_size;
  size_t frag_src_size;
  FILE* vert_file_handle;
  FILE* frag_file_handle;
  char gl_version_str[32] = {0};

  {
    char file_full_path_buffer[256] = {0};
    const char* file_full_path = vert_file;
    if (WuhooNull != rsrc_path) {
#ifdef __APPLE__
      sprintf(file_full_path_buffer, "%s/../Resources/%s", rsrc_path, vert_file);
#else
      sprintf(file_full_path_buffer, "%s/%s", rsrc_path, vert_file);
#endif
      file_full_path = file_full_path_buffer;
    }

    vert_file_handle = fopen(file_full_path, "rb");
    if (!vert_file_handle)
      return 0;
  }

  {
    char file_full_path_buffer[256] = {0};
    const char* file_full_path = frag_file;
    if (WuhooNull != rsrc_path) {
#ifdef __APPLE__
      sprintf(file_full_path_buffer, "%s/../Resources/%s", rsrc_path, frag_file);
#else
      sprintf(file_full_path_buffer, "%s/%s", rsrc_path, frag_file);
#endif
      file_full_path = file_full_path_buffer;
    }
  
    frag_file_handle = fopen(file_full_path, "rb");
    if (!frag_file_handle)
      return 0;
  }

  if (!vert_file_handle || !frag_file_handle)
    return 0;

  int gl_major_version = 0;
  glGetIntegerv(GL_MAJOR_VERSION, &gl_major_version);
  int gl_minor_version = 0;
  glGetIntegerv(GL_MINOR_VERSION, &gl_minor_version);

  if (gl_major_version == 4)
    sprintf(gl_version_str, "#version 400");
  else if (gl_major_version == 3 && gl_minor_version == 3) 
    sprintf(gl_version_str, "#version 330");
  else
    sprintf(gl_version_str, "#version 300 es");

  fseek(vert_file_handle, 0L, SEEK_END);
  vert_src_size = ftell(vert_file_handle);
  fseek(vert_file_handle, 0L, SEEK_SET);

  fseek(frag_file_handle, 0L, SEEK_END);
  frag_src_size = ftell(frag_file_handle);
  fseek(frag_file_handle, 0L, SEEK_SET);

  vert_src = (char*)malloc(vert_src_size + 1);
  frag_src = (char*)malloc(frag_src_size + 1);

  vert_src[vert_src_size] = 0;
  frag_src[frag_src_size] = 0;

  fread (vert_src,1,vert_src_size, vert_file_handle);
  fread (frag_src,1,frag_src_size, frag_file_handle);

  fclose(vert_file_handle);
  fclose(frag_file_handle);

  vert = glCreateShader(GL_VERTEX_SHADER);
  frag = glCreateShader(GL_FRAGMENT_SHADER);

  const GLchar * sources[] = { gl_version_str, WuhooNull };
  sources[1] = vert_src;
  glShaderSource(vert, 2, sources, WuhooNull);
  sources[1] = frag_src;
  glShaderSource(frag, 2, sources, WuhooNull);

  glCompileShader(vert);

  GLint compiled;

  glGetShaderiv(vert, GL_COMPILE_STATUS, &compiled);
  if (!compiled) {
    GLint blen = 0;
    GLsizei slen = 0;

    glGetShaderiv(vert, GL_INFO_LOG_LENGTH , &blen);
    if (blen > 1) {
      GLchar* compiler_log = (GLchar*)malloc(blen);
      glGetShaderInfoLog(vert, blen, &slen, compiler_log);
      printf("Vertex Shader compiler_log: %s\n", compiler_log);
      free (compiler_log);
    }
  }

  glCompileShader(frag);
  glGetShaderiv(frag, GL_COMPILE_STATUS, &compiled);
  if (!compiled) {
    GLint blen = 0;
    GLsizei slen = 0;

    glGetShaderiv(frag, GL_INFO_LOG_LENGTH , &blen);
    if (blen > 1) {
      GLchar* compiler_log = (GLchar*)malloc(blen);
      glGetShaderInfoLog(frag, blen, &slen, compiler_log);
      printf("Fragment Shader compiler_log: %s\n", compiler_log);
      free (compiler_log);
    }
  }
  prog = glCreateProgram();

  glAttachShader(prog, vert);
  glAttachShader(prog, frag);

  glLinkProgram(prog);

  glDetachShader(prog, vert);
  glDetachShader(prog, frag);

  glDeleteShader(vert);
  glDeleteShader(frag);

  free(vert_src);
  free(frag_src);

  return prog;
}

static const char * g_vertex_shader_file = "mandelbrot.vs.glsl";
static const char * g_fragment_shader_file = "mandelbrot.fs.glsl";

int main(int argc, const char * argv[]) {
  WuhooWindow window;
  WuhooEvent event;
  char* resources_path = WuhooNull;

  /* This needs to be done for when the apple bundle is run from within Finder */
  char rsc_path[256] = {0};
  const char * resources_separator = WuhooNull;
  const char * riterator = argv[0];
  char * witerator = rsc_path;
  while(*riterator) {
    resources_separator = (*riterator == '/') ? riterator : resources_separator;
    *witerator++ = *riterator++;
  }
  if (resources_separator && '.' != argv[0][0]) {
    rsc_path[resources_separator - argv[0]] = 0;
    resources_path = rsc_path;
  }

  const char * title = "Mandelbrot Set (OpenGL " WUHOO_PLATFORM_API_STRING ")";
  WuhooBoolean running = 1;
  int posx = 100;
  int posy = 100;
  WuhooSize width = 512;
  WuhooSize height = 512;
  WuhooWindowInit(&window);
  WuhooWindowCreate(&window, 100, 100, width, height, title,
                    WUHOO_FLAG_CANVAS        |
                    WUHOO_FLAG_TITLED        |
                    WUHOO_FLAG_MOUSE_CAPTURE |
                    WUHOO_FLAG_RESIZEABLE    |
		            WUHOO_FLAG_OPENGL        |
                    WUHOO_FLAG_CLOSEABLE, WuhooNull);
  WuhooWindowShow(&window);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    printf("|Mandelbrot GL| glewInit failed with %s\n", glewGetErrorString(err));
    return 1;
  }
  int count = 0;
  WuhooWindowClientRegionGet(&window, &posx, &posy, &width, &height);

  GLuint program = mandelbrot_program_create(resources_path, g_vertex_shader_file, g_fragment_shader_file);
  GLuint screen_loc = glGetUniformLocation(program, "screen");

  printf("|Mandelbrot GL| Rendering mandelbrot within a fragment shader.\n");

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(program);

  while(running) {
    WuhooWindowEventNext(&window, &event);

    switch (event.type) {
    case WUHOO_EVT_WINDOW:
      switch (event.data.window.state) {
      case WUHOO_WSTATE_CLOSED:
        running = 0;
        break;
      case WUHOO_WSTATE_RESIZED:
        WuhooWindowClientRegionGet(&window, &posx, &posy, &width, &height);
	printf("|Mandelbrot GL| Resized %d %d\n", width, height);
        break;
      default:
        break;
      }
    case WUHOO_EVT_KEY: {
      switch(event.data.key.code) {
      case WUHOO_VKEY_ESCAPE:
	running = (event.data.key.state != WUHOO_KSTATE_UP);
	break;
      default:
	break;
      }
    } break;
    default:
      break;
    }

    if (program == 0) {
      glClear(GL_COLOR_BUFFER_BIT);
    } else {
      glViewport(0, 0, width , height);
      glUniform2f(screen_loc, (float)width, (float)height);
      glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    WuhooWindowBlit(&window, WuhooNull, 0, 0, width, height, 0, 0, width, height);
  }

  WuhooWindowDestroy(&window);

  return 0;
}
