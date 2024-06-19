import numpy as np
from PIL import Image
import argparse
import os

def convert_raw_to_png(input_path, output_path, width, height, bit_depth=8):
    try:
        # Calculate the number of bytes per pixel
        if bit_depth == 8:
            dtype = np.uint8
        elif bit_depth == 16:
            dtype = np.uint16
        else:
            raise ValueError("Unsupported bit depth")
        
        # Read raw data
        with open(input_path, 'rb') as f:
            raw_data = np.fromfile(f, dtype=dtype)
        
        # Reshape data into image dimensions
        image_data = raw_data.reshape((height, width))

        # Convert to PIL Image
        image = Image.fromarray(image_data)

        # Save as PNG
        image.save(output_path)
        print(f"Successfully converted {input_path} to {output_path}")
    except Exception as e:
        print(f"Failed to convert {input_path}: {e}")

def main():
    parser = argparse.ArgumentParser(description="Convert raw image files to PNG")
    parser.add_argument('input', help="Path to the input raw file")
    parser.add_argument('output', help="Path to the output PNG file")
    parser.add_argument('--width', type=int, required=True, help="Width of the image")
    parser.add_argument('--height', type=int, required=True, help="Height of the image")
    parser.add_argument('--bit_depth', type=int, default=8, help="Bit depth of the image (8 or 16)")
    args = parser.parse_args()

    # Validate input file
    if not os.path.isfile(args.input):
        print(f"Input file {args.input} does not exist.")
        return

    # Ensure output directory exists
    output_dir = os.path.dirname(args.output)
    if output_dir and not os.path.exists(output_dir):
        os.makedirs(output_dir)

    convert_raw_to_png(args.input, args.output, args.width, args.height, args.bit_depth)

if __name__ == "__main__":
    main()
