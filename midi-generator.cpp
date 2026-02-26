#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Note {
    public:
        int velocity;
        int pitch;
        int start;
        int end;
        Note(int v, int p, int s, int e) {
            velocity = v;
            pitch = p;
            start = s;
            end = e;
        }
};

class Instrument {
    public: 
        int id;
        vector<Note> notes;
        int start;
        int end;
};

vector<string> get_words(string line);
void print_instruments(vector<Instrument> instruments);

int main(int argc, char* argv[]) {

    string line;

    ifstream f(argv[1]);

    vector<Instrument> instruments;
    Instrument instrument;

    while (getline(f, line)) {
        vector<string> words = get_words(line);
        if (words[0][0] == 'e') {
            instruments.push_back(instrument);
            instrument = Instrument();
        }
        else if (words[0][0] == 'i') {
            instrument.id = stoi(words[1]);
            instrument.start = stoi(words[2]);
            instrument.end = stoi(words[3]);
        }
        else {  
            Note note = Note(stoi(words[0]), stoi(words[1]), stoi(words[2]), stoi(words[3]));
            instrument.notes.push_back(note);
        }
    }

    print_instruments(instruments);

    return 0;
}

vector<string> get_words(string line) {
    string word;
    vector<string> words;
    
    stringstream iss(line);

    while(iss >> word) words.push_back(word);
    return words;
}

void print_instruments(vector<Instrument> instruments) {
    for (Instrument i : instruments) {
        cout << "Instrument #" << i.id << " | " << i.start << "-" << i.end << endl;
        for (Note n : i.notes) {
            cout << "-- ";
            cout << n.pitch << " " << n.velocity << " | " << n.start << "-" << n.end << endl;
        }
        cout << endl << endl;
    }
}