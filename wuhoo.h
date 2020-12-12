 /**
 * @file wuhoo.h
 * wuhoo single header library.
 */
 
/* 
 * MIT License

 * Copyright (c) 2020 Nick Vitsas

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* Platform Independent Section */
typedef void*          WuhooHandle;
typedef void*          WuhooResult;
typedef unsigned char  WuhooBoolean;
typedef unsigned char  WuhooByte;
typedef unsigned short WuhooR5G6B5;
typedef unsigned short WuhooR5G5B5;
typedef unsigned int   WuhooSize;

/* Macro helpers and utilities */
#ifdef __cplusplus
#define WuhooNull nullptr
#else
#define WuhooNull ((void*)0)
#endif

#define WuhooSuccess WuhooNull /*!< Returned if everything has gone well */
#define WuhooDefaultPosition (-2147483647 - 1) /* INT_MIN */
#define WuhooTrue (1)
#define WuhooInternal static
#define WuhooYes WuhooTrue
#define WuhooFalse (0)
#define WuhooNo WuhooFalse
#define WuhooUnused(x) (void)(x)
#define WuhooOnlySet(value, flag) (((flag) & (value)) == (flag))
#define WuhooFlag(shift_count) (1 << shift_count)

#define WUHOO_STRING "Wuhoo" /*!< Wuhoo String Representation */
#define WUHOO_MAX_FILE_NAME_LENGTH 256

#ifdef __APPLE__
#define WUHOO_PLATFORM_API_STRING "Cocoa"
#endif
#ifdef _WIN32
#define WUHOO_PLATFORM_API_STRING "Win32"
#endif
#ifdef __linux__
#define WUHOO_PLATFORM_API_STRING "X11"
#endif

/* Constraints */
#define WUHOO_MAX_TITLE_LENGTH 256

typedef enum
{
  WUHOO_FLAG_TITLED = WuhooFlag(0),
#ifdef WUHOO_OPENGL_ENABLE
  WUHOO_FLAG_OPENGL = WuhooFlag(1),
#endif
  WUHOO_FLAG_CANVAS = WuhooFlag(2),
#ifdef WUHOO_VULKAN_ENABLE
  WUHOO_FLAG_VULKAN = WuhooFlag(3),
#endif
  WUHOO_FLAG_RESIZEABLE    = WuhooFlag(4),
  WUHOO_FLAG_BORDERLESS    = WuhooFlag(5),
  WUHOO_FLAG_MOUSE_CAPTURE = WuhooFlag(6), /* Win32 for now */
  WUHOO_FLAG_FILE_DROP     = WuhooFlag(7),
  WUHOO_FLAG_CLOSEABLE     = WuhooFlag(8),
  WUHOO_FLAG_CLIENT_REGION = WuhooFlag(9),
  WUHOO_FLAG_WINDOW_REGION = WuhooFlag(10)
} WuhooFlagsEnum;
typedef unsigned int   WuhooFlags;

#ifdef WUHOO_OPENGL_ENABLE
typedef enum
{
  WUHOO_GL_RED_SIZE,
  WUHOO_GL_GREEN_SIZE,
  WUHOO_GL_BLUE_SIZE,
  WUHOO_GL_ALPHA_SIZE,
  WUHOO_GL_BUFFER_SIZE,
  WUHOO_GL_DOUBLEBUFFER,
  WUHOO_GL_DEPTH_SIZE,
  WUHOO_GL_STENCIL_SIZE,
  WUHOO_GL_ACCUM_RED_SIZE,
  WUHOO_GL_ACCUM_GREEN_SIZE,
  WUHOO_GL_ACCUM_BLUE_SIZE,
  WUHOO_GL_ACCUM_ALPHA_SIZE,
  WUHOO_GL_STEREO,
  WUHOO_GL_MULTISAMPLEBUFFERS,
  WUHOO_GL_MULTISAMPLESAMPLES,
  WUHOO_GL_ACCELERATED_VISUAL,
  WUHOO_GL_RETAINED_BACKING,
  WUHOO_GL_CONTEXT_MAJOR_VERSION,
  WUHOO_GL_CONTEXT_MINOR_VERSION,
  WUHOO_GL_CONTEXT_FLAGS,
  WUHOO_GL_CONTEXT_PROFILE_MASK,
  WUHOO_GL_SHARE_WITH_CURRENT_CONTEXT,
  WUHOO_GL_FRAMEBUFFER_SRGB_CAPABLE,
  WUHOO_GL_CONTEXT_RELEASE_BEHAVIOR,
  WUHOO_GL_CONTEXT_EGL,
} WuhooGLAttrEnum;
#endif
typedef unsigned int   WuhooGLAttr;

typedef enum
{
  WUHOO_KMOD_NONE     = 0,
  WUHOO_KMOD_LSHIFT   = WuhooFlag(0),
  WUHOO_KMOD_RSHIFT   = WuhooFlag(1),
  WUHOO_KMOD_LCTRL    = WuhooFlag(2),
  WUHOO_KMOD_RCTRL    = WuhooFlag(3),
  WUHOO_KMOD_LALT     = WuhooFlag(4),
  WUHOO_KMOD_RALT     = WuhooFlag(5),
  WUHOO_KMOD_LGUI     = WuhooFlag(6),
  WUHOO_KMOD_RGUI     = WuhooFlag(7),
  WUHOO_KMOD_NUM      = WuhooFlag(8),
  WUHOO_KMOD_CAPS     = WuhooFlag(9),
  WUHOO_KMOD_MODE     = WuhooFlag(10),
  WUHOO_KMOD_DEADCHAR = WuhooFlag(11),
  WUHOO_KMOD_CTRL     = (WUHOO_KMOD_LCTRL  | WUHOO_KMOD_RCTRL),
  WUHOO_KMOD_SHIFT    = (WUHOO_KMOD_LSHIFT | WUHOO_KMOD_RSHIFT),
  WUHOO_KMOD_ALT      = (WUHOO_KMOD_LALT   | WUHOO_KMOD_RALT),
  WUHOO_KMOD_GUI      = (WUHOO_KMOD_LGUI   | WUHOO_KMOD_RGUI),
  WUHOO_KMOD_MAX
} WuhooKeyModifiersEnum,
  WuhooMouseModifiersEnum;

typedef int WuhooMouseModifiers;
typedef int WuhooKeyModifiers;

typedef enum
{
  WUHOO_VKEY_UNKNOWN,

  WUHOO_VKEY_BACKSPACE      = 8,
  WUHOO_VKEY_FORWARD_DELETE = WUHOO_VKEY_BACKSPACE,
  WUHOO_VKEY_TAB            = 9,
  WUHOO_VKEY_ENTER          = 13,
  WUHOO_VKEY_KPAD_ENTER,
  WUHOO_VKEY_ESCAPE = 27,
  WUHOO_VKEY_SPACE  = ' ',

  WUHOO_VKEY_QUOTE         = '\'',
  WUHOO_VKEY_COMMA         = ',',
  WUHOO_VKEY_MINUS         = '-',
  WUHOO_VKEY_PERIOD        = '.',
  WUHOO_VKEY_FORWARD_SLASH = '/',

  WUHOO_VKEY_0 = '0',
  WUHOO_VKEY_1,
  WUHOO_VKEY_2,
  WUHOO_VKEY_3,
  WUHOO_VKEY_4,
  WUHOO_VKEY_5,
  WUHOO_VKEY_6,
  WUHOO_VKEY_7,
  WUHOO_VKEY_8,
  WUHOO_VKEY_9 = '9',

  WUHOO_VKEY_SEMICOLON = ';',
  WUHOO_VKEY_EQUALS    = '=',

  WUHOO_VKEY_A = 'A',
  WUHOO_VKEY_B,
  WUHOO_VKEY_C,
  WUHOO_VKEY_D,
  WUHOO_VKEY_E,
  WUHOO_VKEY_F,
  WUHOO_VKEY_G,
  WUHOO_VKEY_H,
  WUHOO_VKEY_I,
  WUHOO_VKEY_J,
  WUHOO_VKEY_K,
  WUHOO_VKEY_L,
  WUHOO_VKEY_M,
  WUHOO_VKEY_N,
  WUHOO_VKEY_O,
  WUHOO_VKEY_P,
  WUHOO_VKEY_Q,
  WUHOO_VKEY_R,
  WUHOO_VKEY_S,
  WUHOO_VKEY_T,
  WUHOO_VKEY_U,
  WUHOO_VKEY_V,
  WUHOO_VKEY_W,
  WUHOO_VKEY_X,
  WUHOO_VKEY_Y,
  WUHOO_VKEY_Z = 'Z',

  WUHOO_VKEY_LEFT_BRACKET  = '[',
  WUHOO_VKEY_BACK_SLASH    = '\\',
  WUHOO_VKEY_RIGHT_BRACKET = ']',

  WUHOO_VKEY_GRAVE  = '`',
  WUHOO_VKEY_TILDA  = WUHOO_VKEY_GRAVE,
  WUHOO_VKEY_DELETE = 127,

  WUHOO_VKEY_F1,
  WUHOO_VKEY_F2,
  WUHOO_VKEY_F3,
  WUHOO_VKEY_F4,
  WUHOO_VKEY_F5,
  WUHOO_VKEY_F6,
  WUHOO_VKEY_F7,
  WUHOO_VKEY_F8,
  WUHOO_VKEY_F9,
  WUHOO_VKEY_F10,
  WUHOO_VKEY_F11,
  WUHOO_VKEY_F12,
  WUHOO_VKEY_F13,
  WUHOO_VKEY_PRINTSCREEN = WUHOO_VKEY_F13,
  WUHOO_VKEY_F14,
  WUHOO_VKEY_F15,

  WUHOO_VKEY_INSERT,
  WUHOO_VKEY_HELP = WUHOO_VKEY_INSERT,
  WUHOO_VKEY_HOME,
  WUHOO_VKEY_PAGE_UP,
  WUHOO_VKEY_END,
  WUHOO_VKEY_PAGE_DOWN,
  WUHOO_VKEY_MENU,

  WUHOO_VKEY_KPAD_0,
  WUHOO_VKEY_KPAD_1,
  WUHOO_VKEY_KPAD_2,
  WUHOO_VKEY_KPAD_3,
  WUHOO_VKEY_KPAD_4,
  WUHOO_VKEY_KPAD_5,
  WUHOO_VKEY_KPAD_6,
  WUHOO_VKEY_KPAD_7,
  WUHOO_VKEY_KPAD_8,
  WUHOO_VKEY_KPAD_9,

  WUHOO_VKEY_KPAD_DIVIDE,
  WUHOO_VKEY_KPAD_SLASH = WUHOO_VKEY_KPAD_DIVIDE,
  WUHOO_VKEY_KPAD_PLUS,
  WUHOO_VKEY_KPAD_MINUS,
  WUHOO_VKEY_KPAD_EQUALS,
  WUHOO_VKEY_KPAD_MULITPLY,
  WUHOO_VKEY_KPAD_DECIMAL,
  WUHOO_VKEY_KPAD_NUM_LOCK,
  WUHOO_VKEY_KPAD_COMMA = WUHOO_VKEY_KPAD_DECIMAL,

  WUHOO_VKEY_SHIFT,
  WUHOO_VKEY_CONTROL,
  WUHOO_VKEY_ALT,
  WUHOO_VKEY_CAPS_LOCK,
  WUHOO_VKEY_UP,
  WUHOO_VKEY_DOWN,
  WUHOO_VKEY_RIGHT,
  WUHOO_VKEY_LEFT,

  WUHOO_VKEY_MAX
} WuhooKeyCode;

/** \enum WuhooWindowFlags
 * Additional window flags accompanying a WuhooEventWindow.
 */
typedef enum {
  WUHOO_WINDOW_FLAG_RESIZED        = WuhooFlag(0),
  WUHOO_WINDOW_FLAG_FULL_SCREEN    = WuhooFlag(1),
  WUHOO_WINDOW_FLAG_FOCUS_GAINED   = WuhooFlag(2),
  WUHOO_WINDOW_FLAG_FOCUS_LOST     = WuhooFlag(3),
  WUHOO_WINDOW_FLAG_MINIMIZED      = WuhooFlag(4),
  WUHOO_WINDOW_FLAG_MAXIMIZED      = WuhooFlag(5),
  WUHOO_WINDOW_FLAG_MOVED          = WuhooFlag(6),
  WUHOO_WINDOW_FLAG_CLOSED         = WuhooFlag(7),
  WUHOO_WINDOW_FLAG_REGION_UPDATED = WuhooFlag(8),
  WUHOO_WINDOW_FLAG_DROP_STARTED   = WuhooFlag(9)
} WuhooWindowFlagsEnum;

typedef int WuhooWindowFlags;

/** \enum WuhooWindowState
 * State of the window that triggered the WuhooEventWindow.
 */
typedef enum {
  WUHOO_WSTATE_UNKNOWN,
  WUHOO_WSTATE_RESIZED,
  WUHOO_WSTATE_FULL_SCREENED,
  WUHOO_WSTATE_MOVED,
  WUHOO_WSTATE_MINIMIZED,
  WUHOO_WSTATE_MAXIMIZED,
  WUHOO_WSTATE_CREATED,
  WUHOO_WSTATE_CLOSED,
  WUHOO_WSTATE_UNFOCUSED,
  WUHOO_WSTATE_FOCUSED,
  WUHOO_WSTATE_HIDDEN,
  WUHOO_WSTATE_INVALIDATED,
  WUHOO_WSTATE_MAX,
} WuhooWindowState;

/** \enum WuhooEventType
 * Wuhoo Event types.
 */
typedef enum {
  WUHOO_EVT_NONE,
  WUHOO_EVT_WINDOW, ///< WuhooEventWindow
  WUHOO_EVT_KEY, ///< WuhooEventKey
  WUHOO_EVT_MOUSE_PRESS, ///< WuhooEventMousePress
  WUHOO_EVT_MOUSE_MOVE, ///< WuhooEventMouseMove
  WUHOO_EVT_MOUSE_WHEEL, ///< WuhooEventMouseWheel
  WUHOO_EVT_DROP, ///< WuhooEventDrop
  WUHOO_EVT_MAX
} WuhooEventType;

typedef enum {
  WUHOO_KSTATE_UNKNOWN,
  WUHOO_KSTATE_UP,
  WUHOO_KSTATE_DOWN,
  WUHOO_KSTATE_MAX
} WuhooKeyState;

typedef unsigned int   WuhooUTF32; /* at least 32 bits */
typedef unsigned short WuhooUTF16; /* at least 16 bits */
typedef unsigned char  WuhooUTF8;  /* typically 8 bits */

#define WUHOO_MAX_CHARACTER_SIZE 6

/**
 * @brief Struct representing a keyboard press
 */
typedef struct
{
  WuhooKeyModifiers mods;  /*!< WuhooKeyModifiers flags for Shift. Ctrl e.t.c*/
  WuhooKeyState     state; /*!< Key Release or Press, see WuhooKeyState */
  WuhooKeyCode      code;  /*!< Corresponding virtual key code */
  WuhooUTF8         character[WUHOO_MAX_CHARACTER_SIZE]; /* UTF-8 representation of the submitted character */
} WuhooEventKey;

/** \enum WuhooMouseState
 * Mouse button state of the triggered WuhooEventMouseMove, WuhooEventMousePress or WuhooEventMouseWheel.
 */
typedef enum {
  WUHOO_MSTATE_UNKNOWN,
  WUHOO_MSTATE_LPRESSED,
  WUHOO_MSTATE_LRELEASED,
  WUHOO_MSTATE_RPRESSED,
  WUHOO_MSTATE_RRELEASED,
  WUHOO_MSTATE_MPRESSED,
  WUHOO_MSTATE_MRELEASED,
  WUHOO_MSTATE_MAX
} WuhooMouseState;

/**
 * @brief Helper struct to work with RGBA system backed buffers.
 * The alpha channel is currently not respected in any backend
 */

typedef struct
{
  unsigned char r; /*!< 'red' channel */
  unsigned char g; /*!< 'green' channel */
  unsigned char b; /*!< 'blue' channel */
  unsigned char a; /*!< 'alpha' channel (no use for now) */
} WuhooRGBA;

typedef struct
{
  WuhooMouseModifiers mods;
  WuhooMouseState     state;
  int                 x;
  int                 y;
} WuhooEventMouseMove;

typedef struct
{
  WuhooMouseModifiers mods;
  WuhooMouseState     state;
  int                 click_count;
  int                 x;
  int                 y;
} WuhooEventMousePress;

typedef struct
{
  WuhooMouseModifiers mods;
  int                 x;
  int                 y;
  float               delta_x;
  float               delta_y;
} WuhooEventMouseWheel;

typedef struct
{
  WuhooWindowState state;
  WuhooWindowFlags flags;
  int              data1;
  int              data2;
} WuhooEventWindow;

typedef struct
{
  WuhooHandle context;
  WuhooSize   count;
  WuhooSize   size;
} WuhooEventDrop;

typedef union
{
  WuhooEventKey        key;
  WuhooEventMousePress mouse_press;
  WuhooEventMouseMove  mouse_move;
  WuhooEventMouseWheel mouse_wheel;
  WuhooEventWindow     window;
  WuhooEventDrop       drop;
} WuhooEventData;

/**
 * @brief The event union that holds event-specific data
 */
typedef struct
{
  WuhooEventType type;
  WuhooEventData data;
} WuhooEvent;

typedef WuhooResult (*WuhooConvertRGBA)(void* dst, WuhooRGBA const* const src,
                                        WuhooSize x, WuhooSize y,
                                        WuhooSize width, WuhooSize height,
                                        WuhooSize src_width,
                                        WuhooSize src_height);

#ifdef WUHOO_OPENGL_ENABLE
typedef struct
{
  int major;
  int minor;
} WuhooGLVersion;

typedef struct
{
  WuhooGLVersion version;
  int            redBits;
  int            greenBits;
  int            blueBits;
  int            alphaBits;
  int            depthBits;
  int            stencilBits;
  int            accumRedBits;
  int            accumGreenBits;
  int            accumBlueBits;
  int            accumAlphaBits;
  int            auxBuffers;
  int            samples;
  WuhooBoolean   stereo;
  WuhooBoolean   sRGB;
  WuhooBoolean   doublebuffer;
  WuhooBoolean   transparent;
} WuhooGLFramebuffer;
#endif /* WUHOO_OPENGL_ENABLE */

typedef struct
{
#ifdef WUHOO_OPENGL_ENABLE
  WuhooGLFramebuffer gl_framebuffer;
#endif
  WuhooHandle      platform_window;
  WuhooConvertRGBA convert_rgba;
  int              window_flags;
  WuhooFlags       flags;
  int              global_mods;
  int              width;   /* window width */
  int              height;  /* window height */
  int              cwidth;  /* client width  */
  int              cheight; /* client height */
  int              x;
  int              y;
  WuhooBoolean     is_initialized;
  WuhooBoolean     is_alive;
  WuhooByte        memory[256];
} WuhooWindow;

/* Public API */

/** Properly initialize a \ref WuhooWindow struct for use by the Wuhoo API.
 * \param WuhooWindow the window struct to initialize.
 * \return WuhooResult
 * \sa WuhooWindow, WuhooResult
 */
WuhooResult
WuhooWindowInit(WuhooWindow* window);
/** Properly release resources aquired for a \ref WuhooWindow struct during use of the Wuhoo API.
 * \param WuhooWindow the window struct to destroy.
 * \return WuhooResult
 * \sa WuhooWindow, WuhooResult
 */
WuhooResult
WuhooWindowDestroy(WuhooWindow* window);
/** Allocate all the resources required for a \ref WuhooWindow struct and prepare for a native Window to show.
 *
 * \param window The \ref WuhooWindow struct handle.
 * \param posx Horizontal window offset of the upper left corner.
 * \param posy Vertical window offset of the upper left corner.
 * \param width width of the window.
 * \param height height of the window.
 * \param title Title of the created window.
 * \param flags Flags to customize the created window.
 * \param data Additional data (Currently unused).
 * \return WuhooResult
 * \sa WuhooWindow, WuhooResult
 */
WuhooResult
WuhooWindowCreate(WuhooWindow* window, int posx, int posy, WuhooSize width,
                  WuhooSize height, const char* title, WuhooFlags flags,
                  const void* data);
/** Allocate all the resources required for a \ref WuhooWindow struct and prepare for a native Window to show.
 * \param window The \ref WuhooWindow struct handle.
 * \param event The \ref WuhooEvent struct to receive the new event information.
 * \return WuhooResult
 * \sa WuhooWindow, WuhooEvent
 */
WuhooResult
WuhooWindowEventNext(WuhooWindow* window, WuhooEvent* event);
/** Allocate all the resources required for a \ref WuhooWindow struct and
 *  prepare for a native Window to show.
 *
 * \param window The \ref WuhooWindow struct handle.
 * \param event The \ref WuhooEvent struct that triggered this event in the first place.
 * \param buffer The buffer that receives the UTF-8 encoded list of the dropeed files. 
 * \param buffer_size The size of the provided buffer (If you can't much the requested size of the event, you will get a truncated list).
 * \return WuhooResult
 * \sa WuhooWindow, WuhooEvent
 */
WuhooResult
WuhooWindowDropContentsGet(WuhooWindow* window, WuhooEvent* event, char* buffer,
                           WuhooSize buffer_size);
/** Set a window's position and size.
 *
 * \param window The \ref WuhooWindow struct handle.
 * \param posx The new horizontal postion of the window.
 * \param posy The new vertical postion of the window.
 * \param width The new width of the window.
 * \param height The new height of the window.
 * \return WuhooResult
 * \sa WuhooWindow
*/
WuhooResult
WuhooWindowRegionSet(WuhooWindow* window, int posx, int posy, WuhooSize width,
                     WuhooSize height);
/** Get a window's position and client region size.
 *
 * \param window The \ref WuhooWindow struct handle.
 * \param posx The horizontal postion of the window.
 * \param posy The vertical postion of the window.
 * \param width The width of the of the window.
 * \param height The height of the of the window (including title bar).
 * \return WuhooResult
 * \sa WuhooWindow
*/
WuhooResult
WuhooWindowRegionGet(WuhooWindow* window, int* posx, int* posy,
                     WuhooSize* width, WuhooSize* height);
/** Get a window's position and client region size.
 *
 * \param window The \ref WuhooWindow struct handle.
 * \param posx The horizontal postion of the window.
 * \param posy The vertical postion of the window.
 * \param width The width of the client region of the window.
 * \param height The height of the client region of the window.
 * \return WuhooResult
 * \sa WuhooWindow
 */
WuhooResult
WuhooWindowClientRegionGet(WuhooWindow* window, int* posx, int* posy,
                           WuhooSize* width, WuhooSize* height);
/** Set a window's position and client region size.
 *
 * \param window The \ref WuhooWindow struct handle.
 * \param posx The new horizontal postion of the window.
 * \param posy The new vertical postion of the window.
 * \param width The new width of the client region of the window.
 * \param height The new height of the client region of the window.
 * \return WuhooResult
 * \sa WuhooWindow
 */
WuhooResult
WuhooWindowClientRegionSet(WuhooWindow* window, int posx, int posy,
                           WuhooSize width, WuhooSize height);
/**
 * Blit pixels to the framebuffer using the window system's native calls.
 * In case of a graphics-enabled window (e.g. OpenGL) this call
 * simply blits the contents of the API buffer to the screen by calling the appropriate
 * API calss (e.g. SwapBuffer, flush e.t.c.).
 *
 * **The current implementation does not properly handle regional drawing.**
 *
 * \param window The \ref WuhooWindow struct handle.
 * \param pixels RGBA unsigned char pixel buffer.
 * \param src_x Read from source starting at x (<b>Not Implemented Yet</b>).
 * \param src_y Read from source starting at y (<b>Not Implemented Yet</b>).
 * \param src_width width of the source region.
 * \param src_height height of the source region.
 * \param dst_x Write to destination starting at x.
 * \param dst_y Write to destination starting at y.
 * \param dst_width width of the destination region.
 * \param dst_height height of the destination region.
 * \return WuhooResult
 * \sa WuhooWindow, WuhooResult
 */
WuhooResult
WuhooWindowBlit(WuhooWindow* window, WuhooRGBA* pixels, WuhooSize src_x,
    WuhooSize src_y, WuhooSize src_width, WuhooSize src_height,
    WuhooSize dst_x, WuhooSize dst_y, WuhooSize dst_width,
    WuhooSize dst_height);
/**
 * Present the previously inited and created WuhooWindow
 * The window should be visible on the screen after this call
 */
WuhooResult
WuhooWindowShow(WuhooWindow* window);

/** Set the title of the window. The title parameter beeds to be encoded in UTF-8.
 *
 *  \param window The \ref WuhooWindow struct handle.
 *  \param title The new title in UTF-8 encoding.
 *  \return WuhooResult
 *  \sa WuhooWindow
 */
WuhooResult
WuhooWindowSetTitle(WuhooWindow* window, const char* title);
/** A descriptive string of the \ref WuhooResult.
 *
 \param result A \ref WuhooResult returned from any of Wuhoo's APIs.
 \return const char *
*/
const char*
WuhooResultString(WuhooResult result);

#ifdef WUHOO_IMPLEMENTATION

WuhooInternal void
WuhooCopy(void* const to, void const* const from, WuhooSize count);
WuhooInternal WuhooBoolean
WuhooStringCmp(const char* to, const char* from, WuhooSize max_count);
/* Color conversion kernels */
WuhooInternal WuhooResult
WuhooConvertRGBANoOp(void* dst, WuhooRGBA const* const src, WuhooSize x,
                     WuhooSize y, WuhooSize width, WuhooSize height,
                     WuhooSize src_width, WuhooSize src_height);
WuhooInternal WuhooResult
WuhooConvertRGBAtoRGBA(void* dst, WuhooRGBA const* const src, WuhooSize x,
                       WuhooSize y, WuhooSize width, WuhooSize height,
                       WuhooSize src_width, WuhooSize src_height);
WuhooInternal WuhooResult
WuhooConvertRGBAtoRGB(void* dst, WuhooRGBA const* const src, WuhooSize x,
                      WuhooSize y, WuhooSize width, WuhooSize height,
                      WuhooSize src_width, WuhooSize src_height);
WuhooInternal WuhooResult
WuhooConvertRGBAtoBGRA(void* dst, WuhooRGBA const* const src, WuhooSize x,
                       WuhooSize y, WuhooSize width, WuhooSize height,
                       WuhooSize src_width, WuhooSize src_height);
WuhooInternal WuhooResult
WuhooConvertRGBAtoR5G6B5(void* dst, WuhooRGBA const* const src, WuhooSize x,
                         WuhooSize y, WuhooSize width, WuhooSize height,
                         WuhooSize src_width, WuhooSize src_height);

/* Helpers and utilities */
WuhooInternal void
WuhooCharacterCopy(char* to, const char* from);
WuhooInternal void
WuhooZeroInit(void* to, WuhooSize count);
WuhooInternal WuhooSize
WuhooStringCopy(char* to, const char* from, WuhooSize max_count);
WuhooInternal int
WuhooMini(int a, int b);
WuhooInternal int
WuhooMaxi(int a, int b);
WuhooInternal void
WuhooMemzero(void* address, WuhooSize size);
WuhooInternal WuhooSize
WuhooStringLength(const char* str, WuhooSize max_count);
#ifdef UNICODE
#ifndef WUHOO_UNICODE
#define WUHOO_UNICODE
#endif
#endif

