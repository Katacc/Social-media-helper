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

    cout << "Kata's social media helper v 0.3" << endl;
    cout << "----------------------------------" << endl;
}

void moodSelection() {

    srand(time(0));

    cout << "\nList of filters:" << endl;
    string path = "../pictures/";
    for (const auto & entry : fs::directory_iterator(path)) {
        cout << entry.path() << endl;
    }

    cout << "What's the mood for today's post? (R for random mood)";
    cout << "\n" << ": ";
    cin >> mood;

    if (mood == "R" || "r") {
        for (const auto & entry : fs::directory_iterator(path)) {
            moodlist.push_back (entry.path().string());
        }

        int randomNumberMood { };
        int moodListSize = moodlist.size() - 1;
        randomNumberMood = rand() % moodlist.size();
        mood = moodlist.at(randomNumberMood);

        fs::path p(mood);
        mood = p.stem().string();

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

    srand(time(0));

    cout << "What filters you want?" << endl;
    cout << "1. Only mood" << endl;
    cout << "2. Mood + inverted cosplay" << endl;
    cout << ": ";
    cin >> filters; 

    if (filters == 1) {
        moodSelection();
    }

    else if (filters == 2) {
        moodSelection();
        cosplaySelectInvert();
    }

    // get the vector full of photos
    getPhotos(mood);

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