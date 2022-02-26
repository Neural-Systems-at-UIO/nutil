**Preparing the input files**
==============================

**File naming requirement**
-------------------------------

**It is strongly recommended to change the file names of the histological images as the first step of the QUINT workflow.** 

**By using images that follow the file naming convention for ilastik, QuickNII and VisuAlign, the output files from these software will also comply with the naming convention, and are thereby directly compatible with Nutil Quantifier.**

* The file name of the segmentation and the atlas map that corresponds to a particular section must contain the same unique ID, and should follow the _sXXX... file naming convention, with XXX.. representing the section number (this is not restricted to three digits, sXXXXX... is also fine). 

* The section number should reflect the serial order and spacing of the sections as this is a requirement for QuickNII. For example, _s02, _s06, _s10 for every 4th section starting with section 2. 

* The unique IDs must also be present in the XML or JSON file containing the registration information (check this by opening with Notepad). This happens automatically as long as the file names of the images that are used for the QuickNII registration contain the unique IDs.

* Nutil Quantifier also supports user-defined IDs using regular expressions – RegExp. This means that it is possible to get round the _sXXX... naming convention. While this is not recommended, it is useful in some cases. For more information see the “help” button in the Nutil GUI or contact user support.  

**Examples that comply with the naming convention:** 

Histological image: tg2345_MMSH_s001.png. 

Segmentation image: tg2345_MMSH_s001_segmentation.png. 

Atlas map: tg2345_MMSH_s001_nl.flat

It is fine to include a string of letters and numbers followed by the unique ID. As Quantifier scans and detects the "_s" part of the name, the file name should not contain additional "_s". Example that would not work: tg2345_MMSH_ss_s001.png.


**Preparing the Segmentations**
------------------------------------
 
Any image analysis software may be used to generate the segmentations as long as the segmentations meet the requirements listed below. 

**Requirement:**

* Image Format: Must be indexed 8-bit or 24-bit RGB images in PNG format.
  
* Image proportions: Must have the same proportions as the histological images used to generate the atlas maps. Note: They do not have the same proportions as the actual atlas maps as QuickNII alters the proportions slightly. 

* Image size: They do not need to be the same size as the images used to generate the atlas maps, and are typically larger in size.

 **We do not recommend running Quantifier on segmented PNG images larger than around 10000x10000 pixels. While Nutil supports segmentations of any size up to this limit - as long as there is enough memory installed on the computer, it is highly recommended to downscale the histological images as much as possible before segmenting them.** 

 Downscaling has several advantages. It improves the quality of the segmentation as it removes noise from the image, and makes them more compatible with the machine learning   algorithms used by ilastik (see the ilastik section of the Read the Doc for more info). It will also speed up the Nutil analysis a lot, and will prevent crashes due to insufficient memory. The aim here is to downscale as much as possible but without losing information from the images that is actually important. The downscaling factor is determined by trial and error and should be applied consistenty to all the images in the series. 

* Internal properties: Quantifier is only able to extract one Red Green Blue (RGB) colour at a time. Apply one RBG colour to all of the objects of interest, and specify this colour code in the Nutil GUI. For example, the objects in the segmentation here are red, so extract RGB colour: 255,0,0.
  
+----------+
| |image11||
+----------+

**Software recommendations**

**Ilastik**: We recommend the Pixel and Object Classification workflows in the ilastik software to generate the segmentations, with the Glasbey lookup table applied with Fiji to visualise the output. See the ilastik section of this Read the Doc for instructions. ilastik is available to download here: http://ilastik.org/download.html. 

**QuPath**: QuPath is an alternative that can be used to generate the segmentations. https://qupath.github.io/

**Fiji**: Fiji is also useful https://imagej.net/software/fiji/ 


**Preparing the Atlas Maps** 
--------------------------------
 
The atlas maps are generated with QuickNII, which applies linear registration of the sections to the atlas, or with VisuAlign that applies nonlinear refinement to an existing QuickNII registration. The VisuAlign atlas maps are thereby typically more accurate than the QuickNII atlas maps, but also take more time to produce. The atlas maps are customised to match the cutting plane and proportions of the brain sections. 

File format: The atlas maps are in .FLAT format and cannot be viewed directly. The image below shows the information contained in an atlas map, but is not the .FLAT file itself.

+----------+
| |image12||
+----------+


**QuickNII**
~~~~~~~~~~~~

* QuickNII is a standalone software for affine spatial registration (anchoring) of section images - typically high resolution histological images - to a reference atlas such as the Allen Mouse Brain Atlas or the Waxholm Atlas of the Sprague Dawley Rat. In QuickNII, the reference atlas is transformed to match anatomical landmarks in the experimental images. In this way, the spatial relationship between experimental image and atlas is defined, without introducing transformations in the original experimental images. 

* Once all the sections are registered, QuickNII may be used to generate atlas maps that match the cutting plane and proportions of the experimental image data. The anchoring information (coordinates) is saved and stored in an XML or JSON file.   

