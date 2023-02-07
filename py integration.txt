import pygame
import math
import serial
import time
ser = serial.Serial('COM3', 9600)
pygame.init()
screen_width = 600
screen_height = 500
screen = pygame.display.set_mode((screen_width, screen_height))
track_image = pygame.image.load("railway_track.jpg")
hinge1 = (150, 300)
hinge2 = (450, 300)
rect_width = 150
rect_height = 100
angle = 0
clockwise = True
speed = 0.0055
line_thickness = 15
line_colors = [(240, 252, 0), (252, 0, 0)]
light_on = True
light_interval = 100
light_counter = 0

def open1():
    global speed,angle,clockwise # Clear the screen
    clockwise=True
    screen.blit(track_image, (0, 0))
    while (clockwise==True):
        clockwise=True
        # Calculate the end points of the rectangles
        end1 = (hinge1[0] + rect_width * math.cos(math.radians(angle)),
                hinge1[1] - rect_height * math.sin(math.radians(angle)))
        end2 = (hinge2[0] - rect_width * math.cos(math.radians(angle)),
                hinge2[1] - rect_height * math.sin(math.radians(angle)))

        for i in range(0, line_thickness):
            color = line_colors[i % 2]
            pygame.draw.line(screen, color, (hinge1[0], hinge1[1] - i), (end1[0], end1[1] - i), 1)
            pygame.draw.line(screen, color, (hinge2[0], hinge2[1] - i), (end2[0], end2[1] - i), 1)

        if clockwise:
           angle += speed
           if angle >= 90:
              #clockwise = False
              #return(clockwise)
              break

        pygame.display.update()
        screen.blit(track_image, (0, 0))

        #if clockwise==False:
        #    return(clockwise)
       #     break

def close1():
    
    global clockwise,angle # Clear the screen
    clockwise=False
    screen.blit(track_image, (0, 0))
    while (clockwise==False):
        clockwise=False# Calculate the end points of the rectangles
        end1 = (hinge1[0] + rect_width * math.cos(math.radians(angle)),
                hinge1[1] - rect_height * math.sin(math.radians(angle)))
        end2 = (hinge2[0] - rect_width * math.cos(math.radians(angle)),
                hinge2[1] - rect_height * math.sin(math.radians(angle)))
        for i in range(0, line_thickness):
            color = line_colors[i % 2]
            pygame.draw.line(screen, color, (hinge1[0], hinge1[1] - i), (end1[0], end1[1] - i), 1)
            pygame.draw.line(screen, color, (hinge2[0], hinge2[1] - i), (end2[0], end2[1] - i), 1)
        if clockwise == False:
           angle -= speed
           if angle <= 0:
               clockwise == True 
               break
        pygame.display.update()
        screen.blit(track_image, (0, 0))
# Start the animation loop
running = True
while running:
    screen.blit(track_image, (0, 0))
    data= ser.readline().decode().strip()
    print(data)
    if data=="open":
        #close1()
        print("Executing open1")
        open1()
            
    elif data=="close":
        #open1()
        close1()
pygame.quit()