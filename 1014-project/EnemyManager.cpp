#include "EnemyManager.h"
#include "Game.h"


EnemyManager::EnemyManager(){

}


EnemyManager::~EnemyManager(){
}


void EnemyManager::Update(){
	// for loop
	if (enemyTimer > 2000)
		enemyTimer = 0;

	enemyTimer++;
  // Generate enemy according to the time lapes from game start and making time limit
  if (enemyTimer % 100 == 0) {
    enemies.push_back(new Enemy(RandX(), RandY(), RED));
  }
  if (enemyTimer % 500 == 0) {
	  enemies.push_back(new Enemy(RandX(), RandY(), BLUE));
  }
  if (enemyTimer % 1000 == 0) {
	  enemies.push_back(new Enemy(RandX(), RandY(), PURPLE));
  }
  if (enemyTimer % 2000 == 0) {
	  enemies.push_back(new Enemy(1200, 200, BOSS));
  }

  for (int i = 0; i < enemies.size(); i++){
		enemies[i] -> Update();
    if (enemies[i]->eDestR.x < 0 || enemies[i]->eDestR.x > 1300 ||
      enemies[i]->eDestR.y < 0 || enemies[i]->eDestR.y > 800){
      enemies[i] -> Clean();
      delete enemies[i];
      enemies[i] = nullptr;
      enemies.erase(enemies.begin() + i);
    }
	}
  enemies.shrink_to_fit();
}


void EnemyManager::Render(){
  for (int i = 0; i < enemies.size(); i++){
		enemies[i] -> Render();
	}
}


void EnemyManager::Clean(){
  for (int i = 0; i < enemies.size(); i++){
    enemies[i] -> Clean();
		delete enemies[i];
		enemies[i] = nullptr;
	}
  enemies.clear();
  enemies.shrink_to_fit();


}
