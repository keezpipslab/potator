#include <potator/PotatorLoader.h>




bool PotatorLoader::load(const std::string filepath, PotatorData& result) {
  std::ifstream ifs(filepath.c_str());
  if(!ifs.is_open()) {
    printf("ERROR: cannot load potator file: %s\n", filepath.c_str());
    return false;
  }

  std::string line;
  while(std::getline(ifs, line)) {
    std::stringstream ss(line);
    PotatorVertexPair p;

    ss >> p.a.x >> p.a.y >> p.a.z >> p.b.x >> p.b.y >> p.b.z >> p.texture_dx;
    if(p.a.x == 10000.0f && p.a.y == 0.0f && p.a.z == p.a.z) {
      p.is_end_marker = true;
    }
    result.addVertexPair(p);
    /*
    SET_MINS(p.a, minv);    
    SET_MINS(p.b, minv);    
    SET_MAXS(p.a, maxv);
    SET_MAXS(p.b, maxv);
    printf("%f, %f, %f -  %f, %f, %f - %d\n", p.a.x, p.a.y, p.a.z, p.b.x, p.b.y, p.b.z, p.texture_dx);
    vertices.push_back(p);
    */
    
  }
  //  printf("min: %f, %f, %f - max: %f, %f, %f\n", minv.x, minv.y, minv.z, maxv.x, maxv.y, maxv.z);

  //  printf("Ranges: %f, %f, %f\n", range_x, range_y, range_z);
  return true;
}


