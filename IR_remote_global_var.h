#ifndef IR_REMOTE_GLOBAL_VAR_H
#define IR_REMOTE_GLOBAL_VAR_H


#define RemoteAdress    0xEF00    //Adress of the Remote
#define IR_RECEIVE_PIN  7         // Pin where the IR is Connected

//######################### IR COMMANDS #############################
extern const int CommandsTable_size;


struct Command {
  uint8_t IRcommand;
  uint32_t RawData;
  int ProgramCommand;
};

extern Command commands[];




#endif