#ifdef WUHOO_UNICODE
#ifndef UNICODE
#define UNICODE
#endif
#else
#define WUHOO_ANSI
#endif

#if defined WUHOO_UNICODE && defined _WIN32
typedef WuhooUTF16             WuhooChar;
#else
typedef WuhooUTF8 WuhooChar;
#endif

/* Some fundamental constants */
#define WUHOO_UNI_REPLACEMENT_CHAR (WuhooUTF32)0x0000FFFD
#define WUHOO_UNI_MAX_BMP (WuhooUTF32)0x0000FFFF
#define WUHOO_UNI_MAX_UTF16 (WuhooUTF32)0x0010FFFF
#define WUHOO_UNI_MAX_UTF32 (WuhooUTF32)0x7FFFFFFF
#define WUHOO_UNI_MAX_LEGAL_UTF32 (WuhooUTF32)0x0010FFFF

#define WUHOO_UNI_MAX_UTF8_BYTES_PER_CODE_POINT 4

#define WUHOO_UNI_UTF16_BYTE_ORDER_MARK_NATIVE 0xFEFF
#define WUHOO_UNI_UTF16_BYTE_ORDER_MARK_SWAPPED 0xFFFE

typedef enum
  {
    WuhooConversionOK,    /* conversion successful */
    WuhooSourceExhausted, /* partial character in source, but hit end */
    WuhooTargetExhausted, /* insuff. room in target for conversion */
    WuhooSourceIllegal    /* source sequence is illegal/malformed */
  } WuhooConversionResult;

typedef enum
  {
    WuhooStrictConversion = 0,
    WuhooLenientConversion
  } WuhooConversionFlags;

WuhooConversionResult
WuhooConvertUTF8toUTF16(const WuhooUTF8** sourceStart,
                        const WuhooUTF8* sourceEnd, WuhooUTF16** targetStart,
                        WuhooUTF16* targetEnd, WuhooConversionFlags flags);

/**
 * Convert a partial UTF8 sequence to UTF32.  If the sequence ends in an
 * incomplete code unit sequence, returns \c WuhooSourceExhausted.
 */
WuhooConversionResult
ConvertUTF8toUTF32Partial(const WuhooUTF8** sourceStart,
                          const WuhooUTF8* sourceEnd, WuhooUTF32** targetStart,
                          WuhooUTF32* targetEnd, WuhooConversionFlags flags);

/**
 * Convert a partial UTF8 sequence to UTF32.  If the sequence ends in an
 * incomplete code unit sequence, returns \c WuhooSourceIllegal.
 */
WuhooConversionResult
WuhooConvertUTF8toUTF32(const WuhooUTF8** sourceStart,
                        const WuhooUTF8* sourceEnd, WuhooUTF32** targetStart,
                        WuhooUTF32* targetEnd, WuhooConversionFlags flags);

WuhooConversionResult
WuhooConvertUTF16toUTF8(const WuhooUTF16** sourceStart,
                        const WuhooUTF16* sourceEnd, WuhooUTF8** targetStart,
                        WuhooUTF8* targetEnd, WuhooConversionFlags flags);

WuhooConversionResult
WuhooConvertUTF32toUTF8(const WuhooUTF32** sourceStart,
                        const WuhooUTF32* sourceEnd, WuhooUTF8** targetStart,
                        WuhooUTF8* targetEnd, WuhooConversionFlags flags);

WuhooConversionResult
ConvertUTF16toUTF32(const WuhooUTF16** sourceStart, const WuhooUTF16* sourceEnd,
                    WuhooUTF32** targetStart, WuhooUTF32* targetEnd,
                    WuhooConversionFlags flags);

WuhooConversionResult
WuhooConvertUTF32toUTF16(const WuhooUTF32** sourceStart,
                         const WuhooUTF32* sourceEnd, WuhooUTF16** targetStart,
                         WuhooUTF16* targetEnd, WuhooConversionFlags flags);

WuhooBoolean
WuhooIsLegalUTF8Sequence(const WuhooUTF8* source, const WuhooUTF8* sourceEnd);

WuhooBoolean
WuhooIsLegalUTF8String(const WuhooUTF8** source, const WuhooUTF8* sourceEnd);

unsigned
WuhooGetNumBytesForUTF8(WuhooUTF8 firstByte);

static const int WuhooHalfShift = 10; /* used for shifting by 10 bits */

static const WuhooUTF32 WuhooHalfBase = 0x0010000UL;
static const WuhooUTF32 WuhooHalfMask = 0x3FFUL;

#define WUHOO_UNI_SUR_HIGH_START (WuhooUTF32)0xD800
#define WUHOO_UNI_SUR_HIGH_END (WuhooUTF32)0xDBFF
#define WUHOO_UNI_SUR_LOW_START (WuhooUTF32)0xDC00
#define WUHOO_UNI_SUR_LOW_END (WuhooUTF32)0xDFFF

/* --------------------------------------------------------------------- */

/*
 * Index into the table below with the first byte of a UTF-8 sequence to
 * get the number of trailing bytes that are supposed to follow it.
 * Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
 * left as-is for anyone who may want to do such conversion, which was
 * allowed in earlier algorithms.
 */
static const char WuhooTrailingBytesForUTF8[256] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
};

/*
 * Magic values subtracted from a buffer value during UTF8 conversion.
 * This table contains as many values as there might be trailing bytes
 * in a UTF-8 sequence.
 */
static const WuhooUTF32 WuhooOffsetsFromUTF8[6] = {
  0x00000000UL, 0x00003080UL, 0x000E2080UL,
  0x03C82080UL, 0xFA082080UL, 0x82082080UL
};

/*
 * Once the bits are split out into bytes of UTF-8, this is a mask OR-ed
 * into the first byte, depending on how many bytes follow.  There are
 * as many entries in this table as there are UTF-8 sequence types.
 * (I.e., one byte sequence, two byte... etc.). Remember that sequencs
 * for *legal* UTF-8 will be 4 or fewer bytes total.
 */
static const WuhooUTF8 WuhooFirstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0,
                                                 0xF0, 0xF8, 0xFC };

/*
 * Utility routine to tell whether a sequence of bytes is legal UTF-8.
 * This must be called with the length pre-determined by the first byte.
 * If not calling this from ConvertUTF8to*, then the length can be set by:
 *  length = trailingBytesForUTF8[*source]+1;
 * and the sequence is illegal right away if there aren't that many bytes
 * available.
 * If presented with a length > 4, this returns false.  The Unicode
 * definition of UTF-8 goes up to 4-byte sequences.
 */

static WuhooBoolean
WuhooIsLegalUTF8(const WuhooUTF8* source, int length)
{
  WuhooUTF8        a;
  const WuhooUTF8* srcptr = source + length;
  switch (length) {
  default:
    return WuhooFalse;
    /* Everything else falls through when "true"... */
  case 4:
    if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
      return WuhooFalse;
  case 3:
    if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
      return WuhooFalse;
  case 2:
    if ((a = (*--srcptr)) < 0x80 || a > 0xBF)
      return WuhooFalse;

    switch (*source) {
      /* no fall-through in this inner switch */
    case 0xE0:
      if (a < 0xA0)
	return WuhooFalse;
      break;
    case 0xED:
      if (a > 0x9F)
	return WuhooFalse;
      break;
    case 0xF0:
      if (a < 0x90)
	return WuhooFalse;
      break;
    case 0xF4:
      if (a > 0x8F)
	return WuhooFalse;
      break;
    default:
      if (a < 0x80)
	return WuhooFalse;
    }

  case 1:
    if (*source >= 0x80 && *source < 0xC2)
      return WuhooFalse;
  }
  if (*source > 0xF4)
    return WuhooFalse;
  return WuhooTrue;
}

/* --------------------------------------------------------------------- */

/*
 * Exported function to return whether a UTF-8 sequence is legal or not.
 * This is not used here; it's just exported.
 */
WuhooBoolean
WuhooIsLegalUTF8Sequence(const WuhooUTF8* source, const WuhooUTF8* sourceEnd)
{
  int length = WuhooTrailingBytesForUTF8[*source] + 1;
  if (length > sourceEnd - source) {
    return WuhooFalse;
  }
  return WuhooIsLegalUTF8(source, length);
}

/* --------------------------------------------------------------------- */

/* The interface converts a whole buffer to avoid function-call overhead.
 * Constants have been gathered. Loops & conditionals have been removed as
 * much as possible for efficiency, in favor of drop-through switches.
 * (See "Note A" at the bottom of the file for equivalent code.)
 * If your compiler supports it, the "isLegalUTF8" call can be turned
 * into an inline function.
 */

WuhooConversionResult
WuhooConvertUTF8toUTF16(const WuhooUTF8** sourceStart,
                        const WuhooUTF8* sourceEnd, WuhooUTF16** targetStart,
                        WuhooUTF16* targetEnd, WuhooConversionFlags flags)
{
  WuhooConversionResult result = WuhooConversionOK;
  const WuhooUTF8*      source = *sourceStart;
  WuhooUTF16*           target = *targetStart;
  while (source < sourceEnd) {
    WuhooUTF32     ch               = 0;
    unsigned short extraBytesToRead = WuhooTrailingBytesForUTF8[*source];
    if (extraBytesToRead >= sourceEnd - source) {
      result = WuhooSourceExhausted;
      break;
    }
    /* Do this check whether lenient or strict */
    if (!WuhooIsLegalUTF8(source, extraBytesToRead + 1)) {
      result = WuhooSourceIllegal;
      break;
    }
    /*
     * The cases all fall through. See "Note A" below.
     */
    switch (extraBytesToRead) {
    case 5: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
    case 4: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
    case 3: ch += *source++; ch <<= 6;
    case 2: ch += *source++; ch <<= 6;
    case 1: ch += *source++; ch <<= 6;
    case 0: ch += *source++;
    }
    ch -= WuhooOffsetsFromUTF8[extraBytesToRead];

    if (target >= targetEnd) {
      source -= (extraBytesToRead + 1); /* Back up source pointer! */
      result = WuhooTargetExhausted;
      break;
    }
    if (ch <= WUHOO_UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
      /* UTF-16 surrogate values are illegal in UTF-32 */
      if (ch >= WUHOO_UNI_SUR_HIGH_START && ch <= WUHOO_UNI_SUR_LOW_END) {
        if (flags == WuhooStrictConversion) {
          source -=
            (extraBytesToRead + 1); /* return to the illegal value itself */
          result = WuhooSourceIllegal;
          break;
        } else {
          *target++ = WUHOO_UNI_REPLACEMENT_CHAR;
        }
      } else {
        *target++ = (WuhooUTF16)ch; /* normal case */
      }
    } else if (ch > WUHOO_UNI_MAX_UTF16) {
      if (flags == WuhooStrictConversion) {
        result = WuhooSourceIllegal;
        source -= (extraBytesToRead + 1); /* return to the start */
        break;                            /* Bail out; shouldn't continue */
      } else {
        *target++ = WUHOO_UNI_REPLACEMENT_CHAR;
      }
    } else {
      /* target is a character in range 0xFFFF - 0x10FFFF. */
      if (target + 1 >= targetEnd) {
        source -= (extraBytesToRead + 1); /* Back up source pointer! */
        result = WuhooTargetExhausted;
        break;
      }
      ch -= WuhooHalfBase;
      *target++ =
        (WuhooUTF16)((ch >> WuhooHalfShift) + WUHOO_UNI_SUR_HIGH_START);
      *target++ = (WuhooUTF16)((ch & WuhooHalfMask) + WUHOO_UNI_SUR_LOW_START);
    }
  }
  *sourceStart = source;
  *targetStart = target;
  return result;
}

static unsigned
WuhooFindMaximalSubpartOfIllFormedUTF8Sequence(const WuhooUTF8* source,
                                               const WuhooUTF8* sourceEnd)
{
  WuhooUTF8 b1, b2, b3;

  // assert(!isLegalUTF8Sequence(source, sourceEnd));

  /*
   * Unicode 6.3.0, D93b:
   *
   *   Maximal subpart of an ill-formed subsequence: The longest code unit
   *   subsequence starting at an unconvertible offset that is either:
   *   a. the initial subsequence of a well-formed code unit sequence, or
   *   b. a subsequence of length one.
   */

  if (source == sourceEnd)
    return 0;

  /*
   * Perform case analysis.  See Unicode 6.3.0, Table 3-7. Well-Formed UTF-8
   * Byte Sequences.
   */

  b1 = *source;
  ++source;
  if (b1 >= 0xC2 && b1 <= 0xDF) {
    /*
     * First byte is valid, but we know that this code unit sequence is
     * invalid, so the maximal subpart has to end after the first byte.
     */
    return 1;
  }

  if (source == sourceEnd)
    return 1;

  b2 = *source;
  ++source;

  if (b1 == 0xE0) {
    return (b2 >= 0xA0 && b2 <= 0xBF) ? 2 : 1;
  }
  if (b1 >= 0xE1 && b1 <= 0xEC) {
    return (b2 >= 0x80 && b2 <= 0xBF) ? 2 : 1;
  }
  if (b1 == 0xED) {
    return (b2 >= 0x80 && b2 <= 0x9F) ? 2 : 1;
  }
  if (b1 >= 0xEE && b1 <= 0xEF) {
    return (b2 >= 0x80 && b2 <= 0xBF) ? 2 : 1;
  }
  if (b1 == 0xF0) {
    if (b2 >= 0x90 && b2 <= 0xBF) {
      if (source == sourceEnd)
        return 2;

      b3 = *source;
      return (b3 >= 0x80 && b3 <= 0xBF) ? 3 : 2;
    }
    return 1;
  }
  if (b1 >= 0xF1 && b1 <= 0xF3) {
    if (b2 >= 0x80 && b2 <= 0xBF) {
      if (source == sourceEnd)
        return 2;

      b3 = *source;
      return (b3 >= 0x80 && b3 <= 0xBF) ? 3 : 2;
    }
    return 1;
  }
  if (b1 == 0xF4) {
    if (b2 >= 0x80 && b2 <= 0x8F) {
      if (source == sourceEnd)
        return 2;

      b3 = *source;
      return (b3 >= 0x80 && b3 <= 0xBF) ? 3 : 2;
    }
    return 1;
  }

  // assert((b1 >= 0x80 && b1 <= 0xC1) || b1 >= 0xF5);
  /*
   * There are no valid sequences that start with these bytes.  Maximal subpart
   * is defined to have length 1 in these cases.
   */
  return 1;
}

static WuhooConversionResult
WuhooConvertUTF8toUTF32Impl(const WuhooUTF8** sourceStart,
                            const WuhooUTF8*  sourceEnd,
                            WuhooUTF32** targetStart, WuhooUTF32* targetEnd,
                            WuhooConversionFlags flags,
                            WuhooBoolean         InputIsPartial)
{
  WuhooConversionResult result = WuhooConversionOK;
  const WuhooUTF8*      source = *sourceStart;
  WuhooUTF32*           target = *targetStart;
  while (source < sourceEnd) {
    WuhooUTF32     ch               = 0;
    unsigned short extraBytesToRead = WuhooTrailingBytesForUTF8[*source];
    if (extraBytesToRead >= sourceEnd - source) {
      if (flags == WuhooStrictConversion || InputIsPartial) {
        result = WuhooSourceExhausted;
        break;
      } else {
        result = WuhooSourceIllegal;

        /*
         * Replace the maximal subpart of ill-formed sequence with
         * replacement character.
         */
        source +=
          WuhooFindMaximalSubpartOfIllFormedUTF8Sequence(source, sourceEnd);
        *target++ = WUHOO_UNI_REPLACEMENT_CHAR;
        continue;
      }
    }
    if (target >= targetEnd) {
      result = WuhooTargetExhausted;
      break;
    }

    /* Do this check whether lenient or strict */
    if (!WuhooIsLegalUTF8(source, extraBytesToRead + 1)) {
      result = WuhooSourceIllegal;
      if (flags == WuhooStrictConversion) {
        /* Abort conversion. */
        break;
      } else {
        /*
         * Replace the maximal subpart of ill-formed sequence with
         * replacement character.
         */
        source +=
          WuhooFindMaximalSubpartOfIllFormedUTF8Sequence(source, sourceEnd);
        *target++ = WUHOO_UNI_REPLACEMENT_CHAR;
        continue;
      }
    }
    /*
     * The cases all fall through. See "Note A" below.
     */
    switch (extraBytesToRead) {
    case 5: ch += *source++; ch <<= 6;
    case 4: ch += *source++; ch <<= 6;
    case 3: ch += *source++; ch <<= 6;
    case 2: ch += *source++; ch <<= 6;
    case 1: ch += *source++; ch <<= 6;
    case 0: ch += *source++;
    }
    ch -= WuhooOffsetsFromUTF8[extraBytesToRead];

    if (ch <= WUHOO_UNI_MAX_LEGAL_UTF32) {
      /*
       * UTF-16 surrogate values are illegal in UTF-32, and anything
       * over Plane 17 (> 0x10FFFF) is illegal.
       */
      if (ch >= WUHOO_UNI_SUR_HIGH_START && ch <= WUHOO_UNI_SUR_LOW_END) {
        if (flags == WuhooStrictConversion) {
          source -=
            (extraBytesToRead + 1); /* return to the illegal value itself */
          result = WuhooSourceIllegal;
          break;
        } else {
          *target++ = WUHOO_UNI_REPLACEMENT_CHAR;
        }
      } else {
        *target++ = ch;
      }
    } else { /* i.e., ch > UNI_MAX_LEGAL_UTF32 */
      result    = WuhooSourceIllegal;
      *target++ = WUHOO_UNI_REPLACEMENT_CHAR;
    }
  }
  *sourceStart = source;
  *targetStart = target;
  return result;
}

WuhooConversionResult
WuhooConvertUTF8toUTF32Partial(const WuhooUTF8** sourceStart,
                               const WuhooUTF8*  sourceEnd,
                               WuhooUTF32** targetStart, WuhooUTF32* targetEnd,
                               WuhooConversionFlags flags)
{
  return WuhooConvertUTF8toUTF32Impl(sourceStart, sourceEnd, targetStart,
                                     targetEnd, flags,
                                     /*InputIsPartial=*/WuhooTrue);
}

WuhooConversionResult
WuhooConvertUTF8toUTF32(const WuhooUTF8** sourceStart,
                        const WuhooUTF8* sourceEnd, WuhooUTF32** targetStart,
                        WuhooUTF32* targetEnd, WuhooConversionFlags flags)
{
  return WuhooConvertUTF8toUTF32Impl(sourceStart, sourceEnd, targetStart,
                                     targetEnd, flags,
                                     /*InputIsPartial=*/WuhooFalse);
}

WuhooConversionResult
WuhooConvertUTF16toUTF8(const WuhooUTF16** sourceStart,
                        const WuhooUTF16* sourceEnd, WuhooUTF8** targetStart,
                        WuhooUTF8* targetEnd, WuhooConversionFlags flags)
{
  WuhooConversionResult result = WuhooConversionOK;
  const WuhooUTF16*     source = *sourceStart;
  WuhooUTF8*            target = *targetStart;
  while (source < sourceEnd) {
    WuhooUTF32        ch;
    unsigned short    bytesToWrite = 0;
    const WuhooUTF32  byteMask     = 0xBF;
    const WuhooUTF32  byteMark     = 0x80;
    const WuhooUTF16* oldSource =
      source; /* In case we have to back up because of target overflow. */
    ch = *source++;
    /* If we have a surrogate pair, convert to UTF32 first. */
    if (ch >= WUHOO_UNI_SUR_HIGH_START && ch <= WUHOO_UNI_SUR_HIGH_END) {
      /* If the 16 bits following the high surrogate are in the source buffer...
       */
      if (source < sourceEnd) {
        WuhooUTF32 ch2 = *source;
        /* If it's a low surrogate, convert to UTF32. */
        if (ch2 >= WUHOO_UNI_SUR_LOW_START && ch2 <= WUHOO_UNI_SUR_LOW_END) {
          ch = ((ch - WUHOO_UNI_SUR_HIGH_START) << WuhooHalfShift) +
	    (ch2 - WUHOO_UNI_SUR_LOW_START) + WuhooHalfBase;
          ++source;
        } else if (flags == WuhooStrictConversion) { /* it's an unpaired high
                                                        surrogate */
          --source; /* return to the illegal value itself */
          result = WuhooSourceIllegal;
          break;
        }
      } else {    /* We don't have the 16 bits following the high surrogate. */
        --source; /* return to the high surrogate */
        result = WuhooSourceExhausted;
        break;
      }
    } else if (flags == WuhooStrictConversion) {
      /* UTF-16 surrogate values are illegal in UTF-32 */
      if (ch >= WUHOO_UNI_SUR_LOW_START && ch <= WUHOO_UNI_SUR_LOW_END) {
        --source; /* return to the illegal value itself */
        result = WuhooSourceIllegal;
        break;
      }
    }
    /* Figure out how many bytes the result will require */
    if (ch < (WuhooUTF32)0x80) {
      bytesToWrite = 1;
    } else if (ch < (WuhooUTF32)0x800) {
      bytesToWrite = 2;
    } else if (ch < (WuhooUTF32)0x10000) {
      bytesToWrite = 3;
    } else if (ch < (WuhooUTF32)0x110000) {
      bytesToWrite = 4;
    } else {
      bytesToWrite = 3;
      ch           = WUHOO_UNI_REPLACEMENT_CHAR;
    }

    target += bytesToWrite;
    if (target > targetEnd) {
      source = oldSource; /* Back up source pointer! */
      target -= bytesToWrite;
      result = WuhooTargetExhausted;
      break;
    }
    switch (bytesToWrite) { /* note: everything falls through. */
    case 4: *--target = (WuhooUTF8)((ch | byteMark) & byteMask); ch >>= 6;
    case 3: *--target = (WuhooUTF8)((ch | byteMark) & byteMask); ch >>= 6;
    case 2: *--target = (WuhooUTF8)((ch | byteMark) & byteMask); ch >>= 6;
    case 1: *--target = (WuhooUTF8)(ch | WuhooFirstByteMark[bytesToWrite]);
    }
    target += bytesToWrite;
  }
  *sourceStart = source;
  *targetStart = target;
  return result;
}

WuhooConversionResult
WuhooConvertUTF32toUTF8(const WuhooUTF32** sourceStart,
                        const WuhooUTF32* sourceEnd, WuhooUTF8** targetStart,
                        WuhooUTF8* targetEnd, WuhooConversionFlags flags)
{
  WuhooConversionResult result = WuhooConversionOK;
  const WuhooUTF32*     source = *sourceStart;
  WuhooUTF8*            target = *targetStart;
  while (source < sourceEnd) {
    WuhooUTF32       ch;
    unsigned short   bytesToWrite = 0;
    const WuhooUTF32 byteMask     = 0xBF;
    const WuhooUTF32 byteMark     = 0x80;
    ch                            = *source++;
    if (flags == WuhooStrictConversion) {
      /* UTF-16 surrogate values are illegal in UTF-32 */
      if (ch >= WUHOO_UNI_SUR_HIGH_START && ch <= WUHOO_UNI_SUR_LOW_END) {
        --source; /* return to the illegal value itself */
        result = WuhooSourceIllegal;
        break;
      }
    }
    /*
     * Figure out how many bytes the result will require. Turn any
     * illegally large UTF32 things (> Plane 17) into replacement chars.
     */
    if (ch < (WuhooUTF32)0x80) {
      bytesToWrite = 1;
    } else if (ch < (WuhooUTF32)0x800) {
      bytesToWrite = 2;
    } else if (ch < (WuhooUTF32)0x10000) {
      bytesToWrite = 3;
    } else if (ch <= WUHOO_UNI_MAX_LEGAL_UTF32) {
      bytesToWrite = 4;
    } else {
      bytesToWrite = 3;
      ch           = WUHOO_UNI_REPLACEMENT_CHAR;
      result       = WuhooSourceIllegal;
    }

    target += bytesToWrite;
    if (target > targetEnd) {
      --source; /* Back up source pointer! */
      target -= bytesToWrite;
      result = WuhooTargetExhausted;
      break;
    }
    switch (bytesToWrite) { /* note: everything falls through. */
    case 4: *--target = (WuhooUTF8)((ch | byteMark) & byteMask); ch >>= 6;
    case 3: *--target = (WuhooUTF8)((ch | byteMark) & byteMask); ch >>= 6;
    case 2: *--target = (WuhooUTF8)((ch | byteMark) & byteMask); ch >>= 6;
    case 1: *--target = (WuhooUTF8)(ch | WuhooFirstByteMark[bytesToWrite]);
    }
    target += bytesToWrite;
  }
  *sourceStart = source;
  *targetStart = target;
  return result;
}

#ifdef __APPLE__

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <Carbon/Carbon.h> /* Mainly for keycodes */
#//define OBJC_OLD_DISPATCH_PROTOTYPES 1
#include <objc/objc.h>
#include <objc/objc-runtime.h>
#include <objc/NSObjCRuntime.h>

//#include <OpenGL/CGLTypes.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>

#include <ApplicationServices/ApplicationServices.h>

#ifdef __cplusplus
#define OBJC_OBJECT_CAST(object) ();
#else
#endif

#define WuhooMaybeUnused __attribute__((unused))

extern CFStringRef NSPasteboardNameDrag;

#ifdef __cplusplus
extern "C"
{
#endif

  SEL
  NSSelectorFromString(CFStringRef str);
  int
  NSRunAlertPanel(CFStringRef strTitle, CFStringRef strMsg,
                  CFStringRef strButton1, CFStringRef strButton2,
                  CFStringRef strButton3, ...);

typedef id(*WuhooObjMsgSendCb)(id, SEL, ...);
typedef id(*WuhooObjMsgSendStretCb)(id, SEL, ...);

typedef id(*CMacsSimpleMessage)(id, SEL);
typedef void(*CMacsVoidMessage)(id, SEL);
typedef void(*CMacsVoidMessage1)(id, SEL, void *);
typedef id(*CMacsRectMessage1)(id, SEL, CGRect);
typedef id(*CMacsWindowInitMessage)(id, SEL, CGRect, int, int, bool);

WuhooObjMsgSendCb WuhooObjMsgSend = (WuhooObjMsgSendCb)objc_msgSend;
WuhooObjMsgSendStretCb WuhooObjMsgSendStret = (WuhooObjMsgSendStretCb)objc_msgSend_stret;

#ifdef __cplusplus
}
#endif

typedef struct
{
  id         app;
  id         window;
  id         view;
  CGImageRef image;
  id         bitmap;
  id         cgctx;
  id         pool;
  id         glctx;
  id         pixelformat;
  id         future_time;

  Class      WuhooNSView;
  Class      WuhooNSWindow;

  SEL get_type;
  SEL get_subtype;
  SEL get_clickcount;
  SEL get_characters;
  SEL get_modifier_flags;
  SEL get_keycode;

  SEL get_distant_future;
  SEL get_scrolling_delta_x;
  SEL get_scrolling_delta_y;
  SEL get_delta_x;
  SEL get_delta_y;

  WuhooRGBA* buffer;

  NSUInteger window_mask;

  unsigned int prev_dead_char;
  int          previous_change_count;
  int          client_offset;
  int          title_pixel_offset;
} WuhooWindowCocoa;

#define TO_ID(id) (struct objc_object*)(id)

