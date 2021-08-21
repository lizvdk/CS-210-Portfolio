import re
import string
import os

def FrequencyOfItemsFromFile():
    file = open("U:\Project_3\Release\GrocerySales.txt", "r")
    
    itemsFrequency = {}
    
    for line in file:
        item = line.strip()
        
        if item in itemsFrequency:
            itemsFrequency[item] += 1
        else:
            itemsFrequency[item] = 1
    
    file.close()

    return itemsFrequency


def PrintFrequencyOfAllItems():
    itemsFrequency = FrequencyOfItemsFromFile()
    
    for key, value in itemsFrequency.items():
	    print(key,':', value)
         
    return null
    
def FrequencyOfItem(item):
    # Return the frequency of a specific word.
    itemsFrequency = FrequencyOfItemsFromFile()
    
    item = item.capitalize()
    if item in itemsFrequency:
        return itemsFrequency[item]
    else:
        return 0

def OutputFrequencyToFile():
    # Output frequency.dat file
    itemsFrequency = FrequencyOfItemsFromFile()
    outputFilepath = "frequency.dat"

    with open(outputFilepath, "w") as file:
        for key, value in itemsFrequency.items():
            file.write('%s %s\n' % (key, value))
    
    return null
