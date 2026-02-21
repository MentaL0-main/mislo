#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::string> variables;

void quit() {
  std::cout << "Bye.\n";
  exit(0);
}

void add_variable(const std::string& cmd) {
  std::istringstream iss(cmd);
  std::string command, varName, equalSign, value;
  iss >> command >> varName >> equalSign >> value;
  variables[varName] = value;
}

void write_variable(const std::string& cmd) {
  std::istringstream iss(cmd);
  std::string command, varName;
  iss >> command >> varName;

  auto it = variables.find(varName);
  if (it != variables.end()) {
      std::cout << it->second << std::endl;
  } else {
      std::cout << "No such variable '" << varName << '\'' << std::endl;
  }
}

void accept_variable(const std::string& cmd) {
  std::istringstream iss(cmd);
  std::string command, varName;
  iss >> command >> varName;

  std::string value;
  std::getline(std::cin, value);
  variables[varName] = value;
}

std::string accept_command(const std::string& prompt) {
  std::cout << prompt;
  std::string command;
  std::getline(std::cin, command);
  return command;
}

void execute_cmd(const std::string& cmd) {
  if (cmd == "exit" || cmd == "quit") {
    quit();
  } else if (cmd == "help") {
    std::cout << "List of commands:\n"
              << "\twrite var_name - write text to console.\n"
              << "\taccept var_name - get value from user and write in var.\n"
              << "\thelp - show this message.\n"
              << "\texit - leave from program.\n"
              << "\tclear - clear console output.\n"
              << "\tquit - alias for exit.\n";
  } else if (cmd == "clear") {
#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#else
  system("clear");
#endif
  } else if (cmd.rfind("write", 0) == 0) {
    write_variable(cmd);
  } else if (cmd.rfind("var", 0) == 0) {
    add_variable(cmd);
  } else if (cmd.rfind("accept", 0) == 0) {
    accept_variable(cmd);
  } else {
    std::cout << "Unknown command: '" << cmd << "'.\n";
  }
}

int main() {
  std::cout << "Welcome to mislo interpreter version 0.1\n";

  while (true) {
    execute_cmd(accept_command("~# "));
  }

  return 0;
}