enum
  {
    /* @see NSWindowStyleMask */
    WuhooNSWindowStyleMaskBorderless     = 0,
    WuhooNSWindowStyleMaskTitled         = 1 << 0,
    WuhooNSWindowStyleMaskClosable       = 1 << 1,
    WuhooNSWindowStyleMaskMiniaturizable = 1 << 2,
    WuhooNSWindowStyleMaskResizable      = 1 << 3,
  };

static const char* notification_name_cache[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static int luda = 0;

void
_WuhooNotificationCenterCallback(CFNotificationCenterRef center, void* observer,
                                 CFStringRef name, const void* object,
                                 CFDictionaryRef userInfo)
{
  const char*  raw_name = CFStringGetCStringPtr(name, kCFStringEncodingUTF8);
  WuhooWindow* window   = (WuhooWindow*)observer;
  WuhooWindowCocoa* cocoa_window;
  id                window_responder = (struct objc_object*)object;

  if (notification_name_cache[0] == raw_name ||
      0 == strcmp("NSWindowDidCloseNotification", raw_name)) {
    window->is_alive = WuhooNo;

  } else if (notification_name_cache[1] == raw_name ||
             0 == strcmp("NSWindowDidResizeNotification", raw_name)) {
    if (WuhooNull == window_responder)
      return;

    cocoa_window = (WuhooWindowCocoa*)window->platform_window;

    id view_responder =
      WuhooObjMsgSend(window_responder, sel_registerName("contentView"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   view_responder, sel_registerName("frame"));
    window->cwidth  = rect.size.width;
    window->cheight = rect.size.height;
    rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(cocoa_window->window,
                                                    sel_getUid("frame"));
    window->width  = rect.size.width;
    window->height = rect.size.height;

    window->window_flags |= WUHOO_WINDOW_FLAG_RESIZED;
  } else if (notification_name_cache[2] == raw_name ||
             0 == strcmp("NSWindowDidEnterFullScreenNotification", raw_name)) {
    if (WuhooNull == window_responder)
      return;

    cocoa_window = (WuhooWindowCocoa*)window->platform_window;

    id view_responder =
      WuhooObjMsgSend(window_responder, sel_registerName("contentView"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   view_responder, sel_registerName("frame"));
    window->cwidth  = rect.size.width;
    window->cheight = rect.size.height;
    rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(cocoa_window->window,
                                                    sel_getUid("frame"));
    window->width  = rect.size.width;
    window->height = rect.size.height;

    /* This seems correct for now */
    window->window_flags |=
      WUHOO_WINDOW_FLAG_FULL_SCREEN | WUHOO_WSTATE_MAXIMIZED;
  } else if (notification_name_cache[3] == raw_name ||
             0 == strcmp("NSWindowDidBecomeKeyNotification", raw_name)) {
    window->window_flags |= WUHOO_WINDOW_FLAG_FOCUS_GAINED;
  } else if (notification_name_cache[4] == raw_name ||
             0 == strcmp("NSWindowDidResignKeyNotification", raw_name)) {
    window->window_flags |= WUHOO_WINDOW_FLAG_FOCUS_LOST;
  } else if (notification_name_cache[5] == raw_name ||
             0 == strcmp("NSWindowDidMiniaturizeNotification", raw_name)) {
    window->window_flags |= WUHOO_WINDOW_FLAG_MINIMIZED;
  } else if (notification_name_cache[6] == raw_name ||
             0 == strcmp("NSWindowDidMoveNotification", raw_name)) {
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   window_responder, sel_registerName("frame"));
    window->x = rect.origin.x;
    window->y = rect.origin.y;
    window->window_flags |= WUHOO_WINDOW_FLAG_MOVED;
  } else if (notification_name_cache[7] == raw_name ||
             0 == strcmp("NSWindowDidEndLiveResizeNotification", raw_name)) {
    if (WuhooNull == window_responder)
      return;

    cocoa_window = (WuhooWindowCocoa*)window->platform_window;

    id view_responder =
      WuhooObjMsgSend(window_responder, sel_registerName("contentView"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   view_responder, sel_registerName("frame"));
    window->cwidth  = rect.size.width;
    window->cheight = rect.size.height;
    rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(cocoa_window->window,
                                                    sel_getUid("frame"));
    window->width  = rect.size.width;
    window->height = rect.size.height;

    window->window_flags |= WUHOO_WINDOW_FLAG_RESIZED;
  } else {
  }
}

WuhooInternal WuhooKeyModifiers
_WuhooKeyModifiersExtractCocoa(NSUInteger mod_flags)
{
  int mods = WUHOO_KMOD_NONE;

  mods |= (NX_DEVICELSHIFTKEYMASK & mod_flags) ? WUHOO_KMOD_LSHIFT : 0;
  mods |= (NX_DEVICERSHIFTKEYMASK & mod_flags) ? WUHOO_KMOD_RSHIFT : 0;
  mods |= (NX_DEVICELCTLKEYMASK & mod_flags) ? WUHOO_KMOD_LCTRL : 0;
  mods |= (NX_DEVICERCTLKEYMASK & mod_flags) ? WUHOO_KMOD_RCTRL : 0;
  mods |= (NX_DEVICELALTKEYMASK & mod_flags) ? WUHOO_KMOD_LALT : 0;
  mods |= (NX_DEVICERALTKEYMASK & mod_flags) ? WUHOO_KMOD_RALT : 0;
  mods |= (NX_DEVICELCMDKEYMASK & mod_flags) ? WUHOO_KMOD_LGUI : 0;
  mods |= (NX_DEVICERCMDKEYMASK & mod_flags) ? WUHOO_KMOD_RGUI : 0;
  mods |= (NX_ALPHASHIFTMASK & mod_flags) ? WUHOO_KMOD_CAPS : 0;
  mods |= (NX_SECONDARYFNMASK & mod_flags) ? WUHOO_KMOD_MODE : 0;

  return (WuhooKeyModifiers)mods;
}

WuhooInternal WuhooKeyCode
_WuhooKeyTranslateCocoa(unsigned int key_code)
{
  switch (key_code) {
    /* Undocumented Kye COde for Mac OS X */
  case 0x6e: return WUHOO_VKEY_MENU; break;
  case kVK_ANSI_Comma: return WUHOO_VKEY_COMMA; break;
  case kVK_ANSI_Semicolon: return WUHOO_VKEY_SEMICOLON; break;
  case kVK_ANSI_Backslash: return WUHOO_VKEY_BACK_SLASH; break;
  case kVK_ANSI_Slash: return WUHOO_VKEY_FORWARD_SLASH; break;
  case kVK_ANSI_Quote: return WUHOO_VKEY_QUOTE; break;
  case kVK_ANSI_LeftBracket: return WUHOO_VKEY_LEFT_BRACKET; break;
  case kVK_ANSI_RightBracket: return WUHOO_VKEY_RIGHT_BRACKET; break;
  case kVK_ANSI_Equal: return WUHOO_VKEY_EQUALS; break;
  case kVK_ANSI_Minus: return WUHOO_VKEY_MINUS; break;
  case kVK_ANSI_Period: return WUHOO_VKEY_PERIOD; break;
  case kVK_ANSI_Grave: return WUHOO_VKEY_GRAVE; break;
  case 0xa: return WUHOO_VKEY_GRAVE; break;
  case kVK_ANSI_KeypadDecimal: return WUHOO_VKEY_KPAD_DECIMAL; break;
  case kVK_ANSI_KeypadMultiply: return WUHOO_VKEY_KPAD_MULITPLY; break;
  case kVK_ANSI_KeypadPlus: return WUHOO_VKEY_KPAD_PLUS; break;
  case kVK_ANSI_KeypadClear: return WUHOO_VKEY_KPAD_NUM_LOCK; break;
  case kVK_ANSI_KeypadDivide: return WUHOO_VKEY_KPAD_DIVIDE; break;
  case kVK_ANSI_KeypadEnter: return WUHOO_VKEY_KPAD_ENTER; break;
  case kVK_ANSI_KeypadMinus: return WUHOO_VKEY_KPAD_MINUS; break;
  case kVK_ANSI_KeypadEquals: return WUHOO_VKEY_KPAD_EQUALS; break;
  case kVK_ANSI_Keypad0: return WUHOO_VKEY_KPAD_0; break;
  case kVK_ANSI_Keypad1: return WUHOO_VKEY_KPAD_1; break;
  case kVK_ANSI_Keypad2: return WUHOO_VKEY_KPAD_2; break;
  case kVK_ANSI_Keypad3: return WUHOO_VKEY_KPAD_3; break;
  case kVK_ANSI_Keypad4: return WUHOO_VKEY_KPAD_4; break;
  case kVK_ANSI_Keypad5: return WUHOO_VKEY_KPAD_5; break;
  case kVK_ANSI_Keypad6: return WUHOO_VKEY_KPAD_6; break;
  case kVK_ANSI_Keypad7: return WUHOO_VKEY_KPAD_7; break;
  case kVK_ANSI_Keypad8: return WUHOO_VKEY_KPAD_8; break;
  case kVK_ANSI_Keypad9: return WUHOO_VKEY_KPAD_9; break;
  case kVK_ANSI_0: return WUHOO_VKEY_0; break;
  case kVK_ANSI_1: return WUHOO_VKEY_1; break;
  case kVK_ANSI_2: return WUHOO_VKEY_2; break;
  case kVK_ANSI_3: return WUHOO_VKEY_3; break;
  case kVK_ANSI_4: return WUHOO_VKEY_4; break;
  case kVK_ANSI_5: return WUHOO_VKEY_5; break;
  case kVK_ANSI_6: return WUHOO_VKEY_6; break;
  case kVK_ANSI_7: return WUHOO_VKEY_7; break;
  case kVK_ANSI_8: return WUHOO_VKEY_8; break;
  case kVK_ANSI_9: return WUHOO_VKEY_9; break;
  case kVK_ANSI_A: return WUHOO_VKEY_A; break;
  case kVK_ANSI_B: return WUHOO_VKEY_B; break;
  case kVK_ANSI_C: return WUHOO_VKEY_C; break;
  case kVK_ANSI_D: return WUHOO_VKEY_D; break;
  case kVK_ANSI_E: return WUHOO_VKEY_E; break;
  case kVK_ANSI_F: return WUHOO_VKEY_F; break;
  case kVK_ANSI_G: return WUHOO_VKEY_G; break;
  case kVK_ANSI_H: return WUHOO_VKEY_H; break;
  case kVK_ANSI_I: return WUHOO_VKEY_I; break;
  case kVK_ANSI_J: return WUHOO_VKEY_J; break;
  case kVK_ANSI_K: return WUHOO_VKEY_K; break;
  case kVK_ANSI_L: return WUHOO_VKEY_L; break;
  case kVK_ANSI_M: return WUHOO_VKEY_M; break;
  case kVK_ANSI_N: return WUHOO_VKEY_N; break;
  case kVK_ANSI_O: return WUHOO_VKEY_O; break;
  case kVK_ANSI_P: return WUHOO_VKEY_P; break;
  case kVK_ANSI_Q: return WUHOO_VKEY_Q; break;
  case kVK_ANSI_R: return WUHOO_VKEY_R; break;
  case kVK_ANSI_S: return WUHOO_VKEY_S; break;
  case kVK_ANSI_T: return WUHOO_VKEY_T; break;
  case kVK_ANSI_U: return WUHOO_VKEY_U; break;
  case kVK_ANSI_V: return WUHOO_VKEY_V; break;
  case kVK_ANSI_W: return WUHOO_VKEY_W; break;
  case kVK_ANSI_X: return WUHOO_VKEY_X; break;
  case kVK_ANSI_Y: return WUHOO_VKEY_Y; break;
  case kVK_ANSI_Z: return WUHOO_VKEY_Z; break;
  case kVK_LeftArrow: return WUHOO_VKEY_LEFT; break;
  case kVK_RightArrow: return WUHOO_VKEY_RIGHT; break;
  case kVK_UpArrow: return WUHOO_VKEY_UP; break;
  case kVK_DownArrow: return WUHOO_VKEY_DOWN; break;
  case kVK_Escape: return WUHOO_VKEY_ESCAPE; break;
  case kVK_Return: return WUHOO_VKEY_ENTER; break;
  case kVK_Tab: return WUHOO_VKEY_TAB; break;
  case kVK_Space: return WUHOO_VKEY_SPACE; break;
  case kVK_Delete: return WUHOO_VKEY_DELETE; break;
  case kVK_Command: break;
  case kVK_Shift: break;
  case kVK_CapsLock: break;
  case kVK_Option: break;
  case kVK_Control: break;
  case kVK_RightCommand: break;
  case kVK_RightShift: break;
  case kVK_RightOption: break;
  case kVK_RightControl: break;
  case kVK_Function: break;
  case kVK_F17: break;
  case kVK_VolumeUp: break;
  case kVK_VolumeDown: break;
  case kVK_Mute: break;
  case kVK_F18: break;
  case kVK_F19: break;
  case kVK_F20: break;
  case kVK_F1: return WUHOO_VKEY_F1; break;
  case kVK_F2: return WUHOO_VKEY_F2; break;
  case kVK_F3: return WUHOO_VKEY_F3; break;
  case kVK_F4: return WUHOO_VKEY_F4; break;
  case kVK_F5: return WUHOO_VKEY_F5; break;
  case kVK_F6: return WUHOO_VKEY_F6; break;
  case kVK_F7: return WUHOO_VKEY_F7; break;
  case kVK_F8: return WUHOO_VKEY_F8; break;
  case kVK_F9: return WUHOO_VKEY_F9; break;
  case kVK_F10: return WUHOO_VKEY_F10; break;
  case kVK_F11: return WUHOO_VKEY_F11; break;
  case kVK_F12: return WUHOO_VKEY_F12; break;
  case kVK_F13: return WUHOO_VKEY_F13; break;
  case kVK_F16: break;
  case kVK_F14: break;
  case kVK_F15: break;
  case kVK_Help: return WUHOO_VKEY_INSERT; break;
  case kVK_Home: return WUHOO_VKEY_HOME; break;
  case kVK_PageUp: return WUHOO_VKEY_PAGE_UP; break;
  case kVK_ForwardDelete: return WUHOO_VKEY_BACKSPACE; break;
  case kVK_End: return WUHOO_VKEY_END; break;
  case kVK_PageDown: return WUHOO_VKEY_PAGE_DOWN; break;
  default: return WUHOO_VKEY_UNKNOWN; break;
  }

  return WUHOO_VKEY_UNKNOWN;
}

WuhooResult
_WuhooWindowDropContentsGetCocoa(WuhooWindow* window, WuhooEvent* event,
                                 char* buffer, WuhooSize buffer_size)
{
  WuhooZeroInit(buffer, buffer_size);

  id pis = (id)event->data.drop.context;

  char* memory_offset = buffer;
  for (NSUInteger item_index = 0; item_index < event->data.drop.count;
       item_index++) {
    id pi = WuhooObjMsgSend(pis, sel_getUid("objectAtIndex:"), item_index);

    id pi_data = WuhooObjMsgSend(pi, sel_getUid("dataForType:"), kUTTypeFileURL);
    id urlString =
      WuhooObjMsgSend(TO_ID(objc_getClass("NSString")), sel_getUid("alloc"));
    urlString =
      WuhooObjMsgSend(urlString, sel_getUid("initWithData:encoding:"), pi_data, 4);

    const char* utf8_chars =
      (const char*)WuhooObjMsgSend(urlString, sel_getUid("UTF8String"));

    id url = WuhooObjMsgSend(TO_ID(objc_getClass("NSURL")), sel_getUid("alloc"));
    url    = WuhooObjMsgSend(url, sel_getUid("initWithString:"), urlString);
    id url_path = WuhooObjMsgSend(url, sel_getUid("path"));
    utf8_chars  = (const char*)WuhooObjMsgSend(url_path, sel_getUid("UTF8String"));
    size_t bytes_copied =
      WuhooStringCopy(memory_offset, utf8_chars, WUHOO_MAX_FILE_NAME_LENGTH);
    memory_offset += bytes_copied;
    *memory_offset++ = '\n';
  }

    WuhooObjMsgSend(pis, sel_getUid("release"));

  return WuhooSuccess;
}

WuhooBoolean
_WuhooDropHandleCocoa(WuhooWindow* window, WuhooEvent* event)
{
  WuhooWindowCocoa* cocoa_window;
  cocoa_window = (WuhooWindowCocoa*)window->platform_window;

  id        pb = WuhooObjMsgSend(TO_ID(objc_getClass("NSPasteboard")),
			      sel_getUid("pasteboardWithName:"), NSPasteboardNameDrag);
  NSInteger changeCount =
    (NSInteger)WuhooObjMsgSend(pb, sel_getUid("changeCount"));
  NSUInteger mouse_pressed = (NSUInteger)WuhooObjMsgSend(
						      TO_ID(objc_getClass("NSEvent")), sel_getUid("pressedMouseButtons"));

  if (window->window_flags & WUHOO_WINDOW_FLAG_DROP_STARTED) {
    if (mouse_pressed == 0) {
      window->window_flags &= ~WUHOO_WINDOW_FLAG_DROP_STARTED;

      CGPoint mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
							  (struct objc_object*)objc_getClass("NSEvent"),
							  sel_registerName("mouseLocation"));
      NSInteger window_id = (NSInteger)WuhooObjMsgSend(
						    (struct objc_object*)objc_getClass("NSWindow"),
						    sel_getUid("windowNumberAtPoint:belowWindowWithWindowNumber:"), mouse,
						    0);
      NSInteger window_id_ours = (NSInteger)WuhooObjMsgSend(
							 cocoa_window->window, sel_getUid("windowNumber"));

      if (window_id_ours != window_id) {
        return WuhooNo;
      }

      id pis = WuhooObjMsgSend(pb, sel_getUid("pasteboardItems"));
      /* We specifacally handle the memory for this */
        WuhooObjMsgSend(pis, sel_getUid("retain"));
      NSUInteger pis_count = (NSUInteger)WuhooObjMsgSend(pis, sel_getUid("count"));

      int bytes_required = 0;
      for (NSUInteger item_index = 0; item_index < pis_count; item_index++) {
        id pi = WuhooObjMsgSend(pis, sel_getUid("objectAtIndex:"), item_index);

        id pi_data =
          WuhooObjMsgSend(pi, sel_getUid("dataForType:"), kUTTypeFileURL);
        id urlString =
          WuhooObjMsgSend(TO_ID(objc_getClass("NSString")), sel_getUid("alloc"));
        urlString = WuhooObjMsgSend(
				 urlString, sel_getUid("initWithData:encoding:"), pi_data, 4);

        const char* utf8_chars =
          (const char*)WuhooObjMsgSend(urlString, sel_getUid("UTF8String"));

        id url =
          WuhooObjMsgSend(TO_ID(objc_getClass("NSURL")), sel_getUid("alloc"));
        url = WuhooObjMsgSend(url, sel_getUid("initWithString:"), urlString);
        id url_path = WuhooObjMsgSend(url, sel_getUid("path"));
        utf8_chars =
          (const char*)WuhooObjMsgSend(url_path, sel_getUid("UTF8String"));
        bytes_required +=
          WuhooStringLength(utf8_chars, WUHOO_MAX_FILE_NAME_LENGTH) + 1;
      }

      event->data.drop.context = (WuhooHandle)pis;
      event->data.drop.size    = bytes_required + 1;
      event->data.drop.count   = (WuhooSize)pis_count;
      event->type              = WUHOO_EVT_DROP;

      return WuhooYes;
    } else {
      cocoa_window->previous_change_count = (int)changeCount;
      return WuhooNo;
    }
  }

  if (cocoa_window->previous_change_count == changeCount ||
      cocoa_window->previous_change_count < 0) {
    cocoa_window->previous_change_count = (int)changeCount;
    return WuhooNo;
  }

  if (mouse_pressed == 1) {
    cocoa_window->previous_change_count = (int)changeCount;
    window->window_flags |= WUHOO_WINDOW_FLAG_DROP_STARTED;
  }

  return WuhooNo;
}

WuhooResult
_WuhooWindowSetTitleCocoa(WuhooWindow* window, const char* title)
{
  WuhooWindowCocoa* cocoa_window = (WuhooWindowCocoa*)window->platform_window;
  WuhooResult       result       = WuhooSuccess;

  CFStringRef window_title =
    CFStringCreateWithCString(WuhooNull, title, kCFStringEncodingUTF8);
    WuhooObjMsgSend(cocoa_window->window, sel_registerName("setTitle:"),
               window_title);
  CFRelease(window_title);

  return result;
}

WuhooResult
_WuhooWindowRegionGetCocoa(WuhooWindow* window, int* posx, int* posy,
                           WuhooSize* width, WuhooSize* height)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowCocoa* cocoa_window = (WuhooWindowCocoa*)window->platform_window;

  CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(cocoa_window->window,
                                                         sel_getUid("frame"));

  if (WuhooNull != posx)
    *posx = rect.origin.x;
  if (WuhooNull != posy)
    *posy = rect.origin.y;
  if (WuhooNull != width)
    *width = rect.size.width;
  if (WuhooNull != height)
    *height = rect.size.height;

  return result;
}

WuhooResult
_WuhooWindowClientRegionGetCocoa(WuhooWindow* window, int* posx, int* posy,
				 WuhooSize* width, WuhooSize* height)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowCocoa* cocoa_window = (WuhooWindowCocoa*)window->platform_window;

  CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(cocoa_window->view,
                                                         sel_getUid("frame"));

  if (WuhooNull != posx)
    *posx = rect.origin.x;
  if (WuhooNull != posy)
    *posy = rect.origin.y;
  if (WuhooNull != width)
    *width = rect.size.width;
  if (WuhooNull != height)
    *height = rect.size.height;

  return result;
}

WuhooResult
_WuhooWindowClientRegionSetCocoa(WuhooWindow* window, int posx, int posy,
                                 WuhooSize width, WuhooSize height)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowCocoa* cocoa_window = (WuhooWindowCocoa*)window->platform_window;

  CGRect test;
  test.origin.x    = posx;
  test.origin.y    = posy;
  test.size.width  = width;
  test.size.height = height;

  CGRect client_rect =
    ((CGRect(*)(id, SEL, CGRect, unsigned int))WuhooObjMsgSendStret)(
								   (struct objc_object*)objc_getClass("NSWindow"),
								   sel_registerName("contentRectForFrameRect:styleMask:"), test,
								   (unsigned int)cocoa_window->window_mask);
  int title_height_diff = (int)height - client_rect.size.height;

  CGRect rect;
  rect.origin.x    = posx;
  rect.origin.y    = posy;
  rect.size.width  = width;
  rect.size.height = height + title_height_diff;

  window->width  = rect.size.width;
  window->height = rect.size.height;
  window->x      = rect.origin.x;
  window->y      = rect.origin.y;

    WuhooObjMsgSend(cocoa_window->window, sel_registerName("setFrame:display:"),
               rect, YES);

  return result;
}

WuhooResult
_WuhooWindowRegionSetCocoa(WuhooWindow* window, int posx, int posy, int width,
                           int height)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowCocoa* cocoa_window = (WuhooWindowCocoa*)window->platform_window;

  CGRect test;
  test.origin.x    = posx;
  test.origin.y    = posy;
  test.size.width  = width;
  test.size.height = height;

  CGRect rect;
  rect.origin.x    = posx;
  rect.origin.y    = posy;
  rect.size.width  = width;
  rect.size.height = height;

  window->width  = rect.size.width;
  window->height = rect.size.height;
  window->x      = rect.origin.x;
  window->y      = rect.origin.y;

    WuhooObjMsgSend(cocoa_window->window, sel_registerName("setFrame:display:"),
               rect, YES);

  return result;
}

WuhooResult
_WuhooWindowDestroyCocoa(WuhooWindow* window)
{
  WuhooResult       result       = WuhooSuccess;
  WuhooWindowCocoa* cocoa_window = (WuhooWindowCocoa*)window->platform_window;

#ifdef WUHOO_OPENGL_ENABLE
  if (WUHOO_FLAG_OPENGL & window->flags) {
    WuhooObjMsgSend((struct objc_object*)objc_getClass("NSGraphicsContext"),
                 sel_getUid("setCurrentContext:"), WuhooNull);
  }
#endif

    WuhooObjMsgSend(cocoa_window->pool, sel_registerName("release"));

  return result;
}

CGRect Window_constrainFrameRect(id self, SEL _cmd, CGRect rect, void* screen) {
  return rect;
}

void View_drawRect(id self, SEL _cmd, CGRect rect) {
  //Ivar ivar = class_getInstanceVariable(cocoa_window->WuhooNSView, "_wheels");
  Ivar ivar = class_getInstanceVariable(objc_getClass("WuhooNSView"), "_wheels");

  id tom = object_getIvar(self, ivar);
  WuhooWindow* window = (WuhooWindow*)tom;
  WuhooWindowCocoa* cocoa_window = (WuhooWindowCocoa*)window->platform_window;
  
  if (WuhooNull == cocoa_window->image)
    return;

  id cgctx = WuhooObjMsgSend((id)objc_getClass("NSGraphicsContext"), sel_getUid("currentContext"));
    
  CGContextRef cgctxref =
      (CGContextRef)WuhooObjMsgSend(cgctx, sel_getUid("CGContext"));

  int width = window->cwidth;
  int height = window->cheight;

  CGContextDrawImage(cgctxref, CGRectMake(0, 0, width, height),
                     cocoa_window->image);

  CGImageRelease(cocoa_window->image);
  
  cocoa_window->image = WuhooNull;
}

WuhooResult
_WuhooWindowBlitCocoa(WuhooWindow* window, WuhooRGBA* pixels, WuhooSize x,
                      WuhooSize y, WuhooSize width, WuhooSize height)
{
  WuhooResult       result       = WuhooSuccess;
  WuhooWindowCocoa* cocoa_window = (WuhooWindowCocoa*)window->platform_window;

  id pool =
    WuhooObjMsgSend((struct objc_object*)objc_getClass("NSAutoreleasePool"),
                 sel_registerName("alloc"));
  pool = WuhooObjMsgSend(pool, sel_registerName("init"));

  //WuhooObjMsgSend(cocoa_window->view, sel_getUid("lockFocus"));

#ifdef WUHOO_OPENGL_ENABLE
  if (WUHOO_FLAG_OPENGL & window->flags) {

    WuhooObjMsgSend(cocoa_window->glctx, sel_getUid("update"));
    WuhooObjMsgSend(cocoa_window->glctx, sel_getUid("flushBuffer"));

    WuhooObjMsgSend(pool, sel_getUid("release"));

    return WuhooSuccess;
  }
#endif

  if (WUHOO_WINDOW_FLAG_CLOSED & window->window_flags ||
      WUHOO_WINDOW_FLAG_RESIZED & window->window_flags ||
      WUHOO_WINDOW_FLAG_REGION_UPDATED & window->window_flags) {
    /* If important window states have not been handled yet
     * don not proceed with blitting because this might
     * cause inconcistent behaviors. **REVISIT**
     */
    return WuhooSuccess;
  }

  CGColorSpaceRef   colorSpace = CGColorSpaceCreateDeviceRGB();
  CGDataProviderRef provider   = CGDataProviderCreateWithData(
							      NULL, pixels, width * height * sizeof(*pixels), NULL);

  cocoa_window->image =
    CGImageCreate(width, height, 8, 32, width * sizeof(*pixels), colorSpace,
                  kCGBitmapByteOrder32Big | kCGImageAlphaNoneSkipLast, provider,
                  NULL, true, kCGRenderingIntentDefault);

  CGRect invalidated_rect = CGRectMake(0, 0, width, height);

  WuhooObjMsgSend(cocoa_window->view,
                  sel_registerName("setNeedsDisplayInRect:"), invalidated_rect);
  
  CGColorSpaceRelease(colorSpace);

  //WuhooObjMsgSend(cocoa_window->view, sel_getUid("unlockFocus"));
  WuhooObjMsgSend(pool, sel_getUid("release"));

  return result;
}

