import numpy as np
import fabio
import matplotlib.pyplot as plt

def show_image( image_file ):
    image = fabio.open( image_file )
    plt.imshow( image.data  )
    plt.show()

if __name__ == '__main__':
    show_image( '../data/min_data.tif' )
