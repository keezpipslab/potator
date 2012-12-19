#ifndef ROXLU_POTATOR_DRAWER_H
#define ROXLU_POTATOR_DRAWER_H

#include <string>
#include <vector>
#include <roxlu/Roxlu.h>
#include <potator/PotatorTypes.h>

const std::string POTATOR_VS = ""
  ""
  "#ifdef GL_ES\n"
  "  precision highp float;\n"
  "#endif\n"
  "" 
  "uniform mat4 u_pm;"
  "uniform mat4 u_vm;"
  "attribute vec4 a_pos;"
  "attribute vec2 a_tex;"
  "varying vec2 v_tex; "
  "void main() {"
  "   gl_Position = u_pm * u_vm * a_pos;"
  "   v_tex = a_tex; "
  "}";
  ;

const std::string POTATOR_FS = ""
  ""
  "#ifdef GL_ES\n"
  "  precision highp float;\n"
  "#endif\n"
  "" 
  "uniform sampler2D u_tex;"
  "varying vec2 v_tex;"
  "void main() { "
  "   vec4 col = texture2D(u_tex, v_tex);"
  "   gl_FragColor = vec4(1.0, 0.4,0.4,1.0); "
  "   gl_FragColor = col; "
  "}";


struct PotatorStrip {
PotatorStrip():start_dx(0),num_vertices(0){}
  size_t start_dx;
  size_t num_vertices;
};

class PotatorDrawer {
 public:
  PotatorDrawer();
  ~PotatorDrawer();
  void setup();
  void update();
  void draw(const float* pm, const float* vm);
  void addVertex(const float x, const float y, const float z, int texLine);
  void addNewStrip();
  void createTexture(int w, int h, int numColumns);
  void addTextureLine(int lineNum, unsigned char* data, int nbytes);
  void reset(); // resets everything to 'empty'
 private:
  void createTexture(GLuint& tex, int w, int h, GLenum format);
  void setupShader();
  void setupBuffer();
 private:
  int num_columns;
  int pixels_per_column;
  GLuint tex;
  int tex_w;
  int tex_h;
  GLuint prog;
  GLuint vbo;
  GLuint vao;
  size_t bytes_allocated;

  vector<PotatorVertex> vertices;
  vector<PotatorStrip> strips;
  size_t num_vertices;

  // uniform and attribute locations
  GLint a_pos_id;
  GLint a_tex_id;
  GLint u_pm_id;
  GLint u_vm_id;
  GLint u_tex_id;
};

#endif
