#include "score.h"

int calculateXP(int matchedPairs, int attempts)
{
    int xp = matchedPairs * 10;

    if (attempts <= matchedPairs + 2)
    {
        xp += 20;
    }
    else if (attempts <= matchedPairs + 5)
    {
        xp += 10;
    }

    return xp;
}

const char* calculateRank(int totalXP)
{
    if (totalXP < 50)
        return "Beginner";

    else if (totalXP < 150)
        return "Explorer";

    else if (totalXP < 300)
        return "Memory Master";

    else
        return "Champion";
}