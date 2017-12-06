all: bin\generate.exe bin\extract.exe bin\edit.exe bin\custom.exe bin\format.exe bin\invoice.exe bin\performance.exe

bin\generate.exe: bin\libxl.dll generate.cpp
	g++ -o bin\generate.exe -I..\..\..\include_cpp -Lbin -lxl generate.cpp		

bin\extract.exe: bin\libxl.dll extract.cpp
	g++ -o bin\extract.exe -I..\..\..\include_cpp -Lbin -lxl extract.cpp

bin\edit.exe: bin\libxl.dll edit.cpp
	g++ -o bin\edit.exe -I..\..\..\include_cpp -Lbin -lxl edit.cpp

bin\custom.exe: bin\libxl.dll custom.cpp
	g++ -o bin\custom.exe -I..\..\..\include_cpp -Lbin -lxl custom.cpp

bin\format.exe: bin\libxl.dll format.cpp
	g++ -o bin\format.exe -I..\..\..\include_cpp -Lbin -lxl format.cpp

bin\invoice.exe: bin\libxl.dll invoice.cpp
	g++ -o bin\invoice.exe -I..\..\..\include_cpp -Lbin -lxl invoice.cpp

bin\performance.exe: bin\libxl.dll performance.cpp
	g++ -o bin\performance.exe -I..\..\..\include_cpp -Lbin -lxl performance.cpp

bin\libxl.dll:
	copy ..\..\..\bin\libxl.dll bin

clean:
	del /q bin\*

