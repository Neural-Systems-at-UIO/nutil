**Customised reports explained**
=================================

Quantifier generates several sets of reports, including CustomRegion reports. These contain quantifications for broader regions: the broad regions are compilations of reference atlas regions, and may either be user-defined ("custom") or the default regions included in the Nutil software ("default"). 


**CustomRegion reports**
-----------------------

1. For the CustomRegion reports, the simplest option is to run the analysis with the "default" regions that are built into the Nutil software, and are assigned by selecting "default". 

  More information on the default regions are found in the CustomRegion files in the Nutil package (located in the CustomRegion folder, there is a separate file for each atlas). The “default” option is a whole brain analysis, which means it includes all the reference atlas regions subdivided into broader regions. 

  *For example, for the Allen Mouse Brain Atlas v3 - 2017, the custom regions are; the cortex; fiber tracts; hippocampus; olfactory regions; hypothalamus; regions in the striatum and pallidum; midbrain - hindbrain - and medulla; thalamus; cerebellum; and ventricular system*. 

2. Alternatively, users have the option to generate CustomRegion reports based on their own compilations of reference atlas regions. To do this, customised regions are defined by the user using the CustomRegionsTemplate.xlsx, which is located in the CustomRegion folder and is part of the Nutil package. In this case, the user selects the "custom" option in the Nutil GUI and navigates to the populated template. Fill in the template exactly as shown below:

.. image:: cfad7c6d57444e3b93185b655ab922e0/media/image12.png
   :width: 4.80278in
   :height: 3.60427in
|

**ROW 1:** assign your own names to the regions (For example, cortex. This is for your information only).

**ROW 2:** assign colours to the regions. Do this by typing a RGB colour code in the following format: 255;0;0 (for red). This colour will be assigned to the objects located in the custom region for the purposes of the image output and coordinate output (for display purposes only).

**ROW 3:** enter the colour name (this is for your information only).

**ROW 4:** define the region by listing the reference atlas IDs that you wish to include. The excel sheets in the AtlasHierarchy folder list all the regions and IDs for each atlas.  
 
For mouse, see the ABAHier2015.xlsx or ABAHier2017.xlsx file for the full list of regions and IDs. 
 
For rat, see the WHS_rat_atlas_v2.xlsx or WHS_rat_atlas_v3.xlsx file for the full list of regions and IDs.  
 
The default .xlsx may be used as a guide for filling out the template.  

|

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

