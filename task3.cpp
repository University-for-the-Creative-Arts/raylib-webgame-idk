#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::this_thread; // sleep_for
using namespace std::chrono;     // seconds

// --- Story Node Structure ---
struct StoryNode {
    string text;
    vector<StoryNode*> choices;
    vector<string> options;
    bool isEnding;

    StoryNode(string t, bool ending = false) {
        text = t;
        isEnding = ending;
    }

    void addChoice(StoryNode* node, string optionText) {
        choices.push_back(node);
        options.push_back(optionText);
    }

    void printNode() {
        cout << "\n--------------------------\n";
        for (char c : text) {
            cout << c;
            sleep_for(milliseconds(15)); // slow print for effect
        }
        cout << "\n--------------------------\n";
    }

    void printOptions() {
        for (size_t i = 0; i < options.size(); ++i) {
            cout << i + 1 << ". " << options[i] << endl;
        }
    }
};

// --- Game Logic ---
void playStory(StoryNode* root) {
    StoryNode* current = root;

    while (true) {
        current->printNode();

        if (current->isEnding) {
            cout << "\n[THE END]\n";
            break;
        }

        current->printOptions();
        int choice;

        cout << "\nEnter your choice: ";
        while (!(cin >> choice) || choice < 1 || choice > current->choices.size()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Try again: ";
        }

        current = current->choices[choice - 1];
    }
}

// --- Main Function ---
int main() {
    // --- Create Story Nodes ---
    StoryNode* start = new StoryNode("You wake up in a crashed car. Smoke rises from the hood. The forest is silent except for whispers in the distance.");

    StoryNode* path1 = new StoryNode("You follow a narrow path deeper into the forest. The whispers grow louder.");
    StoryNode* path2 = new StoryNode("You stay by the road, hoping for help. Hours pass... something is watching you.");

    StoryNode* cave = new StoryNode("You find a hidden cave. It's dark but strangely warm.");
    StoryNode* tower = new StoryNode("You find a rusted radio tower. Maybe you can send a signal.");
    StoryNode* shadow = new StoryNode("A shadowy figure emerges. You freeze. It whispers your name.", true);
    StoryNode* rescue = new StoryNode("A ranger finds you in the morning. You're safe... but changed somehow.", true);
    StoryNode* trapped = new StoryNode("Inside the cave, the entrance collapses. You're not alone in the dark...", true);
    StoryNode* signal = new StoryNode("You manage to send a signal. A chopper arrives. You're rescued!", true);

    // --- Build Tree Structure ---
    start->addChoice(path1, "Leave the car and follow the whispers.");
    start->addChoice(path2, "Stay by the road and wait.");

    path1->addChoice(cave, "Enter the strange cave.");
    path1->addChoice(tower, "Climb the hill toward the old radio tower.");

    path2->addChoice(shadow, "Investigate the feeling of being watched.");
    path2->addChoice(rescue, "Hide in the car and wait until morning.");

    cave->addChoice(trapped, "Go deeper into the cave.");
    tower->addChoice(signal, "Try to fix the radio and send a signal.");

    // --- Start Game ---
    playStory(start);

    // --- Clean Up (Optional) ---
    delete start; delete path1; delete path2;
    delete cave; delete tower;
    delete shadow; delete rescue;
    delete trapped; delete signal;

    return 0;
}
