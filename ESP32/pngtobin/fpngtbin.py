from PIL import Image
import numpy as np

W, H = 200, 74

addr = r"C:\Users\maxim\OneDrive\Documents\Maxenix Arcade\ESP32\pngtobin\Images\image.bin"

img = Image.open(r"C:\Users\maxim\OneDrive\Documents\Maxenix Arcade\ESP32\pngtobin\Images\MAXENIX_LOGO.png") \
           .resize((W, H)) \
           .convert("RGB")

out = np.zeros(W * H, dtype=np.uint16)

i = 0
for y in range(H):
    for x in range(W):
        r, g, b = img.getpixel((x, y))
        out[i] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
        i += 1

out.tofile(addr)