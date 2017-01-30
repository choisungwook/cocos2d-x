#ifndef __RESOURCES_H__
#define __RESOURCES_H__

namespace resources {
	const double const gamespeed = 2.0f / 60.0f;

	/*
		image paths
	*/	
	const char* const character = "me.png";
	const char* const ball = "ball2.png";
	const char* const background = "background2.png";

	//setting image
	const char* const setting = "settings.png";

	//option images
	const char* const menubackground = "menu/background.png";
	const char* const startgame = "menu/startgame.png";
	const char* const resumegame = "menu/resumegame.png";
	const char* const backgame = "menu/backgame.jpg";
	const char* const endgame = "menu/endgame.png";
	const char* const home = "menu/home.png";
	const char* const menu = "menu/menu.png";

	//item images
	const char* const Itemeat = "item/eat.png";

	//sprite z order
	const int const characterOrder = 2;	
	const int const menuOrder = 1;
}

#endif