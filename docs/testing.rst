**Quality assurance**
--------------------------

Nutil is a highly flexible pre- and post- processing toolbox for histological images that enables format conversion (TiffCreator), transformation (Transform and Resize) and analysis (Quantifier). 

Stringent quality assurance routines were introduced in February 2021 in light of several bugs discovered in Nutil affecting core Quantifier functionality. The routines include continuous integration and automated validation on Github, based on a collection of ground truth datasets. As Nutil is a highly flexible software with many options for customised analysis, and has evolved over time in response to users’ needs, not all features have been tested to the same extent. The core functionality is tested more extensively than less central features. The testing status of each feature will be added here in due course. 

We strongly recommend that ALL data that comes from Nutil is validated externally by the user prior to research use, as mistakes in image preparation (for example, preparation of the segmentations and the atlas maps) and set-up (for example, selection of the Quantifier settings) may invalidate the output. However, this recommendation is particularly applicable to analyses performed with features that are not tested as part of the automated validation procedure. 

