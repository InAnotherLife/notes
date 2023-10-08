#include "notes.h"

int main() {
  std::cout << "Программа \"Заметки\"" << std::endl;
  std::cout << std::endl;
  my::Notes notes;
  notes.LoadNotes();
  size_t menu;
  while (true) {
    notes.ShowMenu();
    std::cin >> menu;
    std::cout << "Выбран пункт меню: " << menu << std::endl;
    if (menu == 1) {
      notes.ShowNotes();
    } else if (menu == 2) {
      notes.CreateNote();
    } else if (menu == 3) {
      notes.EditNote();
    } else if (menu == 4) {
      notes.DelNote();
    } else if (menu == 5) {
      notes.SaveNotes();
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
