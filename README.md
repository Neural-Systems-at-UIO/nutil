# Nutil
Nutil aims to both simplify and streamline the mechanism of pre-and-post processing 2D brain image data from mouse and rat. Nutil is developed as a stand-alone application that runs on all operating systems requiring little-to-no experience to execute. The user specifies the path to the input and output directories and the parameters for the pre-and post processing operations in the Nutil GUI. Pre-processing operations include conversion of images from JPEG/PNG format to tiled TIFF format, 2D transformations of extremely large tiled TIFF files (rotation, flipping and scaling), in addition to renaming, copying and downsizing. Post-processing is based on analysis of segmented images in the context of brain regions defined by a reference atlas, such as the Allen Mouse Brain reference atlas or the Waxholm Space Atlas of the Sprague Dawley rat brain. All functions operate in batch mode, and operate in parallel on multiple CPUs.
# Getting started

The Nutil software is available for download from https://www.nitrc.org/projects/nutil/

Nutil is written in C++ using standard Qt libraries, and is optimised for parallel operations on multiple CPUs. Nutil does not require any installation, and does not currently utilise any GPU extensions. The external libraries that are used in Nutil are: 
- Libtiff for fast and efficient TIFF file handling (http://www.libtiff.org/)
- LibXLNT for Excel file I/O (https://github.com/tfussell/xlnt/)

# Prerequisites
In order to compile from scratch, the following software components are also required:
- The “lelib” library: https://github.com/leuat/lelib/).
- Microsoft Visual C++ compiler (MSVC)
- Qt Creator 5+

Nutil can be compiled to work on Mac/Linux with little effort.
Nutil contains an auto updater that checks the servers for a new version on each run. If a new 173 version is found, it is downloaded and extracted automatically.

# Authors
Nicolaas E Groeneboom, Sharon C Yates, Maja A Puchades, Jan G Bjaalie. 
# Licence
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International

# Cite
Nutil is a key component of the QUINT workflow for quantification and spatial analysis of labelled features in histological rodent brain section images: 

Yates SC, Groeneboom NE, Coello C, et al. & Bjaalie JG (2019) QUINT: Workflow for Quantification and Spatial Analysis of Features in Histological Images From Rodent Brain. Front. Neuroinform. 13:75. doi: 10.3389/fninf.2019.00075

# Acknowledgements
Nutil was development with support from the European Union’s Horizon 2020 Framework Programme for Research and Innovation under the Specific Grant Agreement No. 720270 (Human Brain Project SGA1) and Specific Grant Agreement No. 785907 (Human Brain Project SGA2).
