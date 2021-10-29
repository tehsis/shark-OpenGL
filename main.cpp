#include <iostream>
#include "shark/shark.h"

int main() {

    try {
        auto context = Shark(1024, 768, "My App");
        while(!context.ShouldClose()) {
            context.BackgroundColor(BLACK);
            context.Color(BLUE);
            //context.Triangle(0.0f, 0.5f);
            context.Color(RED);
            context.Triangle(0.0f, 0.0f);
            context.Color(GREEN);
           // context.Triangle(0.5, 0.0f);
            context.Square(0.5f, 0.5f);
            context.Draw();
            context.PollEvents();
        }
    } catch (const char* e) {
        std::cout << "Could not create window: " << e << std::endl;
    }

   
}