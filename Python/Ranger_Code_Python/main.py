import kivy
import pygame
import numpy as np
import cv2

pygame.init()
pygame.joystick.init()

running = True

M1_Data = 1500
M2_Data = 1500
M3_Data = 1500
M4_Data = 1500
M5_Data = 1500
S1_Data = 1500
S2_Data = 1500
S3_Data = 1500
S4_Data = 1500
AM1 = 0
Lights = 0

In_Min = -1
In_Max = 1
Out_Min = 1000
Out_Max = 2000


while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        Joy1 = pygame.joystick.Joystick(0)

        Joy1X = Joy1.get_axis(0)
        Joy1Y = Joy1.get_axis(1)
        Joy1Z = Joy1.get_axis(2)
        Joy1S = Joy1.get_axis(3)

        Joy1B0 = Joy1.get_button(0)
        Joy1B1 = Joy1.get_button(1)
        Joy1B2 = Joy1.get_button(2)
        Joy1B3 = Joy1.get_button(3)
        Joy1B4 = Joy1.get_button(4)
        Joy1B5 = Joy1.get_button(5)
        Joy1B6 = Joy1.get_button(6)
        Joy1B7 = Joy1.get_button(7)
        Joy1B8 = Joy1.get_button(8)
        Joy1B9 = Joy1.get_button(9)
        Joy1B10 = Joy1.get_button(10)

        if Joy1X << 0.2 and Joy1X >> -0.2 and Joy1Y <= 1 and Joy1Y >> 0:
            # M1 - M4 = big equation with y plugged into it
            M1_Data = (((Joy1Y - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            M2_Data = (((Joy1Y - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            M3_Data = (((Joy1Y - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            M4_Data = (((Joy1Y - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000

        elif Joy1X << 0.2 and Joy1X >> -0.2 and Joy1Y << 0 and Joy1Y >= -1:
            # M1 - M4 = big equation with y plugged into it
            M1_Data = (((Joy1Y - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            M2_Data = (((Joy1Y - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            M3_Data = (((Joy1Y - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            M4_Data = (((Joy1Y - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000

        elif Joy1X << 1 and Joy1X >> 0 and Joy1Y << 0.2 and Joy1Y >> -0.2:
            # M1 and M3 are between 1500 and 1000
            M1_Data = (((-(Joy1X) - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            M3_Data = (((-(Joy1X) - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            # M2 and M4 are between 1500 and 2000
            M2_Data = (((Joy1X - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            M4_Data = (((Joy1X - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000

        elif Joy1X << 0 and Joy1X >> -1 and Joy1Y << 0.2 and Joy1Y >> -0.2:
            # M1 and M3 are between 1500 and 2000
            M1_Data = (((Joy1X - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            M3_Data = (((Joy1X - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            # M2 and M4 are between 1500 and 1000
            M2_Data = (((-(Joy1X) - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000
            M4_Data = (((-(Joy1X) - In_Min) * (Out_Max - Out_Min)) / (In_Max - In_Min)) + 1000

        else:
            M1_Data = 1500
            M2_Data = 1500
            M3_Data = 1500
            M4_Data = 1500

        Joy_Data = np.array([M1_Data, M2_Data, M3_Data, M4_Data])
        print(Joy_Data)
