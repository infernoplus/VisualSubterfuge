/* 
 * File: Tson property file reader
 * Author: pat
 *
 * Created on May 13, 2015, 4:22 PM
 */

#ifndef TSON_HPP
#define	TSON_HPP

#include <fstream>
#include <sstream>

#include <vector>
#include <string.h>

#define uint unsigned int

namespace tsn {
   
  //Typed Json value
  class TsonValueItf {
  public:
    std::string key;
    TsonValueItf(const std::string key) {
      this->key=key;
    }
    virtual bool getBool() { return false; }
    virtual int getInt() { return 0; }
    virtual float getFloat() { return 0.0f; }
    virtual std::string getString() { return ""; }
  };
  template <class T>
  class TsonValue : public TsonValueItf {
  public:
    T value;
    TsonValue(const std::string key) : TsonValueItf(key) { }; //TODO: It might be a good idea to implement some standard implicit casts and throw exceptions.
    virtual bool getBool() {
      if(typeid(T) == typeid(bool)) {
        try {
          bool b;
          b = *reinterpret_cast<bool*>(&value);
          return b;
        }
        catch(std::bad_cast exp) {
          std::cout << "TSON Type Cast Error: bool\n";
        }
      }
      return false;
    }
    virtual int getInt() {
      if(typeid(T) == typeid(int)) {
        try {
          int i;
          i = *reinterpret_cast<int*>(&value);
          return i;
        }
        catch(std::bad_cast exp) {
          std::cout << "TSON Type Cast Error: int\n";
        }
      }
      return 0;
    }
    virtual float getFloat() { 
      if(typeid(T) == typeid(float)) {
        try {
          float f;
          f = *reinterpret_cast<float*>(&value);
          return f;
        }
        catch(std::bad_cast exp) {
          std::cout << "TSON Type Cast Error: float\n";
        }
      }
      return 0.0f;
    }
    virtual std::string getString() { 
      if(typeid(T) == typeid(std::string)) {
        try {
          std::string str;
          str = *reinterpret_cast<std::string*>(&value);
          return str;
        }
        catch(std::bad_cast exp) {
          std::cout << "TSON Type Cast Error: std::string\n";
        }
      }
      return "null";
    }
  };
  
  //Typed Json array
  class TsonArrayItf {
  public:
    std::string key;
    TsonArrayItf(const std::string key) {
      this->key=key;
    }
    virtual uint size() { return 0; }
    virtual bool getBool(uint i) { return false; }
    virtual int getInt(uint i) { return 0; }
    virtual float getFloat(uint i) { return 0.0f; }
    virtual std::string getString(uint i) { return ""; }
  };
  template <class T>
  class TsonArray : public TsonArrayItf {
  public:
    TsonArray(const std::string key) : TsonArrayItf(key) { }; 
    void add(T val) {
      values.push_back(val);
    }
    virtual uint size() {
      return values.size();
    }
    virtual bool getBool(uint i) {
      if(typeid(T) == typeid(bool)) {
        try {
          bool b;
          T c = values[i];
          b = *reinterpret_cast<bool*>(&c);
//          b = *reinterpret_cast<bool*>(&values[i]);
          return b;
        }
        catch(std::bad_cast exp) {
          std::cout << "TSON Type Cast Error: bool\n";
        }
      }
      return false;
    }
    virtual int getInt(uint i) {
      if(typeid(T) == typeid(int)) {
        try {
          int j;
          T c = values[i];
          j = *reinterpret_cast<int*>(&c);
          return j;
        }
        catch(std::bad_cast exp) {
          std::cout << "TSON Type Cast Error: int\n";
        }
      }
      return 0;
    }
    virtual float getFloat(uint i) { 
      if(typeid(T) == typeid(float)) {
        try {
          float f;
          T c = values[i];
          f = *reinterpret_cast<float*>(&c);
          return f;
        }
        catch(std::bad_cast exp) {
          std::cout << "TSON Type Cast Error: float\n";
        }
      }
      return 0.0f;
    }
    virtual std::string getString(uint i) { 
      if(typeid(T) == typeid(std::string)) {
        try {
          std::string str;
          T c = values[i];
          str = *reinterpret_cast<std::string*>(&c);
          return str;
        }
        catch(std::bad_cast exp) {
          std::cout << "TSON Type Cast Error: std::string\n";
        }
      }
      return "null";
    }
  private:
    std::vector<T> values;
  };
  
