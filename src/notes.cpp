#include "notes.h"

namespace my {

void Notes::ShowMenu() {
  std::cout << "Выберите пункт меню: " << std::endl;
  std::cout << "1. Просмотреть заметки" << std::endl;
  std::cout << "2. Создать заметку" << std::endl;
  std::cout << "3. Редактировать заметку" << std::endl;
  std::cout << "4. Удалить заметку" << std::endl;
  std::cout << "5. Сохранить заметки в файл" << std::endl;
  std::cout << "0. Выйти из программы" << std::endl;
  std::cout << std::endl;
}

void Notes::ValidateFile(const size_t amount_notes) {
  if (notes_.empty()) {
    std::cout << "Ошибка! Заметки отсутствуют. Создайте заметку." << std::endl;
  } else if (amount_notes != notes_.size()) {
    notes_.clear();
    std::cout << "Ошибка! Файл с заметками поврежден. Создайте заметку."
              << std::endl;
  } else {
    read_file_ = true;
    std::cout << "Заметки успешно загружены из файла." << std::endl;
  }
}

void Notes::LoadNotes() {
  std::ifstream file(file_name_);
  if (file.is_open()) {
    Note note;
    std::string line;
    size_t line_count = 0;
    std::string amount_notes;
    std::getline(file, amount_notes);
    while (std::getline(file, line)) {
      if (!line.empty()) {
        line_count++;
        if (line_count == 1) {
          note.date_time = line;
        } else if (line_count == 2) {
          note.title = line;
        } else if (line_count == 3) {
          note.text = line;
          line_count = 0;
          notes_.push_back(note);
        }
      }
    }
    file.close();
    ValidateFile(static_cast<size_t>(std::atoi(amount_notes.c_str())));
  } else {
    std::cout << "Ошибка! Не удалось открыть файл. Создайте заметку."
              << std::endl;
  }
  std::cout << std::endl;
}

bool Notes::CheckAmountNotes() {
  bool res = true;
  if (notes_.empty()) {
    res = false;
    std::cout << "Ошибка! Заметки отсутствуют. Создайте заметку." << std::endl;
    std::cout << std::endl;
  }
  return res;
}

void Notes::ShowNotes() {
  if (CheckAmountNotes() && read_file_) {
    std::cout << std::endl;
    for (size_t i = 0; i < notes_.size(); i++) {
      std::cout << "Заметка " << i + 1 << std::endl;
      std::cout << "Дата: " << notes_[i].date_time << std::endl;
      std::cout << "Заголовок: " << notes_[i].title << std::endl;
      std::cout << "Содержимое: " << notes_[i].text << std::endl;
      std::cout << std::endl;
    }
  }
}

std::string Notes::GetDateTime() {
  std::time_t now = std::time(nullptr);
  struct std::tm* time = std::localtime(&now);
  std::ostringstream oss;
  oss << std::put_time(time, "%H:%M %d.%m.%Y");
  std::string date_time = oss.str();
  return date_time;
}

void Notes::CreateNote() {
  read_file_ = true;
  Note note;
  std::cout << "Введите заголовок новой заметки:" << std::endl;
  std::cin >> note.title;
  std::cout << "Введите текст новой заметки:" << std::endl;
  std::cin >> note.text;
  note.date_time = GetDateTime();
  notes_.push_back(note);
  std::cout << "Заметка " << notes_.size() << " успешно создана." << std::endl;
  std::cout << std::endl;
}

bool Notes::CheckNoteNum(const size_t note_num) {
  bool res = true;
  if (note_num == 0 || note_num > notes_.size()) {
    res = false;
    std::cout << "Ошибка! Заметки с таким номером не существует." << std::endl;
    std::cout << std::endl;
  }
  return res;
}

void Notes::EditNote() {
  if (CheckAmountNotes() && read_file_) {
    std::cout << "Всего заметок: " << notes_.size() << std::endl;
    std::cout << "Введите номер заметки для редактирования:" << std::endl;
    size_t note_num;
    std::cin >> note_num;
    std::cout << "Выбрана заметка: " << note_num << std::endl;
    if (CheckNoteNum(note_num)) {
      std::string title;
      std::cout << "Введите новый заголовок заметки:" << std::endl;
      std::cin >> title;
      std::string text;
      std::cout << "Введите новый текст заметки:" << std::endl;
      std::cin >> text;
      notes_[note_num - 1].title = title;
      notes_[note_num - 1].text = text;
      std::cout << "Заметка " << note_num << " успешно отредактирована."
                << std::endl;
      std::cout << std::endl;
    }
  }
}

void Notes::DelNote() {
  if (CheckAmountNotes() && read_file_) {
    std::cout << "Всего заметок: " << notes_.size() << std::endl;
    std::cout << "Введите номер заметки для удаления:" << std::endl;
    size_t note_num;
    std::cin >> note_num;
    std::cout << "Выбрана заметка: " << note_num << std::endl;
    if (CheckNoteNum(note_num)) {
      notes_.erase(notes_.begin() + note_num - 1);
      std::cout << "Заметка " << note_num << " успешно удалена." << std::endl;
      std::cout << std::endl;
    }
  }
}

void Notes::SaveNotes() {
  if (CheckAmountNotes()) {
    std::ofstream file(file_name_);
    if (file.is_open()) {
      file << notes_.size() << std::endl;
      file << std::endl;
      for (const Note& note : notes_) {
        file << note.date_time << std::endl;
        file << note.title << std::endl;
        file << note.text << std::endl << std::endl;
      }
      file.close();
      std::cout << "Заметки успешно сохранены в файл." << std::endl;
    } else {
      std::cout << "Ошибка! Не удалось открыть файл." << std::endl;
    }
    std::cout << std::endl;
  }
}

}  // namespace my
