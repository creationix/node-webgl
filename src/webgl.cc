#include <node.h>
#include <v8.h>

#include "v8_typed_array.h"

#include <GLES2/gl2.h>

using namespace v8;

namespace webgl {



//void glUniformMatrix4fv(	GLint  	location,
// 	GLsizei  	count,
// 	GLboolean  	transpose,
// 	const GLfloat * 	value);


//(WebGLUniformLocation location, GLboolean transpose, 
//                          Float32Array value);



  Handle<Value> DrawArrays(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 3 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected DrawArrays(Number, Number, Number)")));
    }
    
    
    int mode = args[0]->Int32Value();
    int first = args[1]->Int32Value();
    int count = args[2]->Int32Value();
    
    glDrawArrays(mode, first, count);
    
    return Undefined();
  }

  Handle<Value> UniformMatrix4fv(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 3 && args[0]->IsNumber() && args[1]->IsBoolean() && args[2]->IsObject())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected UniformMatrix(Number, Boolean, Object)")));
    }
    
    int location = args[0]->Int32Value();
    bool transpose = args[1]->BooleanValue();
    Local<Object> value = Local<Object>::Cast(args[2]);

    if (!value->HasIndexedPropertiesInExternalArrayData()) {
      return ThrowException(Exception::TypeError(String::New("Data must be an ArrayBuffer.")));
    }
    int count = value->GetIndexedPropertiesExternalArrayDataLength();

    if (count < 4) {
      return ThrowException(Exception::TypeError(String::New("Not enough data for UniformMatrix4fv")));
    }

    void* data = value->GetIndexedPropertiesExternalArrayData();
    
    glUniformMatrix4fv(location, count, transpose, (const GLfloat*)data);
    
    return Undefined();
  }



  Handle<Value> GetAttribLocation(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsString())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetAttribLocation(Number, String)")));
    }
    
    int program = args[0]->Int32Value();
    String::Utf8Value name(args[1]);
    
    return Number::New(glGetAttribLocation(program, *name));
  }


  Handle<Value> DepthFunc(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected DepthFunc(Number)")));
    }

    glDepthFunc(args[0]->Int32Value());
    
    return Undefined();    
  }


  Handle<Value> Viewport(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 4 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Viewport(Number, Number, Number, Number)")));
    }
    
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

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected CreateShader(Number)")));
    }

    return Number::New(glCreateShader(args[0]->Int32Value()));
  }


  Handle<Value> ShaderSource(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsString())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected ShaderSource(Number, String)")));
    }

    int id = args[0]->Int32Value();
    String::Utf8Value code(args[1]);

    const char* codes[1];
    codes[0] = *code;

    glShaderSource  (id, 1, codes, NULL);
    
    return Undefined();
  }


  Handle<Value> CompileShader(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected CompileShader(Number)")));
    }
    
    
    glCompileShader(args[0]->Int32Value());
    
    return Undefined();
  }


  Handle<Value> GetShaderParameter(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetShaderParameter(Number, Number)")));
    }

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

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetShaderInfoLog(Number)")));
    }

    int id = args[0]->Int32Value();
    int Len = 1024;
    char Error[1024];
    glGetShaderInfoLog(id, 1024, &Len, Error);

    return String::New(Error);
  }


  Handle<Value> CreateProgram(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 0)) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected CreateProgram()")));
    }
    
    return Number::New(glCreateProgram());
  }


  Handle<Value> AttachShader(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected AttachShader(Number, Number)")));
    }
    
    int program = args[0]->Int32Value();
    int shader = args[1]->Int32Value();
    
    glAttachShader(program, shader);
    
    return Undefined();
  }


  Handle<Value> BindAttribLocation(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected BindAttribLocation(Number)")));
    }

    return ThrowException(Exception::Error(String::New("BindAttribLocation not implemented in node-webgl")));
  }


  Handle<Value> LinkProgram(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected LinkProgram(Number)")));
    }
    
    glLinkProgram(args[0]->Int32Value());
    
    return Undefined();
  }


  Handle<Value> GetProgramParameter(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetProgramParameter(Number, Number)")));
    }

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

    if (!(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsString())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected GetUniformLocation(Number, String)")));
    }
    
    int program = args[0]->Int32Value();
    String::Utf8Value name(args[1]);
    
    return Number::New(glGetUniformLocation(program, *name));
  }


  Handle<Value> ClearColor(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 4 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected ClearColor(Number, Number, Number, Number)")));
    }
    
    double red = args[0]->NumberValue();
    double green = args[1]->NumberValue();
    double blue = args[2]->NumberValue();
    double alpha = args[3]->NumberValue();
    
    glClearColor(red, green, blue, alpha);
    
    return Undefined();
  }


  Handle<Value> ClearDepth(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected ClearDepth(Number)")));
    }
    
    double depth = args[0]->NumberValue();
    
    glClearDepthf(depth);
    
    return Undefined();
  }

  Handle<Value> Disable(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Disable(Number)")));
    }

    return ThrowException(Exception::Error(String::New("Disable not implemented in node-webgl")));
  }


  Handle<Value> CreateTexture(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected CreateTexture(Number)")));
    }

    return ThrowException(Exception::Error(String::New("CreateTexture not implemented in node-webgl")));
  }


  Handle<Value> BindTexture(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected BindTexture(Number)")));
    }

    return ThrowException(Exception::Error(String::New("BindTexture not implemented in node-webgl")));
  }


  Handle<Value> TexImage2D(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TexImage2D(Number)")));
    }

    return ThrowException(Exception::Error(String::New("TexImage2D not implemented in node-webgl")));
  }


  Handle<Value> TexParameteri(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected TexParameteri(Number)")));
    }

    return ThrowException(Exception::Error(String::New("TexParameteri not implemented in node-webgl")));
  }


  Handle<Value> Clear(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Clear(Number)")));
    }
    
    glClear(args[0]->Int32Value());

    return Undefined();
  }


  Handle<Value> UseProgram(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected UseProgram(Number)")));
    }
    
    glUseProgram(args[0]->Int32Value());
    
    return Undefined();
  }


  Handle<Value> Uniform4f(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Uniform4f(Number)")));
    }

    return ThrowException(Exception::Error(String::New("Uniform4f not implemented in node-webgl")));
  }


  Handle<Value> CreateBuffer(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 0)) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected CreateBuffer()")));
    }
    
    GLuint buffers[1];
    glGenBuffers(1, buffers);
    
    return Number::New(buffers[0]);
  }


  Handle<Value> BindBuffer(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 2 && args[0]->IsNumber() && args[1]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected BindBuffer(Number, Number)")));
    }
    
    int target = args[0]->Int32Value();
    int buffer = args[0]->Int32Value();
    
    glBindBuffer(target, buffer);
    
    return Undefined();
  }


  Handle<Value> BufferData(const Arguments& args) {
    HandleScope scope;
    if (!(args.Length() == 3 && args[0]->IsNumber() && args[1]->IsObject() && args[2]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected BufferData(Number, Object, Number)")));
    }

    int target = args[0]->Int32Value();
    Local<Object> obj = Local<Object>::Cast(args[1]);
    int usage = args[2]->Int32Value();

    if (!obj->HasIndexedPropertiesInExternalArrayData()) {
      return ThrowException(Exception::TypeError(String::New("Data must be an ArrayBuffer.")));
    }
    int element_size = v8_typed_array::SizeOfArrayElementForType(
        obj->GetIndexedPropertiesExternalArrayDataType());
    int size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
    void* data = obj->GetIndexedPropertiesExternalArrayData();
    
    glBufferData(target, size, data, usage);

    return Undefined(); 
  }


  Handle<Value> BufferSubData(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected BufferSubData(Number)")));
    }

    return ThrowException(Exception::Error(String::New("BufferSubData not implemented in node-webgl")));
  }


  Handle<Value> Enable(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Enable(Number)")));
    }
    
    glEnable(args[0]->Int32Value());
    
    return Undefined();
  }


  Handle<Value> BlendEquation(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected BlendEquation(Number)")));
    }

    return ThrowException(Exception::Error(String::New("BlendEquation not implemented in node-webgl")));
  }


  Handle<Value> BlendFunc(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected BlendFunc(Number)")));
    }

    return ThrowException(Exception::Error(String::New("BlendFunc not implemented in node-webgl")));
  }


  Handle<Value> EnableVertexAttribArray(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected EnableVertexAttribArray(Number)")));
    }
    
    glEnableVertexAttribArray(args[0]->Int32Value());
    
    return Undefined();
  }


  Handle<Value> VertexAttribPointer(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 6 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsBoolean() && args[4]->IsNumber() && args[5]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected VertexAttribPointer(Number, Number, Number, Boolean, Number, Number)")));
    }
    
    int indx = args[0]->Int32Value();
    int size = args[1]->Int32Value();
    int type = args[2]->Int32Value();
    int normalized = args[3]->BooleanValue();
    int stride = args[4]->Int32Value();
    int offset = args[5]->Int32Value();

    glVertexAttribPointer(indx, size, type, normalized, stride, (const GLvoid *)offset);
    
    return Undefined();
  }


  Handle<Value> Uniform1i(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Uniform1i(Number)")));
    }

    return ThrowException(Exception::Error(String::New("Uniform1i not implemented in node-webgl")));
  }


  Handle<Value> ActiveTexture(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected ActiveTexture(Number)")));
    }

    return ThrowException(Exception::Error(String::New("ActiveTexture not implemented in node-webgl")));
  }


  Handle<Value> DrawElements(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected DrawElements(Number)")));
    }

    return ThrowException(Exception::Error(String::New("DrawElements not implemented in node-webgl")));
  }


  Handle<Value> Flush(const Arguments& args) {
    HandleScope scope;

    if (!(args.Length() == 1 && args[0]->IsNumber())) {
      return ThrowException(Exception::TypeError(String::New("Invalid arguments: Expected Flush(Number)")));
    }

    return ThrowException(Exception::Error(String::New("Flush not implemented in node-webgl")));
  }


}

