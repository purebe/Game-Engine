// main_test.cpp
//
// Author: John Conder
// Date: 05/08/2012
//
// Purpose:
// This file should showcase a complete demo game using the game engine.

#include <Windows.h>

#include <iostream>

#include "GE_Core.h"
#include "GE_LoadAssets.h"
#include "GE_Draw.h"
#include "GE_Text.h"
#include "GE_TextStream.h"
#include "GE_Timer.h"
#include "GE_Metrics.h"

#include "GE_Rect.h"
#include "GE_Util.h"
#include "GE_Conversion.h"

//
// The ball object for the game.
//
class Ball
{
private:
	GE::Rect screenPosition;
	GE::Rect spriteSheetPosition;

	float speed;

	SDL_Surface* sprite;
public:
	Ball(int screenWidth, int screenHeight);

	void Load();
	void Unload();
	void Update();
	void Draw(float interpolation, SDL_Surface* screen);
};

//
// The Ball's constructor initializes member data.
//
Ball::Ball(int screenWidth, int screenHeight)
{
	// The GERect screenPosition determines where the ball is drawn to on
	// the screen.  Only considers GERect.x and GERect.y.
	screenPosition.x = (float)screenWidth / 2;
	screenPosition.y = (float)screenHeight / 2;

	// The GERect spriteSheetPosition determines the position on the sprite
	// sheet that the sprite resides on.  If left to NULL it's assumed to use
	// the entire sprite.
	GE::MakeRect(&spriteSheetPosition, 0, 0, 16, 16);

	// Speed is measured in pixels per 1/60th of a second.
	speed = 0.55f;
}

//
// Load's the balls resources.
//
void Ball::Load()
{
	sprite = GE::LoadAssetImg("res\\img\\ball.png");
}

//
// Unload's the balls resources.
//
void Ball::Unload()
{
	SDL_FreeSurface(sprite);
	sprite = nullptr;
}

//
// Run the logic for the ball object.
//
void Ball::Update()
{
	// Update the balls position.
	screenPosition.x += speed;
	screenPosition.y += speed;
}

//
// Draw the ball (position based on interpolation.)
//
void Ball::Draw(float interpolation, SDL_Surface* screen)
{
	// We keep the position and interpolated position of the ball as a GERect
	// which keeps its data members as 'float'.
	GE::Rect interpolPosition;

	interpolPosition.x = screenPosition.x + (speed * interpolation);
	interpolPosition.y = screenPosition.y + (speed * interpolation);

	// The final position must be passed as 'Sint16' data type, so we have
	// to convert (waiting until the last possible second preserves the most
	// data.)
	SDL_Rect finalPosition;
	finalPosition.x = (Sint16)(interpolPosition.x + 0.5f);
	finalPosition.y = (Sint16)(interpolPosition.y + 0.5f);

	// We store this information as a GERect for consistency, however it should
	// be converted to an SDL_Rect before passing it on.
	SDL_Rect _spriteSheetPosition;
	_spriteSheetPosition = GEToSDLRect(spriteSheetPosition);

	// Finally draw the ball to the screen.
	GE::BlitImage(sprite, _spriteSheetPosition, screen, finalPosition);
}

//
// This class is the entry-point for your game using the engine.
//
class DemoGame : public GE_Core
{
private:
	GE_Text Text;
	GE_Text Debug;
	TTF_Font* font;

	GE_FPS fps;
	double _fps;

	Ball ball;
public:
	DemoGame(Uint32 ScreenWidth, Uint32 ScreenHeight);
	~DemoGame() { }

	void Load();
	void Unload();
	void Draw(float interpolation);
	void Update();
	void MetricUpdate();

	void BaseUpdate();
};

//
// The constructor allows for defining the window resolution and title.
// Any initialization code should be handled here.
//
DemoGame::DemoGame(Uint32 ScreenWidth, Uint32 ScreenHeight) : ball(ScreenWidth, ScreenHeight)
{
	screenWidth = ScreenWidth;
	screenHeight = ScreenHeight;

	windowTitle = "Demo Game";
	
	// Initialize private members
}

//
// Override the Load() function for loading our game assets.
//
void DemoGame::Load()
{
	// Load the font for our font engines
	font = nullptr;
	font = TTF_OpenFont("res/fonts/Cantarell/Cantarell-Regular.ttf", 24);

	if ( font == nullptr )
	{
		std::cerr << "Unable to load font.\n";
	}

	// Set up the GE_Font engines
	SDL_Color textColor = {255, 255, 255};
	SDL_Color debugColor = {255, 0, 0};

	Text.SetFont(font);
	Text.SetColor(textColor);

	Debug.SetFont(font);
	Debug.SetColor(debugColor);

	// Set up the FPS metric
	fps.Start();

	// Load the ball for our example
	ball.Load();

	// Push the FPS counter
	_fps = 0;
	GE_TextStream txtStrm;

	txtStrm << "FPS: " << &_fps;
	Text.Print(txtStrm, 50000);
}

//
// Override the Unload() function for unloading game assets.
//
void DemoGame::Unload()
{
	// Free the font we used
	if ( font != nullptr )
	{
		TTF_CloseFont(font);
		font = nullptr;
	}

	// Always clean up
	ball.Unload();
}

//
// Override the Draw(float) function to draw to the screen.
//
void DemoGame::Draw(float interpolation)
{
	// Draw game objects
	ball.Draw(interpolation, screen);

	// Draw the printed text from our font engines
	Text.DrawStrings(screen);
	Debug.DrawStrings(screen);
}

//
// Override the Update() function to handle game logic.
//
void DemoGame::Update()
{
	// Run game object logic
	ball.Update();

	// Font Logic
	Text.Update();
	Debug.Update();
}

//
// Override the BaseUpdate() function to handle SDL events.
//
void DemoGame::BaseUpdate()
{
	while( SDL_PollEvent(&curEvent) )
	{
		if( curEvent.type == SDL_QUIT )
		{
			gameRunning = false;
		}
	}
}

//
// Override the MetricUpdate() function to handle non-rate locked functionality.
//
void DemoGame::MetricUpdate()
{
	// Metric Logic
	fps.Update();
	_fps = fps.GetFPS();
}

//
// Entry point for the program.
//
int main(int argc, char* args[])
{
	DemoGame game(800,600);
	game.Run();

	return 0; 
}