
precision highp float;
precision highp int;

layout(location = 0) out vec4 pixel_color;

uniform vec2 screen; /* viewport width and height */
uniform float zoom;

void main() {
    const int iter = 20;
    int i;
    vec2 factor = vec2(-2.5, -2.0);
    vec2 pixel = gl_FragCoord.xy / screen;
    float zoom = 4.0;
    float Cr, Zr;
    float Ci, Zi;

    pixel = pixel * zoom + factor;

    Cr = pixel.x;
    Ci = pixel.y;
    Zr = Cr;
    Zi = Ci;

    for(i=0; i<iter; i++) {
      float px = (Zr * Zr - Zi * Zi) + Cr;
      float py = (Zi * Zr + Zr * Zi) + Ci;

      Zr = px;
      Zi = py;

      if((px * px + py * py) > 20.0) break;
    }


    float col = float(i) + 1.0 - log(log(sqrt(Zr*Zr+Zi*Zi)))/log(2.0);
    col = col / float(iter);
    //col = float(i) / float(iter);
    float out_val = (i == iter) ? 1.0 : col;

    pixel_color = vec4(out_val);
}
