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

void generate_jgraph(Track t);
Track generate_track(string f);
vector<string> get_words(string l);
void print_track(Track t);

int main(int argc, char* argv[]) {

    string line;

    Track track = generate_track(argv[1]);

    print_track(track);
    generate_jgraph(track);

    return 0;
}

void generate_jgraph(Track t) {
    ofstream jfile(t.name + ".jgr");

    jfile << "newgraph" << endl << endl;

    jfile << "xaxis" << endl;
    jfile << "min 0 " << "max " << t.duration << endl;
    jfile << "label fontsize 10 font Courier : Time" << endl;
    jfile << "hash 60" << endl;
    jfile << "no_auto_hash_marks" << endl;
    jfile << "no_auto_hash_labels" << endl;
    jfile << "hash_label at 0 : 00:00" << endl;
    jfile << "hash_label at " << t.duration << " : "
        << setw(2) << setfill('0') << t.duration / 60
        << ":"
        << setw(2) << setfill('0') << t.duration % 60
        << endl;
    jfile << "hash_labels fontsize 8 font Courier\n\n";


    jfile << "yaxis" << endl;
    jfile << "min 0 " << "max " << t.instruments.size() * 36 << endl;
    jfile << "label fontsize 10 font Courier : Instruments" << endl;
    jfile << "no_auto_hash_marks" << endl;
    jfile << "no_auto_hash_labels" << endl;
    for (int i = 0; i < t.instruments.size(); i++) {
        jfile << "hash_at " << i * 36 + 18 << " hash_label at " << i * 36 + 18 << " : #" << t.instruments[i].id << endl;
    }
    jfile << "hash_labels fontsize 8 font Courier\n\n";

    for (int i = 0; i < t.instruments.size(); i++) {
        for (int j = 0; j < t.instruments[i].notes.size(); j++) {
            Note n = t.instruments[i].notes[j];
            double v = (double)n.velocity / (double)127;

            string color = "0.5 0.5 " + to_string(v);

            string lb_corner = to_string(n.start)   + " " + to_string(i * 36 + n.pitch * 3);
            string lt_corner = to_string(n.start)   + " " + to_string(i * 36 + n.pitch * 3 + 3);
            string rt_corner = to_string(n.end)     + " " + to_string(i * 36 + n.pitch * 3 + 3);
            string rb_corner = to_string(n.end)     + " " + to_string(i * 36 + n.pitch * 3);


            jfile << "newline poly pcfill " << color << " color " << color << " pts " << 
            lb_corner << " " << lt_corner << " " << rt_corner << " " << rb_corner << endl;
        }
    }
    jfile << endl;

    for (int i = 0; i < t.instruments.size() * 36; i += 3) {
        string lb_corner = to_string(0)             + " " + to_string(i);
        string lt_corner = to_string(0)             + " " + to_string(i + 3);
        string rt_corner = to_string(t.duration)    + " " + to_string(i + 3);
        string rb_corner = to_string(t.duration)    + " " + to_string(i);

        jfile << "newline poly linethickness 1 color 0.75 0.75 0.75 pfill -1 pts " <<
        lb_corner << " " << lt_corner << " " << rt_corner << " " << rb_corner << endl;
    }

    for (int i = 0; i < t.instruments.size(); i++) {
        string lb_corner = to_string(0)             + " " + to_string(i * 36);
        string lt_corner = to_string(0)             + " " + to_string(i * 36 + 36);
        string rt_corner = to_string(t.duration)    + " " + to_string(i * 36 + 36);
        string rb_corner = to_string(t.duration)    + " " + to_string(i * 36);

        jfile << "newline poly linethickness 1.5 color 0 0 0 pfill -1 pts " <<
        lb_corner << " " << lt_corner << " " << rt_corner << " " << rb_corner << endl;
    }
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