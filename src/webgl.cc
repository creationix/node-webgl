#include <node.h>
#include <v8.h>

#include "v8_typed_array.h"

#include "arch_wrapper.h"

using namespace v8;

namespace webgl {


  Handle<Value> Uniform1f(const Arguments& args) {
    HandleScope scope;

    int location = args[0]->Int32Value();
    double x = args[1]->NumberValue();

    glUniform1f(location, x);
    return Undefined();
  }

  Handle<Value> Uniform2f(const Arguments& args) {
    HandleScope scope;

    int location = args[0]->Int32Value();
    double x = args[1]->NumberValue();
    double y = args[2]->NumberValue();

    glUniform2f(location, x, y);
    return Undefined();
  }

  Handle<Value> Uniform4f(const Arguments& args) {
    HandleScope scope;

    int location = args[0]->Int32Value();
    double x = args[1]->NumberValue();
    double y = args[2]->NumberValue();
    double z = args[3]->NumberValue();
    double w = args[4]->NumberValue();

    glUniform4f(location, x, y, z, w);
    return Undefined();
  }

  Handle<Value> Uniform1i(const Arguments& args) {
    HandleScope scope;

    int location = args[0]->Int32Value();
    int x = args[1]->Int32Value();

    glUniform1i(location, x);
    return Undefined();
  }

  Handle<Value> Uniform2i(const Arguments& args) {
    HandleScope scope;

    int location = args[0]->Int32Value();
    int x = args[1]->Int32Value();
    int y = args[2]->Int32Value();

    glUniform2i(location, x, y);
    return Undefined();
  }

  Handle<Value> Uniform4i(const Arguments& args) {
    HandleScope scope;

    int location = args[0]->Int32Value();
    int x = args[1]->Int32Value();
    int y = args[2]->Int32Value();
    int z = args[3]->Int32Value();
    int w = args[4]->Int32Value();

    glUniform4i(location, x, y, z, w);
    return Undefined();
  }


  Handle<Value> PixelStorei(const Arguments& args) {
    HandleScope scope;

    int pname = args[0]->Int32Value();
    int param = args[1]->Int32Value();

    glPixelStorei(pname,param);

    return Undefined();
  }

  Handle<Value> BindAttribLocation(const Arguments& args) {
    HandleScope scope;

    int program = args[0]->Int32Value();
    int index = args[1]->Int32Value();
    String::Utf8Value name(args[2]);

    glBindAttribLocation(program, index, *name);

    return Undefined();
  }


  Handle<Value> GetError(const Arguments& args) {
    HandleScope scope;

    return Number::New(glGetError());
  }


  Handle<Value> DrawArrays(const Arguments& args) {
    HandleScope scope;

    int mode = args[0]->Int32Value();
    int first = args[1]->Int32Value();
    int count = args[2]->Int32Value();

    glDrawArrays(mode, first, count);

    return Undefined();
  }

  Handle<Value> UniformMatrix4fv(const Arguments& args) {
    HandleScope scope;

    GLint location = args[0]->Int32Value();
    GLboolean transpose = args[1]->BooleanValue();
    Local<Object> value = Local<Object>::Cast(args[2]);


    GLsizei count = value->GetIndexedPropertiesExternalArrayDataLength();

    if (count < 16) {
      return ThrowException(Exception::TypeError(String::New("Not enough data for UniformMatrix4fv")));
    }

    const GLfloat* data = (const GLfloat*)value->GetIndexedPropertiesExternalArrayData();

//    printf("count=%d\n", count);
//    printf("[%f, %f, %f, %f,\n", data[0], data[1], data[2], data[3]);
//    printf(" %f, %f, %f, %f,\n", data[4], data[5], data[6], data[7]);
//    printf(" %f, %f, %f, %f,\n", data[8], data[9], data[10], data[11]);
//    printf(" %f, %f, %f, %f]\n", data[12], data[13], data[14], data[15]);


    glUniformMatrix4fv(location, count / 16, transpose, data);

    return Undefined();
  }



