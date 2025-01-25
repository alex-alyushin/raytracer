from PIL import Image
import numpy as np

def generate_image(color_array, output_file):
    np_array = np.array(color_array, dtype=np.uint8)

    image = Image.fromarray(np_array, 'RGB')
    image.save(output_file)

    print("PIL: image created")
