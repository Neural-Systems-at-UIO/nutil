**Nutil as a command line tool**
================================

Nutil is a standalone application with a graphical user interface that does not require coding ability to navigate. However, Nutil can also be run as a command line tool for batch processing. This is particularly useful if you have large numbers of series and want to automate the analysis process: it allows you to  initiate batch processing of many image series using .NUT files for each series that have been set up in advance. The batch processing script is called "process_folder.bat" and is located within the Nutil software in the following location: Nutil\program\process_folder.bat

* Set up a unique .NUT file for each image series and save them in a folder.
* Navigate to the process_folder.bat file in the Nutil software using the command line. 
* Enter the path to the folder containing the .NUT files, and type the no. of core processors (threads) to use for the analysis.

Windows example:: 

  C:\nutil\program>process_folder.bat   Z:\HBP_Analytics\Nutil_data\batch   4



