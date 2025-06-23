**Object splitting explained**
================================

In Quantifier, users must specify whether to turn “object splitting” ON or OFF. In Nutil v1.1.0 "object splitting" has been renamed "Area fraction or Counts".

Area fraction: With object splitting switched "ON", segmented objects that overlap atlas regions are divided into parts, with the individual object pixels assigned their precise regional location. This ensures accurate regional area fraction measurements. This invalidates the object counts as some objects will be split and counted more than once which means that N/A appears for counts in the reports. There is a known issue with selection of "area fraction" in Nutil v1.1.0 (see warning below). 

Counts: With object splitting switched "OFF", object counts are correct, but the load measurements may be incorrect since objects that overlap region boundaries will be assigned to one of the regions only, potentially skewing the regional area fraction calculations. This is especially true if objects are large, since a large object that overlaps many regions (e.g. 1000 pixels) may be assigned to a small region (e.g. 100 pixels) giving false area fraction output (1000% load in this case).

.. note::
   **Recommendation:** 

   Select Counts/NO for small objects to get accurate object counts, e.g. cells.  

   Select Area fraction/YES for large objects that overlap atlas regions, e.g. connectivity data, or densely packed cells or features. This gives precise area fraction output. 

   See the object splitting help button in Nutil for an example image.  

.. warning::

  There is a known issue with selection of "counts" or "area fraction" in Nutil v1.1.0. This means that even when "area fraction" is selected, it will perform the calculations as if "counts" were selected. In other words, it is not possible to achieve correct "area fraction" calculations for objects that overlap several atlas regions for Nutil v1.1.0. If you need this functionality, please use Nutil v0.8.0. For objects that do not overlap atlas regions, the "Counts" setting will calculate correct regional area fractions.   


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

