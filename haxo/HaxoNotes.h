/*
  HaxoNotes.h - Read the Haxophone key matrix, convert it to
  a bit-packed representation, and map it to a usable MIDI note.
*/
#ifndef HaxoNotes_h
#define HaxoNotes_h

class HaxoNotes
{
  public:
    HaxoNotes();
    void init();
    uint8_t getMidiNote();
  private:
    uint32_t _scanKeys();

    struct NoteMapEntry {
      uint32_t key;
      uint8_t note;
    };

    // GPIO pins for button rows and columns
    const static int _NUM_ROWS = 8;
    const static int _NUM_COLS = 3;
    const int _ROWS[_NUM_ROWS] = {13, 9, 16, 17, 20, 22, 23, 24};
    const int _COLS[_NUM_COLS] = {25, 26, 27};

    // Bit-packed key state (as integers) mapped to MIDI notes
    const static int _NOTE_MAP_SIZE = 69;
    const NoteMapEntry _NOTE_MAP[_NOTE_MAP_SIZE] = {
      {0, 73}, {1, 85}, {32, 74}, {33, 86}, {37, 87}, {45, 88}, {128, 71}, {129, 83}, {144, 70},
      {145, 82}, {192, 72}, {193, 84}, {208, 72}, {209, 84}, {297, 89}, {301, 89}, {1024, 72},
      {1025, 84}, {1152, 69}, {1153, 81}, {1168, 69}, {1169, 81}, {1664, 70}, {1665, 82}, {9344, 67},
      {9345, 79}, {9360, 67}, {9361, 79}, {25728, 68}, {25729, 80}, {25744, 68}, {25745, 80},
      {65664, 70}, {65665, 82}, {66051, 90}, {74880, 65}, {74881, 77}, {74896, 65}, {74897, 77},
      {78976, 66}, {78977, 78}, {78992, 66}, {78993, 78}, {524416, 70}, {524417, 82}, {533632, 66},
      {533633, 78}, {533648, 66}, {533649, 78}, {599168, 64}, {599169, 76}, {599184, 64}, {599185, 76},
      {4793472, 62}, {4793473, 74}, {4793488, 62}, {4793489, 74}, {4826240, 63}, {4826241, 75},
      {4826256, 63}, {4826257, 75}, {5055616, 60}, {5055632, 60}, {5186688, 61}, {5186704, 61},
      {6104192, 59}, {6104208, 59}, {13444224, 58}, {13444240, 58}
    };
};

#endif
