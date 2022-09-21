**Custom masks explained**
===========================

The mask feature is optional. It allows the application of masks to define which parts of the sections to include in the analysis. The mask is applied in addition to, and not instead of, the reference atlas maps. This is particularly useful for investigating expression differences in the right and left hemisphere, as a mask can be applied to differentiate the two sides.  

* Create binary masks (black and white) in PNG format with an application such as NIH ImageJ, Adobe Photoshop or GIMP. These should have the same proportions as the segmentations but are typically smaller in size.

.. note::
   **QuickMask** is a desktop tool that automatically generates masks to differentiate the right and left hemisphere based on the QuickNII or VisuAlign registration. Peliminary versions of QuickMask tool are available for download on the respective NITRC pages for the tools. There are two versions: one that generates masks based on the linear registration performed with QuickNII, and another that generates masks that reflect the nonlinear adjustments applied with VisuAlign. Contact user support for the user manual.  

* To use the mask feature, select “yes”. This brings up a “custom mask folder” and “Custom mask colour” option.  
* Name these with the unique ID for the section and a “_mask” extension. File name example: Bxb_hgt_s002_mask 
* Navigate to this folder containing the masks.  
* Click on the field for the “Custom mask colour”. Select the colour in the mask that corresponds to the ROI to include in the analysis. For example, for an analysis of the left hand side of an image with the mask shown here, specify black (RGB code: 0,0,0). 



+-----------+
| |image16| |
+-----------+

|

.. |image16| image:: cfad7c6d57444e3b93185b655ab922e0/media/image10.png
   :width: 3.58in
   :height: 2.57in
