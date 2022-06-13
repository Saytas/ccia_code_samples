#include <iostream>
#include <thread>
#include <string>

void open_document_and_display_gui(std::string const& filename) {
  std::cout << "open_document_and_display_gui start and end" << std::endl;
  return;
}

bool done_editing() {
  std::cout << "done_editing start and end" << std::endl;
  return true;
}

enum command_type { open_new_document };

struct user_command {
  //std::cout << "struct user_command start" << std::endl;
  command_type type;
  user_command() : type(open_new_document) {}
  //std::cout << "struct user_command end" << std::endl;
};

user_command get_user_input() {
  std::cout << "get_user_input start and end" << std::endl;
  return user_command();
}

std::string get_filename_from_user() {
  std::cout << "get_filename_from_user start and end" << std::endl;
  return "foo.doc";
}

void process_user_input(user_command const& cmd) {
  std::cout << "process_user_input start and end" << std::endl;
  return;
}

void edit_document(std::string const& filename) {
  std::cout << "edit_document start" << std::endl;
  open_document_and_display_gui(filename);
  while(!done_editing()) {
    user_command cmd = get_user_input();
    if(cmd.type == open_new_document) {
      std::string const new_name = get_filename_from_user();
      std::thread t(edit_document, new_name);
      t.detach();
    } else {
      process_user_input(cmd);
    }
  }
  std::cout << "edit_document end" << std::endl;
  return;
}

int main() {
  std::cout << "main start" << std::endl;
  edit_document("bar.doc");
  std::cout << "main end" << std::endl;
}
