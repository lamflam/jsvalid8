
#include <v8.h>
#include <string>
#include <fstream>

using namespace v8;
using namespace std;

Handle<String> ReadFile(const string& name) {

    ifstream file(name.c_str(),ios::in);

    if(!file.is_open())
       return Handle<String>();

    string contents;
    file.seekg(0,ios::end);
    contents.resize(file.tellg());
    file.seekg(0,ios::beg);
    file.read(&contents[0],contents.size());
    file.close();
    
    return String::New(contents.c_str(), contents.size());
}

int main(int argc, char* argv[])  {

    if(argc != 2) {
       printf("Usage is: jsvalid8 file.js\n");
       return 1;
    }
    
    string file = argv[1];
    
    HandleScope handle_scope;
    Persistent<Context> context = Context::New();
    Context::Scope context_scope(context);

    Handle<String> src = ReadFile(file);

    if(src.IsEmpty()) {
      printf("ERROR - Unable to read file: %s\n",file.c_str());
    } else {

      TryCatch try_catch;

      Handle<Script> script = Script::Compile(src);

      if(script.IsEmpty()) {
         String::Utf8Value error(try_catch.Exception());
         printf("ERROR - JavaScript compilation error\n%s\n",*error);
      } else {
        printf("OK\n");
      }
    }
    context.Dispose();
    return 0;
}
