#include <iostream>
#include "Wormhole.h"

using namespace std;

int main()
{
    cout << "Game main!" << endl;

    Wormhole* game = new Wormhole();

    cout << "Game started!" << endl;

    game->go();

    return 0;
}
