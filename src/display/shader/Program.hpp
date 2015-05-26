/* 
 * GLSL Program loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#ifndef PROGRAM_HPP
#define	PROGRAM_HPP

#include <fstream>
#include <sstream>

#include <string.h>

#include "display/texture/lodepng.h"

#define uint unsigned int

namespace gls {
  class Program {
  public:
    GLuint program;
    Program(GLuint id) {
      this->program = id;
    }
    Program() {}
  };
  
  GLuint compileShader(std::string vert, std::string frag); void printShaderLog( GLuint shader ); void printProgramLog( GLuint gProgramdId );
  
  Program* openProgram(const std::string file) {
    std::ifstream sv(file + ".vert");
    std::stringstream bv;
    bv << sv.rdbuf();

    std::ifstream sf(file + ".frag");
    std::stringstream bf;
    bf << sf.rdbuf();

    GLuint id = compileShader(bv.str(), bf.str());
    Program* program = new Program(id);
    return program;
  }
  
  GLuint compileShader(std::string vert, std::string frag) {
      GLuint gProgramId = glCreateProgram();
      GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
      const char * vertSource = vert.c_str();
      glShaderSource( vertexShader, 1, &vertSource, NULL );
      glCompileShader( vertexShader );
      glAttachShader( gProgramId, vertexShader );
      printShaderLog(vertexShader);

      GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
      const char* fragSource = frag.c_str();
      glShaderSource( fragmentShader, 1, &fragSource, NULL );
      glCompileShader( fragmentShader );
      glAttachShader( gProgramId, fragmentShader );
      printShaderLog(fragmentShader);

      glLinkProgram( gProgramId );
      printProgramLog( gProgramId );

      return gProgramId;
  }

  void printShaderLog( GLuint shader ) {
      int infoLogLength = 0;
      int maxLength = infoLogLength;
      glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
      if(maxLength > 1) {
          char* infoLog = new char[ maxLength ];

          glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
          printf( "%s\n", infoLog );

          delete[] infoLog;
      }
  }

  void printProgramLog( GLuint gProgramdId ) {
      int infoLogLength = 0;
      int maxLength = infoLogLength;
      glGetProgramiv( gProgramdId, GL_INFO_LOG_LENGTH, &maxLength );
      if(maxLength > 1) {
          char* infoLog = new char[ maxLength ];

          glGetProgramInfoLog( gProgramdId, maxLength, &infoLogLength, infoLog );
          printf( "%s\n", infoLog );

          delete[] infoLog;
      }
  }
}
#endif	/* PROGRAM_HPP */

