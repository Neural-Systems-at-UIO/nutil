**Installation and citation**
------------------------------

**System Requirements**
~~~~~~~~~~~~~~~~~~~~~~~~
- Nutil can be executed on either a server, desktop or laptop computer. 
- It will employ all the cores available on the system. 
- While there are no specific hardware limitations, the processing time is dependent on the system’s compute power. The more cores and memory available, the faster the operations will be performed. Running Nutil on a single-core laptop is also possible.
- Nutil version 0.8.0 and above has an automatic plotting feature. This will work if Python is installed on the computer with the Python.exe selected in Nutil through: File –> Settings. It is also necessary to install the following Python packages on your computer: numpy, pandas and matplotlib. 

**Technical information**

Nutil is written as a stand-alone Windows 64-bit application written in Qt C++, which enables the full usage of both memory and processor cores. When performing batch processes, Nutil will utilise all cores available on the system.  

The external libraries that are used in Nutil are: 
* Libtiff for fast and efficient TIFF file handling (http://www.libtiff.org/) 
* LibXLNT for excel file IO (https://github.com/tfussell/xlnt/) 

**TiffCreator**: TiffCreator produces tiled TIFF files from JPEG, PNG and standard TIFF images, and employs the support of multiple CPUs for efficient, parallelised operations. 

**Transform**: Transform enables rotations, scaling and thumbnail compilation of large tiff files (currently up to 4GB).  

**Quantifier**: Quantifier identifies individual binary objects in a PNG file, while matching these to output from QuickNII. The method first finds and sorts areas by using a standard pixel filler routine. Afterwards, a random area pixel is chosen as the look-up in the binary QuickNII label slice for this particular image. When all areas have been assigned a label ID, multiple selections of predefined area IDs are assembled (ID list from the excel input file), and finally output reports are assembled and written to disk (in xlsl format). In addition, original ilastik .png files with colour/ID coding added to underlying atlas slice data are assembled and saved to the output folder.

**Download**

https://www.nitrc.org/projects/nutil/ 

- Download as a zip archive file, save on the C:drive of your computer, extracted and run by double click on "Nutil.cmd". 
- No installation executable is necessary, and the directory can be moved around the file system as required. Settings data are stored in the local program folder.

**Conditions of use**
~~~~~~~~~~~~~~~~~~~~~~~~

**Licence**: GNU General Public License version 3.

**Acknowledgements**: Nutil was developed with support from the EBRAINS infrastructure, and funding from the European Union’s Horizon 2020 Framework Programme for Research and Innovation under the Framework Partnership Agreement No. 650003 (HBP FPA).

**Citation of the tool**

* **Nutil:** Groeneboom NE, Yates SC, Puchades MA and Bjaalie JG (2020) Nutil: A Pre- and Postprocessing Toolbox for Histological Rodent Brain Section Images. Front. Neuroinform. 14:37. https://doi.org/10.3389/fninf.2020.00037

* **QUINT workflow:** Yates SC, Groeneboom NE, Coello C, Lichtenthaler SF, Kuhn P-H, Demuth H-U, HartlageRübsamen M, Roßner S, Leergaard T, Kreshuk A, Puchades MA and Bjaalie JG (2019) QUINT: Workflow for Quantification and Spatial Analysis of Features in Histological Images From Rodent Brain. Front. Neuroinform. 13:75. https://doi.org/10.3389/fninf.2019.00075.

**Citation of the reference atlases used in the tool**

* **Allen Mouse Brain Atlas Common Coordinate Framework version 3**: Wang et al. (2020). The Allen Mouse Brain Common Coordinate Framework: A 3D Reference Atlas. Cell. See the Allen institute `citation policy <https://alleninstitute.org/citation-policy/>`_.

* **Waxholm Space atlas of the Sprague Dawley rat brain version 2 , 3 and 4:** Please refer to the atlas using RRID:SCR_017124, specify the atlas version(s) used, and cite the most recent publication (see the `citation policy. <https://www.nitrc.org/citation/?group_id=1081>`_). If your work makes use of previous atlas versions, or brain region descriptions detailed in earlier publications, please also cite the corresponding publication.
  * WHS version 4: Kleven et al. (2023) Waxholm Space atlas of the rat brain: a 3D atlas supporting data analysis and integration. Nat Methods.
  * WHS version 3: Osen etl al. (2019) Waxholm Space atlas of the rat brain auditory system: Three-dimensional delineations based on structural and diffusion tensor magnetic resonance imaging. NeuroImage 199, 38-56. 
  * WHS version 2: Kjonigsen et al. (2015) Waxholm Space atlas of the rat brain hippocampal region: Three-dimensional delineations based on magnetic resonance and diffusion tensor imaging. NeuroImage 108, 441-449. 
  * WHS version 1: Papp et al. (2014) Waxholm Space atlas of the Sprague Dawley rat brain. NeuroImage 97, 374-386.

* **Kim Unified Adult Mouse Brain Atlas**: * Wang et al. (2020). The Allen Mouse Brain Common Coordinate Framework: A 3D Reference Atlas. Cell.

* **Developmental Mouse Brain Atlas**. We encourage researchers who use DeMBA to cite both the dataset and publication presenting DeMBA, and to specify the age of any template(s) used and the version of any segmentation(s) used.

  * Article: Carey et al. (2024) DeMBA: a developmental atlas for navigating the mouse brain in space and time. bioRxiv. https://doi.org/10.1101/2024.06.14.598876
  * Dataset: Carey et al. (2024). Developmental mouse brain atlas (DeMBA) with continuous coverage of postnatal day 4 to 56 (v1) [Data set]. EBRAINS. https://doi.org/10.25493/PWDG-536
  * Allen CCFv3 segmentations: Wang et al. (2020). The Allen Mouse Brain Common Coordinate Framework: A 3D Reference Atlas. Cell. https://doi.org/10.1016/j.cell.2020.04.007 
  * KimLabDev segmentations: Kronman et al. (2024). Developmental mouse brain common coordinate framework. Nature Communications. https://doi.org/10.1038/s41467-024-53254-w









