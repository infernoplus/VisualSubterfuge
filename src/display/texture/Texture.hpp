/* 
 * PngTexture loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#ifndef TEXTURE_HPP
#define	TEXTURE_HPP

#include <fstream>
#include <sstream>

#include <string.h>

#include "util/Log.h"
#include "lodepng.h"

namespace gls {
  class Texture {
  public:
    Texture(GLuint texId) {
      this->texId=texId;
    }
    Texture() { }
    void bind(int program, int id) {
      std::stringstream ss; ss << "tex"; ss << id;
      GLuint uniformTex = glGetUniformLocation(program, ss.str().c_str());
          glUniform1i(uniformTex, 0);
          glActiveTexture(GL_TEXTURE0 + id);
      glBindTexture(GL_TEXTURE_2D, texId);
    }
  private:
    GLuint texId;
  };
  
  Texture* openTexture(const std::string in) {
    // Load file and decode image.
    GLuint texId = 0;
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, in);

    // If there's an error, display it.
    if(error != 0)
    {
      cmd::log("error : " + std::string(lodepng_error_text(error)));
      exit(1);
    }
    // Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
    size_t u2 = 1; while(u2 < width) u2 *= 2;
    size_t v2 = 1; while(v2 < height) v2 *= 2;
    // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
    double u3 = (double)width / u2;
    double v3 = (double)height / v2;

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4);
    for(size_t y = 0; y < height; y++)
    for(size_t x = 0; x < width; x++)
    for(size_t c = 0; c < 4; c++)
    {
      image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
    }

    // Enable the texture for OpenGL.
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);
    Texture* tex = new Texture(texId);
    return tex;
  }
}
#endif	/* TEXTURE_HPP */

