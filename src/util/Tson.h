/*
 * File: Tson property file reader
 * Author: pat
 *
 * Created on May 13, 2015, 4:22 PM
 */

#ifndef TSON_H
#define TSON_H

#include <fstream>
#include <sstream>
#include <typeinfo>
#include <stdexcept>

#include <vector>
#include <string>

#include "util/Log.h"

namespace tsn {

  //Typed Json value
  class TsonValueItf {
  public:
    std::string key;
    TsonValueItf(const std::string key);
    virtual bool getBool();
    virtual int getInt();
    virtual float getFloat();
    virtual std::string getString();
  };
  template <class T>
  class TsonValue : public TsonValueItf {
  public:
    T value;
    TsonValue(const std::string key);
    virtual bool getBool();
    virtual int getInt();
    virtual float getFloat();
    virtual std::string getString();
  };

  //Typed Json array
  class TsonArrayItf {
  public:
    std::string key;
    TsonArrayItf(const std::string key);
    virtual uint size();
    virtual bool getBool(uint i);
    virtual int getInt(uint i);
    virtual float getFloat(uint i);
    virtual std::string getString(uint i);
  };
  template <class T>
  class TsonArray : public TsonArrayItf {
  public:
    TsonArray(const std::string key);
    void add(T val);
    virtual uint size();
    virtual bool getBool(uint i);
    virtual int getInt(uint i);
    virtual float getFloat(uint i);
    virtual std::string getString(uint i);
  private:
    std::vector<T> values;
  };

  //Typed Json object
  class TsonObject {
  public:
    std::string key;
    TsonObject(const std::string key);
    ~TsonObject();
    void add(TsonObject* obj);
    void add(TsonArrayItf* ary);
    void add(TsonValueItf* val);

    TsonObject* getObject(const std::string id);
    TsonArrayItf* getArray(const std::string id);
    TsonValueItf* getValue(const std::string id);
  private:
    std::vector<TsonObject*> objects;
    std::vector<TsonArrayItf*> arrays;
    std::vector<TsonValueItf*> values;
  };

  //Recursive + forward + no read ahead/back parsing approach.
  TsonObject* openTson(const std::string file);

  //20% recursion & 65% weird states & 15% magic
  TsonObject* parse(const std::string data);
  std::string removeSpace(const std::string data);
}

#endif  /* TSON_H */

