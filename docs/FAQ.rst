**FAQ**
=======

**There are no object counts in the reports (N/A)?**
----------------------------------------------------

This is usually because Object Splitting is turned "on", which means that each object pixel is assigned to its correct anatomical location. This gives correct percentage coverage per region, but invalidates the counts as objects that cross region boundaries are split into two or more objects. Therefore the object count: N/A. To get object counts, turn object splitting "off". This means that each object is assigned to one region only, giving accurate counts per regions. 

See for more info: https://nutil.readthedocs.io/en/latest/QuantifierOS.html

**The reports (CSV) don't open correctly in Microsoft Excel**
-------------------------------------------------

Different countries have different conventions regarding default separators. The CSV files from Nutil use semi-colon (;) as the delimiter. However, in the US, UK and some countries in Europe, comma (,) is the default separator, which means that the CSV files will not open automatically in MicroSoft Excel. To open the CSV in Excel, open Excel, go to "Data" > "From Text" > select the report to open > select "Delimiter" > select "semicolon". 

It is also possible to change the default separator on your computer by changing the regional settings. Start > Control Panel > Regional and Language Options > Additional Settings > List Separator- enter a semicolon (;). This can then be changed back to comma (,) when you have finished your analysis. 

**I don't understand what to enter for the Pixel Scale?**
---------------------------------------------------------

* It is usually not necessary to enter a Pixel Scale in Nutil. This is because the regional loads are ratios (no. of pixels corresponding to your objects divided by no. of pixels representing the region), which means that they are not affected by the pixel scale. If the goal is to measure regional loads (%) or no. of objects per region, then leave the Pixel Scale blank. 

* However, if you need the "real" size of your objects or regions, you'll have to multiply the pixel counts in the reports by the area represented by each pixel in the segmentated images (the pixel scale is an area, your example in um2). As long as all the segmented images have the same pixel scale, the pixel scale can be entered in Nutil and this calculation will be performed automatically. Note that it is the pixel scale of the segmentations that counts here, not the pixel scale of the images used for atlas registration! 

* So how do you work out the Pixel Scale? To do this, you need to know the pixel width of your original images in "real life" terms (for example, pixel width = 0.4 um). This depends on the microscope settings and is usually provided by the scanner. You also need to know the resize factor that was used to downscale the images prior to segmentation (for example, 0.5). The pixel width in the downscaled images can be calculated as follows: original width / resize factor (for example, 0.4 / 0.5 = 0.8 um). To calculate the pixel scale of your downscaled images, square this number. This converts it to an area (for example, 0.8 x 0.8 = 0.64 um2). 



