#include <potator/PotatorDrawer.h>

PotatorDrawer::PotatorDrawer() 
  :bytes_allocated(0)
  ,num_vertices(0)
  ,num_columns(0)
  ,pixels_per_column(0)
  ,tex_w(0)
  ,tex_h(0)
  ,prog(0)
  ,vbo(0)
  ,vao(0)
  ,a_pos_id(0)
  ,a_tex_id(0)
  ,u_pm_id(0)
  ,u_vm_id(0)
  ,u_tex_id(0)
{
}

PotatorDrawer::~PotatorDrawer() {
}

void PotatorDrawer::setup() {
  setupShader();
  setupBuffer();
}

void PotatorDrawer::setupShader() {
  GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);
  const char* vss = POTATOR_VS.c_str();
  const char* fss = POTATOR_FS.c_str();
  glShaderSource(vert_id, 1, &vss, NULL); 
  glShaderSource(frag_id, 1, &fss, NULL);
  glCompileShader(vert_id); eglGetShaderInfoLog(vert_id);
  glCompileShader(frag_id); eglGetShaderInfoLog(frag_id);
  prog = glCreateProgram();
  glAttachShader(prog, vert_id);
  glAttachShader(prog, frag_id);
  glLinkProgram(prog);
  glUseProgram(prog);
  u_pm_id = glGetUniformLocation(prog, "u_pm");
  u_vm_id = glGetUniformLocation(prog, "u_vm");
  u_tex_id = glGetUniformLocation(prog, "u_tex");
  //printf("pm_id: %d, vm_id: %d\n", u_pm_id, u_vm_id);
}

void PotatorDrawer::setupBuffer() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glUseProgram(prog);
  a_pos_id = glGetAttribLocation(prog, "a_pos");
  a_tex_id = glGetAttribLocation(prog, "a_tex");
  glEnableVertexAttribArray(a_pos_id);
  glEnableVertexAttribArray(a_tex_id);
  glVertexAttribPointer(a_pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(PotatorVertex), (GLvoid*)0);  
  glVertexAttribPointer(a_tex_id, 2, GL_FLOAT, GL_FALSE, sizeof(PotatorVertex), (GLvoid*)12);  
}

void PotatorDrawer::draw(const float* pm, const float* vm) {
  if(num_vertices == 0) {
    return;
  }
  glUseProgram(prog);
  glBindVertexArray(vao);
  glUniformMatrix4fv(u_pm_id, 1, GL_FALSE, pm);
  glUniformMatrix4fv(u_vm_id, 1, GL_FALSE, vm);
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(u_tex_id, 0);

  for(std::vector<PotatorStrip>::iterator it = strips.begin(); it != strips.end(); ++it) {
    PotatorStrip& s = *it;
    if(s.num_vertices > 0) {
      glDrawArrays(GL_TRIANGLE_STRIP, s.start_dx, s.num_vertices);
    }
  }
}

void PotatorDrawer::update() {
  size_t bytes_needed = vertices.size() * sizeof(PotatorVertex);
  if(bytes_needed > bytes_allocated) {
    
    while(bytes_allocated < bytes_needed) {
      bytes_allocated = std::max<size_t>(bytes_allocated * 2, 1024);
    }
    // there seems to be a wierd issue with my ATI card on mac 10.6
    // the specs says that the VAO attributes do not need to be reset
    // but this doesn't work on my mac. 
    bool ati_bug = true;
    ati_bug = false;
    if(ati_bug) {
      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, bytes_allocated, NULL, GL_DYNAMIC_DRAW);
      glEnableVertexAttribArray(a_pos_id);
      glEnableVertexAttribArray(a_tex_id);
      glVertexAttribPointer(a_pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(PotatorVertex), (GLvoid*)0); 
      glVertexAttribPointer(a_tex_id, 2, GL_FLOAT, GL_FALSE, sizeof(PotatorVertex), (GLvoid*)12);   
    }
    else {
      // this is what's only needed by the specs, works correctly on e.g. ipad
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, bytes_allocated, NULL, GL_DYNAMIC_DRAW);
    }
  }   
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, bytes_needed, vertices[0].ptr());
}

// You must add the vertex of the left side, then right side, then left side  etc...
void PotatorDrawer::addVertex(const float x, const float y, const float z, int texLine) {
  if(!strips.size()) {
    strips.push_back(PotatorStrip());
  }

  int j = (texLine == 0) ? 0 : texLine % tex_h;
  int i = (texLine == 0) ? 0 : texLine / tex_h;

  int add_to_i = (vertices.size() % 2) * pixels_per_column;
  float s = float( (i * pixels_per_column) + add_to_i) / tex_w;
  float t = (float(j) / tex_h);
  //printf("row: %d, col: %d, s:%f, t: %f, tex_w: %d, tex_h: %d\n", j, i, s, t, tex_w, tex_h);

  PotatorVertex v;
  v.x = x;
  v.y = y;
  v.z = z;
  v.s = s;
  v.t = t;
  vertices.push_back(v);
  num_vertices = vertices.size();
  strips.back().num_vertices++;
}

void PotatorDrawer::addNewStrip() {
  PotatorStrip s;
  s.start_dx = num_vertices;
  strips.push_back(s);
}

void PotatorDrawer::addTextureLine(int lineNum, unsigned char* data, int nbytes) {
  int y = (lineNum % tex_h);
  int x = lineNum / tex_h;
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, pixels_per_column, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
}

void PotatorDrawer::createTexture(int w, int h, int numColumns) {
  tex_w = w;
  tex_h = h;
  createTexture(tex, w, h, GL_RGB);
  num_columns = numColumns;
  pixels_per_column = tex_w / num_columns;
}

void PotatorDrawer::createTexture(GLuint& tex, int w, int h, GLenum format) {
  printf("%d, %d\n", w, h);
  glGetError();
  glGenTextures(1, &tex); eglGetError();
  glBindTexture(GL_TEXTURE_2D, tex); eglGetError();
  glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, NULL); eglGetError();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); eglGetError();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); eglGetError();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); eglGetError();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); eglGetError();
}

void PotatorDrawer::reset() {
  vertices.clear();
  strips.clear();
  num_vertices = 0;
  printf("RESET EVERYTING IN DRAWER!\n");
}
