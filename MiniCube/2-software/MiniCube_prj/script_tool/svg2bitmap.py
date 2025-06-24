import pathlib
import os
from PIL import Image
import argparse

# TODO: TBD
def main():
    parser=argparse.ArgumentParser(description="Transfer svg to bitmap")
    parser.add_argument("-f", "--folder", help="Folder path", required=True)
    parser.add_argument("-o", "--output", help="Ouput path", required=True)
    args=parser.parse_args()
    
    svg_files=[files for files in pathlib.Path(args.folder).rglob("*.svg")]
    bitmap_files=[[str(pathlib.Path(f).with_suffix(".bmp")) for f in svg_files]]
    
    for svg_file in file_list:
        file_name=pathlib.Path(svg_file)
        
        img = img.resize((240, 240))
        pixels = img.load()

if __name__=="__main__":
    main()

