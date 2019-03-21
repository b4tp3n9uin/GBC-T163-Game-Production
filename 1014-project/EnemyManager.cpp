#include "EnemyManager.h"
#include "Game.h"


EnemyManager::EnemyManager(){

}


EnemyManager::~EnemyManager(){
}


void EnemyManager::Update()
{
  // Generate enemy according to the time lapes from game start
  if ((rand() % 100 + 1) % 2 == 1) {
    enemies.push_back(new Enemy(RandX(), RandY(), RandE()));
  }


  for (int i = 0; i < enemies.size(); i++){
		enemies[i] -> Update();
    if (enemies[i]->eDestR.x < 0 || enemies[i]->eDestR.x > 1024 ||
      enemies[i]->eDestR.y < 0 || enemies[i]->eDestR.y > 768){
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
