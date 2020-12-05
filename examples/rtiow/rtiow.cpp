/* compile with
  -- Win32 --
  cl /I../../ /O2 rtiow.cpp /link /out:rtiow.exe kernel32.lib user32.lib gdi32.lib shell32.lib
  clang++ -std=c++14 -I../../ -O2 rtiow.cpp -o rtiow.exe -lkernel32 -luser32 -lgdi32 -lshell32
  -- Mac OS X --
  g++ -std=c++14 -I../../ rtiow.cpp -o rtiow -framework Cocoa -framework Quartz -framework Carbon
  -- Linux --
  g++ -std=c++14 -I../../ rtiow.cpp -o rtiow -lX11 -lm -pthread
*/

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#endif
#include <stdio.h>
#define WUHOO_IMPLEMENTATION
#define WUHOO_UNICODE
#include "wuhoo.h"

#ifdef _WIN32

#define _USE_MATH_DEFINES
#define MAXFLOAT FLT_MAX

float drand48() {
    return (float)rand()/RAND_MAX;
}

#endif

#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"

#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include <random>
#include <cstring>

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001f, 100000.0f, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
             return attenuation*color(scattered, world, depth+1);
        }
        else {
            return vec3(0,0,0);
        }
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5f*(unit_direction.y() + 1.0f);
        return (1.0f-t)*vec3(1.0f, 1.0f, 1.0f) + t*vec3(0.5f, 0.7f, 1.0f);
    }
}

hitable *
random_scene() {
  int n = 500;
  hitable **list = new hitable*[n+1];
  list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
  int i = 1;
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      float choose_mat = drand48();
      vec3 center(a+0.9f*drand48(),0.2f,b+0.9f*drand48());

      if ((center-vec3(4,0.2f,0)).length() > 0.9f) {
        if (choose_mat < 0.8f) {  // diffuse
          list[i++] = new sphere(center, 0.2f, new lambertian(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
        } else if (choose_mat < 0.95f) { // metal
          list[i++] = new sphere(center, 0.2f,
          new metal(vec3(0.5f*(1.0f + drand48()), 0.5f*(1.0f + drand48()), 0.5f*(1.0f + drand48())),  0.5f*drand48()));
        } else {  // glass
          list[i++] = new sphere(center, 0.2f, new dielectric(1.5f));
        }
      }
    }
  }

  list[i++] = new sphere(vec3(0, 1, 0), 1.0f, new dielectric(1.5f));
  list[i++] = new sphere(vec3(-4, 1, 0), 1.0f, new lambertian(vec3(0.4f, 0.2f, 0.1f)));
  list[i++] = new sphere(vec3(4, 1, 0), 1.0f, new metal(vec3(0.7f, 0.6f, 0.5f), 0.0f));

  return new hitable_list(list,i);
}

struct tile {
  int x, y, width, height;
};

struct rtiow {
  camera* cam { WuhooNull };
  hitable* world { WuhooNull };
  std::unique_ptr<WuhooRGBA[]> front_buffer { WuhooNull };
  std::unique_ptr<WuhooRGBA[]> back_buffer { WuhooNull };

  /* regions TO render */
  std::vector<tile> render_tile_queue;
  std::atomic<int> next_tile { 0 };

  /* regions ALREADY rendered */
  std::vector<tile> finished_tile_queue;
  std::atomic<int> next_finished_tile { 0 };

  /* Synchronization primitives */
  std::atomic<int> finished_workers { 0 };
  std::atomic<bool> g_rendering_done { false };
  std::atomic<bool> g_rendering_stop { false };
  std::atomic<bool> g_rendering_exit { false };

  int nx { 512 };
  int ny { 512 };
  int ns { 256 };
  int worker_count {8};

  int tile_count {1000};
  int tile_count_x;
  int tile_count_y;
  int tile_size_x;
  int tile_size_y;
};

void
init_scene(rtiow* scene)
{
  scene->back_buffer = std::make_unique<WuhooRGBA[]>(scene->nx * scene->ny);
  scene->front_buffer = std::make_unique<WuhooRGBA[]>(scene->nx * scene->ny);

  std::memset(scene->back_buffer.get(), 0, scene->nx * scene->ny * sizeof(scene->back_buffer[0]));
  std::memset(scene->front_buffer.get(), 0, scene->nx * scene->ny * sizeof(scene->front_buffer[0]));
}

bool
render_scene_region(rtiow* scene, int x, int y, int width, int height)
{
  for (int j = y; j < height; j++) {
    for (int i = x; i < width; i++) {
      vec3 col(0, 0, 0);
      for (int s=0; s < scene->ns; s++) {
        if (scene->g_rendering_stop) {
          return false;
        }

        float u = float(i + drand48()) / float(scene->nx);
        float v = float(j + drand48()) / float(scene->ny);
        ray r = scene->cam->get_ray(u, v);
        vec3 p = r.point_at_parameter(2.0);
        col += color(r, scene->world,0);
      }
      col /= float(scene->ns);
      col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);

      size_t pixel_index = i + (scene->ny - 1 - j) * scene->nx;

      scene->back_buffer[pixel_index].r = (unsigned char)(ib);
      scene->back_buffer[pixel_index].g = (unsigned char)(ir);
      scene->back_buffer[pixel_index].b = (unsigned char)(ig);
      scene->back_buffer[pixel_index].a = 255;
    }
  }

  return true;
}

