**Transform**
------------------------


The Transform operation enables the batch renaming, rotation, resizing and thumbnail compilation of tiled TIFF images (max size: 4 GB). The transformed TIFF images are in TIFF format, and the thumbnails are in PNG format. 

.. note::
The tiled TIFF image format has an upper size limit of 4 GB. Nutil cannot transform or generate images that are bigger than 4 GB. 


**How to run Transform**

1. Click “New”. Select “Transform”. 
2. Give the project a title. This is for documentation purposes only.
3. Select compression type to apply to the images: LZW (lossless - all information retained, larger images), JPEG (lossy - some unimportant info removed, smaller images) and none. 
3. Select the input folder containing the images to be transformed and select the output folder where you want the images to be saved. 
4. Switch autocropping "on" or "off". To use the autocropping feature, fill in the background colour of the images and a background colour range. There is more information about this in the "Help" buttons in the GUI. 
5. Press the "Fill files" button to view all the images in the input folder. To transform your TIFF images, enter new transformation parameters in the form. The files can also be renamed here. Alternatively, if you wish to downscale the images and convert to PNG images only (for example, for use with ilastik), leave the transformation parameters at the default settings. Open "advanced settings" and select "only create thumbnails". For the thumbnail size enter the required resize factor. e.g. 0.5. 
6. Once everything is filled in press the “Save as” button. This saves a copy of the transformation parameters in a simple text file in .NUT format. This is for your own records, but may also be reloaded into Nutil via the “load” button. 
7. Nutil automatically detects the number of core processor available (8 in the example). Choose one less than the total available to ensure adequate processing power (6 or 7 here). 
8. Press “Start” and wait until the process is complete. 

+----------+
| |image3| |
+----------+

.. |image3| image:: cfad7c6d57444e3b93185b655ab922e0/media/image4.png
   :width: 6.30139in
   :height: 3.52274in
   
.. tip::
   If Nutil gives error message "Maximum TIFF file size exceeded": switch to JPEG compression.  
