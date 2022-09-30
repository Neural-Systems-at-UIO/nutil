**Preparing the input files**
==============================

**File naming requirement**
-------------------------------

.. tip::
   It is recommended to change the names of the images to comply with the QUINT file `naming convention <https://quint-workflow.readthedocs.io/en/latest/Requirements.html#quint-naming-convention>`_ as the first step of the QUINT workflow. 

   By using images that follow the naming convention for QuickNII, VisuAlign and ilastik, the output files from these software will also comply with the naming convention, and are thereby directly compatible with **Quantifier**.

* The file name of the segmentation and the atlas map that corresponds to a particular section must contain the same unique ID: they should follow the _sXXX naming convention, with XXX representing the section number (not restricted to three digits). 

* The section number should reflect the serial order and spacing of the sections as this is a requirement for QuickNII. For example, _s02, _s06, _s10 for every 4th section starting with section 2. 

* The unique IDs must also be present in the XML or JSON file from QuickNII or VisuAlign containing the registration information (check this by opening with Notepad). This happens automatically as long as the images registered with QuickNII contain the unique IDs in the file name.

* **Quantifier** also supports user-defined IDs using regular expressions (RegExp). This means that it is possible to bypass the _sXXX naming convention. While this is not recommended, it is useful in some cases. For more information see the “Help” button in the Nutil GUI or contact User Support.  

**Examples that comply with the naming convention:** 

Histological image: tg2345_MMSH_s001.png. 
Segmentation image: tg2345_MMSH_s001_segmentation.png. 
Atlas map: tg2345_MMSH_s001_nl.flat

It is fine to include a string of letters and numbers followed by the unique ID. As Quantifier scans and detects the "_s" part of the name, the file name should not contain additional "_s"., for example: tg2345_MMSH_ss_s001.png. 


**Preparing the Segmentations**
------------------------------------
 
Any image analysis software may be used to generate the segmentations as long as they meet the following requirements:

+----------+
| |image11||
+----------+

1. **Format:** Must be indexed 8-bit or 24-bit images in PNG format.

   Quantifier is only able to quantify one RGB colour at a time. Apply one RBG colour to all the objects-of-interest, and specify this colour in the Nutil GUI. For example, the objects here are red, so extract RGB colour: 255,0,0.
  
2. **Image proportions:** Must have the same proportions as the images used to generate the atlas maps. 

   They do not have the same proportions as the actual atlas maps as QuickNII alters the proportions slightly. 

3. **Image size:** 

.. Note::
While Nutil supports segmentations up to 32767 x 32767 pixels (as long as there is enough memory installed on the computer: restriction of Qt: QImage class), we do not recommend running Quantifier on images larger than approximately 10000 x 10000 pixels. Downscale the images as much as possible before segmenting them. 

They do not need to be the same size as the images used to generate the atlas maps and are typically larger in size. It is recommended to downscale the images prior to segmentation. This has several advantages: 

* It improves the quality of the segmentation as it removes noise from the image, and makes them more compatible with the machine learning algorithms used by ilasti. 
* It speeds up Nutil analysis and prevent crashes due to insufficient memory. 

The aim is to downscale the images as much as possible but without losing information from the images that is actually important. The optimal scaling factor is determined by trial and error and should be applied consistenty to all the images in the series. 

.. tip::

    **Software recommendations**

    `Ilastik: <http://ilastik.org/download.html>`_ We recommend the Pixel and Object Classification workflows in the ilastik software to generate the segmentations, with the Glasbey lookup table applied with FIJI to visualise the output. See `here <https://quint-workflow.readthedocs.io/en/latest/Ilastik.html>`_ for instructions.

    `QuPath: <https://qupath.github.io/QuPath>`_ is an alternative that can be used to generate the segmentations. In some cases QuPath may perform better than ilastik.

    `FIJI ImageJ: <https://imagej.net/software/fiji/>`_ Fiji is also useful for generating segmentations. 


**Preparing the Atlas Maps** 
--------------------------------
 
The atlas maps are generated with `QuickNII <https://quicknii.readthedocs.io/en/latest/>`_, which applies linear registration of the sections to the atlas, or with `VisuAlign <https://visualign.readthedocs.io/en/latest/>`_ that applies nonlinear refinement to an existing QuickNII registration. The VisuAlign atlas maps are thereby more accurate than the QuickNII atlas maps, but also take more time to generate. The atlas maps are customised to match the cutting plane and proportions of the brain sections. 

File format: The atlas maps are in .FLAT format and cannot be viewed directly. The image below shows the information contained in an atlas map, but is not the .FLAT file itself.

+----------+
| |image12||
+----------+


**Preparing the XML or JSON file**
-------------------------------------
 
Either the XML or JSON file from `QuickNII <https://quint-workflow.readthedocs.io/en/latest/QuickNII.html>`_, `DeepSlice <https://quint-workflow.readthedocs.io/en/latest/DeepSlice.html>`_ or `VisuAlign <https://quint-workflow.readthedocs.io/en/latest/VisuAlign.html>`_ may be used here.



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
