#include <memory>

#include "notes.h"

int main() {
  std::cout << "Программа \"Заметки\"" << std::endl;
  std::cout << std::endl;
  std::unique_ptr<my::Notes> notes = std::make_unique<my::Notes>();
  try {
    notes->LoadNotes();
    notes->ValidateFile();
  } catch (const std::runtime_error &error) {
    std::cout << error.what() << std::endl;
  }
  size_t menu;
  while (true) {
    notes->ShowMenu();
    std::cin >> menu;
    std::cout << "Выбран пункт меню: " << menu << std::endl;
    if (menu == 1) {
      notes->ShowNotes();
    } else if (menu == 2) {
      notes->CreateNote();
    } else if (menu == 3) {
      notes->EditNote();
    } else if (menu == 4) {
      notes->DelNote();
    } else if (menu == 5) {
      try {
        notes->SaveNotes();
      } catch (const std::runtime_error &error) {
        std::cout << error.what() << std::endl;
      }
    } else if (menu == 0) {
      std::cout << "Выход из программы." << std::endl;
      exit(0);
    } else {
      std::cout << "Ошибка! Недопустимый пункт меню." << std::endl;
      std::cout << std::endl;
    }
  }
  return 0;
}
