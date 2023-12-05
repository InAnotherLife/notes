#include "notes.h"

namespace my {

// Вывод меню приложения в консоль
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

// Проверка файла с заметками на валидность, результат проверки выводится в
// консоль
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
  std::cout << std::endl;
}

// Загрузка заметок из файла. Если файл открывается, то происходит построчное
// чтение файла. Если файл не удается открыть, то выбрасывается исключение.
// Первая цифра в файле - общее количество заметок.
// Каждая заметка состоит из трех строк: даты и времени, заголовка, текста.
void Notes::LoadNotes() {
  std::ifstream file;
  file.open(file_name_);
  if (!file.is_open())
    throw std::runtime_error(
        "Ошибка! Не удалось открыть файл. Создайте заметку.");
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
}

// Проверка наличия заметок в векторе notes_. Если вектор пустой, то выводится
// сообщение об ошибке.
bool Notes::CheckAmountNotes() {
  bool res = true;
  if (notes_.empty()) {
    res = false;
    std::cout << "Ошибка! Заметки отсутствуют. Создайте заметку." << std::endl;
    std::cout << std::endl;
  }
  return res;
}

// Вывод всех заметок в консоль
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

// Получение текущей даты и времени
std::string Notes::GetDateTime() {
  std::time_t now = std::time(nullptr);
  struct std::tm* time = std::localtime(&now);
  std::ostringstream oss;
  oss << std::put_time(time, "%H:%M %d.%m.%Y");
  std::string date_time = oss.str();
  return date_time;
}

// Создание новой заметки
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

// Проверка номера заметки. Если номер не существует, то выводится сообщение
// об ошибке.
bool Notes::CheckNoteNum(const size_t note_num) {
  bool res = true;
  if (note_num == 0 || note_num > notes_.size()) {
    res = false;
    std::cout << "Ошибка! Заметки с таким номером не существует." << std::endl;
    std::cout << std::endl;
  }
  return res;
}

// Редактирование существующей заметки. Можно ввести новые заголовок и текст
// заметки.
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

// Удаление существующей заметки
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

// Сохранение заметок в файл. Если файл не удается открыть, то
// выбрасывается исключение.
void Notes::SaveNotes() {
  if (CheckAmountNotes()) {
    std::ofstream file;
    file.open(file_name_);
    if (!file.is_open())
      throw std::runtime_error("Ошибка! Не удалось открыть файл.");
    file << notes_.size() << std::endl;
    file << std::endl;
    for (const Note& note : notes_) {
      file << note.date_time << std::endl;
      file << note.title << std::endl;
      file << note.text << std::endl;
      file << std::endl;
    }
    file.close();
    std::cout << "Заметки успешно сохранены в файл." << std::endl;
    std::cout << std::endl;
  }
}

}  // namespace my