//-------------------------------------------------------------------------
//  translate keyDown to true unichar via inputlayout
//-------------------------------------------------------------------------
WuhooResult
WuhooWindowChracterDecodeCocoa(WuhooWindow* window, WuhooEvent* event,
                               id cocoa_event)
{
  WuhooWindowCocoa* cocoa_window;
  cocoa_window = (WuhooWindowCocoa*)window->platform_window;
  // http://stackoverflow.com/questions/12547007/convert-key-code-into-key-equivalent-string
  // http://stackoverflow.com/questions/8263618/convert-virtual-key-code-to-unicode-string

  id          chars = WuhooObjMsgSend(cocoa_event, cocoa_window->get_characters);
  const char* utf8_chars =
    (const char*)WuhooObjMsgSend(chars, sel_getUid("UTF8String"));
  const size_t unicodeStringLength                = 4;
  UniChar      unicodeString[unicodeStringLength] = { 0 };
  UniCharCount reallength                         = 0;

  TISInputSourceRef fkis     = TISCopyCurrentKeyboardInputSource();
  unsigned short    key_code = (unsigned short)((NSUInteger)WuhooObjMsgSend(
									 cocoa_event, cocoa_window->get_keycode));
  NSUInteger        mod_flags =
    (NSUInteger)WuhooObjMsgSend(cocoa_event, cocoa_window->get_modifier_flags);

  if (fkis) {
    CFDataRef cflayoutdata = (CFDataRef)TISGetInputSourceProperty(
								  fkis, kTISPropertyUnicodeKeyLayoutData);
    const UCKeyboardLayout* keyboardlayout =
      (const UCKeyboardLayout*)CFDataGetBytePtr(cflayoutdata);
    CGEventFlags flags        = mod_flags;
    UInt32       keymodifiers = (flags >> 16) & 0xFF;

    UCKeyTranslate(keyboardlayout, key_code, kUCKeyActionDown, keymodifiers,
                   LMGetKbdType(), 0, &cocoa_window->prev_dead_char,
                   unicodeStringLength, &reallength, unicodeString);
    CFRelease(fkis);
  }

  event->type           = WUHOO_EVT_KEY;
  event->data.key.state = WUHOO_KSTATE_DOWN;
  event->data.key.code  = _WuhooKeyTranslateCocoa(key_code);
  event->data.key.mods  = _WuhooKeyModifiersExtractCocoa(mod_flags);
  event->data.key.mods |=
    (1 == cocoa_window->prev_dead_char) ? (int)WUHOO_KMOD_DEADCHAR : 0;
  if (reallength > 0) {
    id nsstring = (id)CFStringCreateWithCharacters(kCFAllocatorDefault,
                                                   unicodeString, reallength);
    utf8_chars  = (const char*)WuhooObjMsgSend(nsstring, sel_getUid("UTF8String"));
    WuhooCharacterCopy((char *)event->data.key.character, utf8_chars);
    CFRelease(nsstring);
  } else {
    WuhooCharacterCopy((char*)event->data.key.character, utf8_chars);
  }

  return WuhooNull;
}

WuhooResult
_WuhooWindowEventNextCocoa(WuhooWindow* window, WuhooEvent* event)
{
  WuhooWindowCocoa* cocoa_window;
  unsigned short    key_code;
  NSUInteger        mod_flags;

  if (WuhooNo == window->is_alive) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_CLOSED;

    return WuhooSuccess;
  }

  cocoa_window = (WuhooWindowCocoa*)window->platform_window;

  if (window->window_flags & WUHOO_WINDOW_FLAG_RESIZED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_RESIZED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    event->data.window.flags = WUHOO_WINDOW_FLAG_RESIZED;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_RESIZED;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_FULL_SCREEN) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_RESIZED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    event->data.window.flags = (WuhooWindowFlags) (WUHOO_WINDOW_FLAG_RESIZED | WUHOO_WINDOW_FLAG_FULL_SCREEN);
    window->window_flags &= ~WUHOO_WINDOW_FLAG_FULL_SCREEN;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_REGION_UPDATED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_INVALIDATED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    event->data.window.flags = WUHOO_WINDOW_FLAG_REGION_UPDATED;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_REGION_UPDATED;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_FOCUS_LOST) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_UNFOCUSED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_FOCUS_LOST;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_FOCUS_GAINED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_FOCUSED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_FOCUS_GAINED;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_MOVED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_MOVED;
    event->data.window.data1 = window->x;
    event->data.window.data2 = window->y;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_MOVED;

    return WuhooSuccess;
  }

  WuhooBoolean needs_redrawing = (WuhooBoolean)(NSUInteger)WuhooObjMsgSend(
									cocoa_window->window, sel_getUid("viewsNeedDisplay"));
  window->window_flags |=
    (WuhooTrue == needs_redrawing) ? WUHOO_WINDOW_FLAG_REGION_UPDATED : 0;

  id pool =
    WuhooObjMsgSend((struct objc_object*)objc_getClass("NSAutoreleasePool"),
                 sel_registerName("alloc"));
  pool = WuhooObjMsgSend(pool, sel_registerName("init"));

  CGPoint mouse;

  if (WuhooYes == _WuhooDropHandleCocoa(window, event)) {
      WuhooObjMsgSend(pool, sel_registerName("release"));

    return WuhooSuccess;
  }

  id cocoa_event =
    WuhooObjMsgSend(cocoa_window->app,
                 sel_registerName("nextEventMatchingMask:untilDate:inMode:dequeue:"),
                 ULONG_MAX, 0, kCFRunLoopDefaultMode, 1);
  

  NSUInteger type =
    (NSUInteger)WuhooObjMsgSend(cocoa_event, cocoa_window->get_type);
  switch (type) {
    /* Look int IOLLEvent.h */
  case NX_MOUSEENTERED:
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						cocoa_event, sel_registerName("locationInWindow"));
    break;
  case NX_MOUSEEXITED:
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						cocoa_event, sel_registerName("locationInWindow"));
    break;
  case kCGEventOtherMouseUp: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));
    event->data.mouse_press.x     = (int)mouse.x - rect.origin.x;
    event->data.mouse_press.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_press.state = WUHOO_MSTATE_MRELEASED;
    event->type                   = WUHOO_EVT_MOUSE_PRESS;
  } break;
  case kCGEventOtherMouseDown: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));

    event->data.mouse_press.x     = (int)mouse.x - rect.origin.x;
    event->data.mouse_press.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_press.state = WUHOO_MSTATE_MPRESSED;
    event->type                   = WUHOO_EVT_MOUSE_PRESS;

  } break;

  case kCGEventRightMouseUp: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));
    event->data.mouse_press.x     = (int)mouse.x - rect.origin.x;
    event->data.mouse_press.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_press.state = WUHOO_MSTATE_RRELEASED;
    event->type                   = WUHOO_EVT_MOUSE_PRESS;
  } break;
  case kCGEventRightMouseDown: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));

    event->data.mouse_press.x     = (int)mouse.x - rect.origin.x;
    event->data.mouse_press.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_press.state = WUHOO_MSTATE_RPRESSED;
    event->type                   = WUHOO_EVT_MOUSE_PRESS;

  } break;
  case kCGEventLeftMouseUp: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));
    event->data.mouse_press.x     = (int)mouse.x - rect.origin.x;
    event->data.mouse_press.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_press.state = WUHOO_MSTATE_LRELEASED;
    event->type                   = WUHOO_EVT_MOUSE_PRESS;
  } break;
  case kCGEventLeftMouseDown: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));

    event->data.mouse_press.x     = (int)mouse.x - rect.origin.x;
    event->data.mouse_press.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_press.state = WUHOO_MSTATE_LPRESSED;
    event->type                   = WUHOO_EVT_MOUSE_PRESS;

  } break;
  case kCGEventMouseMoved: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));

    event->data.mouse_move.x     = (int)mouse.x - rect.origin.x;
    event->data.mouse_move.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_move.state = WUHOO_MSTATE_UNKNOWN;
    event->type                  = WUHOO_EVT_MOUSE_MOVE;

    if ((WUHOO_FLAG_MOUSE_CAPTURE & window->flags) &&
	(window->width > (int)mouse.x && 0 <= (int)mouse.x) &&
	(window->height > (int)mouse.y && 0 <= (int)mouse.y)) {
    }
  } break;
  case kCGEventFlagsChanged:
    break;
  case kCGEventKeyDown: {
    key_code = (unsigned short)((NSUInteger)WuhooObjMsgSend(
							 cocoa_event, cocoa_window->get_keycode));
    mod_flags =
      (NSUInteger)WuhooObjMsgSend(cocoa_event, cocoa_window->get_modifier_flags);

      WuhooObjMsgSend(pool, sel_registerName("release"));

    return WuhooWindowChracterDecodeCocoa(window, event, cocoa_event);
  } break;
  case kCGEventKeyUp: {
    key_code = (unsigned short)((NSUInteger)WuhooObjMsgSend(
							 cocoa_event, cocoa_window->get_keycode));
    mod_flags =
      (NSUInteger)WuhooObjMsgSend(cocoa_event, cocoa_window->get_modifier_flags);

    event->type           = WUHOO_EVT_KEY;
    event->data.key.state = WUHOO_KSTATE_UP;
    event->data.key.code  = _WuhooKeyTranslateCocoa(key_code);
    event->data.key.mods  = _WuhooKeyModifiersExtractCocoa(mod_flags);
    /* Mimicing SDL and GLFW here Unicode on keyup does not make sense */
    event->data.key.character[0] = 0;

    WuhooObjMsgSend(pool, sel_registerName("release"));

    return WuhooSuccess;
  } break;
  case kCGEventOtherMouseDragged: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));

    event->data.mouse_move.x      = (int)mouse.x - rect.origin.x;
    event->data.mouse_move.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_move.state  = WUHOO_MSTATE_MPRESSED;
    event->type                   = WUHOO_EVT_MOUSE_MOVE;
  } break;
  case kCGEventRightMouseDragged: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));

    event->data.mouse_move.x      = (int)mouse.x - rect.origin.x;
    event->data.mouse_move.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_move.state  = WUHOO_MSTATE_RPRESSED;
    event->type                   = WUHOO_EVT_MOUSE_MOVE;

  } break;
  case kCGEventLeftMouseDragged: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));

    event->data.mouse_move.x      = (int)mouse.x - rect.origin.x;
    event->data.mouse_move.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_move.state  = WUHOO_MSTATE_LPRESSED;
    event->type                   = WUHOO_EVT_MOUSE_MOVE;
  } break;
  case kCGEventScrollWheel: {
    mouse = ((CGPoint(*)(id, SEL))WuhooObjMsgSend)(
						(struct objc_object*)objc_getClass("NSEvent"),
						sel_registerName("mouseLocation"));
    CGRect rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
							   cocoa_window->window, sel_getUid("frame"));

    event->data.mouse_wheel.x       = (int)mouse.x - rect.origin.x;
    event->data.mouse_wheel.y      = rect.size.height - ((int)mouse.y - rect.origin.y) - cocoa_window->title_pixel_offset;
    event->data.mouse_wheel.delta_x = ((CGFloat(*)(id, SEL))WuhooObjMsgSend)(
									  cocoa_event, cocoa_window->get_scrolling_delta_x);
    event->data.mouse_wheel.delta_y = ((CGFloat(*)(id, SEL))WuhooObjMsgSend)(
									  cocoa_event, cocoa_window->get_scrolling_delta_y);
    event->type = WUHOO_EVT_MOUSE_WHEEL;
  } break;
  default:
    break;
  }

  WuhooObjMsgSend(cocoa_window->app, sel_getUid("sendEvent:"), cocoa_event);

  WuhooObjMsgSend(pool, sel_registerName("release"));

  return WuhooSuccess;
}

WuhooResult
_WuhooWindowShowCocoa(WuhooWindow* window)
{
  WuhooWindowCocoa* cocoa_window;

  if (window == WuhooNull) {
    return (WuhooResult)WUHOO_STRING " : Invalid window handle.";
  }

  if (WuhooNo == window->is_initialized) {
    return (WuhooResult)WUHOO_STRING " : Invalid window initialization.";
  }

  cocoa_window = (WuhooWindowCocoa*)window->platform_window;

    WuhooObjMsgSend(cocoa_window->app, sel_registerName("deactivate"));
  cocoa_window->view =
    WuhooObjMsgSend(cocoa_window->window, sel_registerName("contentView"));

  WuhooObjMsgSend(cocoa_window->window, sel_registerName("makeFirstResponder:"),
               cocoa_window->view);
  WuhooObjMsgSend(cocoa_window->window, sel_registerName("makeKeyAndOrderFront:"),                 cocoa_window->window);

  WuhooObjMsgSend(cocoa_window->window, sel_registerName("orderFrontRegardless"),
                  cocoa_window->window);

  WuhooObjMsgSend(cocoa_window->app, sel_getUid("setActivationPolicy:"), 0);
  
  cocoa_window->cgctx = WuhooObjMsgSend(TO_ID(objc_getClass("NSGraphicsContext")),
                                     sel_getUid("graphicsContextWithWindow:"),
                                     cocoa_window->window);
  if (WuhooNull == cocoa_window->cgctx) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : failed to get NSGraphicsContext of window.";
  }

#ifdef WUHOO_OPENGL_ENABLE
  if (!WuhooOnlySet(window->flags, WUHOO_FLAG_OPENGL)) {
    return WuhooSuccess;
  }

  CGLPixelFormatAttribute gl_attrs[64];
  int                     gl_index = 0;
  //gl_attrs[gl_index++]             = kCGLPFAAccelerated;
  if (WuhooTrue == window->gl_framebuffer.doublebuffer)
    gl_attrs[gl_index++] = kCGLPFADoubleBuffer;
  /* deprecated */ // if (WuhooTrue == window->gl_framebuffer.stereo)
                   // gl_attrs[gl_index++] = kCGLPFAStereo;
  gl_attrs[gl_index++] = kCGLPFASampleBuffers;
  gl_attrs[gl_index++] = window->gl_framebuffer.samples;
  gl_attrs[gl_index++] = kCGLPFAAuxBuffers;
  gl_attrs[gl_index++] = window->gl_framebuffer.auxBuffers;
  gl_attrs[gl_index++] = kCGLPFAColorSize;
  gl_attrs[gl_index++] = window->gl_framebuffer.redBits +
                         window->gl_framebuffer.greenBits +
                         window->gl_framebuffer.blueBits;
  gl_attrs[gl_index++] = kCGLPFADepthSize;
  gl_attrs[gl_index++] = window->gl_framebuffer.depthBits;
  gl_attrs[gl_index++] = kCGLPFAAlphaSize;
  gl_attrs[gl_index++] = window->gl_framebuffer.alphaBits;
  gl_attrs[gl_index++] = kCGLPFAStencilSize;
  gl_attrs[gl_index++] = window->gl_framebuffer.stencilBits;
  gl_attrs[gl_index++] = kCGLPFAAccumSize;
  gl_attrs[gl_index++] = window->gl_framebuffer.accumRedBits +
                         window->gl_framebuffer.accumGreenBits +
                         window->gl_framebuffer.accumBlueBits;
  gl_attrs[gl_index++] = kCGLPFAOpenGLProfile;
  if (window->gl_framebuffer.version.major >= 3)
    gl_attrs[gl_index++] = (CGLPixelFormatAttribute)kCGLOGLPVersion_GL3_Core;
  else if (window->gl_framebuffer.version.major >= 4)
    gl_attrs[gl_index++] = (CGLPixelFormatAttribute)kCGLOGLPVersion_GL4_Core;
  else
    gl_attrs[gl_index++] = (CGLPixelFormatAttribute)kCGLOGLPVersion_Legacy;
  gl_attrs[gl_index++] = (CGLPixelFormatAttribute)0;

  CGLPixelFormatObj pix;
  GLint             npix      = 0;
  CGLError          cgl_error = CGLChoosePixelFormat(gl_attrs, &pix, &npix);
  if (0 != cgl_error) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : CGLChoosePixelFormat failed.";
  }

  CGLContextObj ctx;
  cgl_error = CGLCreateContext(pix, NULL, &ctx);
  if (0 != cgl_error) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING " : CGLCreateContext failed.";
  }

  GLint dim[2];
  dim[0] = window->width;
  dim[1] = window->height;
  id gl_ctx =
    WuhooObjMsgSend(TO_ID(objc_getClass("NSOpenGLContext")), sel_getUid("alloc"));
  gl_ctx = WuhooObjMsgSend(gl_ctx, sel_getUid("initWithCGLContextObj:"), ctx);

  WuhooObjMsgSend(gl_ctx, sel_getUid("setView:"), cocoa_window->view);
  WuhooObjMsgSend(gl_ctx, sel_getUid("makeCurrentContext"));
  /* Set this t suppress high dpi mechanisms */
  WuhooObjMsgSend(cocoa_window->view, sel_getUid("setWantsBestResolutionOpenGLSurface:"), 0);
  WuhooObjMsgSend(gl_ctx, sel_getUid("update"));
  WuhooObjMsgSend(gl_ctx, sel_getUid("flushBuffer"));

  cocoa_window->glctx = gl_ctx;
#endif

  return WuhooSuccess;
}

WuhooResult
_WuhooWindowCreateCocoa(WuhooWindow* window, int posx, int posy,
                        WuhooSize width, WuhooSize height, const char* title,
                        WuhooFlags flags)
{
  /* TODO: Size Checks */
  WuhooWindowCocoa* cocoa_window;

  cocoa_window = (WuhooWindowCocoa*)&window->memory[0];

  cocoa_window->WuhooNSView = objc_allocateClassPair((Class)objc_getClass("NSView"), "WuhooNSView", 0);
  cocoa_window->WuhooNSWindow = objc_allocateClassPair((Class)objc_getClass("NSWindow"), "WuhooNSWindow", 0);
  
  /* https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtTypeEncodings.html#//apple_ref/doc/uid/TP40008048-CH100 */
  class_addMethod(cocoa_window->WuhooNSView, sel_getUid("drawRect:"), (IMP) View_drawRect, "v@:{CGRect={CGPoint=dd}{CGSize=dd}}");
	class_addMethod(cocoa_window->WuhooNSWindow, sel_getUid("constrainFrameRect:toScreen:"), (IMP) Window_constrainFrameRect, "{CGRect={CGPoint=dd}{CGSize=dd}}@:{CGRect={CGPoint=dd}{CGSize=dd}}^v");
  
  class_addIvar(cocoa_window->WuhooNSView, "_wheels", sizeof(void*), log2(sizeof(void*)), "^v");
  class_addIvar(cocoa_window->WuhooNSView, "_wheels", sizeof(void*), log2(sizeof(void*)), "^v");

  objc_registerClassPair(cocoa_window->WuhooNSView);
  objc_registerClassPair(cocoa_window->WuhooNSWindow);
 
  window->is_alive    = WuhooYes;
  window->global_mods = (WuhooKeyModifiers)0;

  cocoa_window->client_offset = 0;
  cocoa_window->app           = (struct objc_object*)WuhooNull;
  cocoa_window->window        = (struct objc_object*)WuhooNull;
  cocoa_window->glctx         = (struct objc_object*)WuhooNull;
  cocoa_window->cgctx         = (struct objc_object*)WuhooNull;
  cocoa_window->view          = (struct objc_object*)WuhooNull;
  cocoa_window->image         = (CGImageRef)WuhooNull;
  cocoa_window->pool          = (struct objc_object*)WuhooNull;

  /* Gather global state */
  window->global_mods |= (WuhooKeyModifiers)(
    (CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState) &
     NX_ALPHASHIFTMASK)
      ? (WuhooKeyModifiers)WUHOO_KMOD_CAPS
      : WUHOO_KMOD_NONE);
  window->global_mods |= (WuhooKeyModifiers)(
    (CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState) &
     NX_SECONDARYFNMASK)
      ? (WuhooKeyModifiers)WUHOO_KMOD_MODE
      : WUHOO_KMOD_NONE);

  id screen = WuhooObjMsgSend((struct objc_object*)objc_getClass("NSScreen"),
                           sel_registerName("mainScreen"));

  CGRect screen_rect = ((CGRect(*)(id, SEL))WuhooObjMsgSendStret)(
    screen, sel_registerName("visibleFrame"));

  cocoa_window->pool =
    WuhooObjMsgSend((struct objc_object*)objc_getClass("NSAutoreleasePool"),
                 sel_registerName("alloc"));
  cocoa_window->pool =
    WuhooObjMsgSend(cocoa_window->pool, sel_registerName("init"));
  if (WuhooNull == cocoa_window->pool) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : NSAutoreleasePool failed.";
  }

  cocoa_window->app =
    WuhooObjMsgSend((struct objc_object*)objc_getClass("NSApplication"),
                 sel_getUid("sharedApplication"));
  if (WuhooNull == cocoa_window->app) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : NSApplication sharedApplication failed.";
  }

  CGRect test;
  test.origin.x    = 0;
  test.origin.y    = 0;
  test.size.width  = width;
  test.size.height = height;

  cocoa_window->previous_change_count = -1;
  cocoa_window->window_mask           = WuhooNSWindowStyleMaskMiniaturizable;
  cocoa_window->window_mask |=
   !(WUHOO_FLAG_BORDERLESS & flags) ? WuhooNSWindowStyleMaskTitled : 0;
  cocoa_window->window_mask |=
    (WUHOO_FLAG_RESIZEABLE & flags) ? WuhooNSWindowStyleMaskResizable : 0;
  cocoa_window->window_mask |=
    (WUHOO_FLAG_CLOSEABLE & flags) ? WuhooNSWindowStyleMaskClosable : 0;

  CGRect client_rect =
    ((CGRect(*)(id, SEL, CGRect, unsigned int))WuhooObjMsgSendStret)(
      (struct objc_object*)objc_getClass("NSWindow"),
      sel_registerName("contentRectForFrameRect:styleMask:"), test,
      (unsigned int)cocoa_window->window_mask);
  int     title_height_diff = (int)(height - client_rect.size.height);
  CGFloat dock_height_diff  = screen_rect.size.height - height;
  CGRect  rect;
  rect.size.width  = width;
  rect.size.height = height;

  if (dock_height_diff < 0.0f) {
    cocoa_window->client_offset = ((int)((dock_height_diff + 0.5f)));
    cocoa_window->client_offset +=
      (title_height_diff < 0.0f) ? ((int)((title_height_diff + 0.5f))) : 0;
  }

  cocoa_window->title_pixel_offset = title_height_diff;

  window->width  = rect.size.width;
  window->height = rect.size.height;

  rect.size.height -=
    (WUHOO_FLAG_CLIENT_REGION & flags) ? 0 : title_height_diff;

  rect.origin.x = (WuhooDefaultPosition != posx)
                    ? posx
                    : ((screen_rect.size.width / 2) - (rect.size.width / 2));
  rect.origin.y = (WuhooDefaultPosition != posy)
                    ? posy
                    : ((screen_rect.size.height / 2) - (rect.size.height / 2));

  cocoa_window->window = WuhooObjMsgSend(
    (struct objc_object*)objc_getClass("WuhooNSWindow"), sel_registerName("alloc"));
  cocoa_window->window = WuhooObjMsgSend(
    cocoa_window->window,
    sel_registerName("initWithContentRect:styleMask:backing:defer:"), rect,
    cocoa_window->window_mask, 1, WuhooNo);
  if (WuhooNull == cocoa_window->window) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : NSWindow initWithContentRect failed.";
  }

  CGRect view_rect = CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height);
  id view = WuhooObjMsgSend(WuhooObjMsgSend((id)objc_getClass("WuhooNSView"), sel_getUid("alloc")), sel_getUid("initWithFrame:"), view_rect);

  // here we simply add the view to the window.
  WuhooObjMsgSend(cocoa_window->window, sel_getUid("setContentView:"), view);
  WuhooObjMsgSend(cocoa_window->window, sel_getUid("becomeFirstResponder"));
  
  Ivar ivar = class_getInstanceVariable(cocoa_window->WuhooNSView, "_wheels");
  object_setIvar(view, ivar, (id)window);
  
  window->cwidth  = rect.size.width;
  window->cheight = rect.size.height;

  id typ = WuhooObjMsgSend((struct objc_object*)objc_getClass("NSArray"),
                        sel_registerName("arrayWithObjects:"), kUTTypeURL,
                        kUTTypeFileURL, WuhooNull);
  WuhooObjMsgSend(cocoa_window->window,
             sel_registerName("registerForDraggedTypes:"), typ);

  if ((WUHOO_FLAG_TITLED & flags) && title) {
    /* TODO: Check for reasonable title length??? */
    CFStringRef window_title =
      CFStringCreateWithCString(NULL, title, kCFStringEncodingUTF8);
      WuhooObjMsgSend(cocoa_window->window, sel_registerName("setTitle:"),
                 window_title);
    CFRelease(window_title);
  }

  CFNotificationCenterAddObserver(
    CFNotificationCenterGetLocalCenter(), (const void*)window,
    _WuhooNotificationCenterCallback, (CFStringRef)WuhooNull,
    cocoa_window->window, CFNotificationSuspensionBehaviorDeliverImmediately);

  window->platform_window = cocoa_window;

  cocoa_window->get_type              = sel_registerName("type");
  cocoa_window->get_subtype           = sel_registerName("subtype");
  cocoa_window->get_clickcount        = sel_registerName("clickCount");
  cocoa_window->get_characters        = sel_registerName("characters");
  cocoa_window->get_modifier_flags    = sel_registerName("modifierFlags");
  cocoa_window->get_keycode           = sel_registerName("keyCode");
  cocoa_window->get_scrolling_delta_x = sel_registerName("scrollingDeltaX");
  cocoa_window->get_scrolling_delta_y = sel_registerName("scrollingDeltaY");
  cocoa_window->get_delta_x           = sel_registerName("deltaX");
  cocoa_window->get_delta_y           = sel_registerName("deltaY");

  window->window_flags |= WUHOO_WINDOW_FLAG_RESIZED;


    WuhooObjMsgSend(cocoa_window->app,
                 sel_getUid("finishLaunching"));

  return WuhooSuccess;
}

#endif

#ifdef _WIN32

#define WUHOO_MAX_ENCODED_TITLE_LENGTH 512

#include <Windows.h>
#include <shellapi.h>

#define WuhooMaybeUnused

typedef HGLRC WINAPI
                                 wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext,
                                                                 const int* attribList);
wglCreateContextAttribsARB_type* WUHOO_wglCreateContextAttribsARB;

// See https://www.opengl.org/registry/specs/ARB/wgl_create_context.txt for all
// values
#define WUHOO_WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WUHOO_WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WUHOO_WGL_CONTEXT_PROFILE_MASK_ARB 0x9126

#define WUHOO_WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

typedef BOOL WINAPI
                              wglChoosePixelFormatARB_type(HDC hdc, const int* piAttribIList,
                                                           const FLOAT* pfAttribFList, UINT nMaxFormats,
                                                           int* piFormats, UINT* nNumFormats);
wglChoosePixelFormatARB_type* WUHOO_wglChoosePixelFormatARB;

