#include "notes.h"

namespace my {

void Notes::ShowMenu() {
  std::cout << "Выберите пункт меню: " << std::endl;
  std::cout << "1. Загрузить заметки из файла" << std::endl;
  std::cout << "2. Просмотреть заметки" << std::endl;
  std::cout << "3. Создать заметку" << std::endl;
  std::cout << "4. Редактировать заметку" << std::endl;
  std::cout << "5. Удалить заметку" << std::endl;
  std::cout << "6. Сохранить заметки в файл" << std::endl;
  std::cout << "0. Выйти из программы" << std::endl;
  std::cout << std::endl;
}

void Notes::ValidateFile() {
  if (notes_.empty()) {
    std::cout << "Ошибка! Файл с заметками пустой." << std::endl;
  } else if (static_cast<size_t>(std::atoi(file_size_.c_str())) !=
             notes_.size()) {
    std::cout << "Ошибка! Файл с заметками поврежден." << std::endl;
  } else {
    read_file_ = true;
    std::cout << "Заметки успешно загружены из файла." << std::endl;
  }
}

void Notes::LoadNotes() {
  if (!read_file_) {
    std::ifstream file(file_name_);
    if (file.is_open()) {
      Note note;
      std::string line;
      size_t line_count = 0;
      std::getline(file, file_size_);
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
      ValidateFile();
    } else {
      std::cout << "Ошибка! Не удалось открыть файл." << std::endl;
    }
  } else {
    std::cout << "Ошибка! Заметки уже загружены из файла." << std::endl;
  }
  std::cout << std::endl;
}

bool Notes::CheckReadFile() {
  bool res = true;
  if (!read_file_) {
    res = false;
    std::cout << "Ошибка! Загрузите заметки из файла." << std::endl;
    std::cout << std::endl;
  }
  return res;
}

void Notes::ShowNotes() {
  if (CheckReadFile()) {
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
  if (CheckReadFile()) {
    Note note;
    std::cout << "Введите заголовок заметки:" << std::endl;
    std::cin >> note.title;
    std::cout << "Введите текст заметки:" << std::endl;
    std::cin >> note.text;
    note.date_time = GetDateTime();
    notes_.push_back(note);
    std::cout << "Заметка " << notes_.size() << " успешно создана."
              << std::endl;
    std::cout << std::endl;
  }
}

void Notes::EditNote() {
  if (CheckReadFile()) {
    size_t notes_amount = notes_.size();
    std::cout << "Всего заметок: " << notes_amount << std::endl;
    std::cout << "Введите номер заметки для редактирования:" << std::endl;
    size_t note_num;
    std::cin >> note_num;
    std::cout << "Выбрана заметка: " << note_num << std::endl;
    if (note_num == 0 || note_num > notes_amount) {
      std::cout << "Ошибка! Заметки с таким номером не существует."
                << std::endl;
    } else {
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
    }
    std::cout << std::endl;
  }
}

void Notes::DelNote() {
  if (CheckReadFile()) {
    size_t notes_amount = notes_.size();
    std::cout << "Всего заметок: " << notes_amount << std::endl;
    std::cout << "Введите номер заметки для удаления:" << std::endl;
    size_t note_num;
    std::cin >> note_num;
    std::cout << "Выбрана заметка: " << note_num << std::endl;
    if (note_num == 0 || note_num > notes_amount) {
      std::cout << "Ошибка! Заметки с таким номером не существует."
                << std::endl;
    } else {
      notes_.erase(notes_.begin() + note_num - 1);
      std::cout << "Заметка " << note_num << " успешно удалена." << std::endl;
    }
    std::cout << std::endl;
  }
}

void Notes::SaveNotes() {
  if (CheckReadFile()) {
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