  //Typed Json object
  class TsonObject {
  public:
    std::string key;
    TsonObject(const std::string key) {
      this->key=key;
    }
    ~TsonObject() {
      for(int i=0;i<objects.size();i++)
        delete objects[i];
      for(int i=0;i<arrays.size();i++)
        delete arrays[i];
      for(int i=0;i<values.size();i++)
        delete values[i];
      objects.clear();
      arrays.clear();
      values.clear();
    }
    void add(TsonObject* obj) { objects.push_back(obj); }
    void add(TsonArrayItf* ary) { arrays.push_back(ary); }
    void add(TsonValueItf* val) { values.push_back(val); }
    
    TsonObject* getObject(const std::string id) {
      for(int i=0;i<objects.size();i++)
        if(objects[i]->key == id)
          return objects[i];
      return new TsonObject("null"); //TODO Memory leak aaaaaaaaa
    }
    TsonArrayItf* getArray(const std::string id) {
      for(int i=0;i<arrays.size();i++)
        if(arrays[i]->key == id)
          return arrays[i];
      return new TsonArrayItf("null");
    }
    TsonValueItf* getValue(const std::string id) {
      for(int i=0;i<values.size();i++)
        if(values[i]->key == id)
          return values[i];
      return new TsonValueItf("null");
    }
  private:
    std::vector<TsonObject*> objects;
    std::vector<TsonArrayItf*> arrays;
    std::vector<TsonValueItf*> values;
  };
  
  std::string removeSpace(const std::string); TsonObject* openTson(const std::string); TsonObject* parse(const std::string);
  
  //Recursive + forward + no read ahead/back parsing approach.
  TsonObject* openTson(const std::string file) {
    
    std::ifstream sf(file);
    std::stringstream bf;
    bf << sf.rdbuf();
  
    TsonObject* obj = parse(removeSpace(bf.str()));
        
//    //Test!
//    std::cout << obj->getValue("textures")->getString() << "\n";
//    std::cout << obj->getValue("name")->getString() << "\n";
//    std::cout << obj->getObject("uniforms")->getValue("scale")->getFloat() << "\n";
//    std::cout << obj->getArray("textures")->getString(1) << "\n";
    
    return obj;
  }
  
