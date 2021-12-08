**Introduction**
==================

Quantifier is an integral part of the QUINT workflow, and enables the regional quantification of features extracted from histological images based on a reference atlas such as the Allen Mouse Brain Atlas (AMBA) or the Waxholm Atlas of the Spraque Dawley Rat. 

For an overview watch our tutorial: https://www.youtube.com/watch?v=n-gQigcGMJ0 

**Quantifier requires three sets of input:**

1. Images with the features segmented.
2. Atlas maps.
3. Atlas registration information in XML or JSON format.

**It generates three sets of output:**

1. Reports with quantifications per atlas region.
2. Overlay images with the segmentations superimposed on the atlas maps.
3. Coordinate files for visualising the extracted objects in the 3D brain viewer: Meshview. 

As the QUINT workflow is relatively complex, and requires the use of several software packages including ilastik, QuickNII and Nutil Quantifier, this section is split into several parts with information on how to prepare the input files, how to run Quantifier, and how to interpret the output files.   