  Handle<Value> GetAttribLocation(const Arguments& args) {
    HandleScope scope;

    int program = args[0]->Int32Value();
    String::Utf8Value name(args[1]);

    return Number::New(glGetAttribLocation(program, *name));
  }


  Handle<Value> DepthFunc(const Arguments& args) {
    HandleScope scope;

    glDepthFunc(args[0]->Int32Value());

    return Undefined();
  }


  Handle<Value> Viewport(const Arguments& args) {
    HandleScope scope;

    int x = args[0]->Int32Value();
    int y = args[1]->Int32Value();
    int width = args[2]->Int32Value();
    int height = args[3]->Int32Value();

    glViewport(x, y, width, height);

    return Undefined();

    return Number::New(glCreateShader(args[0]->Int32Value()));
  }

  Handle<Value> CreateShader(const Arguments& args) {
    HandleScope scope;

    return Number::New(glCreateShader(args[0]->Int32Value()));
  }


  Handle<Value> ShaderSource(const Arguments& args) {
    HandleScope scope;

    int id = args[0]->Int32Value();
    String::Utf8Value code(args[1]);

    const char* codes[1];
    codes[0] = *code;

    glShaderSource  (id, 1, codes, NULL);

    return Undefined();
  }


  Handle<Value> CompileShader(const Arguments& args) {
    HandleScope scope;


    glCompileShader(args[0]->Int32Value());

    return Undefined();
  }


  Handle<Value> GetShaderParameter(const Arguments& args) {
    HandleScope scope;

    int shader = args[0]->Int32Value();
    int pname = args[1]->Int32Value();
    int value = 0;
    switch (pname) {
    case GL_DELETE_STATUS:
    case GL_COMPILE_STATUS:
      glGetShaderiv(shader, pname, &value);
      return Boolean::New(static_cast<bool>(value));
    case GL_SHADER_TYPE:
      glGetShaderiv(shader, pname, &value);
      return Number::New(static_cast<unsigned long>(value));
    case GL_INFO_LOG_LENGTH:
    case GL_SHADER_SOURCE_LENGTH:
      glGetShaderiv(shader, pname, &value);
      return Number::New(static_cast<long>(value));
    default:
      return ThrowException(Exception::TypeError(String::New("GetShaderParameter: Invalid Enum")));
    }
  }

  Handle<Value> GetShaderInfoLog(const Arguments& args) {
    HandleScope scope;

    int id = args[0]->Int32Value();
    int Len = 1024;
    char Error[1024];
    glGetShaderInfoLog(id, 1024, &Len, Error);

    return String::New(Error);
  }


  Handle<Value> CreateProgram(const Arguments& args) {
    HandleScope scope;

    return Number::New(glCreateProgram());
  }


  Handle<Value> AttachShader(const Arguments& args) {
    HandleScope scope;

    int program = args[0]->Int32Value();
    int shader = args[1]->Int32Value();

    glAttachShader(program, shader);

    return Undefined();
  }


  Handle<Value> LinkProgram(const Arguments& args) {
    HandleScope scope;

    glLinkProgram(args[0]->Int32Value());

    return Undefined();
  }


  Handle<Value> GetProgramParameter(const Arguments& args) {
    HandleScope scope;

    int program = args[0]->Int32Value();
    int pname = args[1]->Int32Value();

    int value = 0;
    switch (pname) {
    case GL_DELETE_STATUS:
    case GL_LINK_STATUS:
    case GL_VALIDATE_STATUS:
      glGetProgramiv(program, pname, &value);
      return Boolean::New(static_cast<bool>(value));
    case GL_ATTACHED_SHADERS:
    case GL_ACTIVE_ATTRIBUTES:
    case GL_ACTIVE_UNIFORMS:
      glGetProgramiv(program, pname, &value);
      return Number::New(static_cast<long>(value));
    default:
      return ThrowException(Exception::TypeError(String::New("GetProgramParameter: Invalid Enum")));
    }
  }


  Handle<Value> GetUniformLocation(const Arguments& args) {
    HandleScope scope;

    int program = args[0]->Int32Value();
    String::Utf8Value name(args[1]);

    return Number::New(glGetUniformLocation(program, *name));
  }


