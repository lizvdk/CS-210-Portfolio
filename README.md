# CS-210-Portfolio
Portfolio for CS-210 (Programming Languages) at SNHU

## Project 3: Corner Grocer

Project 3 demonstrates how programming languages can be combined to develop secure, efficient code. Python is used for data processing and writing to files. C++ is used for reading files and presenting the user interface. Python counts the number of times each item appears in a file, and creates another file with the item name and frequencies. C++ retrieves the information from the frequency file and displays results to the user in various formats, including a histogram.

I followed directions, even when they seemed unnecessarily complicated. The project requirements specified exactly which language should perform each task. I made sure to read the directions carefully and create a diagram of the program flow before I began coding. Taking time to fully understand the prompt and requirements is a skill I will carry forward in my studies. Although it was great to gain experience integrating languages, the scenario seemed contrived. The application could be improved by standardizing and streamlining the data processing. As it is now, the Python functions sometimes return integers and at other times handle printing and formatting the output. It would be more consistent if Python was limited to performing returning data and C++ handled the output. I avoided duplicating code throughout the application. One of the functions that is used to create the histogram is `printBarWithLabel` which takes in the item's name and quantity and outputs something like `apple *****`. The descriptive function name makes the code self-documenting and more readable, and therefore more maintainable.

***
Menu & Histogram:

<a href="https://ibb.co/VLdjt6W"><img src="https://i.ibb.co/mRmDGpC/menu-and-histogram.png" alt="menu-and-histogram" border="0"></a>
