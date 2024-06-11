**Custom masks explained**
===========================

The mask feature is optional. It allows the application of masks to define which parts of the sections to include in the analysis. The mask is applied in addition to, and not instead of, the reference atlas maps. This feature is useful for investigating expression differences in the right and left hemisphere as masks can be applied to differentiate the two sides. It is also useful for defining areas to exclude from the analysis (for example, in the case of hemibrain sections). 

To use masks:

* Create binary masks that correspond to your sections with an application such as NIH ImageJ, Adobe Photoshop or GIMP (these are black and white images in PNG format). For hemibrain masks, use QuickMask (instructions below). 
* The masks should have the same proportions as the segmentations but are typically smaller in size. 
* The masks must be named with the unique ID for the section with a “_mask” extension. File name example: Bxb_hgt_s002_mask.

.. tip::
   **QuickMask** and **QuickMaskNL** are desktop tools that allow you to automatically create hemisphere masks that correspond to your sections based on an atlas-registration using QuickNII or VisuAlign. Peliminary versions are available for download on the NITRC page for QuickNII (QuickMask) and VisuAlign (QuickMaskNL). 

In Nutil:

* To use the mask feature, select “yes”. This brings up a “custom mask folder” and “Custom mask colour” option.  
* Navigate to this folder containing the masks.  
* Click on the field for the “Custom mask colour”. Select the colour in the mask that corresponds to the ROI to include in the analysis. For example, for an analysis of the left hand side of an image with the mask shown here, specify black (RGB code: 0,0,0). 

+-----------+
| |image16| |
+-----------+


QuickMask
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

QuickMask is a simple tool for generating hemibrain masks that are compatible with the Nutil software.

There are two versions of QuickMask. They work in the same way.

**QuickMask:** generates hemibrain masks that reflect the linear registration performed with QuickNII (download on the nitrc page for QuickNII). 

**QuickMask-NL:** generates hemibrain masks that reflect the nonlinear adjustments applied with VisuAlign (download on the nitrc page for VisuAlign).

1. Open the QuickMask tool.
2. Use the “pick JSON” button to navigate to the QuickNII JSON or VisuAlign JSON for your image series (the file that contains the registration information). 
3. For left-right hemisphere masks, enter the following X, Y and Z coordinated in QuickMaskNL. 

Top left: 227, 32.2, 292.8. 
Top right: 227, 367.9, 291.8
Bottom left: 227, 34.5, 48.7 

Alternatively, enter the following coordinate string in the box at the bottom of the interface: 227 32.2 292.8 227 367.9 291.8 227 34.5 48.7

4. Use the “Destination” button to navigate to the folder where you want your masks to be saved.
5. Press Go. The masks are automatically generated for all the section images in the series. The masks have the original image file name with a _mask extension. 

.. |image16| image:: cfad7c6d57444e3b93185b655ab922e0/media/image10.png
   :width: 3.58in
   :height: 2.57in
   
   
   
   
