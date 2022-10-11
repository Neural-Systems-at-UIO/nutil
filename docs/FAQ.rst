**FAQ**
=======

**There are no object counts in the reports (N/A)?**
----------------------------------------------------

This is usually because Object Splitting is turned "on", which means that each object pixel is assigned to its correct anatomical location. This gives correct percentage coverage per region, but invalidates the counts as objects that cross region boundaries are split into two or more objects. Therefore the object count: N/A. To get object counts, turn object splitting "off". This means that each object is assigned to one region only, giving accurate counts per regions. 

See for more info: https://nutil.readthedocs.io/en/latest/QuantifierOS.html



