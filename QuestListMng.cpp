#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class questNode{
    public:
        int exp;
        string title;
        questNode* next;
        int order;

        questNode(int experience, string name, int order) : exp(experience), title(name), order(order), next(nullptr) {}
};
class questLine{
    public:
        questLine* line;
        int size;

        questLine(questLine* path, int amount): line(path), size(amount){}
};

//global variables
questNode* head_Q;
questNode* current;
questNode* previous;
int listSize = 0, placement = 0;
vector<questNode*> questLines;
vector<int> listSizes;

class nodeFunctions{
    public:
        void pushToStart(string name, int exp, int order){
            questNode* new_node = new questNode(exp, name, order);
            new_node->next = head_Q;
            head_Q = new_node;
            listSize++;
        }

        //inserts quest at position. EX: 4 would make it quest #4
        void pushToMiddle(string name, int exp, int newPosition){
            questNode* new_node = new questNode(exp, name, newPosition);
            current = head_Q;

            //sees if list has more than 2 quest
            if(listSize < 3){
                cout << "Not alot of quest. Maybe use a different method.";
                return;
            }
            if (newPosition <= 1 || newPosition > listSize) {
                cout << "Value for position parameter is invalid." << endl;
                return;
            }
            for (int i = 1; i < newPosition - 1 && current != nullptr; i++) {
                current = current->next;
            }
            if (current == nullptr) {
                cout << "Error! No nodes after this index!";
                return;
            }
            new_node->next = current->next;
            current->next = new_node;
            listSize++;
            updateOrder();
        }

        void pushToEnd(string name, int exp, int order){
            questNode* new_node = new questNode(exp, name, order);
            if(head_Q == nullptr){
                head_Q = new_node;
                
            }
            else{
                current = head_Q;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = new_node;
            }
            listSize++;
        }
        void updateOrder(){
            current = head_Q;
            int order = 1;
            while(current != nullptr){
                current->order = order++;
                current = current->next;
            }
        }
};
class searching{
    public:
        static void details(){
            cout << "Found the quest! It is " << current->title << " and gives " << current->exp << " EXP. It is quest number " << placement << endl;
            return;
        }
        //for all future functions in this class, the previous ptr is a potential tool for the deletion functions
        //returns the first instance of the name
        static questNode* searchByName(string QName){
            current = head_Q;
            placement = 0;
            while (current != nullptr) {
                placement++;
                if (current->title == QName) {
                    details();
                    return current;
                }
                previous = current;
                current = current->next;
            }
            cout << "Quest name not here. Was it something else?" << endl;
            return nullptr;
        }
        //returns the first instance of the EXP target
        static questNode* searchByEXP(int EXP){
            current = head_Q;
            placement = 0;
            while (current != nullptr) {
                placement++;
                if (current->exp == EXP) {
                    details();
                    return current;
                }
                previous = current;
                current = current->next;
            }
            cout << "No quest with this amount of EXP. Was it a different number?" << endl;
            return nullptr;
        }
        //quest 1 = position 1, NOT INDEX BASED
        //used for seeing which quest is in what position.
        static questNode* searchByPos(int pos){
            if(pos < 1){
                cout << "This position is invalid." << endl;
                return nullptr;
            }
            current = head_Q;
            placement = pos;
            while (current != nullptr && --pos > 0) {
                previous = current;
                current = current->next;
            }
            if (current == nullptr) {
                cout << "Out of range error." << endl;
                return nullptr;
            }
            details();
            return current;
        }
        static questNode* minNode(){
            current = head_Q;
            questNode* smallest = current;
            if(current == nullptr){
                return nullptr;
            }
            while (current != nullptr) {
                if(current->exp < smallest->exp){
                    smallest = current;
                }
                current = current->next;
            }
            return smallest;
        }
        static questNode* maxNode(){
            current = head_Q;
            questNode* biggest = current;
            if(current != nullptr && current->next == nullptr){
                return current;
            }
            while (current != nullptr) {
                if(current->exp > biggest->exp){
                    biggest = current;
                }
                current = current->next;
            }
            return biggest;
        }
};

