**Installation**
================================

Nutil is written as a stand-alone Windows 64-bit application written in Qt C++. The external libraries that are used in Nutil are Libtiff for fast and efficient TIFF file handling (http://www.libtiff.org/) and LibXLNT for excel file IO (https://github.com/tfussell/xlnt/).

**Download**: https://www.nitrc.org/projects/nutil/ 

Download as a zip archive file, save on the C:drive of your computer, extracted and run by double click on "Nutil.cmd". 

**System Requirements**
--------------------------
Nutil can be executed on either a server, desktop or laptop computer. It will employ all the cores available on the system. While there are no specific hardware limitations, the processing time is dependent on the system’s compute power. The more cores and memory available, the faster the operations will be performed. Running Nutil on a single-core laptop is also possible.


**Conditions of use**
--------------------------

**Licence**: GNU General Public License version 3.

**Citation**: For publication of QUINT results, please cite the QUINT workflow and Nutil articles and the reference atlas used for analysis.

* **Nutil:** Groeneboom NE, Yates SC, Puchades MA and Bjaalie JG (2020) Nutil: A Pre- and Postprocessing Toolbox for Histological Rodent Brain Section Images. Front. Neuroinform. 14:37. https://doi.org/10.3389/fninf.2020.00037

* **QUINT workflow:** Yates SC, Groeneboom NE, Coello C, Lichtenthaler SF, Kuhn P-H, Demuth H-U, HartlageRübsamen M, Roßner S, Leergaard T, Kreshuk A, Puchades MA and Bjaalie JG (2019) QUINT: Workflow for Quantification and Spatial Analysis of Features in Histological Images From Rodent Brain. Front. Neuroinform. 13:75. https://doi.org/10.3389/fninf.2019.00075.

* **Allen Mouse Brain Atlas Common Coordinate Framework version 3**: Wang et al. (2020). The Allen Mouse Brain Common Coordinate Framework: A 3D Reference Atlas. Cell. See the Allen institute `citation policy <https://alleninstitute.org/citation-policy/>`_.

* **Waxholm Space atlas of the Sprague Dawley rat brain**: Please refer to the atlas using RRID:SCR_017124, specify the atlas version(s) used, and cite the most recent publication (see the `citation policy. <https://www.nitrc.org/citation/?group_id=1081>`_). If your work makes use of previous atlas versions, or brain region descriptions detailed in earlier publications, please also cite the corresponding publication. 

* **Kim Unified Adult Mouse Brain Atlas**: Wang et al. (2020). The Allen Mouse Brain Common Coordinate Framework: A 3D Reference Atlas. Cell.

* **Developmental Mouse Brain Atlas**: We encourage researchers who use DeMBA to cite both the publication and dataset presenting DeMBA, and to specify the age of any template(s) used and the version of any segmentation(s) used. Publication: Carey et al (2025). DeMBA: a developmental atlas for navigating the mouse brain in space and time. Nat Commun 16, 8108. https://doi.org/10.1038/s41467-025-63177-9. Dataset: Carey et al. (2024). Developmental mouse brain atlas (DeMBA) with continuous coverage of postnatal day 4 to 56 (v1) [Data set]. EBRAINS. https://doi.org/10.25493/PWDG-536. Allen CCFv3 segmentations: Wang et al. (2020). The Allen Mouse Brain Common Coordinate Framework: A 3D Reference Atlas. Cell. https://doi.org/10.1016/j.cell.2020.04.007. KimLabDev segmentations: Kronman et al. (2024). Developmental mouse brain common coordinate framework. Nature Communications. https://doi.org/10.1038/s41467-024-53254-w.

**Release notes**
--------------------------

**Nutil v1.1 (Quantifier only)**: This is a major release of Nutil Quantifier with new atlases and new features.
 
* It incorporates new atlases: 1. Kim Unified Adult Mouse Brain Atlas, 2. Developmental Mouse Brain Atlas (DeMBA) with Allen CCFv3 or Kim Lab developmental delineations. 
* Option to extract coordinates corresponding to the centroids of objects ("centroids instead of all points").
* The object splitting feature has been renamed "counts or area fraction" (there is a bug with this feature, see warning below).
* Improved error messaging. 
* Updates to the help text in the Nutil GUI. 
* GUI improvements (e.g. new logo, updated citation info, redundant functionality removed). 
* The Transform, Resize and TiffCreator features in Nutil have been removed from this version (use Nutil v0.8.0). 

.. warning::
    There is a known issue with selection of "counts" or "area fraction" in Nutil v1.1.0. This means that even when "area fraction" is selected, it will perform the calculations as if "counts" were selected. In other words, it is not possible to achieve correct "area fraction" calculations for objects that overlap several atlas regions. If you need this functionality, please use Nutil v0.8.0. For objects that do not overlap atlas regions, the "counts" setting will calculate correct "area fraction".   

**Nutil v0.8.0**: This is a major release with several new features. This includes:

* Point clouds that reflect the nonlinear refinement applied with the VisuAlign software. 
* Updated object reports.
* Support for automatic generation of plots using Python scripts. These display the regional loads from the Reference Atlas reports and the Custom Region reports. 
* Support for defining the Custom Regions with hierarchy.txt files from the QCAlign software.
* Stop button in Nutil has been fixed.
* Improvements to error and warning messages.
* Updates to the help text in the Nutil GUI. 
* This version has been assigned DOI: 10.25790/bml0cm.107

**Nutil v0.7.0**: This release introduces a new reference atlas: the Waxholm Space Atlas of the Sprague Dawley rat v4 (WHSv4). The citation policy has been updated in the Nutil GUI and Nutil readthedoc for use of the Waxholm Space Atlas. The default customised regions for the WHSv3 have been updated. See the customised region.xlsx in the Nutil package for more information. 

* Bug 1 that was discovered in Nutil v0.5.0 and partially fixed in v0.6.0 has been fully fixed in this version: the regional load outputs in the slice reports are now correct irrespective of the pixel scale. 
* The user documentation has been considerably improved. All user manuals have been removed from the Nutil package, and replaced with a "user documentation" button in the Nutil GUI with a direct link to the Nutil readthedocs. These are updated on a regular basis, and also include user documentation for use of ilastik for the QUINT workflow. 
* Improvements to error and warning messaging, and updates to the help text in the Nutil GUI. 

**Nutil v0.6.0**: This release does not introduce new features but fixes recently discovered bugs affecting the Quantifier reports in some older versions of Nutil. As the bugs affected core Quantifier functionality, we have introduced more stringent quality assurance routines, with continuous integration  and automatic validation based on an expanded collection of ground truth datasets. We will provide more information about this in a future release.   

* Bug 1: Regional load output in the slice reports are incorrect for Nutil v0.4.0 – v0.5.0: the other results in the reports are correct. For Nutil v0.6.0_stable, Bug 1 has been fixed for Quantifier analyses run with a pixel scale = 1. A pixel scale of 1 is the default option in Nutil and will be applied in most cases. However, on application of a pixel scale > 1 or < 1, the regional load outputs in the slice reports remain erroneous. This will be fixed in the next version. 
* Bug 2: When using the mask feature: region pixels, region areas and loads in the reports are incorrect for Nutil v0.4.3 – v0.5.0. This bug does not affect analyses run without masks.

**Nutil v0.5.0**: Nutil version 0.407 included an upgrade to Qt 6. This introduced several major bugs due to Qt library updates. We have decided to delete this version entirely, and present Nutil v0.5.0 with upgrades and bug fixes to solve the issues found in Nutil v0.407:

* TiffCreator library fix.
* Improved XML error messaging to prevent spontaneous crashes.
* QuickNII and VisuAlign user manuals have been added to the Nutil package.
* There is a focus on usability improvements in the new release. This includes a scroll bar fix, improvements to file navigation, and improved error messaging. There are also several transform bug fixes.
* Support has been implemented in Quantifier for JSON files containing the registration information. Either the XML or JSON file from QuickNII, or the JSON file from VisuAlign may now be used to supply the linear anchoring information needed for coordinate extraction. 
* Support has also been implemented for navigation to masks from a separate folder, and not from the segmentation folder as in earlier versions.
* There have been updates to the text in the Nutil GUI, and an extensive user manual update.

**Nutil 0.403**: Significant improvements to the Quantifier reports including a bug fix for region area quantifications (the previous version had a slight rounding up error; old reports are still useable, but we recommend switching to the latest version). The Transform feature now supports import of file names and transformation parameters from an Excel template titled "TransformTemplate" (included in the Nutil package).

**Nutil 0.402**: Several bug fixes including a major fix for Nutil Quantifier analysis with WHS rat atlas v3. Updated Nutil user manual and new ilastik user manual. 

**Nutil 0.4.01**: Two minor bug fixes and command line interface script for batch processing added. 

**Nutil 0.4**: Major release with new GUI. Bug fixes and performance improvements. Improved error messaging. Detailed help text for every input parameter. New resize feature implemented. Command line version. 

**Nutil 0.33**: Download the Nutil Windows Binaries and extract the zip file. When running the main program "Nutil.cmd", the executable will automatically check for and download new versions.The package includes a user manual and an example template. 







