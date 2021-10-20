**Disclaimer**
---------------------------------

Nutil is a highly flexible pre- and post- processing toolbox for histological images that enables format conversion (TiffCreator), transformation (Transform and Resize) and analysis (Quantifier). 

More stringent quality assurance routines were introduced in February 2021 in light of several bugs discovered in Nutil affecting core Quantifier functionality (see the release notes for more information about the bugs). The routines include continuous integration and automated validation on Github, based on a collection of ground truth datasets. 

As Nutil is a highly flexible software with many options for customised analysis, and has evolved over time in response to users’ needs, not all features have been tested to the same extent. The core functionality is tested more extensively than less central features. The testing status of each feature will be added here in due course. 

**Quality assurance**

* We strongly recommend that **ALL** data that comes from Nutil is validated externally by the user prior to research use, as mistakes in image preparation (for example, preparation of the segmentations and the atlas maps) and set-up (for example, selection of the Quantifier settings) may invalidate the output. There may also be errors in the Nutil output due to bugs that have not yet detected. This recommendation is particularly applicable to analyses performed with features that are not tested as part of the automated validation procedure. 

* Currently only mouse brain datasets are included as part of the automated validation procedure. 

* The implementation of the Waxholm Space Atlas of the Sprague Dawley rat v4 in Nutil has not been thoroughly tested.  

* If you detect errors please inform us by posting an issue on our `Nutil Github page <https://github.com/Neural-Systems-at-UIO/nutil/issues/>` or by contacting  support@ebrains.eu.
