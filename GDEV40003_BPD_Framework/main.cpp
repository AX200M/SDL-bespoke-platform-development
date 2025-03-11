#include "SDL.h"
#include "constants.h"
#include <iostream>

using namespace std;

//Globals
SDL_Window* g_window = nullptr;

//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* argv[])
{
	//Flag to check if quit
	bool quit = false;

	if (InitSDL())
	{
		while (!quit)
		{
			quit = Update();
		}
	}

	CloseSDL();
	return 0;
}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "[!] SDL did not intialise." << endl;
		cout << "Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//Setup passed so create window 
		g_window = SDL_CreateWindow("Bespoke Platform Development",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//Check if window was created
		if (g_window == nullptr)
		{
			//Window Failed
			cout << "[!] Window was not created." << endl;
			cout << "Error: " << SDL_GetError();
			return false;
		}
	}
}

void CloseSDL()
{
	//Release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	SDL_Quit();
}

bool Update()
{
	//Event Handler
	SDL_Event e;

	//Get Events
	SDL_PollEvent(&e);

	//Handle events
	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			cout << "STOP PRESSING A!!!!! F#CK" << endl;
			break;
		}
	default:
		break;
	}

	return false;
}