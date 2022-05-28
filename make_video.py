import cv2
import numpy as np
from sys import argv


#читаем кадры
imgs = [cv2.imread(str(file)) for file in argv[1:]]

print("hello0")

# создаем видео
height, width, layers = imgs[0].shape

print("hello1")

# video = cv2.VideoWriter('../video.mp4', cv2.VideoWriter_fourcc(* 'XVID'), 1, (width,height))
video = cv2.VideoWriter('../video.mp4', cv2.VideoWriter_fourcc(*'mp4v'), 0.3, (width,height))
_ = [video.write(i) for i in imgs]

print("hello2")

cv2.destroyAllWindows()
video.release()