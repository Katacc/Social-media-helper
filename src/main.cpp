#include <iostream>
#include <stdlib.h>
#include <string>
#include <numbers>
#include <thread>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

vector<string> photos;
string cosplaySelect = "";

void getPhotos(string mood) {
    using namespace std;

    string path = mood;
    for (const auto & entry : fs::directory_iterator(path)) {
        cout << entry.path() << endl;
        photos.push_back (entry.path().string());
    }

}


void titleBar() {
    using namespace std;

    cout << "Kata's social media helper v 0.1" << endl;
    cout << "----------------------------------" << endl;
}

int main() {
    using namespace std;
    using std::string;
    using std::vector;
    std::error_code err;
    // sleep commands
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;
    // sleep_for(10ns);
    // sleep_until(system_clock::now() + 1s)

    string mood = "";
    int vectorLenght { };
    int randomNumber { };
    string selectedPhoto = "";
    string oldDir, newDir;
    titleBar();

    cout << "What's the mood for today's post? (Happy, Moody, Cinematic, Flirty)";
    cout << "\n" << ": ";
    cin >> mood;

    cout << "Type of the name of the cosplay" << endl;
    cout << ": ";
    cin >> cosplaySelect;

    if (cosplaySelect != "l") {
        mood = "../pictures/" + mood;
        mood = mood + "/";
        mood = mood + cosplaySelect;
    }

    else {
        mood = "../pictures/" + mood;
        mood = mood + "/";
        mood = mood + ;
        mood = mood + "/";
    }

    getPhotos(mood);


    cout << "Initializing...";
    sleep_for(2s);

    system("cls");

    randomNumber = rand() % photos.size();

    selectedPhoto = photos.at(randomNumber);

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