**Introduction**
==================

**Nutil Quantifier** is an integral part of the `QUINT workflow <https://quint-workflow.readthedocs.io>`_. It supports the quantification of labelled features in histological image series from mouse and rat brain using a reference atlas. The following atlases are supported:

* Allen Mouse Brain Atlas, Common Coordinate Framework version 3 (CCFv3), delineations from 2015.
* Allen Mouse Brain Atlas, Common Coordinate Framework version 3 (CCFv3), delineations from 2017.
* Waxholm Atlas of the Spraque Dawley Rat (WHS), version 2, 3 and 4.
* Kim Unified Adult Mouse Brain Atlas version 1 (2019) (integrated in Nutil v1).
* Developmental Mouse Brain Atlas for ages P4-P56 (DeMBA), using Allen CCFv3 delineations from 2017 (integrated in Nutil v1).
* Developmental Mouse Brain Atlas for ages P4-P56 (DeMBA), using Kim Lab developmental delineations (KimLabDev CCFv001) (integrated in Nutil v1).
* Other atlases can be used in Nutil via the custom atlas feature as long as they are implemented in QuickNII/VisuAlign.

.. Warning::
   QUINT does not allow quantification without the use of an atlas or for regions that fall outside of the reference atlas.  

Watch our video tutorial:

.. raw:: html

   <iframe width="560" height="315" src="https://www.youtube.com/embed/n-gQigcGMJ0" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


**Quantifier requires the following input files:**

1. A JSON file with registration info to a reference brain atlas (generated with the *QuickNII* or *VisuAlign* software).
2. Atlas maps in .FLAT format corresponding to the JSON file (generated in *QuickNII* or *VisuAlign* using the JSON file).
3. Segmentation images in .PNG format with the features to be quantified displayed with a unique RGB colour code (indexed 8-bit PNG format) (generated with *ilastik*, *ImageJ* or another image analysis software).

**It generates the following results:**

1. Reports with counts and area fraction per reference atlas region (.CSV format).
2. Reports with counts and area fraction per custom atlas region (custom regions are compilations of reference atlas regions) (.CSV format). 
3. Images with the segmentations superimposed on the atlas maps (.PNG format).
4. Point clouds for visualising the extracted features in the MeshView Atlas Viewer (.JSON format). 

As the QUINT workflow requires the use of several software (*QuickNII*, *VisuAlign*, a software for image segmentation and *Nutil*), this section is split into several parts with information on how to prepare the input files, how to run Quantifier, and how to interpret the results. 


