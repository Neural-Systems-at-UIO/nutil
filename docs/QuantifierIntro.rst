**Introduction**
==================

**Quantifier** is an integral part of the `QUINT workflow <https://quint-workflow.readthedocs.io>`_. It support quantification of labelled features in images of histological sections from mouse and rat brain based on a reference atlas. The following atlases are currently supported:

* Allen Mouse Brain Atlas Common Coordinate Framework version 3 (2015 and 2017)
* Waxholm Atlas of the Spraque Dawley Rat, version 2, 3 and 4. 

.. Warning::
   QUINT does not support quantification for regions that fall outside of the reference atlases, or quantification without use of an atlas. 

Watch our video utorial:

.. raw:: html

   <iframe width="560" height="315" src="https://www.youtube.com/embed/n-gQigcGMJ0" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


**Quantifier requires three sets of input:**

1. Atlas maps in FLAT format: these are generate with QuickNII or VisuAlign.
2. Atlas registration information in XML or JSON format: these are generated with QuickNII, VisuAlign or DeepSlice.
3. Segmentations with the features to be quantified represented in a unique RGB colour (8-bit PNG format with RGB colours). These are generated with ilastik or another image analysis tool.

**It generates three sets of results:**

1. Reports with counts and percentage coverage per reference atlas region. There is also the option to generate reports for customized regions (compilations of reference atlas regions) (CSV format). 
2. Images with the segmentations superimposed on the atlas maps (PNG format).
3. Point clouds for visualising the extracted objects in the Meshview Atlas Viewer (JSON format). 

As the QUINT workflow requires the use of several software including QuickNII, Ilastik and Nutil, this section is split into several parts with information on how to prepare the input files, how to run Quantifier, and how to interpret the results. 


