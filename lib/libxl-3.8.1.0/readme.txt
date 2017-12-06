LibXL is a library for direct reading and writing Excel files.


Package contents:

  bin              32-bit dynamic library
  bin64            64-bit dynamic library
  doc              C++ documentation
  examples         C, C++, C#, Delphi and Fortran examples (MinGW, Visual Studio, Qt, Code::Blocks)
  include_c        headers for C
  include_cpp      headers for C++
  lib              32-bit import library for Microsoft Visual C++
  lib64            64-bit import library for Microsoft Visual C++
  net              .NET wrapper (assembly)
  stdcall          32-bit dynamic library with stdcall calling convention
  changelog.txt    change log
  libxl.url        link to home page
  license.txt      end-user license agreement
  readme.txt       this file


Using library:


1. Microsoft Visual C++

   - add include directory in your project, for example: c:\libxl\include_cpp

     Project -> Properties -> C/C++ -> General -> Additional Include Directories

   - add library directory in your project, for example: c:\libxl\lib
    
     Project -> Properties -> Linker -> General -> Additional Library Directories

   - add libxl.lib in project dependencies:
    
     Project -> Properties -> Linker -> Input -> Additional Dependencies

   - copy bin\libxl.dll to directory of your project
     

2. MinGW

   Type in examples/c++/mingw directory:

     g++ generate.cpp -o generate -I../../../include_cpp -L../../../bin -lxl
   
   Use mingw32-make for building examples.


3. C# and other .NET languages

   Use assembly libxl.net.dll in net directory: Project -> Add reference... -> Browse

   Also copy bin\libxl.dll to Debug or Release directory of your project.


4. Qt

   - add the following lines to a configuration file (.pro):

     INCLUDEPATH = c:/libxl-3.6.4.0/include_cpp
     LIBS += c:/libxl-3.6.4.0/lib/libxl.lib

   - copy bin\libxl.dll to the build directory of your project   
   

5. Borland C++ and Embarcadero C++ Builder

   - create import library for your compiler:

       implib -a libxl.lib libxl.dll

   - add include directory to your project, for example: c:\libxl\include_cpp
  
     Project -> Options -> Directories/Conditionals -> Include path

   - add library directory to your project (only for old C++ Builder versions)

     Project -> Options -> Directories/Conditionals -> Library path

   - add libxl.lib to your project

     Project -> Add to Project...

   - copy libxl.dll from bin directory to <your_project_directory>/Win32/Debug


Documentation:

  http://www.libxl.com/doc

Contact:

  support@libxl.com