  Handle<Value> ClearColor(const Arguments& args) {
    HandleScope scope;

    double red = args[0]->NumberValue();
    double green = args[1]->NumberValue();
    double blue = args[2]->NumberValue();
    double alpha = args[3]->NumberValue();

    glClearColor(red, green, blue, alpha);

    return Undefined();
  }


  Handle<Value> ClearDepth(const Arguments& args) {
    HandleScope scope;

    double depth = args[0]->NumberValue();

    glClearDepthf(depth);

    return Undefined();
  }

  Handle<Value> Disable(const Arguments& args) {
    HandleScope scope;

    glDisable(args[0]->Int32Value());
    return Undefined();
  }

  Handle<Value> Enable(const Arguments& args) {
    HandleScope scope;

    glEnable(args[0]->Int32Value());
    return Undefined();
  }


  Handle<Value> CreateTexture(const Arguments& args) {
    HandleScope scope;

    GLuint texture;
    glGenTextures(1, &texture);
    return Number::New(texture);
  }


  Handle<Value> BindTexture(const Arguments& args) {
    HandleScope scope;

    int target = args[0]->Int32Value();
    int texture = args[1]->Int32Value();

    glBindTexture(target, texture);
    return Undefined();
  }


  Handle<Value> TexImage2D(const Arguments& args) {
    HandleScope scope;

    int target = args[0]->Int32Value();
    int level = args[1]->Int32Value();
    int internalformat = args[2]->Int32Value();
    int width = args[3]->Int32Value();
    int height = args[4]->Int32Value();
    int border = args[5]->Int32Value();
    int format = args[6]->Int32Value();
    int type = args[7]->Int32Value();
    Local<Object> obj = Local<Object>::Cast(args[8]);

    void* pixels = obj->GetIndexedPropertiesExternalArrayData();

    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);

