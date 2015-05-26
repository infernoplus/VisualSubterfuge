/* 
 * GlsModel loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#ifndef MODEL_HPP
#define	MODEL_HPP

#include <fstream>
#include <sstream>

#include <string.h>

#include "display/shader/Shader.hpp"

#define uint unsigned int

//Documentation may be needed.
namespace gls {
  class Model {
  public:
    uint gSize;
    gls::Shader** shaders;
    float** data; uint* dSize;
    uint** indices; uint* iSize;
    Model(float** data, uint* dSize, uint** indices, uint* iSize, gls::Shader** shaders, uint gSize) {
      this->data=data; this->dSize=dSize;
      this->indices=indices; this->iSize=iSize;
      this->shaders=shaders;
      this->gSize=gSize;
    }
    Model() { }
  };

  Model openModel(const std::string in) {
    char* header = new char[4];
    uint gSize;
    std::string* shaders; uint* sSize;
    float** data; uint* dSize;
    uint** indices; uint* iSize;

    std::ifstream fin(in);
    if(fin.is_open()) {
      union { uint val; char bytes[sizeof(uint)]; } byteToUint;
      union { float val; char bytes[sizeof(float)]; } byteToFloat;
      //Read header
      for(uint i=0;!fin.eof()&&i<3;i++)
        header[i] = fin.get();
      header[3] = '\00';
      //Read total number of geometry groups
      for(uint i=0;!fin.eof()&&i<sizeof(uint);i++)
        fin.get(byteToUint.bytes[i]);
      gSize = byteToUint.val;

      std::cout << "Header -- " << header << " | Geom Groups -- " << gSize << "\n";

      shaders = new std::string[gSize]; sSize = new uint[gSize];
      data = new float*[gSize]; dSize = new uint[gSize];
      indices = new uint*[gSize]; iSize = new uint[gSize];

      for(uint j=0;j<gSize;j++) {
        //Read size of shader name
        for(uint i=0;!fin.eof()&&i<sizeof(uint);i++)
          fin.get(byteToUint.bytes[i]);
        sSize[j] = byteToUint.val;
        //Read shader name for this geometry group
        std::stringstream ss;
        for(uint i=0;!fin.eof()&&i<sSize[j];i++) {
          char ch;
          fin.get(ch);
          ss << ch;
        }
        ss << '\00';
        shaders[j] = ss.str();
        //Read vertex data size
        for(uint i=0;!fin.eof()&&i<sizeof(uint);i++)
          fin.get(byteToUint.bytes[i]);
        dSize[j] = byteToUint.val;
        //Read vertex data
        data[j] = new float[dSize[j]];
        for(uint i=0;!fin.eof()&&i<dSize[j];i++) {
          for(uint j=0;!fin.eof()&&j<sizeof(float);j++)
            fin.get(byteToFloat.bytes[j]);
          data[j][i] = byteToFloat.val;
        }
        //Read indices data size
        for(uint i=0;!fin.eof()&&i<sizeof(uint);i++)
          fin.get(byteToUint.bytes[i]);
        iSize[j] = byteToUint.val;
        //Read indices data
        indices[j] = new uint[iSize[j]];
        for(uint i=0;!fin.eof()&&i<iSize[j];i++) {
          for(uint j=0;!fin.eof()&&j<sizeof(uint);j++)
            fin.get(byteToUint.bytes[j]);
          indices[j][i] = byteToUint.val;
        }
        std::cout << "Read Group " << j << " - data: " << dSize[j] << " - indices: " << iSize[j] << " - shader: " << shaders[j] << "\n";
      }
    }
    else {
      dSize = new uint[0];
      iSize = new uint[0];
    }
    fin.close();
    gls::Shader** shd = new gls::Shader*[gSize];
    for(int i=0;i<gSize;i++) {
      shd[i] = gls::openShader("/home/inferno/dev/VisualSubterfuge/data/basic.shader");
    }
    return Model{data, dSize, indices, iSize, shd, gSize};
  }
}

#endif	/* GLSMODEL_HPP */

