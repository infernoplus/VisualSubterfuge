/*
 * GLSL Program loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#include <display/shader/Program.h>

#include <game/GameData.h>

  gls::Program::Program(std::string path) {
    this->path = path;
    this->program = 0;
    bound = false;
  }
  gls::Program::Program() {}

  void gls::Program::bindData() {
    if(bound)
      return;
    cmd::log("Binding program '" + path + "' ...");
    std::ifstream sv(path + ".vert");
    std::stringstream bv;
    bv << sv.rdbuf();

    std::ifstream sf(path + ".frag");
    std::stringstream bf;
    bf << sf.rdbuf();
    program = compileShader(bv.str(), bf.str());
    bound = true;
  }

  gls::Program* gls::openProgram(const std::string path, GameData* gd) {

    gls::Program* program = new gls::Program(path);
    return program;
  }

  GLuint gls::Program::compileShader(std::string vert, std::string frag) {
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

  void gls::Program::printShaderLog( GLuint shader ) {
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

  void gls::Program::printProgramLog( GLuint gProgramdId ) {
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

