#ifndef ROXLU_POTATOR_LOADER_H
#define ROXLU_POTATOR_LOADER_H

#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <potator/PotatorData.h>
#include <potator/PotatorTypes.h>
#include <cfloat>

class PotatorLoader {
 public:
  bool load(const std::string filepath, PotatorData& result);
};

#endif

