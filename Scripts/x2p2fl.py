'''
This module traverse xxx.x2p file, find the path attributes, save the attr_value to a file list
'''
import sys
import os
import xml.etree.ElementTree as ET

def print_all_attributes(xml_file):
    # Parse the XML file
    tree = ET.parse(xml_file)
    root = tree.getroot()
    
    with open(f'{xml_file}.sifilelist.txt', 'w') as file:
        # Define a recursive function to traverse the XML tree
        def traverse_and_print_attributes(element):
            # Print attributes of the current element
            if element.attrib:
                #print(f"Element: {element.tag}")
                for attr_name, attr_value in element.attrib.items():
                    if attr_name == 'path':
                        print(f"{os.path.realpath(attr_value)}")
                        file.write(f"{os.path.realpath(attr_value)}\n")

            # Recur for each child element
            for child in element:
                traverse_and_print_attributes(child)
        
        # Start traversing from the root element
        traverse_and_print_attributes(root)

# Example usage
if __name__ == "__main__":
    if len(sys.argv) == 2:
        xml_file = sys.argv[1]  # Replace with the path to your XML file
        print_all_attributes(xml_file)
    else:
        print("Usage: x2p2fl xxx.x2p")
        