class deletion{
    private:
        questNode *temp = nullptr;
        searching search;
        nodeFunctions nodes;
    public:
        void byName(string QName){
            temp = search.searchByName(QName);
            if(temp == nullptr){
                return;
            }
            if(temp == head_Q){
                deleteFirst();
                return;
            }
            else{
                previous->next = temp->next;
                listSize--;
                cout << temp->title << " Has been deleted." << endl;
                nodes.updateOrder();
            }
        }
        void byPosition(int pos){
            temp = search.searchByPos(pos);
            if(temp == nullptr){
                return;
            }
            if(temp == head_Q){
                deleteFirst();
            }
            else{
                previous->next = temp->next;
                listSize--;
                cout << temp->title << " Has been deleted." << endl;
                nodes.updateOrder();
            }
        }
        void deleteFirst(){
            if(head_Q == nullptr){
                cout << "Questline is empty, can't delete anything." << endl;
                return;
            }
            head_Q = head_Q->next;
            listSize--;
        }
        void deleteLast(){
            if(head_Q == nullptr){
                cout << "Questline is empty, can't delete anything." << endl;
                return;
            }
            if(head_Q->next == nullptr){
                head_Q = nullptr;
            }
            else{
                while (temp->next != nullptr){
                    previous = temp;
                    temp = temp->next;
                }
                previous->next = temp->next;
            }
            listSize--;
        }
        void clearLine(){
            listSize = 0;
            head_Q = nullptr;
            cout << "All nodes deleted in this questline.";
        }
};

class sorting{
    using Comparison = function<bool(questNode*, questNode*)>;
    public:
        void sort(questNode*& head_Q, Comparison compareTime){
            //only 1 item or no item
            if (head_Q == nullptr || head_Q->next == nullptr) {
                return;
            }
            bool swapped;
            do {
                swapped = false;
                current = head_Q;
                questNode* previous = nullptr;

                while (current->next != nullptr) {
                    questNode* next = current->next;
                    if (compareTime(current, next)) {
                        previous == nullptr ? head_Q = next : previous->next = next;

                        current->next = next->next;
                        next->next = current;

                        swapped = true;
                        previous = next;
                    } else {
                        previous = current;
                        current = current->next;
                    }
                }
            } while (swapped);
        }
        static bool byExp(questNode* a, questNode* b) {
            return a->exp > b->exp;
        }
        static bool byTitle(questNode* a, questNode* b) {
            return a->title > b->title;
        }
        static bool byOrder(questNode* a, questNode* b) {
            return a->order > b->order;
        }
};
class questLineCmds{
    public:
        void saveLine(){
            questLines.push_back(head_Q);
            listSizes.push_back(listSize);
            listSize = 0;
            head_Q = nullptr;
            cout << "Questline has been stored." << endl;
            return;
        }

        //which quest you want to focus on
        void getLine(int x){
            if (x >= 0 && x < questLines.size()) {
                head_Q = questLines[x];
                listSize = listSizes[x];
                cout << (head_Q ? "Found the questline." : "Questline at index " + to_string(x) + " is empty.") << endl;
            } 
            else {
                cout << "Invalid index. You put " << x << ". There aren't enough questlines for that. Provide one that is valid." << endl;
            }
        }
        void deleteLine(int x){
            if(x >= questLines.size()){
                cout << "Invalid index." << endl;
                return;
            }
            delete questLines[x];
            for (int i = x; i < questLines.size() - 1; ++i) {
                questLines[i] = questLines[i + 1];
            }
            questLines.pop_back();
            cout << "Questline deleted." << endl;
        }
        //merger
        void copyLine(questNode* currentNode, questNode*& SQH, questNode*& end, int& listSize){
            while (currentNode){
                questNode* new_node = new questNode(currentNode->exp, currentNode->title, currentNode->order);
                if(SQH == nullptr){
                    SQH = new_node;
                    end = new_node;
                }
                else{
                    end->next = new_node;
                    end = new_node;
                }
                currentNode = currentNode->next;
                listSize++;
            }
        }
        void copyLine(questNode* currentNode, int listSize){
            if(currentNode != nullptr){
                questNode* copyHead = nullptr;
                questNode* copyEnd = nullptr;
                int count = 0;
                copyLine(currentNode, copyHead, copyEnd, count);
                questLines.push_back(copyHead);
                listSizes.push_back(count);
            }
            else{
                cout << "This node is null, copying can't be done" << endl;
            }
        }
        //starts at questline 1, adds onto that one
        void mergeTwoLines(int first, int second){
            if (first < 0 || first >= questLines.size() || second < 0 || second >= questLines.size()) {
                cout << "Invalid indexes or questline has nothing." << endl;
                return;
            }
            questNode* superQuestHead = nullptr;
            questNode* tail = nullptr;
            listSize = 0;

            copyLine(questLines[first], superQuestHead, tail, listSize);
            copyLine(questLines[second], superQuestHead, tail, listSize);
            questLines.push_back(superQuestHead);
            listSizes.push_back(listSize);
            cout << "Quests have been merged" << endl;
        }
        void reverseLine(){
            if(!head_Q){
                cout << "Nothing in the questline!" << endl;
                return;
            }
            current = head_Q;
            vector <questNode*> storer;
            while(current){
                storer.push_back(current);
                current = current->next;
            }
            if(!storer.empty()){
                head_Q = storer.back();
                current = head_Q;
                storer.pop_back();
                while (!storer.empty()) {
                    current->next = storer.back();
                    current = current->next;
                    storer.pop_back();
                }
                current->next = nullptr;    
            }
        }
};

