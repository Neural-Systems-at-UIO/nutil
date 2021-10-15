**How to interpret the output**
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**1. REPORTS** 
================

   .. image:: cfad7c6d57444e3b93185b655ab922e0/media/image13.png
      :width: 5.88611in
      :height: 2.86512in

**RefAtlasRegion report**
   
Report with output organised based on all the regions in the reference atlas. There is one report for the whole series (all sections combined) and one per section.

**IMPORTANT**: The Allen Mouse Brain Reference Atlas includes regions that are not actually delineated in the atlas. These regions are either big regions that have been delineated into smaller regions and so are not assigned to any pixels in the reference atlas, or are smaller regions that are not delineated. In the reports, these regions have no results (zero for region pixels and for object pixels) and should be excluded from analysis.  

The **Clear Label** ID covers objects that fall outside of the atlas maps
 
**CustomRegion report**

Report with the output organised based on the customised regions defined in the CustomRegionsTemplate.xlsx. These are compilations of reference atlas regions and are either user defined ("custom") or the default regions that are inbuild in the Nutil software. For more information see the "Customised regions explained" section. A report is provided for the whole series (all sections combined) and per section. 

**Object report**

Report with a List of all the objects in the whole series and per section. By switching “ON” the “display object IDs in image file and reports” feature, a unique ID is assigned to each object in your dataset. These IDs are displayed in the image files and in the object reports to enable identification. Object reports are not generated with object splitting switched "ON".   


In each report, interpret the results as follows:

+----------------------+----------------------------------------------+
|    **Region pixels** |    No. of pixels representing the region.    |
+======================+==============================================+
|    **Region area**   |    Area representing the region              |
|                      |    (= Region pixels x pixel scale)           |
+----------------------+----------------------------------------------+
|    **Area unit**     |    Region area unit                          |
|                           (this is the unit of the pixel scale)     |
+----------------------+----------------------------------------------+
|    **Object count**  |    No. of objects located in the region.     |
|                      |                                              |
|                      |    Object counts are not generated           |
|                      |    if object splitting is switched "ON".     |
|                           In this case N/A is displayed.            |
|                      |                                              |
+----------------------+----------------------------------------------+
|    **Object pixels** |    No. of pixels representing objects in     |
|                      |    this region.                              |
+----------------------+----------------------------------------------+
|    **Object area**   |    Area representing objects in this region.
|                      |    (= object pixels x pixel scale)
+----------------------+----------------------------------------------+
|    **Load**          |    Ratio of Object pixels to Region pixels   |
|                      |    (Object pixels / Region                   |
|                      |                                              |
|                      |    pixels).                                  |
+----------------------+----------------------------------------------+

|

**2. IMAGES**
==============

* Segmentations superimposed on the atlas maps in PNG format.  
* The object colours are assigned based on the customised regions. If no regions are specified, or object falls outside of the specified areas, the objects are shown in red by default

**3. COORDINATES**  
===================

* JSON files containing point clouds that can be visualised with the MeshView Atlas Viewer. 
* The viewer is available via the MediaWiki link here: www.nitrc.org/projects/meshview.

**4. NUT FILE** 
=================

The NUT file is a text file containing the analysis settings. This can be loaded into Nutil Quantifier with the “load” button. To view, open with Notepad.

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

