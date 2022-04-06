**Disclaimer - Quality Assurance**
---------------------------------

Nutil is a highly flexible pre- and post- processing toolbox for histological images that enables format conversion (TiffCreator), transformation (Transform and Resize) and analysis (Quantifier). 

More stringent quality assurance routines were introduced in February 2021 in light of several bugs discovered in Nutil affecting core Quantifier functionality (see the release notes for more information about the bugs). The routines include continuous integration and automated validation on Github, based on a collection of ground truth datasets. 

As Nutil is a highly flexible software with many options for customised analysis that has evolved over time in response to users’ needs, not all features have been tested to the same extent. The core functionality is tested more extensively than less central features. The testing status of each feature is listed below. 

* We strongly recommend that ALL data from Nutil is validated externally by the user prior to research use, as mistakes in image preparation and set-up may invalidate the output. 
* This recommendation is particularly applicable to analyses performed with features that are not tested as part of the automated validation procedure as there may be software bugs that are not yet discovered. 
* If you detect errors please inform us by posting an issue on Github https://github.com/Neural-Systems-at-UIO/nutil/issues or by contacting support@ebrains.eu.


**Automated validation**
~~~~~~~~~~~~~~~~~~~~~~

An automatic validator feature was implemented in Nutil on 22.02.21. This directly compares PNG, TIF, TIFF, CSV and HTML output files from two sets of Nutil analyses, with any differences flagged. It is set up so that the output from new versions of Nutil are compared to ground truth data with known output, to ensure that any errors or bugs in the code are picked up prior to release. In order to pass the validation procedure, the Nutil output and ground truth must be identical. 

Two validation systems have been implemented that utilise the Validator: 

**1.	Automated validation on Github that initiates with each pre-release** 

Nutil is open-source and shared with continuous integration and automatic validation on Github. For automatic validation, Nutil is compiled and used to process four small test datasets on a virtual machine. The result of these procedures are compared to corresponding ground truth data with the Validator, with a release on Github if the output matches the ground truth exactly. If the Validator detects differences, the release is blocked and the differences are flagged. We then investigate and fix any code errors before releasing again to initiate a repeat of the validation.

**Ground truth datasets**

  1. Synthetic dataset described in the validation section of Groeneboom et al, 2020 (DOI: 10.3389/fninf.2020.00037). This comprises two sections, with objects of known size and anatomical location in the Allen Mouse Brain Atlas CCF3 v2015. 

  2. Same dataset as above but with hemisphere masks applied to validate the mask feature. 

  3. Synthetic dataset composed of three sections with objects of known size and anatomical location in the Waxholm Space Atlas of the Sprague Dawley rat v4. 

  4. Transform dataset.

**2.	Automated validation on a local machine**

For a more thorough validation, the Validator is initiated manually on a local machine with a larger collection of test datasets. These are not shared on Github.

**Feature testing status**
~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Reference atlases - (Allen mouse brain / Waxholm Space Atlas of the Sprague Dawley rat) - validated.
2. Object colour - standard colours are validated (black 0,0,0 , white 255,255,255, blue 0,0,255, red 255,0,0).
3. Object splitting - (YES/NO) - validated.
4. Mask feature - validated.
5. Customised reports - (default/custom) - validated.
6. Minimum object size - validated.
7. Pixel scale - validated. 
8. Pixel scale unit - validated.
9. Output report type - CSV is validated. HTML has not been extensively tested, some errors known here, but nothing significant. 
10. Coordinate extraction - the output "looks" right but this has not been validated thoroughly. 
11. Coordinate random distortion - do not use, there is a bug here. This feature will be removed in future versions. 
12. Point cloud density - the output "looks" right but this has not been validated thoroughly.
13. Nifti size - not validated.
14. Display object IDs - No known bugs but not validated thoroughly. 
15. Display region IDS - No known bugs but not validated thoroughly.
16. Unique ID format - (_sXXX / user) - no known bugs. 

In some instances, a bug may only occur with certain combinations of settings (for example, with white objects and with the mask feature swithed ON). Be aware that it is not possible to test every combination, and so in rare instances bugs may remain despite being marked as "validated" above.





