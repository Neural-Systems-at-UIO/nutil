**Custom masks explained**
===========================

The mask feature is optional. It allows the application of masks to define which parts of the sections to include in the analysis. The mask is applied in addition to, and not instead of, the reference atlas maps. This is particularly useful for investigating expression differences in the right and left hemisphere, as a mask can be applied to differentiate the two sides.  

* Create binary masks (black and white) in PNG format with an application such as NIH ImageJ, Adobe Photoshop or GIMP. These should have the same proportions as the segmentations but are typically smaller in size.

.. note::
   QMask is a small desktop tool developed in-house that enables automatic generation of masks to differentiate the right and left hemisphere. The tool is applied to the QuickNII or VisuAlign JSON and thereby creates masks that are customized for the image series. This tool has not yet been published but is available at request: contact user support.  

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
