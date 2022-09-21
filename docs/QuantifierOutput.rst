**How to interpret the results**
================================

Nutil generates up to three sets of reports, overlay images and a .NUT file. The sections below give more information on each type of file. 

For each report, interpret the results as follows:

+----------------------+-------------------------------------------------------------------------------+
|    **Region pixels** |    Number of pixels representing the region.                                  |
|                      |                                                                               |
+----------------------+-------------------------------------------------------------------------------+
|    **Region area**   |    Area representing the region (region pixels x pixel scale).                |
|                      |                                                                               |
+----------------------+-------------------------------------------------------------------------------+
|    **Area unit**     |    Region area unit (unit of the pixel scale).                                |
|                      |                                                                               |
+----------------------+-------------------------------------------------------------------------------+
|    **Object count**  |    Number of objects located in the region (N/A if object splitting "ON").    |
|                      |                                                                               |
+----------------------+-------------------------------------------------------------------------------+
|    **Object pixels** |    Number of pixels representing objects in this region.                      |
|                      |                                                                               |
+----------------------+-------------------------------------------------------------------------------+
|    **Object area**   |    Area representing objects in this region (object pixels x pixel scale).    |
|                      |                                                                               |
+----------------------+-------------------------------------------------------------------------------+
|    **Load**          |    Ratio of Object pixels to Region pixels (Object pixels / Region pixels).   |
|                      |                                                                               |
+----------------------+-------------------------------------------------------------------------------+

The main results are:

* Load. This refers to the % regional load (% coverage of the region). Use this with object splitting switched ON (object splitting OFF may invalidate the % load).  
* Count. This is a count of segmented objects that fall within the region. Use this for small objects only, with object splitting switched OFF (object splitting ON may invalidate the counts).

See `Object splitting explained. <https://nutil.readthedocs.io/en/latest/QuantifierOS.html>`_



**RefAtlasRegion report**
----------------------------
   
RefAtlasRegion reports contain quantifications per atlas-region based on the finest level of granularity of the atlas. There is one report for the whole series (all sections combined) and one per section.

.. note::
   The Allen Mouse Brain Reference Atlas includes regions that are not actually delineated in the atlas. These regions are either big regions that have been delineated into smaller regions and so are not assigned to any pixels in the reference atlas, or are smaller regions that are not delineated. In the reports, these regions have no results (zero for region pixels and for object pixels). They should be excluded from analysis.  

   The **Clear Label** ID covers objects that fall outside of the atlas maps

.. image:: cfad7c6d57444e3b93185b655ab922e0/media/image13.png
    :width: 5.88611in
    :height: 2.86512in
 
**CustomRegion report**
------------------------

CustomRegion reports contain quantifications for broader regions. These broader regions are compilations of reference atlas regions, and may either be user-defined ("custom") or the default regions included in the Nutil software ("default"). For more information see the "Customised regions explained" section. A report is provided for the whole series (all sections combined) and per section. 

**Object report**
-------------------

Object reports contain information about individual objects: it lists all the objects in the whole series and per section. As object splitting invalidates the object counts, this report is only generated when the object splitting feature is switched "OFF". 

By switching “ON” the “display object IDs in image file and reports”, a unique ID is assigned to each object in your dataset. These IDs are displayed in the image files and in the object reports to enable identification. 

**Overlay images**
-----------------

* Segmentations superimposed on the atlas maps in PNG format.  
* The object colours are assigned based on the customised regions. If no regions are specified, or object falls outside of the specified areas, the objects are displayed in red by default.
* The **object ID** assigned to an object (for the purpose of identification in the Object report), as well as the **reference atlas region ID** corresponding to its location, may be printed on the overlay images by switching "ON" these options in the "Advanced Settings" for Nutil Quantifier. If both these are switched "ON", the **reference atlas region ID** is printed at the top and the **object ID** at the bottom.   

**Coordinates**  
----------------

* JSON files containing point clouds that can be visualised with the MeshView Atlas Viewer. 
* Links to Meshview are available `here. <https://meshview-for-brain-atlases.readthedocs.io/en/latest/Installation.html#links>`_

.. warning::
   The coordinates generated with Nutil version 0.8 reflect both the linear and nonlinear transformation applied with QuickNII and VisuAlign. Nutil version 0.4 - 0.7 are based on the linear transformation only and do not take into account the nonlinear transformation.   

**NUT file** 
--------------

The NUT file is a text file that contains the parameters that were used for the Nutil analysis. This can be loaded into Nutil Quantifier with the “load” button to recreate the analysis. 

To view its content, open the NUT file in Notepad. As the NUT file is an internal document intended for the transfer of metadata only, it is not always easy to interpret. Some of the parameters stored in the file are conditional on other fields, and so are not activate unless the condition is met. For example, the custom_mask_colour field is not applied unless use_custom_masks = Yes. However, the NUT file does contain information about the Nutil version used for the analysis, and can give clues to potential errors and is useful for problem solving. 

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

