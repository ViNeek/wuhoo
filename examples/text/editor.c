/* compile with
-- Windows --
  cl /I. /I../../ /O2 editor.c /link /out:editor.exe kernel32.lib user32.lib gdi32.lib shell32.lib
  clang -I. -I../../ -O2 editor.c -o editor.exe -lkernel32 -luser32 -lgdi32 -lshell32
  gcc -I. -I../../ -O2 editor.c -o editor.exe -lkernel32 -luser32 -lgdi32 -lshell32
-- Linux --
  gcc -I. -I../../ -O2 editor.c -o editor -lX11 -lm
-- Mac OS X
  gcc -I. -I../../ editor.c -o editor -framework Cocoa -framework Quartz -framework Carbon
*/

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#define WUHOO_IMPLEMENTATION
#define WUHOO_UNICODE
#include "wuhoo.h"

#include <stdio.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"

#ifdef _WIN32
static const char * g_font_file = "C:/Windows/Fonts/ariblk.ttf";
#endif

#ifdef __APPLE__
static const char * g_font_file = "/Library/Fonts/Arial Unicode.ttf";
#endif

#ifdef __linux__
static const char * g_font_file = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
#endif

typedef struct {
  stbtt_bakedchar ascii_cdata[256]; // ASCII 32..126 is 95 glyphs
  stbtt_bakedchar cdata[256];
  stbtt_aligned_quad character_quad;

  unsigned char* ttf_buffer;
  unsigned char* temp_bitmap;

  WuhooRGBA* font_bitmap;
  WuhooRGBA* ascii_font_bitmap;

  int last_char;
  int first_char;
} Editor;

void
editor_init_font(Editor* editor, const char * font_file, int width, int height, float pixel_height)
{
  editor->temp_bitmap = (unsigned char*)malloc(width * height * sizeof(*editor->temp_bitmap));
  editor->font_bitmap = (WuhooRGBA*)malloc(width * height * sizeof(*editor->font_bitmap));
  editor->ascii_font_bitmap = (WuhooRGBA*)malloc(width * height * sizeof(*editor->ascii_font_bitmap));
  int pixel_count = width * height;
  int i;

  FILE* file = fopen(g_font_file, "rb");
  fseek(file, 0L, SEEK_END);
  size_t file_length = ftell(file);

  editor->ttf_buffer = (unsigned char*)malloc(file_length);

  fseek(file, 0L, SEEK_SET);
  fread(editor->ttf_buffer, 1, file_length, file);
  fclose(file);

  editor->first_char = 0x0000;
  editor->last_char = 0x007F;

  stbtt_BakeFontBitmap(editor->ttf_buffer,0, pixel_height, editor->temp_bitmap,width,height, editor->first_char, editor->last_char - editor->first_char, editor->ascii_cdata); // no guarantee this fits!

  for (i = 0; i < pixel_count; i++ ) {
    editor->ascii_font_bitmap[i].r = editor->temp_bitmap[i];
    editor->ascii_font_bitmap[i].b = editor->temp_bitmap[i];
    editor->ascii_font_bitmap[i].g = editor->temp_bitmap[i];
    editor->ascii_font_bitmap[i].a = editor->temp_bitmap[i];
  }

  editor->first_char = 0x0370;
  editor->last_char = 0x03FF;

  stbtt_BakeFontBitmap(editor->ttf_buffer,0, pixel_height, editor->temp_bitmap,width,height, editor->first_char, editor->last_char - editor->first_char, editor->cdata); // no guarantee this fits!

  for (i = 0; i < pixel_count; i++ ) {
    editor->font_bitmap[i].r = editor->temp_bitmap[i];
    editor->font_bitmap[i].b = editor->temp_bitmap[i];
    editor->font_bitmap[i].g = editor->temp_bitmap[i];
    editor->font_bitmap[i].a = editor->temp_bitmap[i];
  }

  if (editor->temp_bitmap) {
    free(editor->temp_bitmap);
    editor->temp_bitmap = WuhooNull;
  }

  if (editor->ttf_buffer) {
    free(editor->ttf_buffer);
    editor->ttf_buffer = WuhooNull;
  }
}

void
editor_clear_font(Editor* editor)
{
  if (editor->ttf_buffer) free(editor->ttf_buffer);
  if (editor->temp_bitmap) free(editor->temp_bitmap);
  if (editor->font_bitmap) free(editor->font_bitmap);
}

