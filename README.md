# CANE2023
## Structure_Notes.md
What the other team does, that we could do, is define the joystick normally (not a pointer) and then pass
it *back* , for example, to the drive class by reference

what we are currently doing is passing the controller forwards from where it is defined in drive, meaning later, 
we need a double pointer to access it. This should work, but I wonder if passing it by reference is a better way.
* * *

UGLY MIRO BOARD: https://miro.com/app/board/uXjVP00XX58=/