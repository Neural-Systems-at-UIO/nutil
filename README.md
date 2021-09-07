# Nutil
Nutil aims to both simplify and streamline the mechanism of pre-and-post processing 2D brain image data from mouse and rat. Nutil is developed as a stand-alone application that runs on all operating systems requiring little-to-no experience to execute. The user specifies the path to the input and output directories and the parameters for the pre-and post processing operations in the Nutil GUI. Pre-processing operations include conversion of images from JPEG/PNG format to tiled TIFF format, 2D transformations of extremely large tiled TIFF files (rotation, flipping and scaling), in addition to renaming, copying and downsizing. Post-processing is based on analysis of segmented images in the context of brain regions defined by a reference atlas, such as the Allen Mouse Brain reference atlas or the Waxholm Space Atlas of the Sprague Dawley rat brain. All functions operate in batch mode, and operate in parallel on multiple CPUs.

# Getting started
Download here on github or from https://www.nitrc.org/projects/nutil/

Nutil is written in C++ using standard Qt libraries, and is optimised for parallel operations on multiple CPUs. Nutil does not require any installation, and does not currently utilise any GPU extensions. The external libraries that are used in Nutil are: 
- Libtiff for fast and efficient TIFF file handling (http://www.libtiff.org/)
- LibXLNT for Excel file I/O (https://github.com/tfussell/xlnt/)

# Compiling from source 
1.In order to compile from scratch, the following software components are also required:
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

# Acknowledgements
Nutil is an integral part of the QUINT workflow and is developed by the Neural Systems Laboratory at the Institute of Basic Medical Sciences, University of Oslo, Norway. Nutil was developed with support from the EBRAINS infrastructure, and funding from the European Union’s Horizon 2020 Framework Programme for Research and Innovation under the Framework Partnership Agreement No. 650003 (HBP FPA).

# Authors
Nicolaas E Groeneboom, Sharon C Yates, Maja A Puchades, Jan G Bjaalie. 

# Licence
- Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
- GNU General Public License v3

# Cite
Groeneboom NE, Yates SC, Puchades MA and Bjaalie JG (2020) Nutil: A Pre- and Post-processing Toolbox for Histological Rodent Brain Section Images. Front. Neuroinform. 14:37. doi: 10.3389/fninf.2020.00037

# Also described in
Yates SC, Groeneboom NE, Coello C, et al. & Bjaalie JG (2019) QUINT: Workflow for Quantification and Spatial Analysis of Features in Histological Images From Rodent Brain. Front. Neuroinform. 13:75. doi: 10.3389/fninf.2019.00075

# Changelog

0.5.11-0.5.38 ** 26.02.2020
- Updated CI script, testing
- Self-validator implemented in CI and updated to support csv etc

v0.5.11 *** 24.02.2020 
- Transform output tiff files do not get an extra ".tif" if the file already ends with ".tiff" or ".tif"

v0.5.10 *** 23.02.2020 
- Introduced changelog to the readme.md
- Nutil validator compares png pixels instead of binary data

v0.5.9 *** 23.02.2020 
- Fixed up Nutil validator output text to be clean
- Added qtiff.dll to the CI build of Nutil due to lack of native tiff support. TiffCreator should work now. 


 
