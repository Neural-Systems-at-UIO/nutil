all: bin\generate.exe bin\extract.exe bin\edit.exe bin\custom.exe bin\format.exe bin\invoice.exe bin\performance.exe

bin\generate.exe: bin\libxl.dll generate.c
	g++ -o bin\generate.exe -I..\..\..\include_c -Lbin -lxl generate.c		

bin\extract.exe: bin\libxl.dll extract.c
	g++ -o bin\extract.exe -I..\..\..\include_c -Lbin -lxl extract.c

bin\edit.exe: bin\libxl.dll edit.c
	g++ -o bin\edit.exe -I..\..\..\include_c -Lbin -lxl edit.c

bin\custom.exe: bin\libxl.dll custom.c
	g++ -o bin\custom.exe -I..\..\..\include_c -Lbin -lxl custom.c

bin\format.exe: bin\libxl.dll format.c
	g++ -o bin\format.exe -I..\..\..\include_c -Lbin -lxl format.c

bin\invoice.exe: bin\libxl.dll invoice.c
	g++ -o bin\invoice.exe -I..\..\..\include_c -Lbin -lxl invoice.c

bin\performance.exe: bin\libxl.dll performance.c
	g++ -o bin\performance.exe -I..\..\..\include_c -Lbin -lxl performance.c

bin\libxl.dll:
	copy ..\..\..\bin\libxl.dll bin

clean:
	del /q bin\*

