
#include <iostream>
using namespace std;

class Fighter {
    private:
        const char* name;
        int health;
        int maxHealth;
        int damage;

    public:
        Fighter(const char* name, int health, int damage)
            : name(name), health(health),
            maxHealth(health), damage(damage) {}

        void TakeDamage(int amount) {
            health -= amount;

            if (health < 0) {
                health = 0;
            }
        }

        void Attack(Fighter& target) const {
            target.TakeDamage(damage);
        }

        bool IsAlive() const {
            return health > 0;
        }

        void PrintStatus() const {
            cout << name << ": "
                << health << "/" << maxHealth
                << " HP\n";
        }
};

void PrintFighter(const Fighter& fighter) {
    fighter.PrintStatus();
}

class Game {
    private:
        Fighter player;
        Fighter enemies[3];
        Fighter* currentTarget = nullptr;

    public:
        Game()
            : player("anton", 30, 8),
            enemies{
                {"Enemy 1", 12, 3},
                {"Enemy 2", 18, 4},
                {"Enemy 3", 24, 5}
            } {}

        bool TrySelectTarget(int number, Fighter*& outTarget) {
            outTarget = nullptr;

            if (number < 1 || number > 3) {
                return false;
            }

            if (!enemies[number - 1].IsAlive()) {
                return false;
            }

            outTarget = &enemies[number - 1];
            return true;
        }

        bool AllEnemiesDefeated() const {
            for (int i = 0; i < 3; i++) {
                if (enemies[i].IsAlive()) {
                    return false;
                }
            }

            return true;
        }

        void Run() {
            int command;
            int number;
            while (player.IsAlive() && !AllEnemiesDefeated()) {
                PrintFighter(player);

                for (int i = 0; i < 3; i++) {
                    PrintFighter(enemies[i]);
                }

                cout << "\nCurrent target: ";

                if (currentTarget != nullptr) {
                    currentTarget->PrintStatus();
                }
                else {
                    cout << "None\n";
                }

                cout << "\n1 - Select target" << endl;
                cout << "2 - Attack" << endl;
                cout << "0 - Exit" << endl;
                cout << "Choose action: ";

                if (!(cin >> command)) {
                    cout << "Input error!" << endl;
                    break;
                }

                if (command == 0) {
                    cout << "Game over" << endl;
                    break;
                }

                if (command == 1) {
                    cout << "Select enemy (1-3): ";

                    if (!(cin >> number)) {
                        cout << "Input error!" << endl;
                        break;
                    }

                    if (TrySelectTarget(number, currentTarget)) {
                        cout << "Target selected!" << endl;
                    }
                    else {
                        cout << "Invalid target!" << endl;
                    }
                }
                else if (command == 2) {
                    if (currentTarget == nullptr) {
                        cout << "Select a target first!" << endl;
                        continue;
                    }

                    player.Attack(*currentTarget);
                    cout << "Anton attacks!" << endl;

                    if (!currentTarget->IsAlive()) {
                        cout << "Enemy defeated!" << endl;
                        currentTarget = nullptr;

                        if (AllEnemiesDefeated()) {
                            cout << "\nYou win!" << endl;
                            break;
                        }
                    }
                    else {
                        currentTarget->Attack(player);
                        cout << "Enemy attacks Anton!" << endl;

                        if (!player.IsAlive()) {
                            cout << "\nYou lose!" << endl;
                            break;
                        }
                    }
                }
                else {
                    cout << "Error" << endl;
                }
            }
        }
};

int main() {
    Game game;
    game.Run();

    return 0;
}
