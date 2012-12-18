#include <potator/PotatorClientApplication.h>

PotatorClientApplication::PotatorClientApplication()
  :potator_client(geometry_client)
{
}

PotatorClientApplication::~PotatorClientApplication() {
}

void PotatorClientApplication::setup() {
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_CULL_FACE);
  geometry_client.setup("home.roxlu.com", "2233");
  potator_thread.create(potator_client);
  drawer.setup();
}

void PotatorClientApplication::update() {
  if(potator_client.hasData()) {
    std::vector<PotatorStreamData*> vertices;
    potator_client.copyAndFlushData(vertices);
    for(std::vector<PotatorStreamData*>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
      PotatorStreamData* pd = *it;
      if(pd->type == PDT_VERTEX_POSITION) {
        PotatorVertexPosition* pvd = static_cast<PotatorVertexPosition*>(pd);
        drawer.addVertex(pvd->x, pvd->y, pvd->z, 0);
        delete pvd;
      }
      else if(pd->type == PDT_VERTEX_POSITIONS) {
        PotatorVertexPositions* pvd = static_cast<PotatorVertexPositions*>(pd);
        drawer.addVertex(pvd->x1, pvd->y1, pvd->z1, pvd->texture_line);
        drawer.addVertex(pvd->x2, pvd->y2, pvd->z2, pvd->texture_line);
        delete pvd;
      }
      else if(pd->type == PDT_VERTEX_POSITIONS_END_MARKER) {
        drawer.addNewStrip();
        delete pd;
      }
      else if(pd->type == PDT_TEXTURE_INFO) {
        PotatorTextureInfo* pti = static_cast<PotatorTextureInfo*>(pd);
        drawer.createTexture(pti->w, pti->h, 6);
        delete pti;
      }
      else if(pd->type == PDT_TEXTURE_LINE) {
        PotatorTextureLine* ptl = static_cast<PotatorTextureLine*>(pd);
        drawer.addTextureLine(ptl->line, ptl->data, ptl->nbytes);
        delete ptl;
      }
      else if(pd->type == PDT_RESET) {
        printf("RESET!\n");
        reset();
        delete pd;
      }
      else {
        delete pd;
      }
    }
  }
  drawer.update();
}

void PotatorClientApplication::draw(const float* pm, const float* vm) {
  drawer.draw(pm, vm);
}

void PotatorClientApplication::reset() {
  printf("PotatorClientApplication::reset()\n");
  drawer.reset();
  //  potator_client.reset();
}
