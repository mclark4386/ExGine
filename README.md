ExGine
======

My first game engine... stopped working on it about 3 years ago, but
thought people might like a look at the code... I was focusing on
playing with the latest techniques of the time (OpenGL3 was just
released). 

Also the code in the animatedMesh branch is probably newer and potentially more interesting.


INSTALL
----------------------------------
Windows:
copy the data folder and the exe file where ever (use the .dev file in the source folder to compile if there is no exe)

Linux:
copy the data folder and the binary file where ever (use the Makefile in the source folder to compile if there is no binary, use make 32bit if you want to build a 32-bit on a 64-bit system)



LICENSE: TBA (till then all rights reserved by Matthew Clark, and this may not be used by anyone without his approval)
COPYRIGHTS: Belong to those who originally made them (assume I didn't make the images, ship created by Travis Jones).


SHORTCUT KEYS
------------------------------------
	"A" and "D" rotate around the model's local Y axis.
	"W" and "S" rotate around the model's local X axis.
	"E" and "C" rotate around the model's local Y axis.
	"Z" and "X" moves the model in the Y axis(up and down in the screen).
	UP and DOWN moves the model in the Z axis(toward and away from the camera).
	RIGHT and LEFT moves the model in the X axis(left and right in the screen).
	"U" and "J" moves the light in the Y axis(up and down in the screen).
	"H" and "K" moves the light in the X axis(left and right in the screen).
	[Shift] doubles rate of all other keys.
	[Esc] and "Q" quits the program.
	"t" tabs through loaded models.
	"T" tabs through loaded lights.
	"I" load models(still a little wanky, but you can use it).
	"L" Add a default light.
	"O" Save Out level(still a little wanky, but you can use it).
	"P" Load In level(still a little wanky, but you can use it)
	"_" Empty the level.
	"-" Delete object(Not implemented at the moment).
	"f" instance currently selected model.
	"F" duplacate currently selected model.
	LMB to select the model under the mouse cursor.
	MMB drag to pan camera.
	MMB+[Shift] drag to rotate the camera.
	MWHEEL to zoom camera in and out.
	RMB to bring up menu.
	"F2" toggles lighting.
	"F3" toggles textures.
	"F4" toggles mipmaps on the currently selected model.
	"F1" toggles fullscreen(only working in Windows...).
