// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Game_Command.cpp

#include "Model.h"
#include "View.h"
#include "Game_Command.h"
#include "Cart_Point.h"
#include "Person.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Input_Handling.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <exception>

// limit of time steps per run
#define NUM_RUN_STEPS 5 // default is 5 time units

using namespace std;

/*****************************************************************/
/* MODEL COMMANDS:                    	                         */
/*****************************************************************/

// do_new_command()
//-----------------------------------------
// creates a new object at location (x, y)

void do_new_command(Model &model, char type, int object_id, double x_coord, double y_coord)
{
	// create new Game_Object
	model.handle_new_command(type, object_id, x_coord, y_coord);

}

// do_move_command()
//-----------------------------------------
// moves a person to location (x, y)

void do_move_command(Model &model, int person_id, double x_coord, double y_coord)
{
	Person *person_ptr = model.get_Person_ptr(person_id);

	if (person_ptr == 0)
		throw Invalid_Input("Invalid ID entered.");

	else
		person_ptr->start_moving(Cart_Point(x_coord,y_coord)); 
}

// do_work_command()
//-----------------------------------------
// starts specified Miner working at specified
// Gold_Mine and Town_Hall

void do_work_command(Model &model, int miner_id, int gold_id, int town_id)
{
	Person *miner_ptr = model.get_Person_ptr(miner_id);
	Gold_Mine *mine_ptr = model.get_Gold_Mine_ptr(gold_id);
	Town_Hall *town_ptr = model.get_Town_Hall_ptr(town_id);

	if (miner_ptr == 0 || mine_ptr == 0 || town_ptr == 0)
		// at least one id is invalid
		throw Invalid_Input("Invalid ID entered.");
	else
		// valid command
		miner_ptr->start_mining(mine_ptr, town_ptr); // start mining
}

// do_stop_command()
//-----------------------------------------
// stops a moving person

void do_stop_command(Model &model, int person_id)
{
	Person *person_ptr = model.get_Person_ptr(person_id);
	if (person_ptr == 0)
		// person does not exist
		throw Invalid_Input("Invalid ID entered.");
	else
		person_ptr->stop(); // stop valid person
}

// do_attack_command()
//-----------------------------------------
// starts Soldier attacking another Person

void do_attack_command(Model &model, int attacker_id, int target_id)
{
	Person *attacker_ptr = model.get_Person_ptr(attacker_id);
	if (attacker_ptr == 0)
	{
		// attacker does not exist
		throw Invalid_Input("Invalid ID for attacker.");
	}
	else
	{
		Person *target_ptr = model.get_Person_ptr(target_id);

		if (target_ptr == 0)
		{
			// target does not exist
			throw Invalid_Input("Invalid ID for target.");
		}
		else
		{
			// initiate attack
			attacker_ptr->start_attack(target_ptr);
		}
	}
}

// do_inspect_command()
//-----------------------------------------
// starts Inspector inspecting Gold_Mines

void do_inspect_command(Model &model, int inspector_id)
{
	Person *inspector_ptr = model.get_Person_ptr(inspector_id);

	if (inspector_ptr == 0) // Inspector does not exist
		throw Invalid_Input("Invalid ID entered.");
	else
	{
		list<Gold_Mine*> mines = model.get_Gold_Mine_list();
		if (mines.empty()) // no gold mines exist
			cout << "No Gold_Mines available for inspection." << endl;
		else
			inspector_ptr->start_inspecting(model);
	}
}

// do_list_command()
//-----------------------------------------	
// lists the status of all objects

void do_list_command(Model &model)
{
	// list the status of all game object
	model.show_status();
}

// do_go_command()
//-----------------------------------------
// advances time by one tick, updates objects

void do_go_command(Model &model, View &view)
{	
	// update objects
	model.update();
	
	// show status
	model.show_status();

	// display game grid
	model.display(view);
}

// do_run_command()
//-----------------------------------------
// advances time until next event or
// NUM_RUN_STEPS ticks, updates objects

void do_run_command(Model &model, View &view)
{
	// advance one time step
	cout << "Advancing to next event." << endl;
	
	// update objects
	bool event = model.update();

	// initialize runtime counter
	int runtime = 2;
	
	// advance additional (NUM_RUN_STEPS - 1) steps
	while(runtime <= NUM_RUN_STEPS && !event)
	{
		// advance one time step
		runtime++;
		event = model.update();
	}
	
	// show status
	model.show_status();

	// refresh view
	model.display(view);
}

// do_save_command()
//-----------------------------------------
// save the current state of the program
// to specified file in current directory

void do_save_command(Model &model, ofstream &save_stream, string filename)
{
	// open specified file
	save_stream.open(filename);

	// save game
	model.save(save_stream);

	// close specified file
	save_stream.close();

	cout << "Game saved!" << endl;
}

// do_restore_command()
//-----------------------------------------
// restore the state from a specified file
// in the current directory

