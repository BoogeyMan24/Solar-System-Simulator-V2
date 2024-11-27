# gravity-simulator-V2
Original version [here](https://github.com/BoogeyMan24/gravity-simulator-V1)
### DON'T FORGET TO SET TICK SPEED!
It defaults to 0 and so no movement. You can change it in the main tab of ImGui.

# About this project
A gravity/solar system simulation application written in c++ using OpenGL. I coded for this project: an input system (mouse and keyboard),camera system, entities, settings, physics calculations, time steps, the renderer (creation of indices, settings up shaders, and drawing to screen). The rendering part was fairly difficult for me since this was my first experience with graphics programming ever, esspecially considering how low level it is, but I did manage after hours of being clueless (OpenGL doesn't give the most comphensive errors). I have also implemented batch rendering for better performance (all quads are grouped into 1 draw call for that frame). This allows OpenGL to handle all draws in one go rather than having to set up everything over and over again for each entity.

## Features:
 - Camera movement (panning and zomming)
 - ImGui inspector (left click on object and see/change properties)
 - ImGui changable settings (Camera speed, Object properties, tick speed, etc.)
 - Tick speed (speed up/slow down time)
 - Planet creation (right click -> left click -> change properties)

### The build comes with a (somewhat) stable 3 body orbit (source [here](https://en.wikipedia.org/wiki/Three-body_problem)) values (values can be found [here](https://en.wikipedia.org/wiki/Three-body_problem#cite_note-13)):
 - Object 1: velocity (-0.97000436f, 0.24308753f), position (0.4662036850f, 0.4323657300f)
 - Object 2: velocity (0.0f, 0.0f), position (-0.93240737f, -0.86473146f)
 - Object 3: velocity (0.97000436f, -0.24308753f), position (0.4662036850f, 0.4323657300f)
 - Gravtiational constant: 1.0f

![3-Body-Orbit-shortened](https://github.com/BoogeyMan24/Solar-System-Simulator-V2/assets/76151726/1d923d22-c61f-4a0e-a74d-c6c918498c15)

*Sorry about bad quality, it wouldn't let me upload larger files*

### I have set a few modifiers on the 3 body orbit to make it move faster and be more visible

## Don't forget:
 - The higher the tick speed the lower the accuracy: for better experience increase tick speed, for more realism decrease tick speed!
 - This was made on a mac for a mac and so there is no support for windows or linux, though, you can add it yourself.