#define WUHOO_WGL_NUMBER_PIXEL_FORMATS_ARB 0x2000
#define WUHOO_WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WUHOO_WGL_DRAW_TO_BITMAP_ARB 0x2002
#define WUHOO_WGL_ACCELERATION_ARB 0x2003
#define WUHOO_WGL_NEED_PALETTE_ARB 0x2004
#define WUHOO_WGL_NEED_SYSTEM_PALETTE_ARB 0x2005
#define WUHOO_WGL_SWAP_LAYER_BUFFERS_ARB 0x2006
#define WUHOO_WGL_SWAP_METHOD_ARB 0x2007
#define WUHOO_WGL_NUMBER_OVERLAYS_ARB 0x2008
#define WUHOO_WGL_NUMBER_UNDERLAYS_ARB 0x2009
#define WUHOO_WGL_TRANSPARENT_ARB 0x200A
#define WUHOO_WGL_SHARE_DEPTH_ARB 0x200C
#define WUHOO_WGL_SHARE_STENCIL_ARB 0x200D
#define WUHOO_WGL_SHARE_ACCUM_ARB 0x200E
#define WUHOO_WGL_SUPPORT_GDI_ARB 0x200F
#define WUHOO_WGL_SUPPORT_OPENGL_ARB 0x2010
#define WUHOO_WGL_DOUBLE_BUFFER_ARB 0x2011
#define WUHOO_WGL_STEREO_ARB 0x2012
#define WUHOO_WGL_PIXEL_TYPE_ARB 0x2013
#define WUHOO_WGL_COLOR_BITS_ARB 0x2014
#define WUHOO_WGL_RED_BITS_ARB 0x2015
#define WUHOO_WGL_RED_SHIFT_ARB 0x2016
#define WUHOO_WGL_GREEN_BITS_ARB 0x2017
#define WUHOO_WGL_GREEN_SHIFT_ARB 0x2018
#define WUHOO_WGL_BLUE_BITS_ARB 0x2019
#define WUHOO_WGL_BLUE_SHIFT_ARB 0x201A
#define WUHOO_WGL_ALPHA_BITS_ARB 0x201B
#define WUHOO_WGL_ALPHA_SHIFT_ARB 0x201C
#define WUHOO_WGL_ACCUM_BITS_ARB 0x201D
#define WUHOO_WGL_ACCUM_RED_BITS_ARB 0x201E
#define WUHOO_WGL_ACCUM_GREEN_BITS_ARB 0x201F
#define WUHOO_WGL_ACCUM_BLUE_BITS_ARB 0x2020
#define WUHOO_WGL_ACCUM_ALPHA_BITS_ARB 0x2021
#define WUHOO_WGL_DEPTH_BITS_ARB 0x2022
#define WUHOO_WGL_STENCIL_BITS_ARB 0x2023
#define WUHOO_WGL_AUX_BUFFERS_ARB 0x2024
#define WUHOO_WGL_NO_ACCELERATION_ARB 0x2025
#define WUHOO_WGL_GENERIC_ACCELERATION_ARB 0x2026
#define WUHOO_WGL_FULL_ACCELERATION_ARB 0x2027
#define WUHOO_WGL_SWAP_EXCHANGE_ARB 0x2028
#define WUHOO_WGL_SWAP_COPY_ARB 0x2029
#define WUHOO_WGL_SWAP_UNDEFINED_ARB 0x202A
#define WUHOO_WGL_TYPE_RGBA_ARB 0x202B
#define WUHOO_WGL_TYPE_COLORINDEX_ARB 0x202C
#define WUHOO_WGL_TRANSPARENT_RED_VALUE_ARB 0x2037
#define WUHOO_WGL_TRANSPARENT_GREEN_VALUE_ARB 0x2038
#define WUHOO_WGL_TRANSPARENT_BLUE_VALUE_ARB 0x2039
#define WUHOO_WGL_TRANSPARENT_ALPHA_VALUE_ARB 0x203A
#define WUHOO_WGL_TRANSPARENT_INDEX_VALUE_ARB 0x203B

typedef struct
{
  HINSTANCE app;
  HWND      window;
  HDC       dc;
#ifdef WUHOO_OPENGL_ENABLE
  HGLRC glrc;
#endif
  HDC        mem_dc;
  HBITMAP    bitmap;
  HDROP      last_drop; /* last drop */
  WuhooRGBA* dib;
  WuhooSize  last_click;
} WuhooWindowWin32;

WuhooResult
_WuhooWindowSetTitleWin32(WuhooWindow* window, const char* title)
{
  WuhooWindowWin32* win32_window = (WuhooWindowWin32*)window->platform_window;
  WuhooResult       result       = WuhooSuccess;

#ifdef WUHOO_UNICODE
  WuhooUTF16  encoded_title[WUHOO_MAX_ENCODED_TITLE_LENGTH];
  WuhooUTF16* encoded_title_ptr = &encoded_title[0];

  WuhooMemzero(encoded_title, sizeof(encoded_title));
  size_t title_length = WuhooStringLength(title, WUHOO_MAX_TITLE_LENGTH);
  WuhooConvertUTF8toUTF16((const WuhooUTF8 **)&title, (const WuhooUTF8 *)title + title_length, &encoded_title_ptr,
                          encoded_title_ptr + WUHOO_MAX_ENCODED_TITLE_LENGTH,
                          WuhooStrictConversion);
#else
  const WuhooUTF8* encoded_title = (const WuhooUTF8*)title;
#endif

  SetWindowText(win32_window->window, (LPTSTR)encoded_title);

  return result;
}

WuhooResult
_WuhooWindowDestroyWin32(WuhooWindow* window)
{
  WuhooWindowWin32* win32_window = (WuhooWindowWin32*)window->platform_window;
  WuhooResult       result       = WuhooSuccess;

  if (WuhooNull != win32_window->last_drop)
    DragFinish(win32_window->last_drop);

  TCHAR classname[32];
  GetClassName(win32_window->window, classname, 32);
  ReleaseDC(win32_window->window, win32_window->dc);
  DestroyWindow(win32_window->window);
  UnregisterClass(classname, win32_window->app);

#ifdef WUHOO_OPENGL_ENABLE
  wglMakeCurrent(win32_window->dc, 0);
  wglDeleteContext(win32_window->glrc);
#endif

  return result;
}

WuhooResult
_WuhooWindowRegionGetWin32(WuhooWindow* window, int* posx, int* posy,
                           WuhooSize* width, WuhooSize* height)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowWin32* win32_window = (WuhooWindowWin32*)window->platform_window;

  RECT rect;
  GetWindowRect(win32_window->window, &rect);

  if (WuhooNull != posx)
    *posx = rect.left;
  if (WuhooNull != posy)
    *posy = rect.top;
  if (WuhooNull != width)
    *width = rect.right - rect.left;
  if (WuhooNull != height)
    *height = rect.bottom - rect.top;

  return result;
}

WuhooResult
_WuhooWindowRegionSetWin32(WuhooWindow* window, int posx, int posy, int width,
                           int height)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowWin32* win32_window = (WuhooWindowWin32*)window->platform_window;

  MoveWindow(win32_window->window, posx, posy, width, height, TRUE);
  UpdateWindow(win32_window->window);
  window->window_flags |= WUHOO_WINDOW_FLAG_RESIZED;

  RECT rect;
  GetClientRect(win32_window->window, &rect);

  window->x      = rect.left;
  window->y      = rect.top;
  window->width  = rect.right;
  window->height = rect.bottom;

  return result;
}

WuhooResult
_WuhooWindowClientRegionGetWin32(WuhooWindow* window, int* posx, int* posy,
                                 WuhooSize* width, WuhooSize* height)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowWin32* win32_window = (WuhooWindowWin32*)window->platform_window;

  RECT rect;
  GetClientRect(win32_window->window, &rect);

  if (WuhooNull != posx)
    *posx = rect.left;
  if (WuhooNull != posy)
    *posy = rect.top;
  if (WuhooNull != width)
    *width = rect.right - rect.left;
  if (WuhooNull != height)
    *height = rect.bottom - rect.top;

  return result;
}

WuhooResult
_WuhooWindowClientRegionSetWin32(WuhooWindow* window, int posx, int posy,
                                 WuhooSize width, WuhooSize height)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowWin32* win32_window = (WuhooWindowWin32*)window->platform_window;

  RECT  rect    = { 0, 0, (LONG)width, (LONG)height };
  DWORD dwStyle = (DWORD)GetWindowLong(win32_window->window, GWL_STYLE);
  AdjustWindowRect(&rect, dwStyle, FALSE); // adjust the size

  MoveWindow(win32_window->window, posx, posy, rect.right - rect.left,
             rect.bottom - rect.top, TRUE);
  UpdateWindow(win32_window->window);
  window->window_flags |= WUHOO_WINDOW_FLAG_RESIZED;

  window->x      = posx;
  window->y      = posy;
  window->width  = rect.right - rect.left;
  window->height = rect.bottom - rect.top;

  return WuhooSuccess;
}

WuhooResult
_WuhooWindowBlitWin32(WuhooWindow* window, WuhooRGBA* pixels, WuhooSize x,
                      WuhooSize y, WuhooSize width, WuhooSize height)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowWin32* win32_window = (WuhooWindowWin32*)window->platform_window;

#ifdef WUHOO_OPENGL_ENABLE
  if (WUHOO_FLAG_OPENGL & window->flags) {
    SwapBuffers(win32_window->dc);
    return WuhooSuccess;
  }
#endif /* WUHOO_OPENGL_ENABLE */

  if (WUHOO_WINDOW_FLAG_CLOSED & window->window_flags ||
      WUHOO_WINDOW_FLAG_RESIZED & window->window_flags ||
      WUHOO_WINDOW_FLAG_REGION_UPDATED & window->window_flags) {
    /* If important window states have not been handled yet
     * don not proceed with blitting because this might
     * cause inconcistent behaviors. **REVISIT**
     */
    return WuhooSuccess;
  }

  RECT rect;
  GetClientRect(win32_window->window, &rect);

  /*BITMAPINFO bmi;
  bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
  bmi.bmiHeader.biWidth = rect.right;
  bmi.bmiHeader.biHeight = -rect.bottom; // Order pixels from top to bottom
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32; // last byte not used, 32 bit for alignment
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biSizeImage = 0;
  bmi.bmiHeader.biXPelsPerMeter = 0;
  bmi.bmiHeader.biYPelsPerMeter = 0;
  bmi.bmiHeader.biClrUsed = 0;
  bmi.bmiHeader.biClrImportant = 0;
  bmi.bmiColors[0].rgbBlue = 0;
  bmi.bmiColors[0].rgbGreen = 0;
  bmi.bmiColors[0].rgbRed = 0;
  bmi.bmiColors[0].rgbReserved = 0;

  HRESULT iRet = StretchDIBits(win32_window->dc,
          // destination rectangle
          0, 0, rect.right, rect.bottom,
          // source rectangle
          0, 0, rect.right, rect.bottom,
          pixels,
          &bmi,
          DIB_RGB_COLORS,
          SRCCOPY);*/

  window->convert_rgba(win32_window->dib, pixels, x, y, window->cwidth,
                       window->cheight, window->cwidth, window->cheight);

  SelectObject(win32_window->mem_dc, win32_window->bitmap);
  BitBlt(win32_window->dc, 0, 0, rect.right, rect.bottom, win32_window->mem_dc,
         0, 0, SRCCOPY);
  // SelectObject( hdcMem, hbmOld );

  return result;
}

WuhooResult
_WuhooWindowDropContentsGetWin32(WuhooWindow* window, WuhooEvent* event,
                                 char* buffer, int buffer_size)
{
  WuhooChar scratch_buffer[WUHOO_MAX_FILE_NAME_LENGTH];

  WuhooZeroInit(scratch_buffer, sizeof(scratch_buffer));
  WuhooZeroInit(buffer, buffer_size);

  WuhooUTF8* data_ptr = (WuhooUTF8*)buffer;
  for (WuhooSize drop_index = 0; drop_index < event->data.drop.count; drop_index++) {
    const WuhooChar* buffer_ptr = &scratch_buffer[0];
    UINT             written    = DragQueryFile(
      (HDROP)event->data.drop.context, drop_index, (TCHAR*)buffer_ptr,
      sizeof(scratch_buffer) / sizeof(scratch_buffer[0]));
#ifdef WUHOO_UNICODE
    WuhooConversionResult res =
      WuhooConvertUTF16toUTF8(&buffer_ptr, buffer_ptr + written, &data_ptr,
                              data_ptr + buffer_size, WuhooStrictConversion);
	*data_ptr++ = '\n';
#else
    WuhooStringCopy((char*)data_ptr, (const char*)buffer_ptr, written);
    data_ptr += written;
	*data_ptr++ = '\n';
#endif
  }

  *data_ptr = 0;

  // DragFinish((HDROP)event->data.drop.context);

  return WuhooSuccess;
}

WuhooResult
_WuhooWindowEventNextWin32(WuhooWindow* window, WuhooEvent* event)
{
  WuhooWindowWin32* win32_window = (WuhooWindowWin32*)window->platform_window;
  int               mods         = WUHOO_KMOD_NONE;
  MSG               msg          = { 0 };
  TCHAR             ch;
  TCHAR             szBuf[128];
  WuhooBoolean      WasDown;

  /* @see
   * https://www.daniweb.com/programming/software-development/code/241875/fast-animation-with-the-windows-gdi
   */
  while (1) {
    // if( PeekMessage( &msg, win32_window->window, 0, 0, PM_REMOVE ) ) {
    if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)) {
      switch (msg.message) {
        case WM_DROPFILES: {
          HDROP hdrop;
          hdrop = (HDROP)msg.wParam;
          if (WuhooNull != win32_window->last_drop)
            DragFinish(win32_window->last_drop);
          win32_window->last_drop = hdrop;

          int drop_count =
            DragQueryFile(hdrop, 0xFFFFFFFF, (TCHAR*)WuhooNull, 0);
          int drop_size       = 0;
          int drop_max_size   = 0;
          int drop_total_size = 0;
          int written         = 0;
          for (int drop_index = 0; drop_index < drop_count; drop_index++) {
            drop_size =
              DragQueryFile(hdrop, drop_index, (TCHAR*)WuhooNull, 0) + 1;
            drop_total_size += drop_size;
            if (drop_size > drop_max_size)
              drop_max_size = drop_size;
          }

          event->data.drop.count   = drop_count;
          event->data.drop.size    = drop_total_size * 4;
          event->data.drop.context = (WuhooHandle)hdrop;
          event->type              = WUHOO_EVT_DROP;
        } break;
		case WM_MOUSEMOVE: {
			event->type = WUHOO_EVT_MOUSE_MOVE;
			event->data.mouse_move.x = LOWORD(msg.lParam);
			event->data.mouse_move.y = HIWORD(msg.lParam);
			event->data.mouse_move.state = (msg.wParam & MK_LBUTTON)
				? WUHOO_MSTATE_LPRESSED
				: WUHOO_MSTATE_UNKNOWN;
			event->data.mouse_move.state = (msg.wParam & MK_MBUTTON)
				? WUHOO_MSTATE_MPRESSED
				: event->data.mouse_move.state;
			event->data.mouse_move.state = (msg.wParam & MK_RBUTTON)
				? WUHOO_MSTATE_RPRESSED
				: event->data.mouse_move.state;
			event->data.mouse_move.mods |=
				(msg.wParam & MK_CONTROL) ? WUHOO_KMOD_CTRL : WUHOO_KMOD_NONE;
			event->data.mouse_move.mods |=
				(msg.wParam & MK_SHIFT) ? WUHOO_KMOD_SHIFT : WUHOO_KMOD_NONE;

		} break;
		case WM_MOUSEWHEEL: {
			event->type = WUHOO_EVT_MOUSE_WHEEL;
			event->data.mouse_wheel.delta_y =
				(float)GET_WHEEL_DELTA_WPARAM(msg.wParam) / WHEEL_DELTA;
		}break;
		case WM_MBUTTONUP: {
			event->type = WUHOO_EVT_MOUSE_PRESS;
			event->data.mouse_press.state = WUHOO_MSTATE_MRELEASED;
			event->data.mouse_press.mods |=
				(msg.wParam & MK_CONTROL) ? WUHOO_KMOD_CTRL : WUHOO_KMOD_NONE;
			event->data.mouse_press.mods |=
				(msg.wParam & MK_SHIFT) ? WUHOO_KMOD_SHIFT : WUHOO_KMOD_NONE;

			if (win32_window->window == GetCapture())
				ReleaseCapture();
		} break;
        case WM_MBUTTONDBLCLK:
          event->data.mouse_press.click_count++;
          /* fallthrough */
		case WM_MBUTTONDOWN: {
			event->type = WUHOO_EVT_MOUSE_PRESS;
			event->data.mouse_press.state = WUHOO_MSTATE_MPRESSED;
			event->data.mouse_press.mods |=
				(msg.wParam & MK_CONTROL) ? WUHOO_KMOD_CTRL : WUHOO_KMOD_NONE;
			event->data.mouse_press.mods |=
				(msg.wParam & MK_SHIFT) ? WUHOO_KMOD_SHIFT : WUHOO_KMOD_NONE;

			if (win32_window->window != GetCapture())
				SetCapture(win32_window->window);
			break;
		case WM_LBUTTONUP:
			event->type = WUHOO_EVT_MOUSE_PRESS;
			event->data.mouse_press.state = WUHOO_MSTATE_LRELEASED;
			event->data.mouse_press.mods |=
				(msg.wParam & MK_CONTROL) ? WUHOO_KMOD_CTRL : WUHOO_KMOD_NONE;
			event->data.mouse_press.mods |=
				(msg.wParam & MK_SHIFT) ? WUHOO_KMOD_SHIFT : WUHOO_KMOD_NONE;

			if (win32_window->window == GetCapture())
				ReleaseCapture();
		} break;
        case WM_LBUTTONDOWN:
          /*if (GetTickCount() - win32_window->last_click <
          GetDoubleClickTime()) { event->data.mouse_press.click_count++;
          }
          win32_window->last_click = GetTickCount();*/
          event->type                   = WUHOO_EVT_MOUSE_PRESS;
          event->data.mouse_press.state = WUHOO_MSTATE_LPRESSED;
          event->data.mouse_press.mods |=
            (msg.wParam & MK_CONTROL) ? WUHOO_KMOD_CTRL : WUHOO_KMOD_NONE;
          event->data.mouse_press.mods |=
            (msg.wParam & MK_SHIFT) ? WUHOO_KMOD_SHIFT : WUHOO_KMOD_NONE;
          event->data.mouse_press.click_count++;

          if (win32_window->window != GetCapture())
            SetCapture(win32_window->window);
          break;
        case WM_RBUTTONUP:
          event->type                   = WUHOO_EVT_MOUSE_PRESS;
          event->data.mouse_press.state = WUHOO_MSTATE_RRELEASED;
          event->data.mouse_press.mods |=
            (msg.wParam & MK_CONTROL) ? WUHOO_KMOD_CTRL : WUHOO_KMOD_NONE;
          event->data.mouse_press.mods |=
            (msg.wParam & MK_SHIFT) ? WUHOO_KMOD_SHIFT : WUHOO_KMOD_NONE;

          if (win32_window->window == GetCapture())
            ReleaseCapture();
          break;
        case WM_RBUTTONDOWN:
          event->type                   = WUHOO_EVT_MOUSE_PRESS;
          event->data.mouse_press.state = WUHOO_MSTATE_RPRESSED;
          event->data.mouse_press.mods |=
            (msg.wParam & MK_CONTROL) ? WUHOO_KMOD_CTRL : WUHOO_KMOD_NONE;
          event->data.mouse_press.mods |=
            (msg.wParam & MK_SHIFT) ? WUHOO_KMOD_SHIFT : WUHOO_KMOD_NONE;

          if (win32_window->window != GetCapture())
            SetCapture(win32_window->window);
          break;
        case WM_DEADCHAR:
          event->data.key.mods |= (int)WUHOO_KMOD_DEADCHAR;
          /* fallthrough */
        case WM_CHAR: {
          ch       = (TCHAR)msg.wParam;
          WasDown  = (msg.lParam >> 31) & 1;
          szBuf[0] = ch;
          szBuf[1] = 0;
#ifdef WUHOO_UNICODE
		  WuhooUTF8*                 data_ptr = &event->data.key.character[0];
          const WuhooUTF16*     datap    = (WuhooUTF16*)&szBuf[0];
          WuhooConversionResult res      = WuhooConvertUTF16toUTF8(
            &datap, datap + sizeof(ch), &data_ptr,
            data_ptr + WUHOO_MAX_CHARACTER_SIZE,
            WuhooStrictConversion);
#else
          event->data.key.character[0] = ch;
#endif

        } break;
        case WM_KEYUP:
          event->type                  = WUHOO_EVT_KEY;
          event->data.key.code         = WUHOO_VKEY_UNKNOWN;
          event->data.key.state        = WUHOO_KSTATE_UP;
          event->data.key.character[0] = 0;

          switch (msg.wParam) {
            case VK_CONTROL:
              event->data.key.mods &= ~WUHOO_KMOD_CTRL;
              event->data.key.code = WUHOO_VKEY_CONTROL;
              break;
            case VK_SHIFT:
              event->data.key.mods &= ~WUHOO_KMOD_SHIFT;
              event->data.key.code = WUHOO_VKEY_SHIFT;
              break;
            case VK_MENU:
              event->data.key.mods &= ~WUHOO_KMOD_ALT;
              event->data.key.code = WUHOO_VKEY_ALT;
              break;
            case VK_LEFT: event->data.key.code = WUHOO_VKEY_LEFT; break;
            case VK_UP: event->data.key.code = WUHOO_VKEY_UP; break;
            case VK_DOWN: event->data.key.code = WUHOO_VKEY_DOWN; break;
            case VK_RIGHT: event->data.key.code = WUHOO_VKEY_RIGHT; break;
            case VK_ESCAPE: event->data.key.code = WUHOO_VKEY_ESCAPE; break;
            case VK_RETURN: event->data.key.code = WUHOO_VKEY_ENTER; break;
            default:
              if ((msg.wParam >= '0' && msg.wParam <= '9') ||
                  (msg.wParam >= 0x41 && msg.wParam <= 0x5A)) {
                event->data.key.code = (WuhooKeyCode)msg.wParam;
              }
              break;
          }
          break;
        case WM_KEYDOWN:
          event->type                  = WUHOO_EVT_KEY;
          event->data.key.code         = WUHOO_VKEY_UNKNOWN;
          event->data.key.state        = WUHOO_KSTATE_DOWN;
          event->data.key.character[0] = 0;

          switch (msg.wParam) {
            case VK_CONTROL:
              event->data.key.mods |= (GetKeyState(VK_LCONTROL) & 0x8000)
                                        ? WUHOO_KMOD_LCTRL
                                        : WUHOO_KMOD_RCTRL;
              event->data.key.code = WUHOO_VKEY_CONTROL;
              break;
            case VK_SHIFT:
              event->data.key.mods |= (GetKeyState(VK_LSHIFT) & 0x8000)
                                        ? WUHOO_KMOD_LSHIFT
                                        : WUHOO_KMOD_RSHIFT;
              event->data.key.code = WUHOO_VKEY_SHIFT;
              break;
            case VK_MENU:
              event->data.key.mods |= (GetKeyState(VK_LMENU) & 0x8000)
                                        ? WUHOO_KMOD_LALT
                                        : WUHOO_KMOD_RALT;
              event->data.key.code = WUHOO_VKEY_ALT;
              break;
            case VK_LEFT: event->data.key.code = WUHOO_VKEY_LEFT; break;
            case VK_UP: event->data.key.code = WUHOO_VKEY_UP; break;
            case VK_DOWN: event->data.key.code = WUHOO_VKEY_DOWN; break;
            case VK_RIGHT: event->data.key.code = WUHOO_VKEY_RIGHT; break;
            case VK_ESCAPE: event->data.key.code = WUHOO_VKEY_ESCAPE; break;
            case VK_RETURN: event->data.key.code = WUHOO_VKEY_ENTER; break;
            default:
              if ((msg.wParam >= '0' && msg.wParam <= '9') ||
                  (msg.wParam >= 0x41 && msg.wParam <= 0x5A)) {
                event->data.key.code = (WuhooKeyCode)msg.wParam;
              }
              break;
          }
          break;
        default: break;
      }

      TranslateMessage(&msg);
      if (msg.message == WM_KEYDOWN)
        continue;
      DispatchMessage(&msg);
      break;
    } else {
      break;
    }
  }

  if (WuhooNo == window->is_alive) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_CLOSED;

    return WuhooSuccess;
  }

  if (window->window_flags & WUHOO_WINDOW_FLAG_CLOSED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_CLOSED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_RESIZED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_RESIZED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_RESIZED;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_FOCUS_LOST) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_UNFOCUSED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_FOCUS_LOST;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_FOCUS_GAINED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_FOCUSED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_FOCUS_GAINED;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_FULL_SCREEN) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_FULL_SCREENED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_FULL_SCREEN;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_MOVED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_MOVED;
    event->data.window.data1 = window->x;
    event->data.window.data2 = window->y;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_MOVED;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_REGION_UPDATED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_INVALIDATED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_REGION_UPDATED;

    return WuhooSuccess;
  }

  return WuhooSuccess;
}

#ifdef WUHOO_OPENGL_ENABLE
WuhooInternal WuhooResult
_WuhooOpenGLContextInit(WuhooWindow* window)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowWin32* win32_window;
  win32_window     = (WuhooWindowWin32*)window->platform_window;
  win32_window->dc = GetDC(win32_window->window);

  int gl_attrs[64];
  int gl_index         = 0;
  gl_attrs[gl_index++] = WUHOO_WGL_PIXEL_TYPE_ARB;
  gl_attrs[gl_index++] = WUHOO_WGL_TYPE_RGBA_ARB;
  gl_attrs[gl_index++] = WUHOO_WGL_ACCELERATION_ARB;
  gl_attrs[gl_index++] = WUHOO_WGL_FULL_ACCELERATION_ARB;
  gl_attrs[gl_index++] = WUHOO_WGL_SUPPORT_OPENGL_ARB;
  gl_attrs[gl_index++] = 1;
  gl_attrs[gl_index++] = WUHOO_WGL_COLOR_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.redBits +
                         window->gl_framebuffer.greenBits +
                         window->gl_framebuffer.blueBits;
  gl_attrs[gl_index++] = WUHOO_WGL_DEPTH_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.depthBits;
  gl_attrs[gl_index++] = WUHOO_WGL_STENCIL_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.stencilBits;
  gl_attrs[gl_index++] = WUHOO_WGL_RED_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.redBits;
  gl_attrs[gl_index++] = WUHOO_WGL_GREEN_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.greenBits;
  gl_attrs[gl_index++] = WUHOO_WGL_BLUE_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.blueBits;
  gl_attrs[gl_index++] = WUHOO_WGL_ALPHA_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.alphaBits;
  gl_attrs[gl_index++] = WUHOO_WGL_ACCUM_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.accumRedBits +
                         window->gl_framebuffer.accumGreenBits +
                         window->gl_framebuffer.accumBlueBits;
  gl_attrs[gl_index++] = WUHOO_WGL_ACCUM_RED_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.accumRedBits;
  gl_attrs[gl_index++] = WUHOO_WGL_ACCUM_GREEN_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.accumGreenBits;
  gl_attrs[gl_index++] = WUHOO_WGL_ACCUM_BLUE_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.accumBlueBits;
  gl_attrs[gl_index++] = WUHOO_WGL_ACCUM_ALPHA_BITS_ARB;
  gl_attrs[gl_index++] = window->gl_framebuffer.accumAlphaBits;
  gl_attrs[gl_index++] = WUHOO_WGL_DOUBLE_BUFFER_ARB;
  gl_attrs[gl_index++] =
    (WuhooTrue == window->gl_framebuffer.doublebuffer) ? 1 : 0;
  gl_attrs[gl_index++] = WUHOO_WGL_STEREO_ARB;
  gl_attrs[gl_index++] = (WuhooTrue == window->gl_framebuffer.stereo) ? 1 : 0;
  gl_attrs[gl_index++] = 0;

  int  pixel_format;
  UINT num_formats;
  WUHOO_wglChoosePixelFormatARB(win32_window->dc, gl_attrs, 0, 1, &pixel_format,
                                &num_formats);
  if (0 == num_formats) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : failed to find suitable pixel format.";
  }

  PIXELFORMATDESCRIPTOR pfd;
  DescribePixelFormat(win32_window->dc, pixel_format, sizeof(pfd), &pfd);
  if (!SetPixelFormat(win32_window->dc, pixel_format, &pfd)) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING " : SetPixelFormat failed.";
  }

  // Specify that we want to create an OpenGL 3.3 core profile context
  int gl33_attribs[] = {
    // WUHOO_WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
    // WUHOO_WGL_CONTEXT_MINOR_VERSION_ARB, 3,
    WUHOO_WGL_CONTEXT_PROFILE_MASK_ARB,
    WUHOO_WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0,
  };

  HGLRC gl33_context =
    WUHOO_wglCreateContextAttribsARB(win32_window->dc, 0, gl33_attribs);
  if (!gl33_context) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : Failed to create a modern GL context.";
  }

  if (!wglMakeCurrent(win32_window->dc, gl33_context)) {
    wglDeleteContext(win32_window->glrc);
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : wglMakeCurrent failed with a modern GL context.";
  }

  win32_window->glrc = gl33_context;

  return result;
}
#endif /* WUHOO_OPENGL_ENABLE */

