// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Game_Command.h

#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H

#include "Model.h"
#include "View.h"
#include <string>
#include <fstream>

using namespace std;

// command functions:
void do_new_command(Model &, char, int, double, double);
void do_move_command(Model &, int, double, double);
void do_work_command(Model &, int, int, int);
void do_stop_command(Model &, int);
void do_attack_command(Model &, int, int);
void do_inspect_command(Model &, int);
void do_list_command(Model &);
void do_go_command(Model &, View &);
void do_run_command(Model &, View &);
void do_save_command(Model &, ofstream &, string);
void do_restore_command(Model &, ifstream &, string);
void do_quit_command(bool &);

// main program functions:
void initialize();
void printCurrentTime(int);

// command parsing functions:
void parse_command(string, string &, char &, char &, int &, double &, double &);
void get_parameters(int, string, char &, int &, double &, double &);
string get_filename(string);
bool check_for_excess(string);

#endif