**Introduction**
----------------

Nutil simplifies the pre-and-post processing of 2D histological images from mouse and rat brain. It is an integral part of the QuickNII - ilastik - Nutil (QUINT) workflow for regional quantification of features such as cells, with the regions defined by a reference atlas (Allen Mouse Brain Atlas or the Waxholm Space Atlas of the Sprague Dawley rat). It also supports transformation, file format conversion and renaming of the huge histological images that are typical of microscopy. 

Nutil is developed as a standalone application and requires no coding experience to execute. The user specifies the input and output folders and the parameters for the pre-and post-processing operations in the Nutil graphical user interface (GUI). All functions operate in batch, and operate in parallel on multiple CPUs. 

**QUINT tutorial**

.. raw:: html

   <iframe width="560" height="315" src="https://www.youtube.com/embed/n-gQigcGMJ0" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


**Nutil operations**

1. **TiffCreator**: convert JPEG, PNG and normal TIFF images to tiled TIFF format.
2. **Transform**: rename, rotate, resize and compile thumbnails of large tiled TIFF images (typical microscopy output format).
3. **Quantifier**: for the batch extraction, quantification and spatial analysis of labelling segmented from 2D mouse or rat brain section images (for example, immunohistochemical labelling).
4. **Resize**: for resizing JPEG/PNG images with output in PNG format.

+----------+                    
| |image1| |                    
+----------+                    
                            

.. note::

   **PLEASE visit** `EBRAINS <https://ebrains.eu/service/quint/>`_ **for more information about the QUINT workflow and to find tutorials, examples of use, and          software download information.** 

.. |image1| image:: cfad7c6d57444e3b93185b655ab922e0/media/image2.png
   :width: 6.30139in
   :height: 2.33688in
