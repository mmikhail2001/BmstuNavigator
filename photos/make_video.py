import cv2
import numpy as np
from sys import argv


#читаем кадры

# photos = ["200-150.jpg", "200-201.jpg", "200-204.jpg"]
photos = ["10.jpeg", "11.jpeg"]

# imgs = [cv2.imread(str(file)) for file in argv[1:]]
imgs = [cv2.imread(str(file)) for file in photos]

print("hello0")

# создаем видео
height, width, layers = imgs[0].shape

print(height, width, layers)


print("hello1")

video = cv2.VideoWriter('video.mp4', cv2.VideoWriter_fourcc(* 'XVID'), 2, (width,height))
# video = cv2.VideoWriter('video.mp4', cv2.VideoWriter_fourcc(*'mp4v'), 1, (width,height))
# video = cv2.VideoWriter('video.mp4', cv2.VideoWriter_fourcc(*'DIVX'), 1, (width,height))
_ = [video.write(i) for i in imgs]

print("hello2")

cv2.destroyAllWindows()
video.release()