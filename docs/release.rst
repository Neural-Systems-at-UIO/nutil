**Release notes**
--------------------------
**Nutil v1 (Quantifier only)**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is a major release of Nutil Quantifier with several new atlases and new features. It will be officially released on NITRC soon (available as a pre-release on the Nutil Github). 

* The Transform, Resize and TiffCreator features in Nutil have been removed from this version (use Nutil v0.8.0).  
* It incorporates several new atlases: the Kim Unified Adult Mouse Brain Atlas, and the Developmental Mouse Brain Atlas (DeMBA) with Allen CCFv3 or Kim Lab developmental delineations. 
* Option to extract coordinates corresponding to the centroids of objects ("centroids instead of all points").
* For clarity, The object splitting feature has been renamed "counts or area fraction?".
* Improved error messaging. 
* Updates to the help text in the Nutil GUI. 
* GUI improvements (e.g. new logo, updated citation info, redundant functionality removed). 

**Nutil v0.8.0** 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is a major release with several new features. This includes:

* Point clouds that reflect the nonlinear refinement applied with the VisuAlign software. 
* Updated object reports.
* Support for automatic generation of plots using Python scripts. These display the regional loads from the Reference Atlas reports and the Custom Region reports. 
* Support for defining the Custom Regions with hierarchy.txt files from the QCAlign software.
* Stop button in Nutil has been fixed.
* Improvements to error and warning messages.
* Updates to the help text in the Nutil GUI. 
* This version has been assigned DOI: 10.25790/bml0cm.107


**Nutil v0.7.0**
~~~~~~~~~~~~~~~~~~~~~~~~

* This release introduces a new reference atlas: the Waxholm Space Atlas of the Sprague Dawley rat v4 (WHSv4). The citation policy has been updated in the Nutil GUI and Nutil readthedoc for use of the Waxholm Space Atlas. 
* The default customised regions for the WHSv3 have been updated. See the customised region.xlsx in the Nutil package for more information. 
* Bug 1 that was discovered in Nutil v0.5.0 and partially fixed in v0.6.0 has been fully fixed in this version: the regional load outputs in the slice reports are now correct irrespective of the pixel scale. 
* The user documentation has been considerably improved. All user manuals have been removed from the Nutil package, and replaced with a "user documentation" button in the Nutil GUI with a direct link to the Nutil readthedocs. These are updated on a regular basis, and also include user documentation for use of ilastik for the QUINT workflow. 
* Improvements to error and warning messaging, and updates to the help text in the Nutil GUI. 


**Nutil v0.6.0**
~~~~~~~~~~~~~~~~~~~~~~~~

This release does not introduce new features but fixes recently discovered bugs affecting the Quantifier reports in some older versions of Nutil.  

*Bug 1*: Regional load output in the slice reports are incorrect for Nutil v0.4.0 – v0.5.0: the other results in the reports are correct. For Nutil v0.6.0_stable, Bug 1 has been fixed for Quantifier analyses run with a pixel scale = 1. A pixel scale of 1 is the default option in Nutil and will be applied in most cases. However, on application of a pixel scale > 1 or < 1, the regional load outputs in the slice reports remain erroneous. This will be fixed in the next version. 

*Bug 2*: When using the mask feature: region pixels, region areas and loads in the reports are incorrect for Nutil v0.4.3 – v0.5.0. This bug does not affect analyses run without masks.

As the bugs affected core Quantifier functionality, we have introduced more stringent quality assurance routines, with continuous integration  and automatic validation based on an expanded collection of ground truth datasets. We will provide more information about this in a future release. 



**Nutil v0.5.0**
~~~~~~~~~~~~~~~~

Nutil version 0.407 included an upgrade to Qt 6. This introduced several major bugs due to Qt library updates. We have decided to delete this version entirely, and present Nutil v0.5.0 with upgrades and bug fixes to solve the issues found in Nutil v0.407:

* Upper size limit for the "segmentation" input files has been removed.
* TiffCreator library fix.
* Improved XML error messaging to prevent spontaneous crashes.
* QuickNII and VisuAlign user manuals have been added to the Nutil package.

The release notes that followed version 0.407 still apply:

* There is a focus on usability improvements in the new release. This includes a scroll bar fix, improvements to file navigation, and improved error messaging. There are also several transform bug fixes.
* Support has been implemented in Quantifier for JSON files containing the registration information. Either the XML or JSON file from QuickNII, or the JSON file from VisuAlign may now be used to supply the linear anchoring information needed for coordinate extraction. 
* Support has also been implemented for navigation to masks from a separate folder, and not from the segmentation folder as in earlier versions.
* There have been updates to the text in the Nutil GUI, and an extensive user manual update.

**Nutil 0.403**
~~~~~~~~~~~~~~~~

* Significant improvements to the Quantifier reports including a bug fix for region area quantifications (the previous version had a slight rounding up error; old reports are still useable, but we recommend switching to the latest version). 
* The Transform feature now supports import of file names and transformation parameters from an Excel template titled "TransformTemplate" (included in the Nutil package).
* Improvements to the inbuilt help text throughout. User manual updates.

**Nutil 0.402**
~~~~~~~~~~~~~~~~

Several bug fixes including a major fix for Nutil Quantifier analysis with WHS rat atlas v3. Updated Nutil user manual and new ilastik user manual. 

**Nutil 0.4.01**
~~~~~~~~~~~~~~~~

Two minor bug fixes and command line interface script for batch processing added. 

**Nutil 0.4**
~~~~~~~~~~~~~~

Major release with new GUI. Bug fixes and performance improvements. Improved error messaging. Detailed help text for every input parameter. New resize feature implemented. Command line version. 

**Nutil 0.33**
~~~~~~~~~~~~~~
Download the Nutil Windows Binaries and extract the zip file. When running the main program "Nutil.cmd", the executable will automatically check for and download new versions.The package includes a user manual and an example template. 
