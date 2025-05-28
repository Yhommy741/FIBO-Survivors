#include "game.h"

int main(int argc, char* argv[]) 
{   
    //Create a Game
    Game game(argc, argv);

	//Loading resources and initializing the game
	game.init();

	//Run the game loop
    game.run();

    return 0;
}
