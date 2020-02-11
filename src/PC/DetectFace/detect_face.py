# python3 face_detect.py story-image-abba.jpg haarcascade_frontalface_default.xml
# https://pypi.org/project/opencv-python/
# pip install opencv-contrib-python
import sys
import cv2

print("[Face recognition]")

# Get user supplied values
imagePath = sys.argv[1]
# cascPath = sys.argv[2]
cascPath = "haarcascade_frontalface_default.xml"

print("[1]", imagePath)
print("[2]", cascPath)

# Create the haar cascade
faceCascade = cv2.CascadeClassifier(cascPath)

# Read the image
image = cv2.imread(imagePath)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Detect faces in the image
faces = faceCascade.detectMultiScale(
    gray,
    scaleFactor=1.1,
    minNeighbors=5,
    minSize=(30, 30),
    flags = cv2.CASCADE_SCALE_IMAGE #flags = cv2.cv.CV_HAAR_SCALE_IMAGE
)

print("Found {0} faces!".format(len(faces)))

# Draw a rectangle around the faces
for (x, y, w, h) in faces:
    cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), 2)

cv2.imshow("Faces found", image)
cv2.waitKey(0)
