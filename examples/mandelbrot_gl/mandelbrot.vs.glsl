
const vec4[3] g_screen_fill_traingle = vec4[3] (
  vec4(-1.0, -1.0, 0.0, 1.0),
  vec4( 3.0, -1.0, 0.0, 1.0),
  vec4(-1.0,  3.0, 0.0, 1.0)
);

void main(void)
{
   gl_Position = g_screen_fill_traingle[gl_VertexID];
}
