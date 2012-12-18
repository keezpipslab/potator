#ifndef ROXLU_POTATOR_DATA_H
#define ROXLU_POTATOR_DATA_H

#include <vector>
#include <potator/PotatorTypes.h>
#include <cfloat>

#define P_SET_MIN(a,b) { if (a < b) { b = a; } } 
#define P_SET_MAX(a,b) { if (a > b) { b = a; } } 
#define P_SET_MINS(a,b) { P_SET_MIN(a.x, b.x); P_SET_MIN(a.y, b.y); P_SET_MIN(a.z, b.z); }
#define P_SET_MAXS(a,b) { P_SET_MAX(a.x, b.x); P_SET_MAX(a.y, b.y); P_SET_MAX(a.z, b.z); }

class PotatorData {
 public:
  PotatorData();
  ~PotatorData();
  void addVertexPair(PotatorVertexPair p);
  void normalize();
  void scale(float s);
  size_t size();
  void copyTextureData(unsigned char* pixels, int w, int h, int numColumns);
  bool getTextureLine(int line, unsigned char** dest);
  int getNumBytesPerTextureLine();
 public:
  PotatorVertexPair& operator[](const unsigned int);
 private:
  std::vector<PotatorVertexPair> vertices;
  PotatorVertex minv;
  PotatorVertex maxv;

  // Max range between min and max values
  float range_x;
  float range_y;
  float range_z;

  // Texture info
  unsigned char* pixels;
  int tex_w;
  int tex_h;
  int num_columns;
  int pixels_per_column;
};

#endif
