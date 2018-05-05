# Polar Dots
This project was made for the Colorado College Coding Club 24 hour hackathon 2018. I chose the topic "video game with unusual controls" and I worked alone. The name of the game is Polar Dots.

## Description of game
The premise of this game is that instead of the controls being in cartesian coordinates, the controls are in polar coordinates. So instead of being able to move up/down/left/right, you can move clockwise/counterclockwise/in/out. This is surprisingly counterintuitive and difficult to control. Also, the movement speed is linear not radial, so to get to a point on the oposite side of the screen it is faster to shrink the circle, go around, and expand the circle. The point of the game is to get as many points as possible by picking up dots. Red dots are -50 points, green are 1 point, blue are 5 points, and purple are 25 points. There are also grey dots which extend the time by 30 seconds. This should theoretically work on linux, macOS, and windows because the libraries I used are cross platform, however I have only tested it on linux.

## Breakdown of work
I used GTK+ and GDK for the windowing and event listeners and cairo for the graphics. The rest of the work is my own.
