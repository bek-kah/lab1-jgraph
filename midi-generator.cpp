#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Note {
    public:
        int pitch;
        int velocity;
        int start;
        int end;
        Note(int p, int v, int s, int e) {
            pitch = p;
            velocity = v;
            start = s;
            end = e;
        }
};

class Instrument {
    public: 
        int id;
        vector<Note> notes;
};

class Track {
    public:
        string name;
        vector<Instrument> instruments;
        int duration;
};

Track generate_track(string f);
vector<string> get_words(string l);
void print_track(Track t);

int main(int argc, char* argv[]) {

    string line;

    Track track = generate_track(argv[1]);

    print_track(track);

    return 0;
}


Track generate_track(string filename) {
    Track track;

    ifstream f(filename);
    string line;

    getline(f,line);
    vector<string> words = get_words(line);
    track.name = words[0];
    track.duration = stoi(words[1]);

    vector<Instrument> instruments;
    Instrument instrument;

    while (getline(f, line)) {
        vector<string> words = get_words(line);
        if (words[0][0] == 'e') {
            track.instruments.push_back(instrument);
            instrument = Instrument();
        }
        else if (words[0][0] == 'i') {
            instrument.id = stoi(words[1]);
        }
        else {  
            Note note = Note(stoi(words[0]), stoi(words[1]), stoi(words[2]), stoi(words[3]));
            instrument.notes.push_back(note);
        }
    }

    return track;
}

vector<string> get_words(string line) {
    string word;
    vector<string> words;
    
    stringstream iss(line);

    while(iss >> word) words.push_back(word);
    return words;
}

void print_track(Track t) {
    printf("%s | 0:00-%d:%02d\n",
         t.name.c_str(), t.duration / 60, t.duration % 60);

    for (Instrument i : t.instruments) {
        printf("  instrument #%d\n", i.id);
        for (Note n : i.notes) {
            printf("    %d %d %d:%02d-%d:%02d\n", 
                n.pitch, n.velocity, n.start / 60, n.start % 60, n.end / 60, n.end % 60);
        }
        cout << endl;
    }
}