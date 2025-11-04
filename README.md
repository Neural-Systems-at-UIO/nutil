# Nutil
Nutil is a desktop application that aims to simplify and streamline the mechanism of pre-and-post processing 2D brain imaging data from mouse and rat. It is an integral part of the QUINT workflow for regional quantification of labelled objects such as cells in histological imaging data. 

Nutil is written in C++ using standard Qt libraries, and is optimised for parallel operations on multiple CPUs. Nutil does not utilise GPU extensions. The external libraries that are used in Nutil are: 
- Libtiff for fast and efficient TIFF file handling (http://www.libtiff.org/)
- LibXLNT for Excel file I/O (https://github.com/tfussell/xlnt/)

Compiling from source (Windows)
1. In order to compile from scratch, the following software components are also required:
 * On Windows, Microsoft Visual C++ 2019 compiler (MSVC), community version (https://visualstudio.microsoft.com/vs/features/cplusplus/)
 * On macOS, XCode (Clang) 
 * On Linux, Gnu C++ compiler
2. Download and install Qt Creator for open source users (https://www.qt.io/download)
 Install the Qt framework version 6 or above (create a user account, custom install, select newest version and MSVC 2019).
3. Install git (https://desktop.github.com/)
4. Clone this repository to a folder (in github desktop: file->clone repository)
5. Open the project file in Qt (file->open file or project)
6. Set up a build path to the project (projects->build->build directory)
7. Compile and run! (ctrl+r)

Compiling from source on linux (debian-based)
1. git clone https://github.com/Neural-Systems-at-UIO/nutil.git
2. Move to the nutil directory : cd nutil
3. Install the required packages: sudo apt-get install qt5-default qtchooser
4. Run Qmake: qmake
5. Compile: make -j 8 (number of threads)

You can now run Nutil from the command line / bash scripts by simply running
./Nutil myProject.nut 8
or ./Nutil to use the GUI

# Download
https://www.nitrc.org/projects/nutil

# Latest stable version
Nutil v0.8
Nutil v1.1 can be used, but has a known bug (see release notes).

# Documentation
https://nutil.readthedocs.io

# Contributors
Programming: Nicolaas E Groeneboom
Conception, design, validation: Sharon C Yates, Maja A Puchades, Gergely Csucs and Jan G Bjaalie. 

# Licence
- Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
- GNU General Public License v3

# Citation
* Nutil has RRID:SCR_017183
* Groeneboom NE, Yates SC, Puchades MA and Bjaalie JG (2020) Nutil: A Pre- and Post-processing Toolbox for Histological Rodent Brain Section Images. Front. Neuroinform. 14:37. doi: 10.3389/fninf.2020.00037
* Yates SC, Groeneboom NE, Coello C, et al. & Bjaalie JG (2019) QUINT: Workflow for Quantification and Spatial Analysis of Features in Histological Images From Rodent Brain. Front. Neuroinform. 13:75. doi: 10.3389/fninf.2019.00075

# Acknowledgements
Nutil is an integral part of the QUINT workflow and is developed by the Neural Systems Laboratory at the Institute of Basic Medical Sciences, University of Oslo, Norway. Nutil was developed with support from the EBRAINS infrastructure, and funding from the European Union’s Horizon 2020 Framework Programme for Research and Innovation under the Framework Partnership Agreement No. 650003 (HBP FPA) and the European Union’s Horizon Europe Programme for Research Infrastructures Grant Agreement No. 101147319 (EBRAINS 2.0).

# Contact us
Report issues here on github or email: support@ebrains.eu











  








 
