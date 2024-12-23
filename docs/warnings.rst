**Warnings and error messages**
==================================

Quantifier
-----------


.. warning::
   WARNING: Some of the area matrices were not initialized.

* The JSON or XML file contains info about sections that are not included in the analysis: for example, if you run an analysis for a few sections only. 
* This is not a problem, the analysis will generate correct results, but alerts you to missing sections in case this was not intended. 


.. warning::
   WARNING: Could not find data in .xml or .json file for slice '_s001', so 3D data will be incorrect. Please make sure that there exists a corresponding field in the xml or json file!
   
This means what it says: Nutil can't find the relevant anchoring information in the .json file. This can happen for a number of reasons.

* The slice is missing in the .json file. Open the .json file in a text editor such as notebook and check.
* The slice is missing anchoring information. This happens if it has not been registered to the reference atlas in QuickNII or VisuAlign. Sometimes it happens because the registration info has not been saved in QuickNII for the slice (remember to confirm the registration!).
* The default ID format is selected in Nutil Quantifier (_sXXX), but the slice ID does not match this format. In this case, switch to "user" defined ID and define the ID using RegEx. It is also possible that the RegEx is incorrect: make sure it correspond to the ID.   
* The slice ID does not match the ID in the corresponding segmentation and atlas map. In this case, the IDs have to be revised so that they match across the board. We recommend using the _sXXX format.  

.. warning::
   ERROR: Could not find FLAT files that contains: _001.
   
* This means that there is a discrepancy in the atlasmaps and segmentation: Nutil will fail to run if there is a discrepancy. 
* To fix this, either add the FLAT file for the missing section or remove the segmentation with this ID from the segmentation directory. 

.. warning::
   WARNING: Unrecognised atlas map in the anchor file. Might be a potential problem, please make sure the atlas is correct! 
   
* Automatic atlas recognition was implemented in Nutil v0.8.0. This means that Nutil selects the atlas version based on the information in the .xml or .json file, rather than relying on the atlas selected by the user in the Nutil interface. This works for the AMBA CCF for the latest versions of QuickNII and VisuAlign, but is not implemented correctly for the rat brain. 
* This warning will come up if older versions of QuickNII are used, or if the WHS atlas is selected. This is not a problem as Nutil will instead use the atlas selected by the user in the Nutil interface. If in doubt, open the .json file to check the atlas version. 


Transform
-----------

.. warning::
   TIFFAppendtoStrip: Maximum TIFF file size exceeded.
   
* Nutil cannot transform or generate images that are larger than 4 GB: this warning means the images exceed this limit. 
* This may happen even if the images do not exceed 4 GB since rotation adds extra space to the image corners to retain the rectangular shape of the image. 
* If the original images are below 4GB but you get this warning, select JPEG compression. This will reduce the size of the images that are generated. 
   
  
