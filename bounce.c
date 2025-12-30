#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_BLUE 0x0000FFFF
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0x00000000
#define A_GRAVITY 1



typedef struct {
    int x;
    int y;
    int radius;
    int vx;
    int vy;

} Circle;

//Circle is (X - Xcenter)^2 + (Y - Ycenter)^2 = radius^2

void FillCircle(SDL_Surface *psurface, Circle circle){

    int low_x = circle.x - circle.radius; // leftmost x coordinate
    int low_y = circle.y - circle.radius;   // bottommost y coordinate
    int high_x = circle.x + circle.radius;  // rightmost x coordinate
    int high_y = circle.y + circle.radius; // topmost y coordinate

    double radius_squared = circle.radius * circle.radius;


    for(int x = low_x; x <= high_x; x++)
    {
        for(int y = low_y; y <= high_y; y++)
        {
            double center_distance_squared = (x- circle.x) * (x - circle.x) + (y - circle.y) * (y - circle.y);
            
            // Check if the pixel is inside the circle, 
            //if this distance is less than radius squared then that pixel is inside the circle
            if(center_distance_squared < radius_squared)
            
            {
                SDL_Rect pixel = (SDL_Rect){x, y, 1, 1};
                SDL_FillRect(psurface, &pixel, COLOR_WHITE);
            }
        

        }
    }



}


void step(Circle *circle){

    circle->x = circle->x + circle->vx;
    circle->y = circle->y + circle->vy;
    circle->vy += A_GRAVITY;

}



int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *pwindow = SDL_CreateWindow("Bouncing Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    
    SDL_Rect erase_rect = (SDL_Rect){0, 0, WIDTH, HEIGHT};
    
    Circle circle = {WIDTH/2, HEIGHT/2, 10, 0, 0};

    SDL_Event event;
    bool app_running = true;
    while(app_running){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app_running = 0;
        }

    }
    SDL_FillRect(psurface, &erase_rect, COLOR_BLACK);
    step(&circle);
    FillCircle(psurface, circle);
    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(30);
}
}