#ifdef WUHOO_OPENGL_ENABLE
WuhooInternal WuhooResult
_WuhooOpenGLExtensionsInit(WuhooWindow* window)
{
  WuhooResult result = WuhooSuccess;

  WuhooWindowWin32* win32_window;
  win32_window = (WuhooWindowWin32*)window->platform_window;

  // Before we can load extensions, we need a dummy OpenGL context, created
  // using a dummy window. We use a dummy window because you can only set the
  // pixel format for a window once. For the real window, we want to use
  // wglChoosePixelFormatARB (so we can potentially specify options that aren't
  // available in PIXELFORMATDESCRIPTOR), but we can't load and use that before
  // we have a context.
  WNDCLASS  window_class     = { 0 };
  LPCTSTR   lpszClassName    = TEXT("Wuhoo_WGL");
  HINSTANCE hInstance        = GetModuleHandle(0);
  window_class.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  window_class.cbClsExtra    = 0;
  window_class.cbWndExtra    = 0;
  window_class.lpfnWndProc   = DefWindowProc;
  window_class.hInstance     = hInstance;
  window_class.lpszClassName = lpszClassName;
  window_class.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
  window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
  window_class.hbrBackground = NULL;
  window_class.lpszMenuName  = NULL;

  if (!RegisterClass(&window_class)) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : Failed to register dummy OpenGL window class for creating a modern "
      "GL context.";
  }

  HWND dummy_window =
    CreateWindowEx(0, window_class.lpszClassName, TEXT("Dummy OpenGL Window"),
                   0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                   CW_USEDEFAULT, 0, 0, window_class.hInstance, 0);

  if (NULL == dummy_window) {
    UnregisterClass(lpszClassName, hInstance);
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : Failed to create dummy OpenGL window for creating a modern GL "
      "context.";
  }

  HDC                   dummy_dc = GetDC(dummy_window);
  PIXELFORMATDESCRIPTOR pfd      = { 0 };
  pfd.nSize                      = sizeof(pfd);
  pfd.nVersion                   = 1;
  pfd.iPixelType                 = PFD_TYPE_RGBA;
  pfd.dwFlags                    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
  pfd.dwFlags |= (WuhooTrue == window->gl_framebuffer.doublebuffer)
                   ? PFD_DOUBLEBUFFER
                   : pfd.dwFlags;
  pfd.cColorBits = window->gl_framebuffer.redBits +
                   window->gl_framebuffer.greenBits +
                   window->gl_framebuffer.blueBits;
  pfd.cRedBits   = window->gl_framebuffer.redBits;
  pfd.cGreenBits = window->gl_framebuffer.greenBits;
  pfd.cBlueBits  = window->gl_framebuffer.blueBits;
  pfd.cAlphaBits = window->gl_framebuffer.alphaBits;
  pfd.cAccumBits = window->gl_framebuffer.accumRedBits +
                   window->gl_framebuffer.accumGreenBits +
                   window->gl_framebuffer.accumBlueBits;
  pfd.cAccumRedBits   = window->gl_framebuffer.accumRedBits;
  pfd.cAccumGreenBits = window->gl_framebuffer.accumGreenBits;
  pfd.cAccumBlueBits  = window->gl_framebuffer.accumBlueBits;
  pfd.cAccumAlphaBits = window->gl_framebuffer.accumAlphaBits;
  pfd.iLayerType      = PFD_MAIN_PLANE;
  pfd.cDepthBits      = window->gl_framebuffer.depthBits;
  pfd.cStencilBits    = window->gl_framebuffer.stencilBits;

  int pixel_format = ChoosePixelFormat(dummy_dc, &pfd);
  if (0 == pixel_format) {
    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);
    UnregisterClass(lpszClassName, hInstance);
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : ChoosePixelFormat failed for dummy OpenGL window.";
  }
  if (!SetPixelFormat(dummy_dc, pixel_format, &pfd)) {
    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);
    UnregisterClass(lpszClassName, hInstance);
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : SetPixelFormat failed for dummy OpenGL window.";
  }

  HGLRC dummy_context = wglCreateContext(dummy_dc);
  if (!dummy_context) {
    wglMakeCurrent(dummy_dc, 0);
    wglDeleteContext(dummy_context);
    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);
    UnregisterClass(lpszClassName, hInstance);
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : wglCreateContext failed for dummy OpenGL window.";
  }

  if (!wglMakeCurrent(dummy_dc, dummy_context)) {
    wglMakeCurrent(dummy_dc, 0);
    wglDeleteContext(dummy_context);
    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);
    UnregisterClass(lpszClassName, hInstance);
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : wglMakeCurrent failed for dummy OpenGL window.";
  }

  WUHOO_wglCreateContextAttribsARB =
    (wglCreateContextAttribsARB_type*)wglGetProcAddress(
      "wglCreateContextAttribsARB");
  WUHOO_wglChoosePixelFormatARB =
    (wglChoosePixelFormatARB_type*)wglGetProcAddress("wglChoosePixelFormatARB");

  wglMakeCurrent(dummy_dc, 0);
  wglDeleteContext(dummy_context);
  ReleaseDC(dummy_window, dummy_dc);
  DestroyWindow(dummy_window);
  UnregisterClass(lpszClassName, hInstance);

  return result;
}
#endif /* WUHOO_OPENGL_ENABLE */

WuhooResult
_WuhooWindowShowWin32(WuhooWindow* window)
{
  WuhooWindowWin32* win32_window;

  if (window == WuhooNull) {
    return (WuhooResult) "Invalid window";
  }

  if (WuhooNo == window->is_initialized) {
    return (WuhooResult) "Invalid window initialization";
  }

  win32_window = (WuhooWindowWin32*)window->platform_window;

#ifdef WUHOO_OPENGL_ENABLE
  if (WuhooOnlySet(window->flags, WUHOO_FLAG_OPENGL)) {
    _WuhooOpenGLExtensionsInit(window);
    _WuhooOpenGLContextInit(window);
  }
#endif /* WUHOO_OPENGL_ENABLE */

  ShowWindow(win32_window->window, SW_SHOW);
  UpdateWindow(win32_window->window);

  return WuhooSuccess;
}

LRESULT CALLBACK
WuhooWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#if _WIN32
WuhooResult
_WuhooWindowCreateWin32(WuhooWindow* window, int posx, int posy,
                        WuhooSize width, WuhooSize height, const char* title,
                        WuhooFlags flags)
{
  WuhooWindowWin32* win32_window = (WuhooWindowWin32*)WuhooNull;
  WuhooResult       result       = WuhooSuccess;

  win32_window = (WuhooWindowWin32*)&window->memory[0];

  window->platform_window = win32_window;
  window->convert_rgba    = &WuhooConvertRGBAtoBGRA;

  HINSTANCE hInstance = GetModuleHandle((TCHAR*)WuhooNull);
  win32_window->app   = hInstance;

  HWND     hWnd;
  TCHAR    buffer[32]  = TEXT("Wuhoo 1");
  WNDCLASS windowClass = { 0 };
  int      class_index = 1;
  while (0 != GetClassInfo(hInstance, buffer, &windowClass) &&
         (class_index < 10)) {
    buffer[6] = class_index++ + '0';
  }
  if (class_index == 10) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : Trying to open too many windows";
  }

  windowClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  windowClass.lpfnWndProc   = WuhooWindowProc;
  windowClass.cbClsExtra    = 0;
  windowClass.cbWndExtra    = 0;
  windowClass.hInstance     = hInstance; // Don't need hInstance
  windowClass.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
  windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
  windowClass.hbrBackground = NULL;
  windowClass.lpszMenuName  = NULL;
  windowClass.lpszClassName = buffer;
  if (!RegisterClass(&windowClass)) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING " : RegisterClass failed";
  }

  DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
  DWORD dwStyle   = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
  dwStyle |= (WUHOO_FLAG_RESIZEABLE & flags)
               ? (WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME)
               : 0;

  if (WUHOO_FLAG_BORDERLESS & flags)
	dwStyle = WS_POPUP;

  RECT window_rect = { 0, 0, (LONG)width,
                       (LONG)height }; // set the size, but not the position
  if (WUHOO_FLAG_CLIENT_REGION & flags)
    AdjustWindowRect(&window_rect, dwStyle, FALSE); // adjust the size

#ifdef WUHOO_UNICODE
  WuhooUTF16  encoded_title[WUHOO_MAX_ENCODED_TITLE_LENGTH];
  WuhooUTF16* encoded_title_ptr = &encoded_title[0];
  WuhooZeroInit(encoded_title, sizeof(encoded_title));
  size_t title_length = WuhooStringLength(title, WUHOO_MAX_TITLE_LENGTH);
  WuhooConvertUTF8toUTF16((const WuhooUTF8 **)&title, (const WuhooUTF8 *)title + title_length, &encoded_title_ptr,
                          encoded_title_ptr + WUHOO_MAX_ENCODED_TITLE_LENGTH,
                          WuhooStrictConversion);
#else
  const WuhooUTF8* encoded_title = (const WuhooUTF8*)title;
#endif

  posx = (WuhooDefaultPosition == posx || WuhooDefaultPosition == posy)
           ? CW_USEDEFAULT
           : posx;
  hWnd = CreateWindowEx(dwExStyle, buffer, (WUHOO_FLAG_TITLED & flags) ? (TCHAR*)encoded_title : NULL, dwStyle, posx,
                        posy, window_rect.right - window_rect.left,
                        window_rect.bottom - window_rect.top, NULL, NULL,
                        hInstance, window);

  if (NULL == hWnd) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING " : CreateWindowEx failed";
  }

  RECT crect, wrect;
  GetWindowRect(hWnd, &wrect);
  GetClientRect(hWnd, &crect);

  win32_window->window = hWnd;
  window->width        = wrect.right - wrect.left;
  window->height       = wrect.bottom - wrect.top;
  window->cwidth       = crect.right - crect.left;
  window->cheight      = crect.bottom - crect.top;

  if (WUHOO_FLAG_FILE_DROP & flags) {
    DragAcceptFiles(hWnd, TRUE);
  }

  return WuhooSuccess;
}
#endif

LRESULT CALLBACK
WuhooWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  WuhooWindow*      window = (WuhooWindow*)GetProp(hWnd, TEXT("Wuhoo"));
  WuhooWindowWin32* win32_window =
    (NULL != window) ? (WuhooWindowWin32*)window->platform_window : NULL;
  HDC  dc;
  LONG height;
  LONG width;
  RECT wrect;

  switch (message) {
    case WM_INPUTLANGCHANGEREQUEST: break;
    case WM_INPUTLANGCHANGE: break;
    case WM_DESTROY: break;
    case WM_QUIT: break;
    case WM_PAINT:
      window->window_flags |= WUHOO_WINDOW_FLAG_REGION_UPDATED;
      break;
    case WM_CLOSE:
      window->window_flags |= WUHOO_WINDOW_FLAG_CLOSED;
      window->window_flags |= WUHOO_WINDOW_FLAG_REGION_UPDATED;
      PostQuitMessage(0);
      break;
    case WM_EXITSIZEMOVE:
      window->window_flags |= WUHOO_WINDOW_FLAG_RESIZED;
      window->window_flags |= WUHOO_WINDOW_FLAG_REGION_UPDATED;
      break;
    case WM_SETFOCUS:
      window->window_flags |= WUHOO_WINDOW_FLAG_FOCUS_GAINED;
      break;
    case WM_KILLFOCUS:
      window->window_flags |= WUHOO_WINDOW_FLAG_FOCUS_LOST;
      break;
    case WM_MOVE:
      window->window_flags |= WUHOO_WINDOW_FLAG_MOVED;
      window->x = (int)(short)LOWORD(lParam); // horizontal position
      window->y = (int)(short)HIWORD(lParam); // vertical position
      break;
    case WM_SIZE:
      width  = LOWORD(lParam);
      height = HIWORD(lParam);

      window->window_flags |= WUHOO_WINDOW_FLAG_RESIZED;
      window->window_flags |= WUHOO_WINDOW_FLAG_REGION_UPDATED;
      if (SIZE_MAXIMIZED == wParam) {
        window->window_flags |= WUHOO_WINDOW_FLAG_MAXIMIZED;
      } else if (SIZE_MINIMIZED == wParam) {
        window->window_flags |= WUHOO_WINDOW_FLAG_MINIMIZED;
      } else if (SIZE_RESTORED == wParam) {
      }

      GetWindowRect(win32_window->window, &wrect);
      window->width   = wrect.right - wrect.left;
      window->height  = wrect.bottom - wrect.top;
      window->cwidth  = width;
      window->cheight = height;

      /* Maybe not needed because of OWNDC */
      dc = GetDC(hWnd);
      if (dc != win32_window->dc) {
        win32_window->dc = (HDC)dc;
      }

      if (!(WUHOO_FLAG_CANVAS & window->flags)) {
        break;
      }

      BITMAPINFO bmi;

      bmi.bmiHeader.biSize     = sizeof(BITMAPINFO);
      bmi.bmiHeader.biWidth    = width;
      bmi.bmiHeader.biHeight   = -height; // Order pixels from top to bottom
      bmi.bmiHeader.biPlanes   = 1;
      bmi.bmiHeader.biBitCount = 32; // last byte not used, 32 bit for alignment
      bmi.bmiHeader.biCompression   = BI_RGB;
      bmi.bmiHeader.biSizeImage     = 0;
      bmi.bmiHeader.biXPelsPerMeter = 0;
      bmi.bmiHeader.biYPelsPerMeter = 0;
      bmi.bmiHeader.biClrUsed       = 0;
      bmi.bmiHeader.biClrImportant  = 0;
      bmi.bmiColors[0].rgbBlue      = 0;
      bmi.bmiColors[0].rgbGreen     = 0;
      bmi.bmiColors[0].rgbRed       = 0;
      bmi.bmiColors[0].rgbReserved  = 0;

      if (WuhooNull != win32_window->mem_dc) {
        ReleaseDC(hWnd, win32_window->mem_dc);
        win32_window->mem_dc = (HDC)WuhooNull;
      }

      if (WuhooNull != win32_window->bitmap) {
        DeleteObject(win32_window->bitmap);
        win32_window->bitmap = (HBITMAP)WuhooNull;
      }

      dc = GetDC(hWnd);
      if (dc != win32_window->dc) {
        win32_window->dc = (HDC)dc;
      }

      win32_window->mem_dc = CreateCompatibleDC(dc);
      win32_window->dib    = (WuhooRGBA*)WuhooNull;
      win32_window->bitmap =
        CreateDIBSection(win32_window->dc, &bmi, DIB_RGB_COLORS,
                         (void**)&win32_window->dib, NULL, 0);

      break;
    case WM_CREATE:
      window       = (WuhooWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
      win32_window = (WuhooWindowWin32*)window->platform_window;

      /* Possibly absolete */
      SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);

      SetProp(hWnd, TEXT("Wuhoo"), (HANDLE)window);
      break;
    default: return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}
#endif

#ifdef __linux__

/* For now, we only support X11 on linux systems */
#define WUHOO_X11_ENABLE
#ifdef WUHOO_X11_ENABLE
#define WUHOO_X11_ENABLE
#endif

#define WuhooMaybeUnused __attribute__((unused))

#endif

#ifdef WUHOO_X11_ENABLE

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

#include <locale.h>

typedef struct
{
  XSizeHints*    size_hints;
  XWMHints*      wm_hints;
  XClassHint*    class_hints;
  XFontStruct*   font_info;
  XImage*        image;
  XIC            ic;
  unsigned char* image_data;
  Visual*        visual;
  Display*       display;
#ifdef WUHOO_OPENGL_ENABLE
  GLXContext glc;
#endif
  int prev_x;
  int prev_y;
  int title_extents;
  int screen;
  int red_offset, red_length;
  int green_offset, green_length;
  int blue_offset, blue_length;
  int bytes_per_pixel;
  int depth;

  GC     gc;
  Window window;
  Window root;

  Atom wmDeleteMessage;
  Atom wmState;
  Atom wmStateMaxHorz;
  Atom wmStateMaxVert;
  Atom wmStateFull;
  Atom wmStateHidden;

  Atom XA_text_uri_list;
  Atom XA_text_uri;
  Atom XA_text_plain;
  Atom XA_text;
  Atom XA_XdndSelection;
  Atom XA_XdndAware;
  Atom XA_XdndEnter;
  Atom XA_XdndLeave;
  Atom XA_XdndTypeList;
  Atom XA_XdndPosition;
  Atom XA_XdndActionCopy;
  Atom XA_XdndStatus;
  Atom XA_XdndDrop;
  Atom XA_XdndFinished;
  Atom XA_XdndReq;
  int  XdndVersion;

} WuhooWindowX11;

void*
WuhooMalloc(size_t count)
{
  return mmap((void*)WuhooNull, // Map from the start of the 2^20th page
              count,            // for one page length
              PROT_READ | PROT_WRITE,
              MAP_ANON | MAP_PRIVATE, // to a private block of hardware memory
              0, 0);
}

WuhooResult
WuhooFree(void* mem)
{
  munmap(mem, sizeof(WuhooWindow));

  return WuhooSuccess;
}

WuhooResult
_WuhooWindowRegionGetX11(WuhooWindow* window, int* posx, int* posy,
                         WuhooSize* width, WuhooSize* height)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  WuhooResult     result     = WuhooSuccess;

  int               window_posx, window_posy;
  Window            child;
  XWindowAttributes xwa;
  XTranslateCoordinates(x11_window->display, x11_window->window,
                        x11_window->root, 0, 0, &window_posx, &window_posy,
                        &child);
  XGetWindowAttributes(x11_window->display, x11_window->window, &xwa);
  if (WuhooNull != posx)
    *posx = window_posx - xwa.x;
  if (WuhooNull != posy)
    *posy = window_posy - xwa.y;

  if (WuhooNull != width)
    *width = xwa.width;
  if (WuhooNull != height)
    *height = xwa.height + x11_window->title_extents;

  return result;
}

WuhooResult
_WuhooWindowClientRegionGetX11(WuhooWindow* window, int* posx, int* posy,
                               WuhooSize* width, WuhooSize* height)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  WuhooResult     result     = WuhooSuccess;

  int               window_posx, window_posy;
  Window            child;
  XWindowAttributes xwa;
  XTranslateCoordinates(x11_window->display, x11_window->window,
                        x11_window->root, 0, 0, &window_posx, &window_posy,
                        &child);
  XGetWindowAttributes(x11_window->display, x11_window->window, &xwa);
  *posx = window_posx - xwa.x;
  *posy = window_posy - xwa.y;

  *width  = xwa.width;
  *height = xwa.height;

  return result;
}

WuhooResult
_WuhooWindowRegionSetX11(WuhooWindow* window, int posx, int posy,
                         WuhooSize width, WuhooSize height)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  WuhooResult     result     = WuhooSuccess;

  height -= x11_window->title_extents;

  XMoveResizeWindow(x11_window->display, x11_window->window, posx, posy, width,
                    height);

  window->window_flags |= WUHOO_WINDOW_FLAG_RESIZED;

  return result;
}

WuhooResult
_WuhooWindowClientRegionSetX11(WuhooWindow* window, int posx, int posy,
                               WuhooSize width, WuhooSize height)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  WuhooResult     result     = WuhooSuccess;

  XMoveResizeWindow(x11_window->display, x11_window->window, posx, posy, width,
                    height);

  window->window_flags |= WUHOO_WINDOW_FLAG_RESIZED;

  return result;
}

WuhooInternal int wuhoo_TrappedErrorCode = 0;
WuhooInternal int (*wuhoo_OldErrorHandle)(Display*, XErrorEvent*);

WuhooInternal int
_WuhooErrorHandleX11(Display* display, XErrorEvent* error)
{
  wuhoo_TrappedErrorCode = error->error_code;
  return 0;
}

WuhooInternal void
_WuhooTrapErrorsX11(void)
{
  wuhoo_TrappedErrorCode = 0;
  wuhoo_OldErrorHandle   = XSetErrorHandler(_WuhooErrorHandleX11);
}

WuhooInternal int
_WuhooUntrapErrorsX11(void)
{
  XSetErrorHandler(wuhoo_OldErrorHandle);
  return wuhoo_TrappedErrorCode;
}

WuhooResult
_WuhooWindowBlitX11(WuhooWindow* window, WuhooRGBA* pixels, WuhooSize x,
                    WuhooSize y, WuhooSize width, WuhooSize height)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  WuhooResult     result     = WuhooSuccess;

#ifdef WUHOO_OPENGL_ENABLE
  if (WUHOO_FLAG_OPENGL & window->flags) {
    glXSwapBuffers(x11_window->display, x11_window->window);

    return WuhooSuccess;
  }
#endif

  if (WUHOO_WINDOW_FLAG_CLOSED & window->window_flags ||
      WUHOO_WINDOW_FLAG_RESIZED & window->window_flags ||
      WUHOO_WINDOW_FLAG_REGION_UPDATED & window->window_flags) {
    /* If important window states have not been handled yet
     * don not proceed with blitting because this might
     * cause inconcistent behaviors. **REVISIT**
     */
    return WuhooSuccess;
  }

  Window       root;
  unsigned int screen_depth;
  int          screen_x;
  int          screen_y;
  unsigned int screen_width;
  unsigned int screen_height;
  unsigned int screen_border_width;

  if (XGetGeometry(x11_window->display, x11_window->root, &root, &screen_x,
                   &screen_y, &screen_width, &screen_height,
                   &screen_border_width, &screen_depth) == False) {
  }
  int               ax, ay;
  Window            child;
  XWindowAttributes xwa;
  XTranslateCoordinates(x11_window->display, x11_window->window,
                        x11_window->root, 0, 0, &ax, &ay, &child);
  XGetWindowAttributes(x11_window->display, x11_window->window, &xwa);
  window->x = ax - xwa.x;
  window->y = ay - xwa.y;

  window->cwidth  = xwa.width;
  window->cheight = xwa.height;

  window->width  = window->cwidth;
  window->height = window->cheight + x11_window->title_extents;

  int valid_width  = screen_width - window->x;
  int valid_height = screen_height - x11_window->title_extents - window->y;

  valid_width  = WuhooMini(valid_width, width);
  valid_height = WuhooMini(valid_height, height);
  
  /* https://stackoverflow.com/questions/43442675/how-to-use-xshmgetimage-and-xshmputimage
   */
  XImage* image = WuhooNull;
  _WuhooTrapErrorsX11();
  image = XGetImage(x11_window->display, x11_window->window, x, y, valid_width,
                    valid_height, AllPlanes, ZPixmap);
  int trapped_error = _WuhooUntrapErrorsX11();

  if (trapped_error == BadMatch) {
    return (WuhooResult) "Invalid Region";
  }

  if (WuhooNull == image) {
    return (WuhooResult) "Failed to get a valid draw region";
  }

  window->convert_rgba(image->data, pixels, x, y, valid_width, valid_height,
                       width, height);

  XPutImage(x11_window->display, x11_window->window, x11_window->gc, image, 0,
            0, x, y, valid_width, valid_height);

  XDestroyImage(image);

  return result;
}

WuhooResult
_WuhooWindowDestroyX11(WuhooWindow* window)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  WuhooResult     result     = WuhooSuccess;

  if (None != x11_window->gc) {
    XFreeGC(x11_window->display, x11_window->gc);
    x11_window->gc = None;
  }

  if (None != x11_window->window) {
    XUnmapWindow(x11_window->display, x11_window->window);
    XDestroyWindow(x11_window->display, x11_window->window);
    x11_window->window = None;
  }
  if (None != x11_window->display) {
    XCloseDisplay(x11_window->display);
    x11_window->display = None;
  }

  return result;
}

WuhooResult
_WuhooWindowSetTitleX11(WuhooWindow* window, const char* title)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  WuhooResult     result     = WuhooSuccess;
  XChangeProperty( x11_window->display, x11_window->window,
                   XInternAtom(x11_window->display, "_NET_WM_NAME", False),
                   XInternAtom(x11_window->display, "UTF8_STRING", False),
                   8, PropModeReplace, (unsigned char *) title,
                   WuhooStringLength(title, WUHOO_MAX_TITLE_LENGTH));

  return result;
}

WuhooInternal WuhooResult
_WuhooWindowExtentsX11(WuhooWindow* window)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  WuhooResult     result     = WuhooSuccess;

  Display* d;
  Window   w;
  int      s;

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    return WuhooSuccess;
  }

  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, 1, 1, 1, BlackPixel(d, s),
                          WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapWindow(d, w);

  /* Extended Window Manager Hints */
  /* https://specifications.freedesktop.org/wm-spec/wm-spec-latest.html#idm140200472552416
   */

  Atom a, t;

  int            f;
  unsigned char* data = 0;
  long*          extents;
  XEvent         e;
  unsigned long  n, b;

  a = XInternAtom(d, "_NET_FRAME_EXTENTS", True); /* Property to check */

  /* Window manager doesn't set up the extents immediately */
  /* Wait until they are set up and there are 4 of them */
  while (XGetWindowProperty(d, w, a, 0, 4, False, AnyPropertyType, &t, &f, &n,
                            &b, &data) != Success ||
         n != 4 || b != 0) {
    XNextEvent(d, &e);
  }
  
  /* OK got extents */
  if(WuhooNull != data) {
    extents = (long*)data;
    x11_window->title_extents = extents[2];
    XFree(data);
  }
  XCloseDisplay(d);

  return result;
}

