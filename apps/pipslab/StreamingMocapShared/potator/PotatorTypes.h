#ifndef ROXLU_POTATOR_TYPES_H
#define ROXLU_POTATOR_TYPES_H

#ifdef DEBUG 
#define V(x) { printf x; }
#else
#define V(x) {}
#endif

enum PotatorDataType {
  PDT_VERTEX_POSITION, /* used while testing, a single position  */
  PDT_VERTEX_POSITIONS,  /* struct containing two points */
  PDT_VERTEX_POSITIONS_END_MARKER, /* is send in between PDT_VERTEX_POSITIONS to mark the end of a strip */
  PDT_TEXTURE_INFO, /* width and the height */
  PDT_TEXTURE_LINE, /* one line of texture data */
  PDT_RESET, /* reset everything to default state */
  PDT_NONE
};

struct PotatorVertex {
  float x;
  float y;
  float z;
  float s;
  float t;
  const float* ptr() { return &x; };
  size_t size() { return sizeof(this); }
  void set(const float xx, const float yy, const float zz, const float ss, const float tt) {  x = xx;  y = yy; z = zz; s = ss; t = tt;  }
};

struct PotatorStreamData {
  PotatorStreamData(int type):type(type) {}
  int type;
};

struct PotatorVertexPosition : public PotatorStreamData {
 PotatorVertexPosition():x(0),y(0),z(0),PotatorStreamData(PDT_VERTEX_POSITION) {}
  float x;
  float y;
  float z;
};

struct PotatorVertexPositions : PotatorStreamData {
 PotatorVertexPositions():x1(0),y1(0),z1(0),x2(0),y2(0),z2(0),texture_line(0),PotatorStreamData(PDT_VERTEX_POSITIONS) {}
  float x1;
  float y1;
  float z1;
  float x2;
  float y2;
  float z2;
  int texture_line;
};

struct PotatorTextureInfo : PotatorStreamData {
 PotatorTextureInfo():w(0),h(0),PotatorStreamData(PDT_TEXTURE_INFO) {}
 PotatorTextureInfo(int w, int h):w(w),h(h),PotatorStreamData(PDT_TEXTURE_INFO){}
  int w;
  int h;
};

// One line of texture data; we're not responsible for the memory (See PotatorData which keeps the pixels)
// @todo When you change this structure make sure to fix the client too!
struct PotatorTextureLine : PotatorStreamData {
 PotatorTextureLine():line(0),data(NULL),nbytes(0),PotatorStreamData(PDT_TEXTURE_LINE) {}

 PotatorTextureLine(int line, unsigned char* ptr, int nbytes)
   :line(line),
    nbytes(nbytes),
    PotatorStreamData(PDT_TEXTURE_LINE) 
  {
    data = new unsigned char[nbytes];
    memcpy(data, ptr, nbytes);
  }

  ~PotatorTextureLine() {
    if(data) {
      V(("~PotatorTextureLine()\n"));
      delete[] data;
    }
  }

  size_t getNumBytes() { 
    return (sizeof(line) + sizeof(nbytes) + nbytes * sizeof(unsigned char)); 
  }

  int line;
  int nbytes;
  unsigned char* data;
};


struct PotatorVertexPair {
PotatorVertexPair():texture_dx(0),is_end_marker(false){}
  PotatorVertex a;
  PotatorVertex b;
  int texture_dx;
  bool is_end_marker; /* we use a PotatorVertexPair, where is_end_marker = true which indicates that we reachaed the end of a strip */
};

#endif