    return Undefined();
  }


  Handle<Value> TexParameteri(const Arguments& args) {
    HandleScope scope;

    int target = args[0]->Int32Value();
    int pname = args[1]->Int32Value();
    int param = args[2]->Int32Value();

    glTexParameteri(target, pname, param);

    return Undefined();
  }


  Handle<Value> Clear(const Arguments& args) {
    HandleScope scope;

    glClear(args[0]->Int32Value());

    return Undefined();
  }


  Handle<Value> UseProgram(const Arguments& args) {
    HandleScope scope;

    glUseProgram(args[0]->Int32Value());

    return Undefined();
  }


  Handle<Value> CreateBuffer(const Arguments& args) {
    HandleScope scope;

    GLuint buffer;
    glGenBuffers(1, &buffer);
    return Number::New(buffer);
  }


  Handle<Value> BindBuffer(const Arguments& args) {
    HandleScope scope;

    int target = args[0]->Int32Value();
    int buffer = args[1]->Int32Value();

    glBindBuffer(target, buffer);

    return Undefined();
  }


  Handle<Value> CreateFramebuffer(const Arguments& args) {
    HandleScope scope;

    GLuint buffer;
    glGenFramebuffers(1, &buffer);
    return Number::New(buffer);
  }


  Handle<Value> BindFramebuffer(const Arguments& args) {
    HandleScope scope;

    int target = args[0]->Int32Value();
    int buffer = args[1]->Int32Value();

    glBindFramebuffer(target, buffer);

    return Undefined();
  }


  Handle<Value> FramebufferTexture2D(const Arguments& args) {
    HandleScope scope;

    int target = args[0]->Int32Value();
    int attachment = args[1]->Int32Value();
    int textarget = args[2]->Int32Value();
    int texture = args[3]->Int32Value();
    int level = args[4]->Int32Value();

    glFramebufferTexture2D(target, attachment, textarget, texture, level);

    return Undefined();
  }


  Handle<Value> BufferData(const Arguments& args) {
    HandleScope scope;

    int target = args[0]->Int32Value();
    Local<Object> obj = Local<Object>::Cast(args[1]);
    int usage = args[2]->Int32Value();

    int element_size = v8_typed_array::SizeOfArrayElementForType(
        obj->GetIndexedPropertiesExternalArrayDataType());
    int size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
    void* data = obj->GetIndexedPropertiesExternalArrayData();


//    printf("BufferData %d %d %d\n", target, size, usage);
    glBufferData(target, size, data, usage);

    return Undefined();
  }


  Handle<Value> BufferSubData(const Arguments& args) {
    HandleScope scope;

    int target = args[0]->Int32Value();
    int offset = args[1]->Int32Value();
    Local<Object> obj = Local<Object>::Cast(args[2]);

    int element_size = v8_typed_array::SizeOfArrayElementForType(
        obj->GetIndexedPropertiesExternalArrayDataType());
    int size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
    void* data = obj->GetIndexedPropertiesExternalArrayData();

    glBufferSubData(target, offset, size, data);

    return Undefined();
  }


  Handle<Value> BlendEquation(const Arguments& args) {
    HandleScope scope;

    return ThrowException(Exception::Error(String::New("BlendEquation not implemented in node-webgl")));
  }


  Handle<Value> BlendFunc(const Arguments& args) {
    HandleScope scope;

    return ThrowException(Exception::Error(String::New("BlendFunc not implemented in node-webgl")));
  }


  Handle<Value> EnableVertexAttribArray(const Arguments& args) {
    HandleScope scope;

    glEnableVertexAttribArray(args[0]->Int32Value());

    return Undefined();
  }


  Handle<Value> VertexAttribPointer(const Arguments& args) {
    HandleScope scope;

    int indx = args[0]->Int32Value();
    int size = args[1]->Int32Value();
    int type = args[2]->Int32Value();
    int normalized = args[3]->BooleanValue();
    int stride = args[4]->Int32Value();
    int offset = args[5]->Int32Value();

//    printf("VertexAttribPointer %d %d %d %d %d %d\n", indx, size, type, normalized, stride, offset);
    glVertexAttribPointer(indx, size, type, normalized, stride, (const GLvoid *)offset);

    return Undefined();
  }


  Handle<Value> ActiveTexture(const Arguments& args) {
    HandleScope scope;

    glActiveTexture(args[0]->Int32Value());
    return Undefined();
  }


  Handle<Value> DrawElements(const Arguments& args) {
    HandleScope scope;

    int mode = args[0]->Int32Value();
    int count = args[1]->Int32Value();
    int type = args[2]->Int32Value();
    int offset = args[3]->Int32Value();
    glDrawElements(mode, count, type, (const GLvoid*)offset);
    return Undefined();
  }


  Handle<Value> Flush(const Arguments& args) {
    HandleScope scope;

    glFlush();
    return Undefined();
  }


}