WuhooResult
_WuhooWindowCreateX11(WuhooWindow* window, int posx, int posy, WuhooSize width,
                      WuhooSize height, const char* title, WuhooFlags flags)
{
  WuhooWindowX11*      x11_window = (WuhooWindowX11*)WuhooNull;
  WuhooResult          result     = WuhooSuccess;
  Colormap             cmap;
  XSetWindowAttributes swa;
  XWindowAttributes    gwa;
  int                  depth;

  x11_window              = (WuhooWindowX11*)&window->memory[0];
  window->platform_window = x11_window;

  _WuhooWindowExtentsX11(window);

  /* fallback to LC_CTYPE in env */
  setlocale(LC_CTYPE, "");
  /* implementation-dependent behavior, on my machine it defaults to
   * XMODIFIERS in env */

  if (XSetLocaleModifiers("") == NULL) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : XSetLocaleModifiers failed";
  }

  x11_window->display = XOpenDisplay(WuhooNull);

  if (WuhooNull == x11_window->display) { 
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : XOpenDisplay failed";
  }

  x11_window->root = DefaultRootWindow(x11_window->display);
  if (0 == x11_window->root) { 
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : DefaultRootWindow failed";
  }

  /* By default, assume 24-bit RGB */
  x11_window->red_offset = 0;
  x11_window->red_length = 8;

  x11_window->green_offset = 8;
  x11_window->green_length = 8;

  x11_window->blue_offset = 16;
  x11_window->blue_length = 8;

  x11_window->bytes_per_pixel = 24 / 8;

  int fbfd = open("/dev/fb0", O_RDWR);
  if (fbfd >= 0) {
    struct fb_var_screeninfo vinfo;
    ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);
    x11_window->red_offset = vinfo.red.offset;
    x11_window->red_length = vinfo.red.length;

    x11_window->green_offset = vinfo.green.offset;
    x11_window->green_length = vinfo.green.length;

    x11_window->blue_offset = vinfo.blue.offset;
    x11_window->blue_length = vinfo.blue.length;

    x11_window->bytes_per_pixel = vinfo.bits_per_pixel / 8;
    x11_window->depth           = vinfo.bits_per_pixel;

    close(fbfd);
  }

#ifdef WUHOO_OPENGL_ENABLE
  window->gl_framebuffer.depthBits;
  window->gl_framebuffer.redBits        = x11_window->red_length;
  window->gl_framebuffer.greenBits      = x11_window->green_length;
  window->gl_framebuffer.blueBits       = x11_window->blue_length;
  window->gl_framebuffer.accumRedBits   = x11_window->red_length;
  window->gl_framebuffer.accumGreenBits = x11_window->green_length;
  window->gl_framebuffer.accumBlueBits  = x11_window->blue_length;

  int gl_index = 0;

  GLint gl_attrs[32];
  gl_attrs[gl_index++] = GLX_RGBA;
  gl_attrs[gl_index++] = GLX_DEPTH_SIZE;
  gl_attrs[gl_index++] = window->gl_framebuffer.depthBits;
  gl_attrs[gl_index++] = GLX_STENCIL_SIZE;
  gl_attrs[gl_index++] = window->gl_framebuffer.stencilBits;
  gl_attrs[gl_index++] = GLX_RED_SIZE;
  gl_attrs[gl_index++] = window->gl_framebuffer.redBits;
  gl_attrs[gl_index++] = GLX_GREEN_SIZE;
  gl_attrs[gl_index++] = window->gl_framebuffer.greenBits;
  gl_attrs[gl_index++] = GLX_BLUE_SIZE;
  gl_attrs[gl_index++] = window->gl_framebuffer.blueBits;
  gl_attrs[gl_index++] = GLX_ALPHA_SIZE;
  gl_attrs[gl_index++] = window->gl_framebuffer.alphaBits;
  gl_attrs[gl_index++] = GLX_ACCUM_RED_SIZE;
  gl_attrs[gl_index++] = window->gl_framebuffer.accumRedBits;
  gl_attrs[gl_index++] = GLX_ACCUM_GREEN_SIZE;
  gl_attrs[gl_index++] = window->gl_framebuffer.accumGreenBits;
  gl_attrs[gl_index++] = GLX_ACCUM_BLUE_SIZE;
  gl_attrs[gl_index++] = window->gl_framebuffer.accumBlueBits;
  gl_attrs[gl_index++] = GLX_ACCUM_ALPHA_SIZE;
  gl_attrs[gl_index++] = window->gl_framebuffer.accumAlphaBits;
  if (WuhooTrue == window->gl_framebuffer.doublebuffer)
    gl_attrs[gl_index++] = GLX_DOUBLEBUFFER;
  if (WuhooTrue == window->gl_framebuffer.stereo)
    gl_attrs[gl_index++] = GLX_STEREO;
  gl_attrs[gl_index++] = None;
#endif

  int bytes_per_pixel = x11_window->bytes_per_pixel;

  int screen_num     = DefaultScreen(x11_window->display);
  x11_window->screen = screen_num;

#ifdef WUHOO_OPENGL_ENABLE
  XVisualInfo* vi;

  vi    = glXChooseVisual(x11_window->display, 0, gl_attrs);
  cmap  = XCreateColormap(x11_window->display, x11_window->root, vi->visual,
                         AllocNone);
  depth = vi->depth;
  x11_window->visual = vi->visual;
#else
  x11_window->visual = DefaultVisual(x11_window->display, x11_window->screen);
  cmap               = XCreateColormap(x11_window->display, x11_window->root,
                         x11_window->visual, AllocNone);
  depth              = DefaultDepth(x11_window->display, x11_window->screen);
#endif

  if (WuhooNull == x11_window->visual) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : Failed to create appropriate visual";
  }

  if (x11_window->red_offset == 11 && x11_window->green_offset == 5 &&
      x11_window->blue_offset == 0) {
    window->convert_rgba = &WuhooConvertRGBAtoR5G6B5;
  } else if (x11_window->red_offset == 16 && x11_window->green_offset == 8 &&
      x11_window->blue_offset == 0) {
    window->convert_rgba = &WuhooConvertRGBAtoBGRA;
  } else {
    window->convert_rgba = &WuhooConvertRGBAtoRGBA;
  }

  XSetWindowAttributes setwinattr;
  setwinattr.override_redirect   = False;
  setwinattr.border_pixel   = 0;
  setwinattr.colormap   = cmap;
  setwinattr.event_mask = StructureNotifyMask | FocusChangeMask | ExposureMask |
                          KeyPressMask | KeyReleaseMask | ButtonPressMask |
                          ButtonReleaseMask | PointerMotionMask;

  /* Get geometry information about root window */
  Window       root;
  int          screen_x, screen_y;
  unsigned int screen_width, screen_height, border_width, root_depth;
  if (XGetGeometry(x11_window->display, x11_window->root, &root, &screen_x,
                   &screen_y, &screen_width, &screen_height, &border_width,
                   &root_depth) == False) {
  }

  window->x =
    (WuhooDefaultPosition != posx) ? posx : ((screen_width / 2) - (width / 2));
  window->y = (WuhooDefaultPosition != posy)
                ? posy
                : ((screen_height / 2) - (height / 2));

  window->width  = width;
  window->height = height;
  window->height +=
    (WUHOO_FLAG_CLIENT_REGION & flags) ? x11_window->title_extents : 0;

  window->cwidth = window->width;
  window->cheight =
    window->height -
    ((WUHOO_FLAG_CLIENT_REGION & flags) ? x11_window->title_extents : 0);
  x11_window->window =
    XCreateWindow(x11_window->display, x11_window->root, window->x, window->y,
                  window->cwidth, window->cheight, 0, depth, InputOutput,
                  x11_window->visual, CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &setwinattr);
  
  if (0 == x11_window->window) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : XCreateWindow failed";
  }

#ifdef WUHOO_OPENGL_ENABLE
  x11_window->glc = glXCreateContext(x11_window->display, vi, NULL, GL_TRUE);
  if (WuhooNull == x11_window->glc) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : glXCreateContext failed";
  }
  glXMakeCurrent(x11_window->display, x11_window->window, x11_window->glc);
#endif

  if (WUHOO_FLAG_TITLED & flags)
    XSetStandardProperties(x11_window->display, x11_window->window, title, title,
                           None, NULL, 0, NULL);

  XSelectInput(x11_window->display, x11_window->window,
               StructureNotifyMask | FocusChangeMask | ExposureMask |
                 KeyPressMask | KeyReleaseMask | ButtonPressMask |
                 ButtonReleaseMask | PointerMotionMask);
  XSetWindowBorder(x11_window->display, x11_window->window, 1);

  x11_window->gc = XCreateGC(x11_window->display, x11_window->window, 0, NULL);

  x11_window->wmDeleteMessage =
    XInternAtom(x11_window->display, "WM_DELETE_WINDOW", 0);
  x11_window->wmState = XInternAtom(x11_window->display, "_NET_WM_STATE", True);
  x11_window->wmStateMaxHorz =
    XInternAtom(x11_window->display, "_NET_WM_STATE_MAXIMIZED_HORZ", True);
  x11_window->wmStateMaxVert =
    XInternAtom(x11_window->display, "_NET_WM_STATE_MAXIMIZED_VERT", True);
  x11_window->wmStateHidden =
    XInternAtom(x11_window->display, "_NET_WM_STATE_HIDDEN", True);
  x11_window->wmStateFull =
    XInternAtom(x11_window->display, "_NET_WM_STATE_FULLSCREEN", True);

  XSetWMProtocols(x11_window->display, x11_window->window,
                  &x11_window->wmDeleteMessage, 1);

  if (WUHOO_FLAG_BORDERLESS & window->flags) {
    Atom wmMotifHints = XInternAtom(x11_window->display, "_MOTIF_WM_HINTS", True);
    if (None != wmMotifHints) {
      /* Hints used by Motif compliant window managers */
      struct
      {
        unsigned long flags;
        unsigned long functions;
        unsigned long decorations;
        long input_mode;
        unsigned long status;
      } MWMHints = {
        (1L << 1), 0, 0, 0, 0
      };

      XChangeProperty(x11_window->display, x11_window->window, wmMotifHints, wmMotifHints, 32, PropModeReplace, (unsigned char *) &MWMHints, sizeof(MWMHints) / sizeof(long));
    } else { 
      /* set the transient hints instead, if necessary */
      XSetTransientForHint(x11_window->display, x11_window->window, RootWindow(x11_window->display, x11_window->screen));
    }
  }
  
  if (!(WUHOO_FLAG_RESIZEABLE & window->flags)) {
    XSizeHints* size_hints = XAllocSizeHints();
    size_hints->flags = PMinSize | PMaxSize;
    size_hints->min_width = size_hints->max_width = window->cwidth;
    size_hints->min_height = size_hints->max_height = window->cheight;
    XSetNormalHints(x11_window->display, x11_window->window, size_hints);
    XFree(size_hints);
  }
 
  /* Set up useful Atoms */
  if (WUHOO_FLAG_FILE_DROP & flags) {
    x11_window->XA_text_uri_list =
      XInternAtom(x11_window->display, "text/uri-list", False);
    x11_window->XA_XdndSelection =
      XInternAtom(x11_window->display, "XdndSelection", False);
    x11_window->XA_XdndAware =
      XInternAtom(x11_window->display, "XdndAware", False);
    x11_window->XA_XdndEnter =
      XInternAtom(x11_window->display, "XdndEnter", False);
    x11_window->XA_XdndLeave =
      XInternAtom(x11_window->display, "XdndLeave", False);
    x11_window->XA_XdndTypeList =
      XInternAtom(x11_window->display, "XdndTypeList", False);
    x11_window->XA_XdndPosition =
      XInternAtom(x11_window->display, "XdndPosition", False);
    x11_window->XA_XdndActionCopy =
      XInternAtom(x11_window->display, "XdndActionCopy", False);
    x11_window->XA_XdndStatus =
      XInternAtom(x11_window->display, "XdndStatus", False);
    x11_window->XA_XdndDrop =
      XInternAtom(x11_window->display, "XdndDrop", False);
    x11_window->XA_XdndFinished =
      XInternAtom(x11_window->display, "XdndFinished", False);
    x11_window->XA_XdndReq = None;

    x11_window->XdndVersion = 4;
    XChangeProperty(x11_window->display, x11_window->window,
                    x11_window->XA_XdndAware, XA_ATOM, 32, PropModeReplace,
                    (unsigned char*)&x11_window->XdndVersion, 1);
  }

  return result;
}

WuhooResult
_WuhooWindowShowX11(WuhooWindow* window)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;

  XMapWindow(x11_window->display, x11_window->window);
  XMapRaised(x11_window->display, x11_window->window);

  XSetLocaleModifiers("");

  XIM xim = XOpenIM(x11_window->display, NULL, NULL, NULL);
  if (!xim) {
    // fallback to internal input method
    XSetLocaleModifiers("@im=none");
    xim = XOpenIM(x11_window->display, 0, 0, 0);
  }

  // X input context, you can have multiple for text boxes etc, but having a
  x11_window->ic = XCreateIC(
    xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, XNClientWindow,
    x11_window->window, XNFocusWindow, x11_window->window, NULL);

  XSetICFocus(x11_window->ic);

  XMoveWindow(x11_window->display, x11_window->window, window->x, window->y);

  return WuhooSuccess;
}

WuhooInternal WuhooResult
_WuhooWindowStateX11(WuhooWindow* window)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  WuhooResult     result     = WuhooSuccess;

  Atom           type;
  int            format;
  unsigned long  nItem, bytesAfter;
  unsigned char* properties = NULL;
  while (XGetWindowProperty(x11_window->display, x11_window->window,
                            x11_window->wmState, 0, (~0L) /* LONG_MAX */, False,
                            AnyPropertyType, &type, &format, &nItem,
                            &bytesAfter, &properties) != Success ||
         bytesAfter != 0) {
  }

  WuhooBoolean max_vertical_resize = WuhooFalse;
  WuhooBoolean max_horizontal_resize = WuhooFalse;
 
  int iItem;
  for (iItem = 0; iItem < nItem; ++iItem) {
     max_horizontal_resize = (((unsigned long *)properties)[iItem] == x11_window->wmStateMaxHorz) ? WuhooTrue : max_horizontal_resize;
     max_vertical_resize = (((unsigned long *)properties)[iItem] == x11_window->wmStateMaxVert) ? WuhooTrue : max_vertical_resize;
  }

  if ( WuhooTrue == max_horizontal_resize && WuhooTrue == max_vertical_resize ) {
    window->window_flags |= WUHOO_WINDOW_FLAG_FULL_SCREEN | WUHOO_WINDOW_FLAG_MAXIMIZED;
  }

  return result;
}

typedef struct
{
  unsigned char* data;
  int            format, count;
  Atom           type;
} WuhooPropertyX11;

/* Reads property
   Must call X11_XFree on results
 */
WuhooInternal void
_WuhooReadPropertyX11(WuhooPropertyX11* p, Display* disp, Window w, Atom prop)
{
  unsigned char* ret = NULL;
  Atom           type;
  int            fmt;
  unsigned long  count;
  unsigned long  bytes_left;
  int            bytes_fetch = 0;

  do {
    if (ret != 0)
      XFree(ret);
    XGetWindowProperty(disp, w, prop, 0, bytes_fetch, False, AnyPropertyType,
                       &type, &fmt, &count, &bytes_left, &ret);
    bytes_fetch += bytes_left;
  } while (bytes_left != 0);

  p->data   = ret;
  p->format = fmt;
  p->count  = count;
  p->type   = type;
}

WuhooInternal WuhooKeyCode
_WuhooKeyTranslateX11(KeySym ksym)
{
  switch (ksym) {
      /* Undocumented KyeCode for X11X */
    case XK_Menu: return WUHOO_VKEY_MENU; break;
    case XK_comma: return WUHOO_VKEY_COMMA; break;
    case XK_semicolon: return WUHOO_VKEY_SEMICOLON; break;
    case XK_backslash: return WUHOO_VKEY_BACK_SLASH; break;
    case XK_slash: return WUHOO_VKEY_FORWARD_SLASH; break;
    case XK_quoteright: return WUHOO_VKEY_QUOTE; break;
    case XK_bracketleft: return WUHOO_VKEY_LEFT_BRACKET; break;
    case XK_bracketright: return WUHOO_VKEY_RIGHT_BRACKET; break;
    case XK_equal: return WUHOO_VKEY_EQUALS; break;
    case XK_minus: return WUHOO_VKEY_MINUS; break;
    case XK_period: return WUHOO_VKEY_PERIOD; break;
    case XK_grave: return WUHOO_VKEY_GRAVE; break;
    case XK_KP_Decimal: return WUHOO_VKEY_KPAD_DECIMAL; break;
    case XK_KP_Multiply: return WUHOO_VKEY_KPAD_MULITPLY; break;
    case XK_KP_Add: return WUHOO_VKEY_KPAD_PLUS; break;
    case XK_Num_Lock: return WUHOO_VKEY_KPAD_NUM_LOCK; break;
    case XK_KP_Divide: return WUHOO_VKEY_KPAD_DIVIDE; break;
    case XK_KP_Enter: return WUHOO_VKEY_KPAD_ENTER; break;
    case XK_KP_Subtract: return WUHOO_VKEY_KPAD_MINUS; break;
    case XK_KP_0: return WUHOO_VKEY_KPAD_0; break;
    case XK_KP_1: return WUHOO_VKEY_KPAD_1; break;
    case XK_KP_2: return WUHOO_VKEY_KPAD_2; break;
    case XK_KP_3: return WUHOO_VKEY_KPAD_3; break;
    case XK_KP_4: return WUHOO_VKEY_KPAD_4; break;
    case XK_KP_5: return WUHOO_VKEY_KPAD_5; break;
    case XK_KP_6: return WUHOO_VKEY_KPAD_6; break;
    case XK_KP_7: return WUHOO_VKEY_KPAD_7; break;
    case XK_KP_8: return WUHOO_VKEY_KPAD_8; break;
    case XK_KP_9: return WUHOO_VKEY_KPAD_9; break;
    case XK_0: return WUHOO_VKEY_0; break;
    case XK_1: return WUHOO_VKEY_1; break;
    case XK_2: return WUHOO_VKEY_2; break;
    case XK_3: return WUHOO_VKEY_3; break;
    case XK_4: return WUHOO_VKEY_4; break;
    case XK_5: return WUHOO_VKEY_5; break;
    case XK_6: return WUHOO_VKEY_6; break;
    case XK_7: return WUHOO_VKEY_7; break;
    case XK_8: return WUHOO_VKEY_8; break;
    case XK_9: return WUHOO_VKEY_9; break;
    case XK_A: return WUHOO_VKEY_A; break;
    case XK_B: return WUHOO_VKEY_B; break;
    case XK_C: return WUHOO_VKEY_C; break;
    case XK_D: return WUHOO_VKEY_D; break;
    case XK_E: return WUHOO_VKEY_E; break;
    case XK_F: return WUHOO_VKEY_F; break;
    case XK_G: return WUHOO_VKEY_G; break;
    case XK_H: return WUHOO_VKEY_H; break;
    case XK_I: return WUHOO_VKEY_I; break;
    case XK_J: return WUHOO_VKEY_J; break;
    case XK_K: return WUHOO_VKEY_K; break;
    case XK_L: return WUHOO_VKEY_L; break;
    case XK_M: return WUHOO_VKEY_M; break;
    case XK_N: return WUHOO_VKEY_N; break;
    case XK_O: return WUHOO_VKEY_O; break;
    case XK_P: return WUHOO_VKEY_P; break;
    case XK_Q: return WUHOO_VKEY_Q; break;
    case XK_R: return WUHOO_VKEY_R; break;
    case XK_S: return WUHOO_VKEY_S; break;
    case XK_T: return WUHOO_VKEY_T; break;
    case XK_U: return WUHOO_VKEY_U; break;
    case XK_V: return WUHOO_VKEY_V; break;
    case XK_W: return WUHOO_VKEY_W; break;
    case XK_X: return WUHOO_VKEY_X; break;
    case XK_Y: return WUHOO_VKEY_Y; break;
    case XK_Z: return WUHOO_VKEY_Z; break;
    case XK_Left: return WUHOO_VKEY_LEFT; break;
    case XK_Right: return WUHOO_VKEY_RIGHT; break;
    case XK_Up: return WUHOO_VKEY_UP; break;
    case XK_Down: return WUHOO_VKEY_DOWN; break;
    case XK_Escape: return WUHOO_VKEY_ESCAPE; break;
    case XK_Return: return WUHOO_VKEY_ENTER; break;
    case XK_Tab: return WUHOO_VKEY_TAB; break;
    case XK_space: return WUHOO_VKEY_SPACE; break;
    case XK_Delete: return WUHOO_VKEY_DELETE; break;
    case XK_Shift_R: return WUHOO_VKEY_SHIFT; break;
    case XK_Shift_L: return WUHOO_VKEY_SHIFT; break;
    case XK_Alt_L: return WUHOO_VKEY_ALT; break;
    case XK_Alt_R: return WUHOO_VKEY_ALT; break;
    case XK_Caps_Lock: return WUHOO_VKEY_CAPS_LOCK; break;
    case XK_Control_R: return WUHOO_VKEY_CONTROL; break;
    case XK_Control_L: return WUHOO_VKEY_CONTROL; break;
    case XK_F1: return WUHOO_VKEY_F1; break;
    case XK_F2: return WUHOO_VKEY_F2; break;
    case XK_F3: return WUHOO_VKEY_F3; break;
    case XK_F4: return WUHOO_VKEY_F4; break;
    case XK_F5: return WUHOO_VKEY_F5; break;
    case XK_F6: return WUHOO_VKEY_F6; break;
    case XK_F7: return WUHOO_VKEY_F7; break;
    case XK_F8: return WUHOO_VKEY_F8; break;
    case XK_F9: return WUHOO_VKEY_F9; break;
    case XK_F10: return WUHOO_VKEY_F10; break;
    case XK_F11: return WUHOO_VKEY_F11; break;
    case XK_F12: return WUHOO_VKEY_F12; break;
    case XK_Insert: return WUHOO_VKEY_INSERT; break;
    case XK_Home: return WUHOO_VKEY_HOME; break;
    case XK_Page_Up: return WUHOO_VKEY_PAGE_UP; break;
    case XK_BackSpace: WUHOO_VKEY_BACKSPACE; break;
    case XK_End: return WUHOO_VKEY_END; break;
    case XK_Page_Down: return WUHOO_VKEY_PAGE_DOWN; break;

    default: return WUHOO_VKEY_UNKNOWN; break;
  }

  return WUHOO_VKEY_UNKNOWN;
}

/* Find text-uri-list in a list of targets and return it's atom
   if available, else return None */
WuhooInternal Atom
_WuhooPickTextTargetX11(Display* disp, Atom* list, int list_count)
{
  Atom  request = None;
  char* name;
  int   i;
  for (i = 0; i < list_count && request == None; i++) {
    name = XGetAtomName(disp, list[i]);

    if (WuhooTrue == WuhooStringCmp("text/plain;charset=utf-8", name, 100)) {

      request = list[i];
    }
    XFree(name);
  }

  return request;
}

WuhooInternal Atom
_WuhooPickTextTargetFromThreeX11(Display* disp, Atom a0, Atom a1, Atom a2)
{
  int  count = 0;
  Atom atom[3];
  if (a0 != None)
    atom[count++] = a0;
  if (a1 != None)
    atom[count++] = a1;
  if (a2 != None)
    atom[count++] = a2;
  return _WuhooPickTextTargetX11(disp, atom, count);
}

WuhooInternal WuhooBoolean
_WuhooIsXDigit(char c)
{
  return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
          (c >= 'A' && c <= 'F'));
}

WuhooInternal void
_WuhooURIDecode(char* dst, const char* src)
{
  char a, b;
  while (*src) {
    if ((*src == '%') && ((a = src[1]) && (b = src[2])) &&
        (_WuhooIsXDigit(a) && _WuhooIsXDigit(b))) {
      if (a >= 'a')
        a -= 'a' - 'A';
      if (a >= 'A')
        a -= ('A' - 10);
      else
        a -= '0';
      if (b >= 'a')
        b -= 'a' - 'A';
      if (b >= 'A')
        b -= ('A' - 10);
      else
        b -= '0';
      *dst++ = 16 * a + b;
      src += 3;
    } else if (*src == '+') {
      *dst++ = ' ';
      src++;
    } else {
      *dst++ = *src++;
    }
  }
  *dst++ = '\0';
}

WuhooInternal WuhooResult
_WuhooWindowDropContentsGetX11(WuhooWindow* window, WuhooEvent* event,
                               char* buffer, int buffer_size)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  WuhooZeroInit(buffer, buffer_size);

  WuhooPropertyX11 p;
  _WuhooReadPropertyX11(&p, x11_window->display, x11_window->window,
                        (Atom)event->data.drop.context);

  char* at  = (char*)p.data;
  char* end = at;
  while (*end) {
    end++;
  }
  end--;
  while (*end == 10 || *end == 13) {
    end--;
  }

  end++;

  int   count         = 0;
  char* memory_offset = buffer;
  int   index         = 0;
  for (index = 0; index < event->data.drop.count; index++) {
    at += sizeof("file://") - 1;
    while (*at != 10 && *at != 13) {
      *memory_offset++ = *at++;
    }
    *memory_offset++ = '\n';
    while (*at == 10 || *at == 13) {
      at++;
    }
  }

  *memory_offset = 0;

  _WuhooURIDecode(buffer, buffer);

  XFree(p.data);
  XDeleteProperty(x11_window->display, x11_window->window,
                  (Atom)event->data.drop.context);

  return WuhooSuccess;
}

WuhooInternal void
_WuhooWindowEventGobbleX11(WuhooWindow* window, int event_type)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;
  XEvent          dummy;
  while (True == XCheckTypedEvent(x11_window->display, event_type, &dummy)) {
  }
}

