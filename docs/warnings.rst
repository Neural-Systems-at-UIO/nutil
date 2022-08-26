**Troubleshooting: Warnings and error messages**
--------------------------------------------------

.. warning::
   WARNING: Some of the area matrices were not initialized.

This warning informs you that the JSON or XML file contains info about sections that are not included in the analysis. For example, if you run an analysis for a few sections only. This is not a problem - the analysis will produce correct results - but alerts you to missing sections in case this was not intended. 


.. warning::
   WARNING: Could not find data in .xml or .json file for slice '_s001', so 3D data will be incorrect. Please make sure that there exists a corresponding field in the xml or json file!
   
This means what it says: Nutil can't find the relevant anchoring information in the .json file. This can happen for a number of reasons:

* The slice is missing in the .json file. Open the .json file in a text editor such as notebook and check.
* The slice is missing anchoring information. This happens if it has not been registered to the reference atlas in QuickNII or VisuAlign. Sometimes it happens because the registration info has not been saved in QuickNII for the slice (remember to confirm the registration!).
* The default ID format is selected in Nutil Quantifier (_sXXX), but the slice ID does not match this format. In this case, switch to "user" defined ID and define the ID using RegEx. It is also possible that the RegEx is incorrect: make sure it correspond to the ID.   
* The slice ID does not match the ID in the corresponding segmentation and atlas map. In this case, the IDs have to be revised so that they match across the board. We recommend using the _sXXX format.  
