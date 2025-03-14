#include "SDL.h"
#include "SDL_image.h"
#include "constants.h"
#include <iostream>

using namespace std;

//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();

int main(int argc, char* argv[])
{
	//Flag to check if quit
	bool quit = false;

	if (InitSDL())
	{
		while (!quit)
		{
			Render();
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
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_renderer != nullptr)
	{
		//Init PNG Loading
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			cout << "[!] SDL_Image could not initialise." << endl;
			cout << "Error: " << IMG_GetError();
			return false;
		}
	}
	else
	{
		cout << "[!] Renderer could not initialise." << endl;
		cout << "Error: " << SDL_GetError();
		return false;
	}
	g_texture = LoadTextureFromFile("Images/DD.jpg");
	if (g_texture == nullptr)
	{
		return false;
	}
}

void Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(g_renderer);
	//Where to render texture
	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	//Render to screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);
	//Update Screen
	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path)
{
	//Remove mem used for previous texture
	FreeTexture();

	SDL_Texture* p_texture = nullptr;

	//Load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr)
		{
			cout << "[!] Unable to create texture from surface" << endl;
			cout << "Error: " << SDL_GetError();
		}
		SDL_FreeSurface(p_surface);
	}
	return p_texture;
}

void FreeTexture()
{
	//Check if texture exists before removing 
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}

void CloseSDL()
{
	//Clear Texture 
	FreeTexture();
	//Release renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
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