WuhooResult
_WuhooWindowEventNextX11(WuhooWindow* window, WuhooEvent* event)
{
  WuhooWindowX11* x11_window = (WuhooWindowX11*)window->platform_window;

  XEvent xevent;

  if (XPending(x11_window->display) == 0) {
    return WuhooSuccess;
  }

  XNextEvent(x11_window->display, &xevent);
  if (Expose == xevent.type)
    _WuhooWindowEventGobbleX11(window, Expose);
  if (MotionNotify == xevent.type)
    _WuhooWindowEventGobbleX11(window, MotionNotify);
  if (True == XFilterEvent(&xevent, None)) {
    XNextEvent(x11_window->display, &xevent);
  }

  switch (xevent.type) {
    case FocusIn: {
      window->window_flags |= WUHOO_WINDOW_FLAG_FOCUS_GAINED;
      break;
    }
    case FocusOut: {
      window->window_flags |= WUHOO_WINDOW_FLAG_FOCUS_GAINED;
      break;
    }
    case Expose: {
      /* https://tronche.com/gui/x/xlib/events/exposure/expose.html */
      /* Careful with how many expensive "expose" events we trigger */
      XExposeEvent* xexpose = &xevent.xexpose;
      window->window_flags |=
        (xexpose->count < 5) ? WUHOO_WINDOW_FLAG_REGION_UPDATED : 0;
      break;
    }
    case ConfigureNotify: {
      XConfigureEvent* xce = &xevent.xconfigure;

      /* This event type is generated for a variety of
         happenings, so check whether the window has been
         resized. */

      if (xce->x != x11_window->prev_x || xce->y != x11_window->prev_y) {
        x11_window->prev_x = xce->x;     
        x11_window->prev_y = xce->y;

        int               x, y;
        Window            child;
        XWindowAttributes xwa;
        XTranslateCoordinates(x11_window->display, x11_window->window,
                              x11_window->root, 0, 0, &x, &y, &child);
        XGetWindowAttributes(x11_window->display, x11_window->window, &xwa);

        window->x = x - xwa.x;
        window->y = y - xwa.y;

        _WuhooWindowStateX11(window);
        window->window_flags |= WUHOO_WINDOW_FLAG_MOVED;
      }

      if (xce->width != window->cwidth || xce->height != window->cheight) {

        int               x, y;
        Window            child;
        XWindowAttributes xwa;
        XTranslateCoordinates(x11_window->display, x11_window->window,
                              x11_window->root, 0, 0, &x, &y, &child);
        XGetWindowAttributes(x11_window->display, x11_window->window, &xwa);

        window->cwidth  = xce->width;
        window->cheight = xce->height;

        window->width  = window->cwidth;
        window->height = window->cheight + x11_window->title_extents;

        _WuhooWindowStateX11(window);
        window->window_flags |= WUHOO_WINDOW_FLAG_RESIZED;
      }
    } break;
    case SelectionNotify: {
      XSelectionEvent* sev = (XSelectionEvent*)&xevent.xselection;
      if (sev->property == None)
        break;

      WuhooPropertyX11 p;
      _WuhooReadPropertyX11(&p, x11_window->display, x11_window->window,
                            sev->property);

      char* at             = (char*)p.data;
      int   count          = 0;
      int   bytes_required = 0;
      while (*at) {
        if (*at == 10) {
          at++;
          continue;
        }
        count += (*at == 13) ? 1 : 0;
        bytes_required += (*at != 13) ? 1 : 0;
        at++;
      }

      event->data.drop.context = (WuhooHandle)sev->property;
      event->data.drop.size =
        bytes_required + 1 - (sizeof("file://") - 1) * count + 1;
      event->data.drop.count = count;
      event->type            = WUHOO_EVT_DROP;

      XFree(p.data);

    } break;
    case ClientMessage: {
      if (xevent.xclient.data.l[0] == x11_window->wmDeleteMessage) {
        window->window_flags |= WUHOO_WINDOW_FLAG_CLOSED;
        window->is_alive = WuhooFalse;

        break;
      } else if (xevent.xclient.message_type == x11_window->XA_XdndDrop) {
        if (x11_window->XA_XdndReq == None) {
          /* say again - not interested! */
          XClientMessageEvent m;
          /* reply with status */
          WuhooZeroInit(&m, sizeof(XClientMessageEvent));
          m.type         = ClientMessage;
          m.display      = xevent.xclient.display;
          m.window       = xevent.xclient.data.l[0];
          m.message_type = x11_window->XA_XdndFinished;
          m.format       = 32;
          m.data.l[0]    = x11_window->window;
          m.data.l[1]    = 0;
          m.data.l[2]    = None; /* fail! */
          XSendEvent(x11_window->display, xevent.xclient.data.l[0], False,
                     NoEventMask, (XEvent*)&m);
          XFlush(x11_window->display);
        } else {
          /* convert */
          if (x11_window->XdndVersion >= 1) {
            XConvertSelection(x11_window->display, x11_window->XA_XdndSelection,
                              x11_window->XA_XdndReq, XA_PRIMARY,
                              x11_window->window, xevent.xclient.data.l[2]);
          } else {
            XConvertSelection(x11_window->display, x11_window->XA_XdndSelection,
                              x11_window->XA_XdndReq, XA_PRIMARY,
                              x11_window->window, CurrentTime);
          }
        }
      } else if (xevent.xclient.message_type == x11_window->XA_XdndPosition) {

      } else if (xevent.xclient.message_type == x11_window->XA_XdndEnter) {
        WuhooBoolean use_list = xevent.xclient.data.l[1] & 1;
        if (use_list) {
          WuhooPropertyX11 p;
          _WuhooReadPropertyX11(&p, x11_window->display,
                                xevent.xclient.data.l[0],
                                x11_window->XA_XdndTypeList);
          /* pick one */
          x11_window->XA_XdndReq = _WuhooPickTextTargetX11(
            x11_window->display, (Atom*)p.data, p.count);
          XFree(p.data);
        } else {
          /* pick from list of three */
          x11_window->XA_XdndReq = _WuhooPickTextTargetFromThreeX11(
            x11_window->display, xevent.xclient.data.l[2],
            xevent.xclient.data.l[3], xevent.xclient.data.l[4]);
        }

        XClientMessageEvent m;
        /* reply with status */
        WuhooZeroInit(&m, sizeof(XClientMessageEvent));
        m.type         = ClientMessage;
        m.display      = xevent.xclient.display;
        m.window       = xevent.xclient.data.l[0];
        m.message_type = x11_window->XA_XdndStatus;
        m.format       = 32;
        m.data.l[0]    = x11_window->window;
        m.data.l[1]    = (x11_window->XA_XdndReq != None);
        m.data.l[2]    = 0; /* specify an empty rectangle */
        m.data.l[3]    = 0;
        m.data.l[4] =
          x11_window->XA_XdndActionCopy; /* we only accept copying anyway */

        XSendEvent(x11_window->display, xevent.xclient.data.l[0], False,
                   NoEventMask, (XEvent*)&m);
        XFlush(x11_window->display);
      }
    } break;
    case MotionNotify: {
      event->type                  = WUHOO_EVT_MOUSE_MOVE;
      event->data.mouse_move.x     = xevent.xmotion.x;
      event->data.mouse_move.y     = xevent.xmotion.y;
      event->data.mouse_move.state = WUHOO_MSTATE_UNKNOWN;

      if (xevent.xmotion.state & Button1MotionMask)
        event->data.mouse_move.state = WUHOO_MSTATE_LPRESSED;
      else if (xevent.xmotion.state & Button2MotionMask)
        event->data.mouse_move.state = WUHOO_MSTATE_MPRESSED;
      else if (xevent.xmotion.state & Button3MotionMask)
        event->data.mouse_move.state = WUHOO_MSTATE_RPRESSED;
      event->data.mouse_move.mods |=
        (xevent.xmotion.state & ShiftMask) ? WUHOO_KMOD_SHIFT : 0;
      event->data.mouse_move.mods |=
        (xevent.xmotion.state & ControlMask) ? WUHOO_KMOD_CTRL : 0;
      event->data.mouse_move.mods |=
        (xevent.xmotion.state & LockMask) ? WUHOO_KMOD_CAPS : 0;
    } break;
    case ButtonPress: {
      if (Button4 == xevent.xbutton.button ||
          Button5 == xevent.xbutton.button) {
        event->type = WUHOO_EVT_MOUSE_WHEEL;
        event->data.mouse_wheel.mods |=
          (xevent.xbutton.state & ShiftMask) ? WUHOO_KMOD_SHIFT : 0;
        event->data.mouse_wheel.mods |=
          (xevent.xbutton.state & ControlMask) ? WUHOO_KMOD_CTRL : 0;
        event->data.mouse_wheel.mods |=
          (xevent.xbutton.state & LockMask) ? WUHOO_KMOD_CAPS : 0;
        event->data.mouse_wheel.x = xevent.xbutton.x;
        event->data.mouse_wheel.y = xevent.xbutton.y;
        event->data.mouse_wheel.delta_y =
          (Button4 == xevent.xbutton.button) ? 1.0f : -1.0f;

        break;
      }

      event->type                         = WUHOO_EVT_MOUSE_PRESS;
      event->data.mouse_press.click_count = 1;
      event->data.mouse_press.mods |=
        (xevent.xbutton.state & ShiftMask) ? WUHOO_KMOD_SHIFT : 0;
      event->data.mouse_press.mods |=
        (xevent.xbutton.state & ControlMask) ? WUHOO_KMOD_CTRL : 0;
      event->data.mouse_press.mods |=
        (xevent.xbutton.state & LockMask) ? WUHOO_KMOD_CAPS : 0;
      if (Button1 == xevent.xbutton.button)
        event->data.mouse_press.state = WUHOO_MSTATE_LPRESSED;
      else if (Button2 == xevent.xbutton.button)
        event->data.mouse_press.state = WUHOO_MSTATE_MPRESSED;
      else if (Button3 == xevent.xbutton.button)
        event->data.mouse_press.state = WUHOO_MSTATE_RPRESSED;

    } break;
    case ButtonRelease: {
      if (Button4 == xevent.xbutton.button || Button5 == xevent.xbutton.button)
        break;

      event->type                         = WUHOO_EVT_MOUSE_PRESS;
      event->data.mouse_press.click_count = 1;
      if (Button1 == xevent.xbutton.button)
        event->data.mouse_press.state = WUHOO_MSTATE_LRELEASED;
      else if (Button2 == xevent.xbutton.button)
        event->data.mouse_press.state = WUHOO_MSTATE_RRELEASED;
      else if (Button3 == xevent.xbutton.button)
        event->data.mouse_press.state = WUHOO_MSTATE_MRELEASED;
      event->data.mouse_press.mods |=
        (xevent.xbutton.state & ShiftMask) ? WUHOO_KMOD_SHIFT : 0;
      event->data.mouse_press.mods |=
        (xevent.xbutton.state & ControlMask) ? WUHOO_KMOD_CTRL : 0;
      event->data.mouse_press.mods |=
        (xevent.xbutton.state & LockMask) ? WUHOO_KMOD_CAPS : 0;
    } break;
    case KeyRelease: {
      KeySym ksym;
      Status status;
      char   buff[16];

      /* Override this in order for Xutf8LookupString to work */
      xevent.xkey.type = KeyPress;
      size_t c = Xutf8LookupString(x11_window->ic, &xevent.xkey, buff, 16 - 1,
                                   &ksym, &status);

      buff[c] = 0;

      event->type = WUHOO_EVT_KEY;
      WuhooStringCopy((char*)event->data.key.character, buff, c);
      event->data.key.state = WUHOO_KSTATE_UP;
      event->data.key.code  = _WuhooKeyTranslateX11(ksym);
      event->data.key.mods |=
        (xevent.xkey.state & ShiftMask) ? WUHOO_KMOD_SHIFT : 0;
      event->data.key.mods |=
        (xevent.xkey.state & ControlMask) ? WUHOO_KMOD_CTRL : 0;
      event->data.key.mods |=
        (xevent.xkey.state & LockMask) ? WUHOO_KMOD_CAPS : 0;

      break;
    }
    case KeyPress: {
      KeySym ksym;
      Status status;
      char   buff[16];

      size_t c = Xutf8LookupString(x11_window->ic, &xevent.xkey, buff, 16 - 1,
                                   &ksym, &status);

      buff[c] = 0;

      event->type = WUHOO_EVT_KEY;
      WuhooStringCopy((char*)event->data.key.character, buff, c);
      event->data.key.state = WUHOO_KSTATE_DOWN;
      event->data.key.code  = _WuhooKeyTranslateX11(ksym);
      event->data.key.mods |=
        (xevent.xkey.state & ShiftMask) ? WUHOO_KMOD_SHIFT : 0;
      event->data.key.mods |=
        (xevent.xkey.state & ControlMask) ? WUHOO_KMOD_CTRL : 0;
      event->data.key.mods |=
        (xevent.xkey.state & LockMask) ? WUHOO_KMOD_CAPS : 0;

      break;
    }
    default:
      // XFlush(x11_window->display);
      break;
  }

  if (window->window_flags & WUHOO_WINDOW_FLAG_CLOSED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_CLOSED;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_RESIZED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_RESIZED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    event->data.window.flags = WUHOO_WINDOW_FLAG_RESIZED;
    event->data.window.flags |= (window->window_flags & WUHOO_WINDOW_FLAG_MAXIMIZED) ? WUHOO_WINDOW_FLAG_MAXIMIZED : 0;
    event->data.window.flags |= (window->window_flags & WUHOO_WINDOW_FLAG_FULL_SCREEN) ? WUHOO_WINDOW_FLAG_FULL_SCREEN : 0;
    event->data.window.flags |= (window->window_flags & WUHOO_WINDOW_FLAG_MINIMIZED) ? WUHOO_WINDOW_FLAG_MINIMIZED : 0;

    window->window_flags &= ~WUHOO_WINDOW_FLAG_RESIZED;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_MAXIMIZED;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_MINIMIZED;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_FULL_SCREEN;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_MOVED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_MOVED;
    event->data.window.data1 = window->x;
    event->data.window.data2 = window->y;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_MOVED;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_FOCUS_LOST) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_UNFOCUSED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_FOCUS_LOST;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_FOCUS_GAINED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_FOCUSED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_FOCUS_GAINED;

    return WuhooSuccess;
  } else if (window->window_flags & WUHOO_WINDOW_FLAG_REGION_UPDATED) {
    event->type              = WUHOO_EVT_WINDOW;
    event->data.window.state = WUHOO_WSTATE_INVALIDATED;
    event->data.window.data1 = window->cwidth;
    event->data.window.data2 = window->cheight;
    window->window_flags &= ~WUHOO_WINDOW_FLAG_REGION_UPDATED;

    return WuhooSuccess;
  }

  return WuhooSuccess;
}

#endif /* WUHOO_X11_ENABLE */

WuhooResult
WuhooWindowInit(WuhooWindow* window)
{
  WuhooZeroInit(window, sizeof(*window));

#ifdef WUHOO_OPENGL_ENABLE
  window->gl_framebuffer.version.major  = 4;
  window->gl_framebuffer.version.minor  = 0;
  window->gl_framebuffer.redBits        = 3;
  window->gl_framebuffer.greenBits      = 3;
  window->gl_framebuffer.blueBits       = 2;
  window->gl_framebuffer.alphaBits      = 0;
  window->gl_framebuffer.depthBits      = 16;
  window->gl_framebuffer.stencilBits    = 0;
  window->gl_framebuffer.accumRedBits   = 0;
  window->gl_framebuffer.accumGreenBits = 0;
  window->gl_framebuffer.accumBlueBits  = 0;
  window->gl_framebuffer.accumAlphaBits = 0;
  window->gl_framebuffer.auxBuffers     = 0;
  window->gl_framebuffer.stereo         = WuhooFalse;
  window->gl_framebuffer.samples        = 0;
  window->gl_framebuffer.sRGB           = WuhooFalse;
  window->gl_framebuffer.doublebuffer   = WuhooTrue;
  window->gl_framebuffer.transparent    = WuhooFalse;
#endif

  return WuhooSuccess;
}

WuhooResult
WuhooWindowDestroy(WuhooWindow* window)
{
  WuhooResult result = WuhooSuccess;

#ifdef _WIN32
  result = _WuhooWindowDestroyWin32(window);
#endif

#ifdef __APPLE__
  result = _WuhooWindowDestroyCocoa(window);
#endif

#ifdef WUHOO_X11_ENABLE
  result = _WuhooWindowDestroyX11(window);
#endif

  return result;
}
WuhooResult
WuhooWindowCreate(WuhooWindow* window, int posx, int posy, WuhooSize width,
                  WuhooSize height, const char* title, WuhooFlags flags,
                  const void* data)
{
  WuhooResult result = WuhooSuccess;

  window->width  = width;
  window->height = height;
  window->flags  = flags;
  window->x      = posx;
  window->y      = posy;

#ifdef _WIN32
  result =
    _WuhooWindowCreateWin32(window, posx, posy, width, height, title, flags);
#endif

#ifdef __APPLE__
  result =
    _WuhooWindowCreateCocoa(window, posx, posy, width, height, title, flags);
#endif

#ifdef WUHOO_X11_ENABLE
  result =
    _WuhooWindowCreateX11(window, posx, posy, width, height, title, flags);
#endif

  window->is_initialized = (WuhooSuccess == result);
  window->is_alive       = (WuhooSuccess == result);

  return result;
}
WuhooResult
WuhooWindowEventNext(WuhooWindow* window, WuhooEvent* event)
{
  WuhooZeroInit(event, sizeof(*event));

#ifdef _WIN32
  return _WuhooWindowEventNextWin32(window, event);
#endif
#ifdef __APPLE__
  return _WuhooWindowEventNextCocoa(window, event);
#endif
#ifdef WUHOO_X11_ENABLE
  return _WuhooWindowEventNextX11(window, event);
#endif
}

WuhooResult
WuhooWindowShow(WuhooWindow* window)
{
#ifdef _WIN32
  return _WuhooWindowShowWin32(window);
#endif
#ifdef __APPLE__
  return _WuhooWindowShowCocoa(window);
#endif
#ifdef WUHOO_X11_ENABLE
  return _WuhooWindowShowX11(window);
#endif
}
WuhooResult
WuhooWindowRegionSet(WuhooWindow* window, int posx, int posy, WuhooSize width,
                     WuhooSize height)
{

  if (!(WUHOO_FLAG_RESIZEABLE & window->flags)) {
    return (WuhooResult)WUHOO_PLATFORM_API_STRING
      " : WUHOO_FLAG_RESIZEABLE is not set for this window";
  }

  /* Stick to lower left origin for everyone */
#ifdef __APPLE__
  return _WuhooWindowRegionSetCocoa(window, posx, posy, width, height);
#endif

#ifdef _WIN32
  return _WuhooWindowRegionSetWin32(window, posx, posy, width, height);
#endif

#ifdef WUHOO_X11_ENABLE
  return _WuhooWindowRegionSetX11(window, posx, posy, width, height);
#endif
}
WuhooResult
WuhooWindowRegionGet(WuhooWindow* window, int* posx, int* posy,
                     WuhooSize* width, WuhooSize* height)
{
#ifdef __APPLE__
  return _WuhooWindowRegionGetCocoa(window, posx, posy, width, height);
#endif

#ifdef _WIN32
  return _WuhooWindowRegionGetWin32(window, posx, posy, width, height);
#endif

#ifdef WUHOO_X11_ENABLE
  return _WuhooWindowRegionGetX11(window, posx, posy, width, height);
#endif
}
WuhooResult
WuhooWindowClientRegionGet(WuhooWindow* window, int* posx, int* posy,
                           WuhooSize* width, WuhooSize* height)
{
#ifdef __APPLE__
  return _WuhooWindowClientRegionGetCocoa(window, posx, posy, width, height);
#endif

#ifdef _WIN32
  return _WuhooWindowClientRegionGetWin32(window, posx, posy, width, height);
#endif

#ifdef WUHOO_X11_ENABLE
  return _WuhooWindowClientRegionGetX11(window, posx, posy, width, height);
#endif

  return WuhooSuccess;
}
WuhooResult
WuhooWindowClientRegionSet(WuhooWindow* window, int posx, int posy,
                           WuhooSize width, WuhooSize height)
{
#ifdef __APPLE__
  return _WuhooWindowClientRegionSetCocoa(window, posx, posy, width, height);
#endif

#ifdef _WIN32
  return _WuhooWindowClientRegionSetWin32(window, posx, posy, width, height);
#endif

#ifdef WUHOO_X11_ENABLE
  return _WuhooWindowClientRegionSetX11(window, posx, posy, width, height);
#endif

  return WuhooSuccess;
}
WuhooResult
WuhooWindowSetTitle(WuhooWindow* window, const char* title)
{
  WuhooResult result = WuhooSuccess;

  if (WuhooNull == title)
    return (WuhooResult) "Invalid title";

  if ( !(WUHOO_FLAG_TITLED & window->flags) )
    return (WuhooResult) "WUHOO_FLAG_TITLED is not set";

#ifdef __APPLE__
  result = _WuhooWindowSetTitleCocoa(window, title);
#endif

#ifdef _WIN32
  result = _WuhooWindowSetTitleWin32(window, title);
#endif

#ifdef WUHOO_X11_ENABLE
  result = _WuhooWindowSetTitleX11(window, title);
#endif

  return result;
}

WuhooResult
WuhooWindowDropContentsGet(WuhooWindow* window, WuhooEvent* event, char* buffer,
                           WuhooSize buffer_size)
{
  WuhooResult result = WuhooSuccess;

  if (WuhooNull == buffer) {
	  return (WuhooResult)"invalid buffer passed.";
  }

  if (buffer_size < event->data.drop.size) {
	  return (WuhooResult)"invalid buffer size.";
  }

#ifdef __APPLE__
  result = _WuhooWindowDropContentsGetCocoa(window, event, buffer, buffer_size);
#endif

#ifdef _WIN32
  result = _WuhooWindowDropContentsGetWin32(window, event, buffer, buffer_size);
#endif

#ifdef WUHOO_X11_ENABLE
  result = _WuhooWindowDropContentsGetX11(window, event, buffer, buffer_size);
#endif

  return result;
}

WuhooResult
WuhooWindowBlit(WuhooWindow* window, WuhooRGBA* pixels, WuhooSize src_x,
                WuhooSize src_y, WuhooSize src_width, WuhooSize src_height,
                WuhooSize dst_x, WuhooSize dst_y, WuhooSize dst_width,
                WuhooSize dst_height)
{
  WuhooResult result = WuhooSuccess;

#ifdef __APPLE__
  result =
    _WuhooWindowBlitCocoa(window, pixels, dst_x, dst_y, dst_width, dst_height);
#endif

#ifdef _WIN32
  result =
    _WuhooWindowBlitWin32(window, pixels, dst_x, dst_y, dst_width, dst_height);
#endif

#ifdef WUHOO_X11_ENABLE
  result =
    _WuhooWindowBlitX11(window, pixels, dst_x, dst_y, dst_width, dst_height);
#endif

  return result;
}

WuhooInternal void
WuhooCopy(void* const to, void const* const from, WuhooSize count)
{
  unsigned char* const       char_view_to   = (unsigned char* const)to;
  unsigned char const* const char_view_from = (unsigned char const* const)from;
  while (--count)
    char_view_to[count] = char_view_from[count];
  char_view_to[count] = char_view_from[count];
}

/* Color conversion kernels */
WuhooMaybeUnused WuhooInternal WuhooResult
WuhooConvertRGBANoOp(void* dst, WuhooRGBA const* const src, WuhooSize x,
                     WuhooSize y, WuhooSize width, WuhooSize height,
                     WuhooSize src_width, WuhooSize src_height)
{

  return WuhooSuccess;
}

WuhooMaybeUnused WuhooInternal WuhooResult
WuhooConvertRGBAtoRGBA(void* dst, WuhooRGBA const* const src, WuhooSize x,
                       WuhooSize y, WuhooSize width, WuhooSize height,
                       WuhooSize src_width, WuhooSize src_height)
{

  WuhooCopy(dst, src, width * height * sizeof(*src));

  return WuhooSuccess;
}

WuhooMaybeUnused WuhooInternal WuhooResult
WuhooConvertRGBAtoRGB(void* dst, WuhooRGBA const* const src, WuhooSize x,
                      WuhooSize y, WuhooSize width, WuhooSize height,
                      WuhooSize src_width, WuhooSize src_height)
{
  WuhooResult result   = WuhooSuccess;
  WuhooRGBA*  rgba_dst = (WuhooRGBA*)dst;

  WuhooSize i = 0;
  for (i = 0; i < width * height; i++) {
    rgba_dst[i].r = src[i].b;
    rgba_dst[i].g = src[i].g;
    rgba_dst[i].b = src[i].r;
    rgba_dst[i].a = 0;
  }

  return result;
}

WuhooMaybeUnused WuhooInternal WuhooResult
WuhooConvertRGBAtoBGRA(void* dst, WuhooRGBA const* const src, WuhooSize x,
                       WuhooSize y, WuhooSize width, WuhooSize height,
                       WuhooSize src_width, WuhooSize src_height)
{
  WuhooResult result   = WuhooSuccess;
  WuhooRGBA*  rgba_dst = (WuhooRGBA*)dst;

  WuhooSize i = 0;
  for (i = 0; i < width * height; i++) {
    rgba_dst[i].r = src[i].b;
    rgba_dst[i].g = src[i].g;
    rgba_dst[i].b = src[i].r;
    rgba_dst[i].a = src[i].a;
  }

  return result;
}

WuhooMaybeUnused WuhooInternal WuhooResult
WuhooConvertRGBAtoR5G6B5(void* dst, WuhooRGBA const* const src, WuhooSize dst_x,
                         WuhooSize dst_y, WuhooSize dst_width,
                         WuhooSize dst_height, WuhooSize src_width,
                         WuhooSize src_height)
{
  WuhooResult result = WuhooSuccess;

  /* https://stackoverflow.com/questions/42388721/x11-graphics-rendering-improvement
   */
  /* Why do we need to go off by one */
  WuhooSize i = 0, j = 0;
  for (i = 0; i < dst_width; ++i) {
    for (j = 0; j < dst_height; ++j) {
      WuhooSize pixel_index          = i + j * src_width;
      WuhooSize pixel_index_relative = i + j * (dst_width + (dst_width & 1));

      unsigned short out =
        (unsigned char)(((float)src[pixel_index].r / 255.0f) * 31.0f);
      unsigned short outg =
        (unsigned char)(((float)src[pixel_index].g / 255.0f) * 63.0f);

      unsigned short pixel_val = (out << 11) | (outg << 5) | (out << 0);

      ((unsigned short*)dst)[pixel_index_relative] = pixel_val;
      //((unsigned char*)dst)[2 * pixel_index + 0] = (unsigned char)(pixel_val &
      // 0x00FF);
      //((unsigned char*)dst)[2 * pixel_index + 1] = (unsigned char)((pixel_val
      //>> 8) & 0x00FF);
    }
  }

  return result;
}

/* Helpers and utilities */
WuhooMaybeUnused WuhooInternal void
WuhooCharacterCopy(char* to, const char* from)
{
  while ('\0' != *from) {
    *to++ = *from++;
  }
  *to = 0;
}

WuhooMaybeUnused WuhooInternal void
WuhooZeroInit(void* to, WuhooSize count)
{
  unsigned char* char_view = (unsigned char*)to;
  while (--count)
    char_view[count] = 0;
  char_view[count] = 0;
}

WuhooMaybeUnused WuhooInternal WuhooSize
WuhooStringCopy(char* to, const char* from, WuhooSize max_count)
{
  WuhooSize count = max_count;
  while ('\0' != *from && (count > 0)) {
    *to++ = *from++;
    count--;
  }
  *to = 0;
  return (max_count - count);
}

WuhooMaybeUnused WuhooInternal WuhooBoolean
WuhooStringCmp(const char* to, const char* from, WuhooSize max_count)
{
  WuhooSize count = max_count;

  while (0 != *from && 0 != *to && (count > 0)) {
    if (*to != *from) {
      return WuhooFalse;
    }

    to++;
    from++;
    count--;
  }

  return WuhooTrue;
}

WuhooMaybeUnused WuhooInternal int
WuhooMini(int a, int b)
{
  return (a < b) ? a : b;
}
WuhooMaybeUnused WuhooInternal int
WuhooMaxi(int a, int b)
{
  return !(a < b) ? a : b;
}
WuhooMaybeUnused WuhooInternal void
WuhooMemzero(void* address, WuhooSize size)
{
  while (size--) {
    ((WuhooByte*)address)[size] = 0;
  }
}
WuhooMaybeUnused WuhooSize
WuhooStringLength(const char* str, WuhooSize max_count)
{
  WuhooSize count = max_count;
  while ('\0' != *str && (count > 0)) {
    str++;
    count--;
  }
  return (max_count - count);
}

const char*
WuhooResultString(WuhooResult result)
{
  return (const char* const)(WuhooSuccess == result ? "Success" : result);
}

#endif /* WUHOO_IMPLEMENTATION */