int main(int argc, const char * argv[]) {
  WuhooUnused(argc);
  WuhooUnused(argv);

  WuhooWindow window;
  WuhooEvent event;

  WuhooBoolean running = 1;
  WuhooSize width = 512;
  WuhooSize height = 512;

  Editor editor;

  WuhooRGBA* image_data = WuhooNull;
  WuhooRGBA const * font_atlas = WuhooNull;
  editor_init_font(&editor, g_font_file, width, height, 32.0f);

  WuhooWindowInit(&window);
  WuhooWindowCreate(&window, 0, 0, width, height, "Wuhoo Editor",
		    WUHOO_FLAG_CANVAS        |
		    WUHOO_FLAG_TITLED        |
		    WUHOO_FLAG_CLIENT_REGION |
		    WUHOO_FLAG_CLOSEABLE, WuhooNull);
  WuhooWindowShow(&window);

  WuhooWindowSetTitle(&window, g_font_file);

  int posx, posy;
  WuhooWindowClientRegionGet(&window, &posx, &posy, &width, &height);

  char last_char = 'a';
  float x = 0;
  float y = 0;
  float x_old = x;
  float y_old = y;
  WuhooBoolean print_char = WuhooYes;

  int ix = (int)x;
  int iy = (int)y + 20;
  int advance = 0;
  int advance_y = 0;

  stbtt_aligned_quad q = { 0 };

  image_data = malloc(width * height * sizeof(*image_data));
  memset(image_data, 0, width * height * sizeof(*image_data));

  while(running) {
    WuhooWindowEventNext(&window, &event);

    switch (event.type) {
    case WUHOO_EVT_WINDOW:
      switch (event.data.window.state) {
      case WUHOO_WSTATE_INVALIDATED:
	WuhooWindowBlit(&window, image_data, 0, 0, width, height, 0, 0, width, height);
	break;
      case WUHOO_WSTATE_CLOSED:
		running = 0;
		break;
      case WUHOO_WSTATE_RESIZED:
        WuhooWindowClientRegionGet(&window, &posx, &posy, &width, &height);
	break;
      default:
	break;
      }
      break;
    case WUHOO_EVT_KEY:
      switch(event.data.key.code) {
      case WUHOO_VKEY_ESCAPE:
	if (event.data.key.state == WUHOO_KSTATE_UP) {
	  running = 0;
	}
	break;
      default:
	if (WUHOO_KSTATE_DOWN != event.data.key.state)
	  break;

	if (event.data.key.mods & WUHOO_KMOD_DEADCHAR) {
		break;
	}

	if (event.data.key.code == WUHOO_VKEY_ENTER) {
	  x_old = 0;
	  ix = 0;
	  x = 0;
	  iy += 32;
	  break;
	}
	last_char = event.data.key.character[0];
	
	if ('\0' == last_char)
		break;

	if (((unsigned char)last_char) > 0x007F) {
		WuhooUTF32 str32[512];
		WuhooUTF32* str32p = &str32[0];
	  const WuhooUTF8* str = &event.data.key.character[0];
    size_t len = strlen((const char*)str);

	  memset(str32, 0, sizeof(str32));
	  WuhooConvertUTF8toUTF32(&str, str + len, &str32p, str32p + 512, WuhooStrictConversion);

	  last_char = (char)(str32[0] - editor.first_char);

	  stbtt_GetBakedQuad(editor.cdata, width, height, last_char, &x, &y, &q,1);
	  font_atlas = editor.font_bitmap;
	} else {
	  stbtt_GetBakedQuad(editor.ascii_cdata, width, height, last_char, &x, &y, &q,1);
	  font_atlas = editor.ascii_font_bitmap;
	}

	advance = (int)(x - x_old);
	if ( (x) > (float)(width) ) {
	  float strech = q.x1 - q.x0;
	  q.x0 = 0;
	  q.x1 = strech;
	  x = strech;
	  x_old = 0;
	  ix = 0;
	  iy += 32;
	}

	print_char = WuhooYes;

	break;
      }
    }

    if (WuhooYes == print_char) {
      print_char = WuhooNo;
      int tx = (int)(q.s0 * width);
      int ty = (int)(q.t0 * height);
      int bx = (int)(q.s1 * width);
      int by = (int)(q.t1 * height);
      int range = by - ty;

      int ix2 = (int)(q.x0);
      int iy2 = iy;
      int i, j;
      for (i = tx; i < bx; i++ ) {
	for (j = ty; j < by; j++ ) {
          
		int bitmap_index = i + j * width;
		int pixel_index  = ix2 + (iy2++ + (int)q.y0) * width;

if (pixel_index < 0 || pixel_index >= width * height) continue;

          image_data[pixel_index] = font_atlas[bitmap_index];
	}
	ix2++;
	iy2 = iy + advance_y;
      }
      WuhooWindowBlit(&window, image_data, 0, 0, width, height, 0, 0, width, height);
    }
  }

  WuhooWindowDestroy(&window);

  editor_clear_font(&editor);

  return 0;
}
