#include <SDL2/SDL.h>
#include <iostream>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect stick01{0,0,25,100};
    SDL_Rect stick02{615,0,25,100};
    SDL_Rect ball{320,240,50,50};

    // booleans for ball movement
    bool balltox = true;
    bool balltoy = true;

    int score = 0;
    int lastScore = 0;
    
    bool running = true;

    while (running) {
        SDL_Event event;

		// stick02 movement
		if (ball.y > stick02.y && stick02.y != 380) {
			stick02.y += 10;
		} else if (ball.y < stick02.y && stick02.y != 0) {
			stick02.y -= 10;
		}

		    // Update ball position
    		 ball.x += (balltox ? 1 : -1); 
   		 ball.y += (balltoy ? 1 : -1); 

    		// Check for collision with window edges
    		if (ball.x <= 0 || ball.x >= 590) {
        		balltox = !balltox; 
        		score--;
    		}
    		if (ball.y <= 0 || ball.y >= 430) {
        		balltoy = !balltoy;
    		}


		// Check for collision with paddles
		if (ball.x + ball.w >= stick01.x && ball.x <= stick01.x + stick01.w && ball.y + ball.h >= stick01.y && ball.y <= stick01.y + stick01.h) {
    		balltox = !balltox; // Reverse horizontal direction
    		score++;
		}
		if (ball.x + ball.w >= stick02.x && ball.x <= stick02.x + stick02.w && ball.y + ball.h >= stick02.y && ball.y <= stick02.y + stick02.h) {
    		balltox = !balltox; // Reverse horizontal direction
		}

		if (lastScore != score) {
			std::cout << "score: " << score << "\n";
		}	
		lastScore = score;
		
        // event listener
        while (SDL_PollEvent(&event)) {
        	// stick01 movement
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_w:
						if (stick01.y != 0) {
							stick01.y -= 10;
						}
						break;
					case SDLK_s:
						if (stick01.y != 380) {
							stick01.y += 10;
						}
						break;
				}
			}

        	// close window
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        SDL_RenderFillRect(renderer, &stick01);
        SDL_RenderFillRect(renderer, &stick02);
        SDL_RenderFillRect(renderer, &ball);

        SDL_RenderPresent(renderer);

        SDL_Delay(7);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
