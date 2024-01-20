#include "menu.h"

namespace my {

// Вывод меню приложения в консоль
void Menu::ShowMenu() {
  std::cout << "Выберите пункт меню: " << std::endl;
  std::cout << "1. Просмотреть заметки" << std::endl;
  std::cout << "2. Создать заметку" << std::endl;
  std::cout << "3. Редактировать заметку" << std::endl;
  std::cout << "4. Удалить заметку" << std::endl;
  std::cout << "5. Сохранить заметки в файл" << std::endl;
  std::cout << "0. Выйти из программы" << std::endl;
  std::cout << std::endl;
}

}  // namespace my
