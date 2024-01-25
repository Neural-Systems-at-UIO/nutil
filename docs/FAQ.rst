**FAQ**
=======

**I can't open the application. "Windows protected your PC"**
---------------------------------------------------------------

"Windows protected your PC, Microsoft Defender SmartScreen prevented an unrecognized app from starting. Running this app might put your PC at risk".'

To fix this, right click on the Nutil.cmd > Properties > General > check "unblock" under Security. 

**Nutil shuts down during a run and/or generates corrupt files**
---------------------------------------------------------------

Nutil will either shut down or create corrupt files if it loses connection with the images while running. To prevent this, install Nutil locally (on the C:drive) and apply Nutil to images that are stored locally (on the C:drive). Nutil can also be applied from the C:drive to files stored elsewhere (for example, on a remove drive). However, if you have problems with crashing and corrupt files, try saving the input images in the same location as the Nutil software. 

Nutil will also shut down if it encounters an unexpected error. While we have done our best to add informative error messages, if it encounters an error we have not anticipated, it will automatically shut down. 

**Transform: "Maximum TIFF file size exceeded", what do I do?**
--------------------------------------------------------------------------------
Older versions of Nutil (v0.4.0 - v0.8.0) do not support BigTIFF images (TIFFs exceeding 4 GB). This means that transformation will fail if your images exceed 4 GB either at their original size or during transformation (e.g. rotation may temporarily increase size since the images are filled with pixels to keep them rectangular). If your images are large (almost 4 GB), use "JPEG compression" to reduce the chance of errors.

BigTIFF support is implemented in Nutilv1.0.0.

**Quantifier: There are no object counts in the reports (N/A)?**
----------------------------------------------------------------

This is usually because Object Splitting is turned "on", which means that each object pixel is assigned to its precise anatomical location. This gives correct regional coverage, but invalidates the counts as objects that overlap region boundaries are split into two or more objects (giving object count: N/A). To get precise object counts, turn object splitting "off". This means that each object is assigned to one region only, giving reliable counts per regions (objects that overlap many regions will be assigned to one at random). 

See for more info: https://nutil.readthedocs.io/en/latest/QuantifierOS.html

**Quantifier: The reports (CSV) don't open correctly in Microsoft Excel**
-----------------------------------------------------------------------------

Different countries have different conventions regarding file separators. Output files (CSV) from Nutil have semi-colon delimiters (;) since this is the default delimiter in the Norwegian version of Microsoft Excel. However, comma (,) is the default separator in the US, UK and some European countries, which means that the CSV files will not open automatically in Microsoft Excel in these countries. 

To open the CSV in Excel, open Excel, go to "Data" > "From Text" > select the report to open > select "Delimiter" > select "semicolon". 

It is also possible to change the default separator on your computer by changing the regional settings. Start > Control Panel > Regional and Language Options > Additional Settings > List Separator- enter a semicolon (;). This can then be changed back to comma (,) when you have finished your analysis. 

**Quantifier: I don't understand what to enter for the Pixel Scale?**
---------------------------------------------------------

* It is not usually necessary to enter a Pixel Scale in Nutil. This is because the regional loads are ratios, which means that they are not affected by the pixel scale (no. of pixels representing your objects divided by the no. of pixels representing the region). If the goal is to measure regional loads or no. of objects per region, then leave the Pixel Scale blank. 
* If you need the "real-life" size of your objects or regions, multiply the pixel counts in the reports by the area (e.g. in um2) represented by each pixel in the segmentations. As long as all the segmented images have the same scale, the pixel scale can be entered in Nutil and this calculation will be performed automatically. It is the pixel scale of the segmentations that counts here, not the pixel scale of the images used for atlas registration! 

**Quantifier: How do I calculate the Pixel Scale of images that have been downscaled?**
--------------------------------------------------------------------------

To do this, you need the pixel width of your original images in "real-life" terms, for example, pixel width = 0.4 um (this depends on the microscope settings and is usually provided by the scanner). You also need to know the resize factor that was used to downscale the images prior to segmentation, for example, 0.5. The pixel width in the downscaled images can be calculated as follows: original width / resize factor, for example, 0.4 / 0.5 = 0.8 um. To calculate the pixel scale of your downscaled images, square this number. This converts it to an area, for example, 0.8 x 0.8 = 0.64 um2. 

**Quantifier: The QUINT coordinates do not match Allen Common Coordinate Framework coordinates. What's going on?**
-------------------------------------------------------------------------------------------------------------------

This is true, but is easy to solve as we provide a `converter <https://www.nesys.uio.no/QuickNII/Q2ABA.html>`_.

The coordinates from `QuickNII and QUINT <https://www.nitrc.org/plugins/mwiki/index.php?title=quicknii:Coordinate_systems>`_ follow a Right-Anterior-Superior orientation and are expressed in voxels (this matches the Nifti standard). 

* First axis (x) starts from the left side of the volume, and points towards the right
* Second axis (y) starts from the backmost position in the volume, and points towards the front
* Third axis (z) starts from the bottom of the volume and points towards the top

The `Allen CCFv3 <http://help.brain-map.org/display/mousebrain/API>`_ follows a Posterior-Inferior-Right axis directions, and the values are expressed in μm. This necessitates a three-step transformation:

* Reordering coordinates: [x,y,z]RAS,vox => [y,z,x]ASR,vox
* Flipping posterior-anterior and inferior-superior axes: [x,y,z]RAS,vox => [527-y,319-z,x]PIR,vox
* Multiplying the components with 25: [x,y,z]RAS,vox => [(527-y)*25,(319-z)*25,x*25]PIR,μm 

**Quantifier: The QUINT coordinates do not match the WHS coordinate system. What going on?**
---------------------------------------------------------------------------------------------

The `WHS rat brain atlas <https://www.nitrc.org/plugins/mwiki/index.php?title=quicknii:Coordinate_systems>`_ uses the same axis order and orientation as QuickNII: only translation of origin, and scaling have to be applied. WHS origin is at 244, 623, 248 voxel coordinates, and everything has to be converted to mm, where the atlas resolution is 0.0390625 mm (isotropic). 

A converter is provided `here <https://www.nesys.uio.no/QuickNII/Q2WHSRat.html>`_.

Quantifier: How do the QUINT coordinates for mouse (Allen CCFv3) relate to Bregma?
---------------------------------------------------------------------------------------
For the mouse, the QUINT workflow uses the Allen CCFv3 as the reference atlas. The CCF was created from brains out-of-skull that have been registered to create an average volume. Bregma location is not recorded, so it is not possible to directly convert to stereotaxic coordinates. However, it is possible to estimate the position of Bregma. See the following posts on the Allen Brain Map community forum:

https://community.brain-map.org/t/why-doesnt-the-3d-mouse-brain-atlas-have-bregma-coordinates/158
https://community.brain-map.org/t/how-to-transform-ccf-x-y-z-coordinates-into-stereotactic-coordinates/1858



