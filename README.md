# gravity-simulator-V2
Original version [here](https://github.com/BoogeyMan24/gravity-simulator-V1)
## DON'T FORGET TO SET TICK SPEED!
### It defaults to 0 and so no movement. Its in the main tab of ImGui.

## New Features:
 - Camera movement (panning and zomming)
 - ImGui inspector (left click on object and see/change properties)
 - ImGui changable settings (Camera speed, Object properties, tick speed, etc.)
 - Tick speed (speed up/slow down time)
 - Planet creation (right click -> left click -> change properties)

### The build comes with a (somewhat) stable 3 body orbit (source [here](https://en.wikipedia.org/wiki/Three-body_problem)) values:
 - Object 1: velocity (-0.97000436f, 0.24308753f), position (0.4662036850f, 0.4323657300f)
 - Object 2: velocity (0.0f, 0.0f), position (-0.93240737f, -0.86473146f)
 - Object 3: velocity (0.97000436f, -0.24308753f), position (0.4662036850f, 0.4323657300f)
 - Gravtiational constant: 1.0f
 
### I have set a few modifiers to make it faster and have bigger values for viewability

# The higher the tick speed the lower the accuracy: for better experience increase tick speed, for more realism decrease tick speed!

# This was made on a mac and so there is no support for windows, though, you can add it yourself.