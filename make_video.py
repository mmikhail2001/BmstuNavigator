import cv2
import numpy as np
from sys import argv


#читаем кадры
imgs = [cv2.imread(str(file)) for file in argv[1:]]

# создаем видео
height, width, layers = imgs[0].shape

# video = cv2.VideoWriter('../video.mp4', cv2.VideoWriter_fourcc(* 'XVID'), 1, (width,height))
video = cv2.VideoWriter('../video.mp4', cv2.VideoWriter_fourcc(*'mp4v'), 1, (width,height))
_ = [video.write(i) for i in imgs]

cv2.destroyAllWindows()
video.release()