from PIL import Image
import numpy as np

def pillow_generate_image(color_array, output_file):
    image = Image.fromarray(np.array(color_array, dtype=np.uint8), 'RGB')
    image.save(output_file)
    print("[Python] image created: " + output_file)
