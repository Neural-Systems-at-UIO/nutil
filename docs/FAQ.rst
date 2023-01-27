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



