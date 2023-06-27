**FAQ**
=======

**I can't open the application. "Windows protected your PC"**
----------------------------------------------------

"Windows protected your PC, Microsoft Defender SmartScreen prevented an unrecognized app from starting. Running this app might put your PC at risk".'

To fix this, right click on the Nutil.cmd > Properties > General > check "unblock" under Security. 

**Nutil shuts down during a run and/or generates corrupt files**
----------------------------------------------------

Nutil will either shut down or create corrupt files if it loses connection with the images while running. To prevent this, install the Nutil software locally (on the C: drive) and apply to images installed locally where possible. In many cases, Nutil can also be applied from the C:drive to files located elsewhere (for example, a remove drive). However, if you have problems with crashing and corrupt files, try saving the input images in the same location as the Nutil software. 

**There are no object counts in the reports (N/A)?**
----------------------------------------------------

This is usually because Object Splitting is turned "on", which means that each object pixel is assigned to its correct anatomical location. This gives correct percentage coverage per regioon, but invalidates the counts as objects that cross region boundaries are split into two or more objects. Therefore the object count: N/A. To get object counts, turn object splitting "off". This means that each object is assigned to one region only, giving accurate counts per regions. 

See for more info: https://nutil.readthedocs.io/en/latest/QuantifierOS.html

**The reports (CSV) don't open correctly in Microsoft Excel**
-------------------------------------------------

Different countries have different conventions regarding file separators. The CSV files from Nutil have semi-colon (;) delimiters (this is the default delimiter in the Norwegian version of Microsoft Excel). However, comma (,) is the default separator in the US, UK and some European countries, which means that the CSV files will not open automatically in MicroSoft Excel. To open the CSV in Excel, open Excel, go to "Data" > "From Text" > select the report to open > select "Delimiter" > select "semicolon". 

It is also possible to change the default separator on your computer by changing the regional settings. Start > Control Panel > Regional and Language Options > Additional Settings > List Separator- enter a semicolon (;). This can then be changed back to comma (,) when you have finished your analysis. 

**I don't understand what to enter for the Pixel Scale?**
---------------------------------------------------------

* It is not usually necessary to enter a Pixel Scale in Nutil. This is because the regional loads are ratios (no. of pixels corresponding to your objects divided by no. of pixels representing the region), which means that they are not affected by the pixel scale. If the goal is to measure regional loads or no. of objects per region, then leave the Pixel Scale blank. 

* If you need the "real" size of your objects or regions, multiply the pixel counts in the reports by the area represented by each pixel in the segmentated images (pixel scale is an area, for example in um2). As long as all the segmented images have the same pixel scale, the pixel scale can be entered in Nutil and this calculation will be performed automatically. **Note** that it is the pixel scale of the segmentations that counts here, not the pixel scale of the images used for atlas registration! 

**How do I calculate the Pixel Scale of images that have been downscaled?**
--------------------------------------------------------------------------

To do this, you need the pixel width of your original images in "real life" terms, for example, pixel width = 0.4 um (this depends on the microscope settings and is usually provided by the scanner). You also need to know the resize factor that was used to downscale the images prior to segmentation, for example, 0.5. The pixel width in the downscaled images can be calculated as follows: original width / resize factor, for example, 0.4 / 0.5 = 0.8 um. To calculate the pixel scale of your downscaled images, square this number. This converts it to an area, for example, 0.8 x 0.8 = 0.64 um2. 

**The QUINT coordinate output does not match the Allen CCFv3 coordinate system. What's going on?**
----------------------------------------------------------------------------------------------------

This is true and is confusing. The coordinates from QuickNII and the QUINT workflow follow Right-Anterior-Superior orientation and are expressed in voxels. 

* First axis (x) starts from the left side of the volume, and points towards the right
* Second axis (y) starts from the backmost position in the volume, and points towards the front
* Third axis (z) starts from the bottom of the volume and points towards the top

The `Allen CCFv3 <http://help.brain-map.org/display/mousebrain/API>`_ follows a Posterior-Inferior-Right axis directions, and the values are expressed in μm . This necessitates a three-step transformation:

* Reordering coordinates: [x,y,z]RAS,vox => [y,z,x]ASR,vox
* Flipping posterior-anterior and inferior-superior axes: [x,y,z]RAS,vox => [527-y,319-z,x]PIR,vox
* Multiplying the components with 25: [x,y,z]RAS,vox => [(527-y)*25,(319-z)*25,x*25]PIR,μm 

A converter is provided `here <https://quicknii.readthedocs.io/en/latest/coordinates.html>`_.

**The QUINT coordinate output does not match the WHS coordinate system. What going on?**
---------------------------------------------------------------------------------------------

The `WHS rat brain atlas <https://www.nitrc.org/plugins/mwiki/index.php?title=quicknii:Coordinate_systems>`_ uses the same axis order and orientation as QuickNII, only translation of origin, and scaling have to be applied. WHS origin is at 244, 623, 248 voxel coordinates, and everything has to be converted to mm, where the atlas resolution is 0.0390625 mm (isotropic). 

A converter is provided `here <https://quicknii.readthedocs.io/en/latest/coordinates.html>`_.



