#ifndef SRC_NOTES_H_
#define SRC_NOTES_H_

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace my {

struct Note {
  std::string date_time;
  std::string title;
  std::string text;
};

class Notes {
 public:
  Notes() : read_file_(false){};
  ~Notes() { notes_.clear(); };
  void ShowMenu();
  void LoadNotes();
  bool CheckReadFile();
  void ShowNotes();
  void CreateNote();
  void EditNote();
  void DelNote();
  void SaveNotes();

 private:
  std::vector<Note> notes_;
  bool read_file_;
  std::string file_name_ = "notes.txt";
  std::string GetDateTime();
};

}  // namespace my

#endif  // SRC_NOTES_H_
