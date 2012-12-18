#include <potator/PotatorData.h>

PotatorData::PotatorData()
  :range_x(0)
  ,range_y(0)
  ,range_z(0)
  ,pixels(NULL)
  ,tex_w(0)
  ,tex_h(0)
  ,num_columns(0)
  ,pixels_per_column(0)
{
  minv.set(FLT_MAX, FLT_MAX, FLT_MAX, 0.0f, 0.0f);
  maxv.set(FLT_MIN, FLT_MIN, FLT_MIN, 0.0f, 0.0f);
}

PotatorData::~PotatorData() {
}

void PotatorData::addVertexPair(PotatorVertexPair p) {
  vertices.push_back(p);

  if(p.is_end_marker) {
    return;
  }

  P_SET_MINS(p.a, minv);    
  P_SET_MINS(p.b, minv);    
  P_SET_MAXS(p.a, maxv);
  P_SET_MAXS(p.b, maxv);
}

void PotatorData::normalize() {
  range_x = maxv.x - minv.x;
  range_y = maxv.y - minv.y;
  range_z = maxv.z - minv.z;

  for(std::vector<PotatorVertexPair>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    PotatorVertexPair& p = *it;

    if(p.is_end_marker) {
      continue;
    }

    p.a.x /= range_x;
    p.a.y /= range_y;
    p.a.z /= range_z;
    p.b.x /= range_x;
    p.b.y /= range_y;
    p.b.z /= range_z;
    //printf("- %f, %f, %f\n", p.a.x, p.a.y, p.a.z);
  }
}

void PotatorData::scale(const float s) {
  for(std::vector<PotatorVertexPair>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
    PotatorVertexPair& p = *it;

    if(p.is_end_marker) {
      continue;
    }

    p.a.x *= s;
    p.a.y *= s;
    p.a.z *= s;
    p.b.x *= s;
    p.b.y *= s;
    p.b.z *= s;
  }
}

size_t PotatorData::size() {
  return vertices.size();
}

PotatorVertexPair& PotatorData::operator[](const unsigned int dx) {
  #ifdef DEBUG
  return vertices.at(dx);
  #else
  return vertices[dx];
  #endif
}

void PotatorData::copyTextureData(unsigned char* pix, int w, int h, int numColumns) {
  tex_w = w;
  tex_h = h;
  num_columns = numColumns;
  pixels_per_column = tex_w / num_columns;
  pixels = new unsigned char[w*h*3];
  memcpy(pixels, pix, w*h*3);
  //printf("tex_w: %d, tex_h: %d, num_columns: %d, pixels_per_column: %d\n", tex_w, tex_h, num_columns, pixels_per_column);
}

int PotatorData::getNumBytesPerTextureLine() {
  return pixels_per_column * 3;
}

// set 'dest' to the correct position in the pixel data for the given line.
bool PotatorData::getTextureLine(int line, unsigned char** dest) {
  if(!pixels) {
    return false;
  }
  int y = line % tex_h;
  int x = (line / tex_h) * pixels_per_column;
  //printf("x: %d, y: %d\n", x, y);
  int offset = (y * tex_w * 3) + (x * 3);
  *dest = &pixels[offset];
  return true;
}
