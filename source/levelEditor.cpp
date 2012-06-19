/*
 *      VBOs.cpp
 *      
 *      Copyright 2007 System <system@localhost>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */
 //#ifdef WIN32_NOT_SO_LEAN
//	#define _WIN32
//        #include <windows.h>
//
//	#pragma comment(linker, "OPT:NOWIN98")
//	#pragma comment(lib, "opengl32.lib")
//	#pragma comment(lib, "glu32.lib")
//	#pragma comment(lib, "glut32.lib")
// #endif

#include <iostream>
#include "LEgame.h"

void printHelp();

int main(int argc, char** argv)
{
	Game* meGame = Game::getInstance();
	meGame->init(argc,argv);
	printHelp();
	meGame->run();
}

void printHelp()
{
	cout<<"Keymap:\n";
	cout<<"\"A\" and \"D\" rotate around the model's local Y axis.\n";
	cout<<"\"W\" and \"S\" rotate around the model's local X axis.\n";
	cout<<"\"E\" and \"C\" rotate around the model's local Y axis.\n";
	cout<<"\"Z\" and \"X\" moves the model in the Y axis(up and down in the screen).\n";
	cout<<"UP and DOWN moves the model in the Z axis(toward and away from the camera).\n";
	cout<<"RIGHT and LEFT moves the model in the X axis(left and right in the screen).\n";
	cout<<"\"U\" and \"J\" moves the light in the Y axis(up and down in the screen).\n";
	cout<<"\"H\" and \"K\" moves the light in the X axis(left and right in the screen).\n";
	cout<<"[Shift] doubles rate of all other keys.\n";
	cout<<"[Esc] and \"Q\" quits the program.\n";
	cout<<"\"t\" tabs through loaded models.\n";
	cout<<"\"T\" tabs through loaded lights.\n";
	cout<<"\"g\" and \"G\" tabs through loaded shaders.\n";
	cout<<"\"I\" load models(still a little wanky, but you can use it).\n";
	cout<<"\"L\" Add a default light.\n";
	cout<<"\"O\" Save Out level(still a little wanky, but you can use it).\n";
	cout<<"\"P\" Load In level(still a little wanky, but you can use it)\n";
	cout<<"\"_\" Empty the level.\n";
	cout<<"\"-\" Delete object(Not implemented at the moment).\n";
	cout<<"\"f\" instance currently selected model.\n";
	cout<<"\"F\" duplacate currently selected model.\n";
	cout<<"\"v\" delete current shader.\n";
	cout<<"\"V\" add shader(vertex and then fragment).\n";
	cout<<"LMB to select the model under the mouse cursor.\n";
	cout<<"MMB drag to pan camera.\n";
	cout<<"MMB+[Shift] drag to rotate the camera.\n";
	cout<<"MWHEEL to zoom camera in and out.\n";
	cout<<"RMB to bring up menu.\n";
	cout<<"\"F2\" toggles lighting.\n";
	cout<<"\"F3\" toggles textures.\n";
	cout<<"\"F4\" toggles mipmaps on the currently selected model.\n";
	cout<<"\"F1\" toggles fullscreen(only working in Windows...)."<<endl;
}
