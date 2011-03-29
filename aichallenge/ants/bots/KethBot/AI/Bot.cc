#include "Bot.h"
#include "Ant.h"
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef __DEBUG
#include "Logger.h"
#endif

#include "globals.h"

Bot::Bot()
{

};

void Bot::playGame()
{
    cin >> state;

    #ifdef __DEBUG
    logger.logPreState(true);
    #endif
    while(cin >> state)
    {

        onThink();
        endTurn();
    }
};

void Bot::firstMove()
{
    #ifdef __DEBUG
    logger.debugLog << "ACTION: firstMove()" << endl;
    #endif
}

void Bot::validateAnts()
{
    int i = 0;
    while (true) {
        i = 0;
        std::list<Ant*>::iterator iter_ant;
        for (iter_ant = gameMap.getAnts().begin(); iter_ant != gameMap.getAnts().end(); iter_ant++)
        {
            Ant* ant = (*iter_ant);
            ant->hasMoved = false;

            if (state.grid[ant->getLocation().row][ant->getLocation().col] != 'a') {
                Ant* foundAnt = gameMap.getAntAt(ant->getLocation());
                if (foundAnt) {
                    gameMap.setAntAt(foundAnt->getLocation(), NULL);
                    delete foundAnt;
                    i++;
                }
            }
            if (i > 0) break;
        }
        if (i == 0) break;
    }
}

void Bot::makeMoves()
{
    if (state.turn == 1) firstMove();
    #ifdef __DEBUG
    logger.debugLog << "ACTION: makeMoves()" << endl;
    #endif

    for(int ant_id = 0; ant_id < (int)state.ants.size(); ant_id++)
    {
        Location loc = state.ants[ant_id];
        Ant* ant = gameMap.getAntAt(loc);
        if (ant) {
            ant->onThink();
        } else {
            #ifdef __DEBUG
            logger.logError("Structural ant at location not found");
            #endif
        }
    }
}

void Bot::updateMap()
{
    state.updateFogOfWar();
    logger.logMapState();
}

void Bot::onThink()
{
    #ifdef __DEBUG
    logger.logPreState(false);
    #endif

    validateAnts();
    updateMap();
    makeMoves();

    #ifdef __DEBUG
    if ((int)state.ants.size() != (int)gameMap.getAnts().size()) {
        logger.logError("Number of ants given is not equal to structural ants");
    }

    logger.logPostState();
    #endif


};

void Bot::endTurn()
{
    state.reset();
    state.turn++;

    cout << "go" << endl;
};