void do_restore_command(Model &model, ifstream &restore_stream, string filename)
{
	// open specified file
	restore_stream.open(filename);

	// error check
	if (restore_stream.is_open())
	{
		// restore game from file
		model.restore(restore_stream);
		
		// close file
		restore_stream.close();
	}
	else
		throw Invalid_Input("Restore file does not exist.");
}

// do_quit_command()
//-----------------------------------------
// quits the program, terminates the main loop

void do_quit_command(bool &progRunning)
{
	cout << "Terminating Program." << endl;
	progRunning = false;
}

/*****************************************************************/
/* MAIN PROGRAM FUNCTIONS:                                       */
/*****************************************************************/

// initialize()
//-----------------------------------------	
// prints the program header

void initialize()
{
	cout << "MineCraft 2.0" << endl;
	cout << "EC 327: Introduction to Software Engineering" << endl;
	cout << "Carlton Duffett" << endl;
	cout << "24 November, 2013"<< endl << endl;
}

// printCurrentTime()
//-----------------------------------------
// prints the current time unit

void printCurrentTime(int currentTime)
{
	cout << "Time: " << currentTime << endl;
}

/*****************************************************************/
/* COMMAND PARSING:                                              */
/*****************************************************************/

// get_command()
//-----------------------------------------
// evaluates and error checks user commands.
// valid commands are:
//
// "new" TYPE of ID at location (x,y):
// >> n TYPE ID x y
//
// "move" ID1 to location (x,y): 
// >> m ID1 x y
//
// "work" ID1 at ID2 and deposit at ID3:
// >> w ID1 ID2 ID3
//
// "stop" ID1:
// >> s ID1
//
// "attack" ID1 attack ID2:
// >> a ID1 ID2
//
// "inspect" all gold mines using ID:
// >> i ID
//
// "list" the status of all objects:
// >> l
//
// "go" advance one unit of time:
// >> g
//
// "run" advance 5 units of time:
// >> r
//
// "save" the current state to FILENAME:
// >> S FILENAME
//
// "restore" the state from FILENAME:
// >> R FILENAME
//
// "quit" the program:
// >> q

void parse_command(string command, string &filename, char &cmd, char &type, int &par1, double &par2, double &par3)
{	
	// string must be at least 1 character to begin parsing
	if (command.length() == 0)
		throw Invalid_Input("No command given.");

	// get first character of string
	char character = command.at(0);

	char new_type;
	int parameter1;
	double parameter2;
	double parameter3;

	// error check command
	switch (character)
	{
		case 'n':
			cmd = character;
			try
			{
				get_parameters(4, command, new_type, parameter1, parameter2, parameter3);
				type = new_type;
				par1 = parameter1;
				par2 = parameter2;
				par3 = parameter3;
			}
			catch (exception &e)
			{
				throw Invalid_Input("Invalid parameters for command 'n'.");
			}
			break;

		case 'm':
			cmd = character;
			try
			{
				get_parameters(3, command, new_type, parameter1, parameter2, parameter3);
				par1 = parameter1;
				par2 = parameter2;
				par3 = parameter3;
			}
			catch(exception &e)
			{
				throw Invalid_Input("Invalid parameters for command 'm'.");
			}
			break;
				
		case 'w':
			cmd = character;
			try
			{
				get_parameters(3, command, new_type, parameter1, parameter2, parameter3);
				par1 = parameter1;
				par2 = parameter2;
				par3 = parameter3;
			}
			catch(exception &e)
			{
				throw Invalid_Input("Invalid parameters for command 'w'.");
			}
			break;
				
		case 's':
			cmd = character;
			try
			{
				get_parameters(1, command, new_type, parameter1, parameter2, parameter3);
				par1 = parameter1;
			}
			catch(exception &e)
			{
				throw Invalid_Input("Invalid parameters for command 's'.");
			}
			break;

		case 'a':
			cmd = character;
			try
			{
				get_parameters(2, command, new_type, parameter1, parameter2, parameter3);
				par1 = parameter1;
				par2 = parameter2;
			}
			catch(exception &e)
			{
				throw Invalid_Input("Invalid parameters for command 'a'.");
			}
			break;

		case 'i':
			cmd = character;
			try
			{
				get_parameters(1, command, new_type, parameter1, parameter2, parameter3);
				par1 = parameter1;
			}
			catch(exception &e)
			{
				throw Invalid_Input("Invalid parameters for command 'i'.");
			}
			break;

		case 'l':
			cmd = character;
			break;
				
		case 'g':
			cmd = character;
			break;
				
		case 'r':
			cmd = character;
			break;

		case 'S':
		{
			cmd = character;
			string tryfile;
			try
			{
				tryfile = get_filename(command);
				filename = tryfile;
			}
			catch (Invalid_Input &e)
			{
				// rethrow exception
				throw e;
			}
			break;
		}
		case 'R':
		{
			cmd = character;
			string tryfile;
			try
			{
				tryfile = get_filename(command);
				filename = tryfile;
			}
			catch (Invalid_Input &e)
			{
				// rethrow exception
				throw e;
			}
			break;
		}	
		case 'q':
			cmd = character;
			break;
				
		default:	// invalid command
			throw Invalid_Input("Not a valid character command.");
			break;
	}
		
	// evaluate single letter commands
	if (cmd == 'g' || cmd == 'r' || cmd == 'l' || cmd == 'q')
	{
		if (command.length() != 1) // valid single character command (g, r, l, q)
			throw Invalid_Input("Invalid format for single-character command.");
	}
}