  //20% recursion & 65% weird states & 15% magic
  TsonObject* parse(const std::string data) {
    //std::cout << "\nOriginal Data:\n " << data << "\n";
    
    std::stringstream key;
    std::stringstream val;
    bool onKey = true; bool onBreak = false;
    int rightBracket = 1;
    for(int i=0;i<data.length();i++) {
      char c = data.at(i);
      if(onKey) {
        if(c != ':') {
            key << c;
        }
        else {
          onKey = false;
        }
      }
      else {
        if(!onBreak) {
          onBreak = true;
        }
        else if(c == '}' && rightBracket < 1){
            break; //End of object, a break is fine too...
        }
        else {
          switch(c) {
            case '{' : rightBracket++; break;
            case '}' : rightBracket--; break;
          }
          val << c;
        }
      }
    }
    //std::cout << "\nKey: \n" << key.str() << "\nValue: \n" << val.str() << "\n";
    TsonObject* obj = new TsonObject(key.str());
    
    const std::string inner = val.str();
    std::vector<std::string> ary;
    key.str(std::string()); val.str(std::string());
    onKey = true; onBreak = false; bool onNext = false;
    rightBracket = 0;
    char breakToken = '\00';
    for(int i=0;i<inner.length();i++) {
      char c = inner.at(i);
      if(onKey) {
        if(c == ':') {
          if(!onBreak) {
            onBreak = true;
          }
        }
        else {
          if(!onBreak) {
            key << c;
          }
          else {
            switch(c) {
              case '{' : breakToken = '}'; break;
              case '[' : breakToken = ']'; break;
              default : breakToken = ','; val << c; break;
            }
            onKey = false;
          }
        }
      }
      else {
        switch(breakToken) {
          case '}' : {
            if((c == ',' || c == '}') && onNext) {
              TsonObject* o = parse(key.str() + ":{" + val.str() + "}");
              obj->add(o);
              rightBracket = 0; onKey = true; onBreak = false; onNext = false; breakToken = '\00';
              key.str(std::string()); val.str(std::string());
            }
            else if(c == breakToken && rightBracket < 1) {
              onNext = true;
            }
            else {
              if(!onNext) {
                switch(c) {
                  case '{' : rightBracket++; break;
                  case '}' : rightBracket--; break;
                }
                val << c;
              }
            }
            break;
          }
          case ']' : {
            if((c == ',' || c == '}') && onNext) { //TODO: bool arrays are bugged
              if(ary[0] == "true" || ary[0] == "false") { //Bool
                TsonArray<bool>* a = new TsonArray<bool>(key.str());
                for(int i=0;i<ary.size();i++)
                  a->add(ary[i] == "true" ? true : false);
                obj->add(a);
              }
              if(ary[0].front() == '\'' && ary[0].back() == '\'') { //String
                TsonArray<std::string>* a = new TsonArray<std::string>(key.str());
                for(int i=0;i<ary.size();i++)
                  a->add(ary[i].substr(1,ary[i].size()-2));
                obj->add(a);
              }
              else if(ary[0].back() == 'f') { //Float
                TsonArray<float>* a = new TsonArray<float>(key.str());
                for(int i=0;i<ary.size();i++) {
                  try {
                    a->add(std::stof(ary[i]));
                  }
                  catch(std::invalid_argument) {
                     a->add(0.0f);
                  }
                }
                obj->add(a);
              }
              else { //Int
                TsonArray<int>* a = new TsonArray<int>(key.str());
                for(int i=0;i<ary.size();i++) {
                  try {
                    a->add(std::stoi(ary[i]));
                  }
                  catch(std::invalid_argument) {
                     a->add(0);
                  }
                }
                obj->add(a);
              }

              ary.clear(); onKey = true; onBreak = false; onNext = false; breakToken = '\00';
              key.str(std::string()); val.str(std::string());
            }
            else if(c == breakToken) {
              onNext = true;
            }
            else {
              if(!onNext) {
                if(c == ',') {
                  ary.push_back(val.str());
                  val.str(std::string());
                }
                else {
                  val << c;
                }
              }
            }
            break;
          }
          default : {
            if(c == breakToken || c == '}') {
              std::string valData = val.str();
              if(valData == "true" || valData == "false") { //Bool
                TsonValue<bool>* a = new TsonValue<bool>(key.str());
                a->value = valData == "true" ? true : false;
                obj->add(a);
              }
              else if(valData.front() == '\'' && valData.back() == '\'') { //String
                TsonValue<std::string>* a = new TsonValue<std::string>(key.str());
                a->value = valData.substr(1,valData.size()-2);
                obj->add(a);
              }
              else if(valData.back() == 'f') { //Float
                TsonValue<float>* a = new TsonValue<float>(key.str());
                try {
                    a->value = std::stof(valData);
                }
                catch(std::invalid_argument) {
                  a->value = 0.0f;
                }
                obj->add(a);
              }
              else { //Int
                TsonValue<int>* a = new TsonValue<int>(key.str());
                try {
                    a->value = std::stoi(valData);
                }
                catch(std::invalid_argument) {
                  a->value = 0;
                }
                obj->add(a);
              }
              onKey = true; onBreak = false; breakToken = '\00';
              key.str(std::string()); val.str(std::string());
            }
            else {
              val << c;
            }
            break;
          }
        }
      }
    }
    
    return obj;
  }
  
  std::string removeSpace(const std::string data) {
    std::stringstream ss;
    bool literal = false; bool comment = false;
    for(int i=0;i<data.length();i++) {
      char c = data.at(i);
      if(i < data.length()-1) {
        if(c == '/' && data.at(i+1) == '/' && !literal) {
          comment = true;
        }
      }
      if(comment) {
        if(c == '\n' || c == '\r') {
          comment = false;
        }
      }
      else {
        if(c == '\'') {
          literal = !literal;
        }
        if(literal) {
          if(c != '\n' && c != '\r') {
            ss << c;
          }
        }
        else {
          if(c != '\n' && c != '\r' && c != ' ' && c != '\t') {
            ss << c;
          }
        }
      }
    }
    return ss.str();
  }
}

#endif	/* TSON_HPP */

