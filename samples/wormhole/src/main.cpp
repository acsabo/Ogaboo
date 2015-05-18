#include <iostream>
#include "Wormhole.h"

using namespace std;

int main()
{
    Wormhole* game = new Wormhole();

    cout << "Game started!" << endl;

    game->go();

    return 0;
}