void
render_work(rtiow* scene) {
  int tile_index = scene->next_tile.fetch_add(1);

  while (tile_index < scene->tile_count) {
    tile t = scene->render_tile_queue[tile_index];

    if (!render_scene_region(scene, t.x, t.y, t.width, t.height)) {
      break;
    }

    int finished_tile_index = scene->next_finished_tile.fetch_add(1);
    if (finished_tile_index < scene->tile_count)
      scene->finished_tile_queue[finished_tile_index] = t;

    tile_index = scene->next_tile.fetch_add(1);
  }

  int finished_worker_count = scene->finished_workers.fetch_add(1);
  if (finished_worker_count == scene->worker_count - 1) {
    if(!scene->g_rendering_stop) {
                scene->g_rendering_done = true;
    }
        scene->g_rendering_exit = true;
  }
}

int main(int argc, const char * argv[]) {
  WuhooWindow window;
  WuhooEvent event;
  WuhooResult result;
  rtiow scene;

  const char * title = "Ray Tracing In A Weekend (" WUHOO_PLATFORM_API_STRING ")";
  int running = 1;

  result = WuhooWindowInit(&window);
  result = WuhooWindowCreate(&window, 0, 0, scene.nx, scene.ny, title,
                    WUHOO_FLAG_CANVAS        |
                    WUHOO_FLAG_TITLED        |
                    WUHOO_FLAG_MOUSE_CAPTURE |
                    WUHOO_FLAG_CLIENT_REGION |
                    WUHOO_FLAG_CLOSEABLE, WuhooNull);
  result = WuhooWindowShow(&window);

  init_scene(&scene);

  srand((unsigned int)time(NULL));

  scene.world = random_scene();
  scene.tile_count_y = (int)sqrtf((float)scene.tile_count);
  scene.tile_count_x = scene.tile_count_y;
  scene.tile_size_x = ( ( scene.nx - 1 ) / scene.tile_count_x ) + 1;
  scene.tile_size_y = ( ( scene.ny - 1 ) / scene.tile_count_y ) + 1;
  scene.tile_count = scene.tile_count_x * scene.tile_count_y;

  for (int i = 0; i < scene.tile_count_x; i++) {
    for (int j = 0; j < scene.tile_count_y; j++) {
      scene.finished_tile_queue.push_back({ 0, 0, 0, 0 });
      scene.render_tile_queue.push_back(
                                        {
                                          std::min((i + 0) * scene.tile_size_x, scene.nx),
                                          std::min((j + 0) * scene.tile_size_y, scene.ny),
                                          std::min((i + 1) * scene.tile_size_x, scene.nx),
                                          std::min((j + 1) * scene.tile_size_y, scene.ny)
                                        });
    }
  }

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle ( scene.render_tile_queue.begin(), scene.render_tile_queue.end(), g );

  vec3 lookfrom(13,2,3);
  vec3 lookat(0,0,0);
  float dist_to_focus = 10.0f;
  float aperture = 0.1f;

  scene.cam = new camera(lookfrom, lookat, vec3(0,1,0), 20, float(scene.nx)/float(scene.ny), aperture, dist_to_focus);

  unsigned worker_count = std::thread::hardware_concurrency();
  //worker_count = 1;
  scene.worker_count = worker_count;
  std::vector<std::thread> worker_pool;

  for (size_t worker_index = 0; worker_index < scene.worker_count; worker_index++) {
    std::thread worker(render_work, &scene);
    worker.detach();
  }

  printf("[RTIOW] : Rendering with %d worker threads\n", scene.worker_count);

  while(running) {
    WuhooWindowEventNext(&window, &event);

    switch (event.type) {
    case WUHOO_EVT_WINDOW:
      switch (event.data.window.state) {
      case WUHOO_WSTATE_CLOSED:
        scene.g_rendering_stop = true;
        running = 0;
        break;
      default:
        break;
      }
    case WUHOO_EVT_KEY:
      switch(event.data.key.code) {
      case WUHOO_VKEY_ESCAPE:
        if (event.data.key.state == WUHOO_KSTATE_UP) {
                        scene.g_rendering_stop = true;
          running = 0;
        }
        break;

      default:
        break;
      }
    default:
      break;
    }

    int max_tile_count = std::min(scene.next_finished_tile.load(), scene.tile_count);
    char progress_report[256]{ 0 };
    char* progress_report_at = progress_report;
    int progrees_report_next = 0;
    float progress = ((float)max_tile_count / scene.tile_count) * 100.0f;
    progrees_report_next = sprintf(progress_report_at + progrees_report_next, "[RTIOW] : |");
    progress_report_at += progrees_report_next;
    for (int i = 0; i < 50; i++) {
      if (i < (int)(progress * 0.5)) {
        progrees_report_next = sprintf(progress_report_at, "%c", '=');
      } else {
        progrees_report_next = sprintf(progress_report_at, " ");
      }
      progress_report_at += progrees_report_next;
    }

    progrees_report_next = sprintf(progress_report_at, "| %04f%%\r", progress);
    progress_report_at += progrees_report_next;
    printf("%s", progress_report);

    if (scene.g_rendering_done) {
      WuhooWindowBlit(&window, scene.back_buffer.get(), 0, 0, scene.nx, scene.ny, 0, 0, scene.nx, scene.ny);
    } else {
      for (int tile_index = 0; tile_index < max_tile_count; tile_index++) {
        tile t = scene.finished_tile_queue[tile_index];
        for (int j = t.y; j < t.height; j++) {
          for (int i = t.x; i < t.width; i++) {
            size_t pixel_index = i + (scene.ny - 1 - j) * scene.nx;
            scene.front_buffer[pixel_index] = scene.back_buffer[pixel_index];
          }
        }
      }

      WuhooWindowBlit(&window, scene.front_buffer.get(), 0, 0, scene.nx, scene.ny, 0, 0, scene.nx, scene.ny);
    }

  }

  printf("\n[RTIOW] : Done!\n");

  /* Wait for all workers to finsih */
  while(false == scene.g_rendering_exit) { }

  WuhooWindowDestroy(&window);

  return 0;
}
