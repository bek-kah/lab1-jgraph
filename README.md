hi,

midi-generator takes in a text file with instrument and midi info and generates an image.

---

MIDI stands for Musical Instrument Digital Interface. Technical jargon is not my forte, so I'll explain with an example.

Imagine you're a music producer. To start producing you typically launch your DAW (program to make music) of choice and plug in your MIDI controller (a small keyboard) to your laptop and and hit record.
Whenever you press one of the keys on your MIDI controller, that goes to the program with some info. There's usually a lot of it, but I'll only take into consideration the basics:

**Pitch** - the note you played (C to G, including sharps/flats)

**Velocity** - intensity of the sound (how hard you hit the note i.e. how loud it sounds)

**Start** - when you hit the note

**End** - when you let go of the note

---

Now that I've explained that, I'll go over how the input file for my progam should be formatted.

First line should be start like this:

`track_name duration`

`track_name` can be any string as it's just the title of the entire track. 

`duration` is the number of seconds you want your track to span.


now after the first line every other line should follow this kind of format:
```
instrument n 
note p v s e
... 
note p v s e
end
```

the string `instrument` lets my program know that we'll create a new instrument with id number `n` (int).

notes that follow will be added to that instrument with `p` for pitch, `v` for velocity, `s` for start time, and `e` for end time. (all of which are ints).

`end` lets my program know that `instrument n` is finished so I can add it to the track.
