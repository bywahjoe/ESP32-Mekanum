import cv2

cam = cv2.VideoCapture(0)
print("WIDTH",cam.get(3))
print("HEIGHT",cam.get(4))

width,height=int(640/2),int(480/2)

while True:
    check, frame = cam.read()
    frame=cv2.resize(frame,(width,height))
    cv2.imshow('Camera Stream', frame)

    key = cv2.waitKey(1)
    if key == 27:
        break

cam.release()
cv2.destroyAllWindows()