void displayQuests() {
    questNode* questPtr = head_Q;
    if(questPtr == nullptr){
        cout << "No quest to print" << endl;
        return;
    }
    cout << "\nPrinting questline:" << endl;
    while (questPtr != nullptr) {
        cout << "Quest Name: " << questPtr->title << ", Exp: " << questPtr->exp << " " << endl;
        //error handling for infinite loop
        if (questPtr->next == head_Q){
            cout << "Loop has been found!" << endl;
            break;
        }
        questPtr = questPtr->next;
    }
}
void moveNode(int position, int newPosition){
    if (position < 1 || newPosition < 1) {
        cout << "Invalid positions." << endl;
        return;
    }
    deletion deleter;
    searching search;
    nodeFunctions push;
    questNode* holder = search.searchByPos(position);
    if(holder == nullptr){
        cout << "No node in position " << position << endl;
        return;
    }
    deleter.byPosition(position);
    push.pushToMiddle(holder->title, holder->exp, newPosition);
}

int getNodeNum(){
    current = head_Q;
    int num = 0;
    while(current != nullptr){
        ++num;
        current = current->next;
    }
    return num;
}

void alterData(string name, int exp, int position){
    if (position < 1 || position > listSize) {
        cout << "Position " << position << " is out of bounds. Try a different number." << endl;
        return;
    }

    current = head_Q;
    while (current != nullptr && current->order != position) {
        current = current->next;
    }
    if (current != nullptr) {
        current->title = name;
        current->exp = exp;
    } else {
        cout << "The node at position " << position << " is not found." << endl;
    }
}

int main(){
    nodeFunctions pusher;
    deletion eraser;
    sorting sorter;
    searching searcher;
    questLineCmds lines;
    questNode* example;

    //DEMO: starting questline
    pusher.pushToStart("Slay 10 enemies", 4, 1);
    pusher.pushToEnd("Find Zakio", 3, 2);
    pusher.pushToEnd("Help Black Phoenix", 8, 3);
    pusher.pushToEnd("Defeat Shadow of Moryx", 10, 4); //will be 5th quest soon
    pusher.pushToMiddle("Defeat Vespera", 2, 4);
    alterData("Help Harune", 8, 3);
    displayQuests();

    //DEMO SECTION 1: search, delete, and reorder nodes
    /* example = searcher.searchByName("Defeat Vespera");
    example = searcher.searchByEXP(10);
    example = searcher.searchByPos(3); */

    /*eraser.byName("Defeat Vespera");
    eraser.byPosition(1);
    eraser.deleteFirst();
    eraser.deleteLast();
    displayQuests();
    pusher.pushToStart("Slay 10 enemies", 4, 1);
    pusher.pushToEnd("Find Zakio", 3, 2);
    pusher.pushToEnd("Defeat Shadow of Moryx", 10, 4);
    pusher.pushToMiddle("Defeat Vespera", 2, 4);
    moveNode(4, 2);
    displayQuests();*/

    //DEMO SECTION 2: save, start new, restore, delete, copy and merge questlines
    //new questline
    /*lines.saveLine();
    pusher.pushToEnd("New quest", 4, 1);
    pusher.pushToEnd("New quest 2", 7, 2);
    displayQuests();
    lines.saveLine();*/

    //merge and restore
    /*lines.mergeTwoLines(0, 1);
    displayQuests();
    lines.getLine(2);
    displayQuests();
    lines.getLine(0);
    displayQuests();
    lines.deleteLine(2);
    lines.getLine(1);
    displayQuests(); */

    //copy
    /*lines.copyLine(questLines[0], listSize);
    lines.getLine(2);
    displayQuests();*/

    //DEMO SECTION 3: Facts
    /*cout << "There are exactly " << getNodeNum() << " quests in this questline." << endl;
    example = searcher.minNode();
    if(example != nullptr){
        cout << example->title << " gives the least exp, which is " << example->exp << " points." << endl;
    }
    example = searcher.maxNode();
    if(example != nullptr){
        cout << example->title << " gives the most exp, which is " << example->exp << " points." << endl;
    }*/

    //DEMO SECTION 4: algorithms
    /* sorter.sort(head_Q, sorter.byExp);
    sorter.sort(head_Q, sorter.byTitle);
    reverseLine();
    displayQuests();
    sorter.sort(head_Q, sorter.byOrder);
    displayQuests(); */

    return 0;
};