extern "C" void
init(Handle<Object> target)
{



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
  NODE_SET_METHOD(target, "bindAttribLocation", webgl::BindAttribLocation);
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
  NODE_SET_METHOD(target, "uniform4f", webgl::Uniform4f);
  NODE_SET_METHOD(target, "createBuffer", webgl::CreateBuffer);
  NODE_SET_METHOD(target, "bindBuffer", webgl::BindBuffer);
  NODE_SET_METHOD(target, "bufferData", webgl::BufferData);
  NODE_SET_METHOD(target, "bufferSubData", webgl::BufferSubData);
  NODE_SET_METHOD(target, "enable", webgl::Enable);
  NODE_SET_METHOD(target, "blendEquation", webgl::BlendEquation);
  NODE_SET_METHOD(target, "blendFunc", webgl::BlendFunc);
  NODE_SET_METHOD(target, "enableVertexAttribArray", webgl::EnableVertexAttribArray);
  NODE_SET_METHOD(target, "vertexAttribPointer", webgl::VertexAttribPointer);
  NODE_SET_METHOD(target, "uniform1i", webgl::Uniform1i);
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

  target->Set(String::New("FLOAT"), Number::New(GL_FLOAT));
  target->Set(String::New("TRIANGLES"), Number::New(GL_TRIANGLES));
  target->Set(String::New("TRIANGLE_STRIP"), Number::New(GL_TRIANGLE_STRIP));
  
  
  v8_typed_array::AttachBindings(Context::GetCurrent()->Global());
   
  
}

