**What is Nutil?**
====================

**Nutil** is a standalone desktop application that simplifies the pre-and-post processing of histological brain section images from mouse and rat. It can be used to pre-process images in preparation for analysis (TiffCreator, Transform, Resize), and is used as part of the `QUINT workflow <https://quint-workflow.readthedocs.io>`_ for analysis of brain section image series using a reference brain atlas (Quantifier).

Nutil allows four key operations:

Prepare histological images for analysis using:

1. **TiffCreator**: convert JPEG, PNG and normal TIFF images to tiled TIFF format.
2. **Transform**: rename, rotate, resize and compile thumbnails of large tiled TIFF images (typical microscopy output format).
3. **Resize**: for resizing JPEG/PNG images with output in PNG format.

As part of the QUINT workflow, use a reference brain atlas to perform brain-wide quantification using:

4. **Quantifier**: for the batch extraction, quantification and spatial analysis of labelling in mouse or rat brain sections using a reference brain atas (for example, immunohistochemical labelling).


.. tip::   
   Visit `EBRAINS <https://ebrains.eu/service/quint/>`_ for more information about QUINT.


**Which atlases are supported?**
---------------------------------

Nutil supports analysis using Quantifier as part of the QUINT workflow using the following atlases: 

* Allen Mouse Brain Atlas Common Coordinate Framework version 3 (CCFv3) (delineations from 2017 or 2015).

* Waxholm Atlas of the Spraque Dawley Rat (WHS) (version 2, 3 and 4).

* Kim Unified Adult Mouse Brain Atlas (version 1, 2019).

* Developmental Mouse Brain Atlas for ages P4-P56 (DeMBA) with Allen CCFv3 delineations from 2017.

* Developmental Mouse Brain Atlas for ages P4-P56 (DeMBA) with Kim Lab developmental delineations (KimLabDev CCFv001).

* It is also possible to use other atlases using the "custom atlas" feature as long as they are integrated in the other QUINT tools (contact us at EBRAINS support to find out more).

.. Warning::
   While the Kim Unified and Developmental Mouse Brain Atlases are integrated in Nutil v1.0, a bug in this version (see `release notes <https://nutil.readthedocs.io/en/latest/release.html>`_) means it is often best to use Nutil v0.8 for these atlases, with the atlases loaded via the "custom atlas" feature (see `using a custom atlas <https://nutil.readthedocs.io/en/latest/QuantifierRun.html>`_).

   The Allen Mouse Brain Atlas and Waxholm Atlas of the Sprague Dawley Rat Atlas are fully integrated in all versions of Nutil. 


**What is the output of Nutil?**
---------------------------------

The output of the pre-processing operations (TiffCreator, Transform and Resize) are images in TIFF or PNG format. 

The output of the Quantifier operation as part of the QUINT workflow are as follows: 

1. Reports with counts and area fraction per reference atlas region (.CSV format).
2. Reports with counts and area fraction per custom atlas region (custom regions are compilations of reference atlas regions) (.CSV format)
3. Images with the segmentations superimposed on the atlas maps (.PNG format).
4. Point clouds for visualising the extracted features using the 3D MeshView Atlas Viewer (.JSON format).


**Learn more**
----------------

Check out the following articles that have used **Nutil** as part of the QUINT workflow:

* Yao Y, Barger Z, Saffari Doost M, Tso CF, Darmohray D, Silverman D, Liu D, Ma C, Cetin A, Yao S, Zeng H, Dan Y. Cardiovascular baroreflex circuit moonlights in sleep control. Neuron. 2022 Sep 23:S0896-6273(22)00802-9. https://doi.org/10.1016/j.neuron.2022.08.027.

* Ham GX, Augustine GJ. Topologically Organized Networks in the Claustrum Reflect Functional Modularization. Frontiers in Neuroanatomy. 16 June 2022. https://doi.org/10.3389/fnana.2022.901807 

* Bjerke IE, Cullity ER, Kjelsberg K, Charan KM, Leergaard TB, Kim JH. DOPAMAP, high-resolution images of dopamine 1 and 2 receptor expression in developing and adult mouse brains. Sci Data. 2022 Apr 19;9(1):175. https://doi.org/10.1038/s41597-022-01268-8

* Tocco C, Øvsthus M, Bjaalie J.G, Leergaard T.B and Studer M. Topography of corticopontine projections is controlled by postmitotic expression of the area-mapping gene Nr2f1. bioRxiv - May 2021 https://doi.org/10.1101/2021.05.10.443413
   
* Kim S, Jo Y, Kook G, Pasquinelli C, Kim H, Kim K, Hoe HS, Choe Y, Rhim H, Thielscher A, Kim J, Lee HJ. Transcranial focused ultrasound stimulation with high spatial resolution. Brain Stimul. 2021 Mar-Apr;14(2):290-300. https://doi.org/10.1016/j.brs.2021.01.002
   
* Whilden CM, Chevée M, An Seong Yeol,  Pezon Brown S. The synaptic inputs and thalamic projections of two classes of layer 6 corticothalamic neurons in primary somatosensory cortex of the mouse. J Comp Neurol. 2021 Dec;529(17):3751-3771. doi: https://doi.org/10.1002/cne.25163. Epub 2021 May 6. 
   
* McDonald MW, Jeffers MS, Filadelfi M, Vicencio A, Heidenreich G, Wu J and Silasi G. Localizing Microemboli within the Rodent Brain through Block-Face Imaging and Atlas Registration. eNeuro 16 July 2021, 8 (4) ENEURO.0216-21.2021; DOI: https://doi.org/10.1523/ENEURO.0216-21.2021    
   
* Bjerke IE, Yates SC, Laja A, Witter MP, Puchades MA, Bjaalie JG and Leergaard TB. Densities and numbers of calbindin and parvalbumin positive neurons across the rat and mouse brain. 2021, iScience.https://doi.org/10.1016/j.isci.2020.101906




             
                            


