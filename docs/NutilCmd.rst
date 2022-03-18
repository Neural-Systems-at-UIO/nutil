**Nutil as a command line tool**
================================

Nutil is a standalone application with a graphical user interface (GUI) that does not require coding ability to navigate. However, Nutil can also be run as a command line tool for batch processing. This is particularly useful if you have large numbers of series and want to automate the analysis. The batch processing script is called "process_folder.bat" and is located within the Nutil software in the following location: Nutil\program\process_folder.bat

To use Nutil as a command line tool:
-------------------------------------
* set up a unique .NUT file for each image series and save them in a folder.
* Navigate to the process_folder.bat file in the Nutil software using the command line. Enter the path to the folder containing the .NUT files and type the no. of threads to use for the analysis.

For example:: 

  C:\nutil\program>process_folder.bat   Z:\HBP_Analytics\Nutil_data\batch   4



