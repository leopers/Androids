#ifndef SOCCER_CPP
#define SOCCER_CPP

#include <array>
#include <cstddef>
#include <iostream>
#include <memory>

class Robot{
public:  
  Robot(std::string robotName, std::size_t robotNumber);
  std::string getName() const;
  std::size_t getNumber() const;
  virtual std::size_t goalCount() const = 0;

  virtual void reset() = 0;

private:
  std::string name;
  std::size_t number;
};

class Attack : public Robot{
public:
  Attack(std::string robotName, std::size_t robotNumber);

  void markGoal();
  std::size_t goalCount() const override;
  void reset() override;

private:
  std::size_t markedGoals;
};

class Goalkeeper : public Robot{
public:
  Goalkeeper(std::string robotName, std::size_t robotNumber);

  void concedGoal();
  std::size_t getConcededGoals() const;
  void reset() override;

private:
  std::size_t concededGoals;
};

class Defense : public Robot{
public:
  Defense(std::string robotName, std::size_t robotNumber);

  void makeFoul();
  std::size_t getFouls() const;
  std::size_t goalCount() const override;
  void reset() override;

private:
  std::size_t fouls;
};

class Team{
public:
  Team(std::string name, std::array<std::shared_ptr<Robot>, 10> players, std::shared_ptr<Goalkeeper> goalkeeper);
 
  std::array<std::shared_ptr<Robot>, 10> players;
  std::shared_ptr<Goalkeeper> goalkeeper;

  std::string getName() const;
  std::size_t goalBalance() const;

private:
  std::string name;
};

#endif