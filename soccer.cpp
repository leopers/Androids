#include "soccer.hpp"

Robot::Robot(std::string robotName, std::size_t robotNumber)
            : name{robotName}, number{robotNumber}
{}

std::string Robot::getName() const{
  return name;
}

std::size_t Robot::getNumber() const{
  return number;
}


Attack::Attack(std::string robotName, std::size_t robotNumber)
              : Robot(robotName, robotNumber), markedGoals{0}
{}

void Attack::markGoal(){
  markedGoals++;
}

std::size_t Attack::goalCount() const{
  return markedGoals;
}

void Attack::reset(){
  markedGoals = 0;
}



Goalkeeper::Goalkeeper(std::string robotName, std::size_t robotNumber)
              : Robot(robotName, robotNumber), concededGoals{0}
{}

void Goalkeeper::concedGoal(){
  concededGoals++;
}

std::size_t Goalkeeper::getConcededGoals() const{
  return concededGoals;
}

void Goalkeeper::reset(){
  concededGoals = 0;
}



Defense::Defense(std::string robotName, std::size_t robotNumber)
              : Robot(robotName, robotNumber), fouls{0}
{}

void Defense::makeFoul(){
  fouls++;
}

std::size_t Defense::getFouls() const{
  return fouls;
}

std::size_t Defense::goalCount() const{
  return 0;
}

void Defense::reset(){
  fouls = 0;
}



Team::Team(std::string teamName, 
          std::array<std::shared_ptr<Robot>, 10> teamPlayers, std::shared_ptr<Goalkeeper> goalkeeper)
          :
          players{teamPlayers}, goalkeeper{goalkeeper}, name{teamName}
{}

std::size_t Team::goalBalance() const{
  std::size_t balance = 0;
  for(auto x : players){
    balance += x->goalCount();
  }
  return balance;
}

int main(){}