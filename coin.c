#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

int main(){
  std::string buf;
  std::string guess_buf;
  std::string command;
  int number;
  int chance;
  int result;
  int begin;
  int end;
  int aux;
  int state{0};
  bool starting1{false};
  bool starting2{false};

  while(true){
    std::cin >> buf;

    if(!buf.compare("sec..."))
      starting1 = true;

    if(!buf.compare("-") && starting1)
      starting2 = true;

    if(starting1 && starting2){
      if(!buf.compare("Correct!")){
        state = -1;
      }
      if(state == -1){
        state = 0;
        continue;
      }
      if(buf[0] == 'N'){
        state++;
        number = std::stoi(buf.substr(2,std::string::npos));

      }
      if(buf[0] == 'C'){
        state++;
        chance = std::stoi(buf.substr(2,std::string::npos));
      }

      if(state == 2){
        begin = 0;
        end = number - 1;
        aux = (end + begin) / 2;
        for(int index = begin; index <= aux; index++){
          if(index == aux){
            guess_buf.append(std::to_string(index));
          }
          else{
            guess_buf.append(std::to_string(index) + " ");
          }
        }
        //"echo guess_buf > /proc/pid/fd/0"

        command = "echo " + guess_buf;

        char * cstr_command = new char [command.length()+1];
        std::strcpy (cstr_command, command.c_str());
        system(cstr_command);
        delete[] cstr_command;
        state++;
        guess_buf.clear();
        continue;
      }

      if(state >= 3){
        result = std::stoi(buf);

        if(result % 10 == 0){
          begin = aux + 1;
          aux = (end + begin) / 2;
        }
        else{
          end = aux;
          aux = (end + begin) / 2;
        }

        if(aux == end || aux == begin){
          command = "echo " + std::to_string(aux);
          char * cstr_command = new char [command.length()+1];
          std::strcpy (cstr_command, command.c_str());
          system(cstr_command);
          delete[] cstr_command;
          state++;

          guess_buf.clear();
          continue;
        }
        else{
          for(int index = begin; index <= aux; index++){
            if(index == aux){
              guess_buf = guess_buf + std::to_string(index);
            }
            else{
              guess_buf = guess_buf + std::to_string(index) + " ";
            }
          }
          command = "echo " + guess_buf;
          char * cstr_command = new char [command.length()+1];
          std::strcpy (cstr_command, command.c_str());
          system(cstr_command);
          delete[] cstr_command;
          state++;
          guess_buf.clear();
          continue;

        }


      }



    }

  }
}