extern "C" void
init(Handle<Object> target)
{

  NODE_SET_METHOD(target, "uniform1f", webgl::Uniform1f);
  NODE_SET_METHOD(target, "uniform2f", webgl::Uniform2f);
  NODE_SET_METHOD(target, "uniform4f", webgl::Uniform4f);
  NODE_SET_METHOD(target, "uniform1i", webgl::Uniform1i);
  NODE_SET_METHOD(target, "uniform2i", webgl::Uniform2i);
  NODE_SET_METHOD(target, "uniform4i", webgl::Uniform4i);
  NODE_SET_METHOD(target, "pixelStorei", webgl::PixelStorei);
  NODE_SET_METHOD(target, "bindAttribLocation", webgl::BindAttribLocation);
  NODE_SET_METHOD(target, "getError", webgl::GetError);
  NODE_SET_METHOD(target, "drawArrays", webgl::DrawArrays);
  NODE_SET_METHOD(target, "uniformMatrix4fv", webgl::UniformMatrix4fv);

  NODE_SET_METHOD(target, "getAttribLocation", webgl::GetAttribLocation);
  NODE_SET_METHOD(target, "depthFunc", webgl::DepthFunc);
  NODE_SET_METHOD(target, "viewport", webgl::Viewport);
  NODE_SET_METHOD(target, "createShader", webgl::CreateShader);
  NODE_SET_METHOD(target, "shaderSource", webgl::ShaderSource);
  NODE_SET_METHOD(target, "compileShader", webgl::CompileShader);
  NODE_SET_METHOD(target, "getShaderParameter", webgl::GetShaderParameter);
  NODE_SET_METHOD(target, "getShaderInfoLog", webgl::GetShaderInfoLog);
  NODE_SET_METHOD(target, "createProgram", webgl::CreateProgram);
  NODE_SET_METHOD(target, "attachShader", webgl::AttachShader);
  NODE_SET_METHOD(target, "linkProgram", webgl::LinkProgram);
  NODE_SET_METHOD(target, "getProgramParameter", webgl::GetProgramParameter);
  NODE_SET_METHOD(target, "getUniformLocation", webgl::GetUniformLocation);
  NODE_SET_METHOD(target, "clearColor", webgl::ClearColor);
  NODE_SET_METHOD(target, "clearDepth", webgl::ClearDepth);

  NODE_SET_METHOD(target, "disable", webgl::Disable);
  NODE_SET_METHOD(target, "createTexture", webgl::CreateTexture);
  NODE_SET_METHOD(target, "bindTexture", webgl::BindTexture);
  NODE_SET_METHOD(target, "texImage2D", webgl::TexImage2D);
  NODE_SET_METHOD(target, "texParameteri", webgl::TexParameteri);
  NODE_SET_METHOD(target, "clear", webgl::Clear);
  NODE_SET_METHOD(target, "useProgram", webgl::UseProgram);
  NODE_SET_METHOD(target, "createFramebuffer", webgl::CreateFramebuffer);
  NODE_SET_METHOD(target, "bindFramebuffer", webgl::BindFramebuffer);
  NODE_SET_METHOD(target, "framebufferTexture2D", webgl::FramebufferTexture2D);
  NODE_SET_METHOD(target, "createBuffer", webgl::CreateBuffer);
  NODE_SET_METHOD(target, "bindBuffer", webgl::BindBuffer);
  NODE_SET_METHOD(target, "bufferData", webgl::BufferData);
  NODE_SET_METHOD(target, "bufferSubData", webgl::BufferSubData);
  NODE_SET_METHOD(target, "enable", webgl::Enable);
  NODE_SET_METHOD(target, "blendEquation", webgl::BlendEquation);
  NODE_SET_METHOD(target, "blendFunc", webgl::BlendFunc);
  NODE_SET_METHOD(target, "enableVertexAttribArray", webgl::EnableVertexAttribArray);
  NODE_SET_METHOD(target, "vertexAttribPointer", webgl::VertexAttribPointer);
  NODE_SET_METHOD(target, "activeTexture", webgl::ActiveTexture);
  NODE_SET_METHOD(target, "drawElements", webgl::DrawElements);
  NODE_SET_METHOD(target, "flush", webgl::Flush);

  target->Set(String::New("FRAGMENT_SHADER"), Number::New(GL_FRAGMENT_SHADER));
  target->Set(String::New("VERTEX_SHADER"), Number::New(GL_VERTEX_SHADER));
  target->Set(String::New("COMPILE_STATUS"), Number::New(GL_COMPILE_STATUS));
  target->Set(String::New("DELETE_STATUS"), Number::New(GL_DELETE_STATUS));
  target->Set(String::New("LINK_STATUS"), Number::New(GL_LINK_STATUS));
  target->Set(String::New("VALIDATE_STATUS"), Number::New(GL_VALIDATE_STATUS));
  target->Set(String::New("ATTACHED_SHADERS"), Number::New(GL_ATTACHED_SHADERS));
  target->Set(String::New("ACTIVE_ATTRIBUTES"), Number::New(GL_ACTIVE_ATTRIBUTES));
  target->Set(String::New("ACTIVE_UNIFORMS"), Number::New(GL_ACTIVE_UNIFORMS));
  target->Set(String::New("ELEMENT_ARRAY_BUFFER"), Number::New(GL_ELEMENT_ARRAY_BUFFER));


  target->Set(String::New("NEVER"), Number::New(GL_NEVER));
  target->Set(String::New("LESS"), Number::New(GL_LESS));
  target->Set(String::New("EQUAL"), Number::New(GL_EQUAL));
  target->Set(String::New("LEQUAL"), Number::New(GL_LEQUAL));
  target->Set(String::New("GREATER"), Number::New(GL_GREATER));
  target->Set(String::New("NOTEQUAL"), Number::New(GL_NOTEQUAL));
  target->Set(String::New("GEQUAL"), Number::New(GL_GEQUAL));
  target->Set(String::New("ALWAYS"), Number::New(GL_ALWAYS));

  target->Set(String::New("DEPTH_TEST"), Number::New(GL_DEPTH_TEST));
  target->Set(String::New("ARRAY_BUFFER"), Number::New(GL_ARRAY_BUFFER));
  target->Set(String::New("STATIC_DRAW"), Number::New(GL_STATIC_DRAW));
  target->Set(String::New("STREAM_DRAW"), Number::New(GL_STREAM_DRAW));
  target->Set(String::New("DYNAMIC_DRAW"), Number::New(GL_DYNAMIC_DRAW));

  target->Set(String::New("FLOAT"), Number::New(GL_FLOAT));
  target->Set(String::New("UNSIGNED_BYTE"), Number::New(GL_UNSIGNED_BYTE));
  target->Set(String::New("UNSIGNED_SHORT"), Number::New(GL_UNSIGNED_SHORT));
  target->Set(String::New("FALSE"), Boolean::New(GL_FALSE));
  target->Set(String::New("TRIANGLES"), Number::New(GL_TRIANGLES));
  target->Set(String::New("TRIANGLE_STRIP"), Number::New(GL_TRIANGLE_STRIP));
  target->Set(String::New("COLOR_BUFFER_BIT"), Number::New(GL_COLOR_BUFFER_BIT));
  target->Set(String::New("DEPTH_BUFFER_BIT"), Number::New(GL_DEPTH_BUFFER_BIT));

  target->Set(String::New("TEXTURE_2D"), Number::New(GL_TEXTURE_2D));
  target->Set(String::New("TEXTURE0"), Number::New(GL_TEXTURE0));
  target->Set(String::New("TEXTURE1"), Number::New(GL_TEXTURE1));
  target->Set(String::New("TEXTURE2"), Number::New(GL_TEXTURE2));
  target->Set(String::New("TEXTURE3"), Number::New(GL_TEXTURE3));
  target->Set(String::New("TEXTURE4"), Number::New(GL_TEXTURE4));
  target->Set(String::New("TEXTURE_MIN_FILTER"), Number::New(GL_TEXTURE_MIN_FILTER));
  target->Set(String::New("TEXTURE_MAG_FILTER"), Number::New(GL_TEXTURE_MAG_FILTER));
  target->Set(String::New("LINEAR"), Number::New(GL_LINEAR));
  target->Set(String::New("NEAREST"), Number::New(GL_NEAREST));

  target->Set(String::New("FRAMEBUFFER"), Number::New(GL_FRAMEBUFFER));
  target->Set(String::New("COLOR_ATTACHMENT0"), Number::New(GL_COLOR_ATTACHMENT0));

  target->Set(String::New("INVALID_ENUM"), Number::New(GL_INVALID_ENUM));
  target->Set(String::New("INVALID_VALUE"), Number::New(GL_INVALID_VALUE));
  target->Set(String::New("INVALID_OPERATION"), Number::New(GL_INVALID_OPERATION));
//  target->Set(String::New("STACK_OVERFLOW"), Number::New(GL_STACK_OVERFLOW));
//  target->Set(String::New("STACK_UNDERFLOW"), Number::New(GL_STACK_UNDERFLOW));
  target->Set(String::New("OUT_OF_MEMORY"), Number::New(GL_OUT_OF_MEMORY));
//  target->Set(String::New("TABLE_TOO_LARGE"), Number::New(GL_TABLE_TOO_LARGE));


  target->Set(String::New("UNPACK_ALIGNMENT"), Number::New(GL_UNPACK_ALIGNMENT));
  target->Set(String::New("RGBA"), Number::New(GL_RGBA));



  v8_typed_array::AttachBindings(Context::GetCurrent()->Global());


}