// get_parameters()
//-----------------------------------------
// gets required parameters for a valid command.

void get_parameters(int num_params, string command, char &type, int &par1, double &par2, double &par3)
{
	int parameter1;
	double parameter2;
	double parameter3;

	// get expected space after command character
	char space = command.at(1);
	if (space != ' ')
		throw exception();

	switch (num_params)
	{
		case 1:
		{
			// Parameter 1
			string par1str = command.substr(2);

			// check for excess input, yielding an invalid command
			if (check_for_excess(par1str))
				throw exception();

			istringstream convert1(par1str); // convert string to number

			if(!(convert1 >> parameter1))
				throw exception();

			par1 = parameter1;
			break;
		}
		case 2:
		{
			// Parameter 1
			int nextspace = command.find(' ',2);
			string par1str = command.substr(2,nextspace - 2);
			istringstream convert1(par1str);

			if(!(convert1 >> parameter1))
				throw exception();

			par1 = parameter1;

			// Parameter 2
			string par2str = command.substr((nextspace + 1));

			// check for excess input, yielding an invalid command
			if (check_for_excess(par2str))
				throw exception();

			istringstream convert2(par2str);

			if(!(convert2 >> parameter2))
				throw exception();

			par2 = parameter2;
			break;
		}
		case 3:
		{
			// Parameter 1
			int nextspace = command.find(' ',2);
			string par1str = command.substr(2,nextspace - 2);

			istringstream convert1(par1str);

			if(!(convert1 >> parameter1))
				throw exception();

			par1 = parameter1;

			// Parameter 2
			int currentspace = nextspace;
			nextspace = command.find(' ', (currentspace + 1));

			string par2str = command.substr((currentspace + 1),(nextspace - currentspace - 1));
			istringstream convert2(par2str);

			if(!(convert2 >> parameter2))
				throw exception();

			par2 = parameter2;

			// Parameter 3
			string par3str = command.substr((nextspace + 1)); // remaining string

			// check for excess input, yielding an invalid command
			if (check_for_excess(par3str))
				throw exception();

			istringstream convert3(par3str); // convert string to a number

			if(!(convert3 >> parameter3))
				throw exception();

			par3 = parameter3;
			break;
		}
		case 4:
		{
			// Parameter 1
			type = command.at(2); // character type for the "new" command

			// Parameter 2
			int currentspace = command.find(' ',2);
			int nextspace = command.find(' ',(currentspace + 1));

			string par1str = command.substr((currentspace + 1),(nextspace - currentspace - 1));
			istringstream convert1(par1str);

			if(!(convert1 >> parameter1))
				throw exception();

			par1 = parameter1;

			// Parameter 3
			currentspace = nextspace;
			nextspace = command.find(' ', (currentspace + 1));

			string par2str = command.substr((currentspace + 1),(nextspace - currentspace - 1));
			istringstream convert2(par2str);

			if(!(convert2 >> parameter2))
				throw exception();

			par2 = parameter2;

			// Parameter 4
			string par3str = command.substr((nextspace + 1)); // remaining string

			// check for excess input, yielding an invalid command
			if (check_for_excess(par3str))
				throw exception();

			istringstream convert3(par3str);

			if(!(convert3 >> parameter3))
				throw exception();

			par3 = parameter3;
			break;
		}
	}
}

// get_filename()
//-----------------------------------------
// gets filename for save and restore commands.

string get_filename(string command)
{
	// get expected space after command character
	char space = command.at(1);
	if (space != ' ')
		throw Invalid_Input("Invalid format for command.");

	// filename should be remaining string
	string filename = command.substr(2);

	// maximum length is 99 characters
	if (filename.length() > 99)
		throw Invalid_Input("Filename exceeds maximum length (99).");

	// filename may not contain spaces
	if (filename.find(' ') != -1)
		throw Invalid_Input("Filename cannot contain spaces.");

	// no exceptions thrown, valid filename
	return filename;
}

// check_for_excess()
//-----------------------------------------
// evaluates the last parameter in each
// command. If a space is present, excess
// input was provided and the command is invalid.

bool check_for_excess(string remaining)
{
	int unknown_space = remaining.find(' ');

	if (unknown_space == -1)
		return false; // NO excess input found
	else
		return true; // excess input found
}