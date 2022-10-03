import PIL.Image as Image
import numpy as np
import os

class FileFuncs:
    @staticmethod
    def Write(Data, FileName, mode="w"):
        with open( FileName, mode) as write_file:  # json dosyası oluştur/sıfırla
            write_file.write(Data)  # datayı json iiçine yaz

    @staticmethod
    def Read(FileName):
        with open(FileName) as file:  # json dosyasını aç
            return  file.readlines() # verileri oku

    @staticmethod
    def GetFiles(fileloc: str, fileType: str):
        files = [os.listdir(fileloc)]
        FilesList = []
        for temp in files:
            if len(temp) != 0:

                for g in range(len(temp)):
                    if temp[g].endswith(fileType):
                        FilesList.append(temp[g])
                        pass
        return FilesList

def cga_quantize(image,size):
    image=image.resize(size)
    pal_image= Image.new("P", (1,1))
    pal_image.putpalette( [0,0,0,
                           0,255,0,
                           255,0,0,
                           0, 0, 255,
                            255,255,255,
                            255,255,0,
                            255,0,255,
                            0,255,255

                           ])
    return image.convert("RGB").quantize(palette=pal_image)

im=Image.open("Aerkany_reisen_from_touhou_flying_through_light_bulletstouhouga_0251718f-cc6b-42b3-be22-8fa6026c324b.png")

im=cga_quantize(im,(600,480))
im=np.asarray(im,)
pixelarray=[]

once=False
tval=0
for x in im:

    for y in x:
        if(not once):
            tval=y
            once=True
        else:
            once=False
            pixelarray.append((tval<<3)|y)


res = ',0x'.join((format(x, '02x') for x in pixelarray))
res="0x"+res
res="const unsigned char image[]={"+res+"};"
print(res)
FileFuncs.Write(res,"test.cpp","w")


im.save("newim.png")