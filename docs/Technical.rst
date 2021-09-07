**Technical information**
-------------------------

Nutil is written as a stand-alone Windows 64-bit application written in Qt C++, which enables the full usage of both memory and processor cores. Nutil can be downloaded and compiled from the github page. When performing batch processes, Nutil will utilise all cores available on the system.  

The external libraries that are used in Nutil are: 
 
* Libtiff for fast and efficient TIFF file handling (http://www.libtiff.org/) 
* LibXLNT for excel file IO (https://github.com/tfussell/xlnt/) 

**TiffCreator**

TiffCreator produces tiled TIFF files from JPEG, PNG and standard TIFF images, and employs the support of multiple CPUs for efficient, parallelised operations. 

**Transform** 

Transform enables rotations, scaling and thumbnail compilation of large tiff files (currently up to 4GB).  

**Quantifier**

Quantifier identifies individual binary objects in a PNG file, while matching these to output from QuickNII. The method first finds and sorts areas by using a standard pixel filler routine. Afterwards, a random area pixel is chosen as the look-up in the binary QuickNII label slice for this particular image. When all areas have been assigned a label ID, multiple selections of predefined area IDs are assembled (ID list from the excel input file), and finally output reports are assembled and written to disk (in xlsl format). In addition, original ilastik .png files with colour/ID coding added to underlying atlas slice data are assembled and saved to the output folder. 

**Authors**

Nicolaas E Groeneboom, Sharon C. Yates, Maja A. Puchades, Jan G. Bjaalie. 

**Licence**

Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International 

**Cite**

Groeneboom NE, Yates SC, Puchades MA and Bjaalie JG (2020) Nutil: A Pre- and Postprocessing Toolbox for Histological Rodent Brain Section Images. Front. Neuroinform. 14:37. doi: 10.3389/fninf.2020.00037

**Also described in** 

Yates SC, Groeneboom NE, Coello C, Lichtenthaler SF, Kuhn P-H, Demuth H-U, HartlageRübsamen M, Roßner S, Leergaard T, Kreshuk A, Puchades MA and Bjaalie JG (2019) QUINT: Workflow for Quantification and Spatial Analysis of Features in Histological Images From Rodent Brain. Front. Neuroinform. 13:75. doi: 10.3389/fninf.2019.00075. 

**Acknowledgements**

Nutil is developed by the Neural Systems Laboratory at the Institute of Basic Medical Sciences, University of Oslo, Norway, with support from the EBRAINS infrastructure, and funding from the European Union’s Horizon 2020 Framework Programme for Research and Innovation under the Framework Partnership Agreement No. 650003 (HBP FPA).

**Release notes**

Can be found here https://www.nitrc.org/frs/?group_id=1365 

**Contact us** 

For user support and to report issues contact us at: support@ebrains.eu
