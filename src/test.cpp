#include <iostream>
#include <stdlib.h>
#include <string>
#include <numbers>
#include <thread>
#include <vector>
#include <filesystem>
#include <iomanip>

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


void titleBar() {
    using namespace std;

    cout << "Kata's social media helper v 0.2" << endl;
    cout << "----------------------------------" << endl;
}

void moodSelection() {

    cout << "\nList of filters:" << endl;
    string path = "../pictures/";
    for (const auto & entry : fs::directory_iterator(path)) {
        cout << entry.path() << endl;
    }

    cout << "What's the mood for today's post?";
    cout << "\n" << ": ";
    cin >> mood;
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

void colourSelect() {

    cout << "\nList of colours:" << endl;
    string path = "../pictures/" + mood;
    path = path + "/";
    for (const auto & entry : fs::directory_iterator(path)) {
        cout << entry.path() << endl;
    }

    cout << "\nColour palette name:" << endl;
    cout << ": ";
    cin >> colourSelection;

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

void randomizeAll() {
    system("cls");
    titleBar();

    int randomNumber2 { };
    string selectedMood = "";

    cout << "Randomizing all..";
    sleep_for(2s);

    string path = "../pictures/";
    for (const auto & entry : fs::directory_iterator(path)) {
        moodlist.push_back (entry.path().string());
    }

    randomNumber2 = rand() % moodlist.size();
    mood = moodlist.at(randomNumber2);
    // path = selectedMood;
    // for (const auto & entry : fs::directory_iterator(path)) {
    //     photos.push_back (entry.path().string());
    // }
}


int main() {
    using namespace std;
    using std::string;
    using std::vector;
    std::error_code err;
    // sleep commands

    // sleep_for(10ns);
    // sleep_until(system_clock::now() + 1s)

    int vectorLenght { };
    int randomNumber { };
    int randomNumber2 { };
    string selectedPhoto = "";
    string oldDir, newDir;
    int filters { };
    titleBar();

    cout << "What filters you want?" << endl;
    cout << "1. Only mood" << endl;
    cout << "2. Mood + inverted cosplay" << endl;
    cout << "3. Mood + colours" << endl; 
    cout << "4. Mood + inverted cosplay + colours" << endl;
    cout << "5. Randomize all" << endl;
    cout << ": ";
    cin >> filters; 

    if (filters == 1) {
        moodSelection();
    }

    else if (filters == 2) {
        moodSelection();
        cosplaySelectInvert();
    }

    else if (filters == 3) {
        moodSelection();
        colourSelect();
    }

    else if (filters == 5) {
        randomizeAll();
    }

    else {
        moodSelection();
        cosplaySelectInvert();
        colourSelect();
    }

    // get the vector full of photos
    getPhotos(mood);

    // clear and thingys
    cout << "Initializing...";
    sleep_for(2s);
    system("cls");

    cout << "testi 1";

    // random number generation and selecting the photo
    randomNumber = rand() % photos.size();
    selectedPhoto = photos.at(randomNumber);

    cout << "testi 2";

    if (filters == 2 || 4) {
        while (selectedPhoto.find(cosplaySelect) != std::string::npos) {
            randomNumber = rand() % photos.size();
            selectedPhoto = photos.at(randomNumber);
        }
    }

    cout << "testi 3";

    oldDir = selectedPhoto;

    titleBar();
    cout << "Your photo is: " << selectedPhoto << "! Enjoy." << endl;

    newDir = "../toPost/topostphoto.jpg";

    fs::rename(oldDir, newDir, err);
    if (err) {
        std::cerr << "Error moving file: " << err.message() << endl;
    }
    else {
        std::cout << "File moved succesfully" << endl;
    }


    cout << "\n";

    system("pause");
    return 0; 
}