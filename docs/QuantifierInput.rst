**Preparing the input files**
==============================

**File naming requirement**
-------------------------------

* The file names of the *segmentation files* and the *atlas maps* that correspond to a particular section image must contain the same unique ID. These unique IDs must also be present in the XML or JSON file containing the anchoring information. This happens automatically as long as the images that are anchored with QuickNII contain the unique IDs.

* By default Quantifier supports IDs in the format: _sXXX.., with XXX.. representing the section number. The section number should reflect the serial order and spacing of the sections as this is a requirement for the QuickNII software (e.g. _s002, _s006, _s010 for every 4th section starting with section 2). Example: tg2345_MMSH_s001_segmentation.png. It is fine to include a string of letters and numbers followed by the unique ID. As Quantifier scans and detects the "_s" part of the name, the file name should not contain additional "_s". Example that would not work: tg2345_MMSH_ss_s001.png.

**As the _sXXX naming convention applies to both QuickNII and Quantifier, we strongly recommend changing the file names as the first step in the QUINT workflow. This can be done with Transform.**

* Quantifier also supports user-defined IDs using regular expressions – RegExp. This means that it is possible to get round the _sXXX... naming convention. While this is not recommended, it is useful in some cases. For more information on this see the “help” button in the Nutil GUI or contact user support.  


**Preparing the segmentations**
------------------------------------
 
Any image analysis software may be used to generate the segmentations as long as they meet the requirements listed below. 

**Requirement:**

* Must be indexed 8-bit or 24-bit RGB images in PNG format.
  
* Must have the same proportions as the images used to generate the atlas maps (not the same proportions as the actual atlas maps as QuickNII alters the proportions slightly). They do not need to be the same size as the images used to generate the atlas maps, and are typically larger in size.
  
* Quantifier is only able to extract one RGB (Red Green Blue) colour at a time. Apply one RBG colour to all of the objects of interest, and specify this colour code in the GUI (e.g. the objects in the segmentation here are red, which is RGB colour code: 255,0,0).
  
+----------+
| |image11||
+----------+


**Software recommendations**

**Ilastik**: We recommend the pixel and Object Classification workflows in the ilastik software to generate the segmentations, with the Glasbey lookup table applied with Fiji to visualise the output. See the ilastik section of this ReadtheDoc for instructions. ilastik is available to download at: http://ilastik.org/download.html. 

**QuPath**: QuPath is an alternative that can be used to generate the segmentations. https://qupath.github.io/

**Fiji**: Fiji is also useful https://imagej.net/software/fiji/ 


**Preparing the atlas maps** 
--------------------------------
 
The atlas maps are customised to match the cutting plane and proportions of the brain sections. They are generated with either the QuickNII software that applies linear registration only, or with the VisuAlign software that applies nonlinear refinement to an existing QuickNII anchoring file. The atlas maps are in .FLAT format and cannot be directly viewed. The image below shows the information contained in the atlas map, but is not the .FLAT file itself.

+----------+
| |image12||
+----------+

|

  **QuickNII**
  ~~~~~~~~~~~~

  * QuickNII is a standalone software for affine spatial registration (anchoring) of section images - typically high resolution histological images - to a reference atlas such as the Allen Mouse Brain Atlas or the Waxholm Atlas of the Sprague Dawley Rat. In QuickNII, the reference atlas is transformed to match anatomical landmarks in the experimental images. In this way, the spatial relationship between experimental image and atlas is defined, without introducing transformations in the original experimental images. 

  * Once all the sections are registered, QuickNII may be used to generate atlas maps that match the cutting plane and proportions of the experimental image data. The anchoring information (coordinates) is saved and stored in an XML or JSON file.   

  * The registration is user-guided with some automation. Following anchoring of a limited number of sections containing key landmarks, transformations are propagated across the entire series of images to reduce the manual work required. These propagations must be validated by visual inspection and typically require fine adjustments for most sections. A user manual that describes how to use QuickNII in the context of the QUINT workflow is included as part of the Nutil package. See: QuickNII userguide. 

  **VisuAlign**
  ~~~~~~~~~~~~~~

  * VisuAlign is a standalone software for applying nonlinear refinements (inplane) to an existing affine 2D-to-3D registration (the 2D-to-3D registration is performed with QuickNII and stored in the JSON file). It is used to make manual adjustments to the atlas maps to better match the sections. The adjustments are nonlinear.  

  * Open the JSON file from QuickNII in VisuAlign and apply adjustments by simple drop and drag of markers placed on the image. The adjusted atlas maps may then be exported in .FLAT format and are compatible with Quantifier. VisuAlign does not update the linear coordinate information contained in the JSON file. A user manual that describes how to use VisuAlign in the context of the QUINT workflow is included as part of the Nutil package. See: VisuAlign userguide.

  Visit and download QuickNII and VisuAlign here: https://ebrains.eu/service/quicknii-and-visualign 

**Preparing the XML or JSON file.**
----------------------------------------------------------------------------
 
Either the XML or JSON file from QuickNII, or the JSON file from VisuAlign may be used. They all contain the linear registration information that is needed to generate coordinate output. Nonlinear adjustment of the atlas maps with VisuAlign does not alter the linear coordinate information contained in the file. 

**OBS! Make sure your XML or JSON file has anchoring information for every section image in your dataset.**



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
   :width: 2.05417in
   :height: 1.39783in
.. |image12| image:: cfad7c6d57444e3b93185b655ab922e0/media/image7.png
   :width: 1.76111in
   :height: 1.39185in
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
