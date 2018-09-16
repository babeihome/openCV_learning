from PIL import Image,ImageDraw,ImageFont
import os

#walk directory


targetDir = "./"
list_dirs = os.walk(targetDir)
font = ImageFont.truetype('simsun.ttc',100)
for root,dirs,files in list_dirs:
    for f in files:
        imagePath = os.path.join(root,f)
        im = Image.open(imagePath)
        draw = ImageDraw.Draw(im)
        draw.font = font
        draw.fill = (255,0,0)
        draw.text('1')
        draw.text((100,6),'1',fill=(255,0,0),font =font)
        im.show()