* The registration is user-guided with some automation. Following anchoring of a limited number of sections containing key landmarks, transformations are propagated across the entire series of images to reduce the manual work required. These propagations must be validated by visual inspection and typically require fine adjustments for most sections. A user manual is provided here: https://quicknii.readthedocs.io/en/latest/ 

**VisuAlign**
~~~~~~~~~~~~~~

* VisuAlign is a standalone software for applying nonlinear refinements (inplane) to an existing affine 2D-to-3D registration. The 2D-to-3D registration is performed with QuickNII and stored in the JSON file. It is used to make manual adjustments to the atlas maps to better match the sections. The adjustments are nonlinear.  

* Open the JSON file from QuickNII in VisuAlign and apply adjustments by simple drop and drag of markers placed on the image. The adjusted atlas maps may be exported in .FLAT format. VisuAlign does not update the linear coordinate information contained in the JSON file. A user manual is provided here: https://visualign.readthedocs.io/en/latest/

Visit and download QuickNII and VisuAlign here: https://ebrains.eu/service/quicknii-and-visualign 


**Preparing the XML or JSON file**
-------------------------------------
 
Either the XML or JSON file from QuickNII, or the JSON file from VisuAlign may be used here. 

Note: Nonlinear adjustment of the atlas maps with VisuAlign does not alter the linear coordinate information contained in the file. The linear coordinate information is the part that is extracted to generate the coordinate output and so any file may be used.  

**Make sure your XML or JSON file has anchoring information for every section image in your dataset.**



.. |image1| image:: cfad7c6d57444e3b93185b655ab922e0/media/image2.png
   :width: 6.30139in
   :height: 2.33688in
.. |image2| image:: cfad7c6d57444e3b93185b655ab922e0/media/image3.png
   :width: 6.30139in
   :height: 2.95442in
.. |image3| image:: cfad7c6d57444e3b93185b655ab922e0/media/image4.png
   :width: 6.30139in
   :height: 3.52274in
.. |image4| image:: cfad7c6d57444e3b93185b655ab922e0/media/image5.png
   :width: 6.30139in
   :height: 2.87841in
.. |image5| image:: cfad7c6d57444e3b93185b655ab922e0/media/image5.png
   :width: 6.30139in
   :height: 2.87841in
.. |image6| image:: cfad7c6d57444e3b93185b655ab922e0/media/image5.png
   :width: 6.30139in
   :height: 2.87841in
.. |image7| image:: cfad7c6d57444e3b93185b655ab922e0/media/image6.png
   :width: 2.05417in
   :height: 1.39783in
.. |image8| image:: cfad7c6d57444e3b93185b655ab922e0/media/image7.png
   :width: 1.76111in
   :height: 1.39185in
.. |image9| image:: cfad7c6d57444e3b93185b655ab922e0/media/image6.png
   :width: 2.05417in
   :height: 1.39783in
.. |image10| image:: cfad7c6d57444e3b93185b655ab922e0/media/image7.png
   :width: 1.76111in
   :height: 1.39185in
.. |image11| image:: cfad7c6d57444e3b93185b655ab922e0/media/image6.png
   :width: 4.1in
   :height: 2.8in
.. |image12| image:: cfad7c6d57444e3b93185b655ab922e0/media/image7.png
   :width: 3.5in
   :height: 2.8in
.. |image13| image:: cfad7c6d57444e3b93185b655ab922e0/media/image8.png
   :width: 5.90694in
   :height: 2.724in
.. |image14| image:: cfad7c6d57444e3b93185b655ab922e0/media/image10.png
   :width: 1.79722in
   :height: 1.28892in
.. |image15| image:: cfad7c6d57444e3b93185b655ab922e0/media/image10.png
   :width: 1.79722in
   :height: 1.28892in
.. |image16| image:: cfad7c6d57444e3b93185b655ab922e0/media/image10.png
   :width: 1.79722in
   :height: 1.28892in
.. |image17| image:: cfad7c6d57444e3b93185b655ab922e0/media/image14.png
   :width: 2.30556in
   :height: 1.53537in
.. |image18| image:: cfad7c6d57444e3b93185b655ab922e0/media/image14.png
   :width: 2.30556in
   :height: 1.53537in
.. |image19| image:: cfad7c6d57444e3b93185b655ab922e0/media/image14.png
   :width: 2.30556in
   :height: 1.53537in
.. |image20| image:: cfad7c6d57444e3b93185b655ab922e0/media/image16.png
   :width: 2.59306in
   :height: 3.53443in
.. |image21| image:: cfad7c6d57444e3b93185b655ab922e0/media/image16.png
   :width: 2.59306in
   :height: 3.53443in
.. |image22| image:: cfad7c6d57444e3b93185b655ab922e0/media/image16.png
   :width: 2.59306in
   :height: 3.53443in
