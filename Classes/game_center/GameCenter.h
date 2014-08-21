#ifndef AVALON_GAMECENTER_H
#define AVALON_GAMECENTER_H

class GameCenter
{
public:
    void login();

    bool showAchievements();
    void postAchievement(const char* idName, int percentComplete);
    void clearAllAchievements();

    bool showScores();
    void postScore(const char* idName, int score);
    void clearAllScores();

};

#endif /* AVALON_GAMECENTER_H */
