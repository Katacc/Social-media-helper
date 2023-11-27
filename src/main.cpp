#include <iostream>
#include <stdlib.h>
#include <string>
#include <numbers>
#include <thread>
#include <vector>
#include <filesystem>
#include <iomanip>
#include <cstdlib>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

namespace fs = std::filesystem;
using namespace std;

vector<string> photos;
vector<string> pathsInverted;
vector<string> moodlist;

string mood = "";
string cosplaySelect = "";
string colourSelection = "";
int filters { };
bool checkIfEmpty2 = false;


int validInput()
{
    int x;
    std::cin >> x;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Bad entry.  Enter a NUMBER: ";
        std::cin >> x;
    }
    return x;
}

void titleBar() {
    using namespace std;

    cout << "Kata's social media helper v 0.3" << endl;
    cout << "----------------------------------" << endl;
}

void moodSelection() {

    start:

    srand(time(0));

    string moodFolder = "";
    bool checkIfEmpty1;

    cout << "\nList of filters:" << endl;
    string path = "../pictures/";
    for (const auto & entry : fs::directory_iterator(path)) {
        cout << entry.path() << endl;
    }

    cout << "What's the mood for today's post? (r for random mood)";
    cout << "\n" << ": ";
    cin >> mood;
    moodFolder = "../pictures/" + mood;

    if (mood == "r") {
        for (const auto & entry : fs::directory_iterator(path)) {
            moodlist.push_back (entry.path().string());
        }

        int i = 0;
        do {
            int randomNumberMood { };
            int moodListSize = moodlist.size() - 1;
            randomNumberMood = rand() % moodlist.size();
            mood = moodlist.at(randomNumberMood);

            fs::path p(mood);
            mood = p.stem().string();
            moodFolder = "../pictures/" + mood;

            checkIfEmpty2 = fs::is_empty(moodFolder);
            i++;
        }
        while ((checkIfEmpty2) || (i < moodlist.size()));

        if (checkIfEmpty2) {
            cout << "All of the folders are empty.. Please close this window and try again after making sure there are pictures to choose from..";
            system("pause");
            return;
        }

    }


    checkIfEmpty1 = fs::is_empty(moodFolder);

    if (checkIfEmpty1) {
        cout << "Folder is empty.. going back to start.." << endl;
        system("pause");
        system("cls");
        titleBar();
        goto start;
    }

    system("cls");
    titleBar();
}

void cosplaySelectInvert() {

    cout << "\nList of filenames:" << endl;
    string path = "../pictures/" + mood;
    path = path + "/";
    for (const auto & entry : fs::directory_iterator(path)) {
        cout << entry.path() << endl;
    }

    cout << "Type of the name of the cosplay" << endl;
    cout << ": ";
    cin >> cosplaySelect;

    system("cls");
    titleBar();
}


void getPhotos(string mood) {
    using namespace std;

    string path = "../pictures/" + mood;
    path = path + "/";
    for (const auto & entry : fs::directory_iterator(path)) {
        cout << entry.path() << endl;
        photos.push_back (entry.path().string());
    }

}

void endOfItAll() {

    using namespace std;
    using std::string;
    using std::vector;
    std::error_code err;

    int vectorLenght { };
    int randomNumber { };
    int randomNumber2 { };
    string selectedPhoto = "";
    string oldDir, newDir;

    srand(time(0));

        // clear and thingys
    cout << "Initializing...";
    sleep_for(2s);
    system("cls");

    // random number generation and selecting the photo
    randomNumber = rand() % photos.size();
    selectedPhoto = photos.at(randomNumber);


    if (filters == 2) {
        while (selectedPhoto.find(cosplaySelect) != std::string::npos) {
            randomNumber = rand() % photos.size();
            selectedPhoto = photos.at(randomNumber);
        }
    }


    oldDir = selectedPhoto;
    string selectedPhotoName = "";

    titleBar();
    cout << "Your photo is: " << selectedPhoto << "! Enjoy." << endl;
    fs::path s(selectedPhoto);
    selectedPhotoName = s.filename().string();

    newDir = "../toPost/" + selectedPhotoName;

    bool checkIfDuplicate;
    checkIfDuplicate = fs::exists(newDir);

    while (checkIfDuplicate) {
        randomNumber2 = rand() % 1000;
        auto s = std::to_string(randomNumber2);
        newDir = "../toPost/" + s;
        newDir = newDir + ".jpg";
        checkIfDuplicate = fs::exists(newDir);

    }

    fs::rename(oldDir, newDir, err);
    if (err) {
        std::cerr << "Error moving file: " << err.message() << endl;
    }
    else {
        std::cout << "File moved succesfully" << endl;
    }


    cout << "\n";

    system("pause");
}

int main() {
    using namespace std;
    using std::string;
    using std::vector;
    std::error_code err;
    // sleep commands

    // sleep_for(10ns);
    // sleep_until(system_clock::now() + 1s)

    titleBar();

    srand(time(0));

    cout << "What filters you want?" << endl;
    cout << "1. Only mood" << endl;
    cout << "2. Mood + inverted cosplay" << endl;
    cout << ": ";
    filters = validInput();

    if (filters == 1) {
        moodSelection();
    }

    else if (filters == 2) {
        moodSelection();
        cosplaySelectInvert();
    }

    // get the vector full of photos
    getPhotos(mood);


    if (checkIfEmpty2) {
        return 0;
    }
    endOfItAll();

    return 0; 
}