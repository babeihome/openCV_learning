from PIL import Image,ImageDraw,ImageFont
import os
import imageio
import numpy as np
import re
#walk directory


targetDir = "./baseline/"
list_dirs = os.walk(targetDir)
font = ImageFont.truetype('simsun.ttc',40)
frame = []
seq = []
for root,dirs,files in list_dirs:
    if(re.match(targetDir,root)):
        for f in files:
            if(re.match('\d+.png',f)):
                imagePath = os.path.join(root,f)
                im = Image.open(imagePath)
                draw = ImageDraw.Draw(im)
                draw.text((0,0),f.split('.')[0],fill=(255),font =font)
                #imshow(im)
                im.save(root+f.split('.')[0]+'_label.png');
list_dirs = os.walk(targetDir)
for root,dirs,files in list_dirs:
    if(re.match(targetDir,root)):
        for f in files:
            if(re.match('\d+_label.png',f)):
                frame.append(imageio.imread(root+f))
                seq.append(int(re.findall(r"(\d+)_label",f)[0]))

frame_sorted = [x for (y,x) in sorted(zip(seq,frame))]
#y = sorted(seq)
imageio.mimsave(targetDir+"demo.gif",frame_sorted,'GIF',duration = 0.3)
