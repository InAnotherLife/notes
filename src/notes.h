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
  Notes() : read_file_(false), file_name_("notes.txt"){};
  ~Notes(){};
  void ShowMenu();
  void ValidateFile();
  size_t StringToInt(std::string str);
  void LoadNotes();
  bool CheckAmountNotes();
  void ShowNotes();
  void CreateNote();
  bool CheckNoteNum(const size_t note_num);
  void EditNote();
  void DelNote();
  void SaveNotes();
  // Для тестов
  void SetFilename(std::string file_name) { file_name_ = file_name; }
  size_t GetAmountNotes() { return notes_.size(); }
  bool GetReadfile() { return read_file_; }

 private:
  std::vector<Note> notes_;
  bool read_file_;
  std::string file_name_;
  std::string amount_notes_;
  std::string GetDateTime();
};

}  // namespace my

#endif  // SRC_NOTES_H_
