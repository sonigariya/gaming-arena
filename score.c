#include "score.h"

/* Calculate XP based on level and attempts */
int calculateXP(int level, int attempts)
{
    if(level == 1)  // Easy Level
    {
        if(attempts < 5)
            return 20;
    }

    else if(level == 2)  // Medium Level
    {
        if(attempts < 8)
            return 30;
    }

    return 0;
}

/* Calculate Player Rank */
const char* calculateRank(int totalXP)
{
    if(totalXP >= 200)
        return "Champion";

    else if(totalXP >= 100)
        return "Master";

    else if(totalXP >= 50)
        return "Explorer";

    else
        return "Beginner";
}