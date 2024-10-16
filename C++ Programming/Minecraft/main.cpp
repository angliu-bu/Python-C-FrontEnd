// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// main.cpp

#include "View.h"
#include "Model.h"
#include "Game_Command.h"
#include "Input_Handling.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

/*****************************************************************/
/* MAIN PROGRAM:                                                 */
/*****************************************************************/

int main()
{
	// initialize model, view
	Model model;
	View view;

	// open filestreams for saving and restoring
	ofstream save_stream;
	ifstream restore_stream;

	// show initial game status
	model.show_status();
	model.display(view);

	bool progRunning = true;
	
	// MAIN PROGRAM LOOP:
	while (progRunning)
	{
		// get command from user
		string command;
		
		cout << "Enter Command: ";
		getline(cin, command);
		
		string filename;
		char cmd;
		char new_type;
		int par1 = 0;
		double par2 = 0;
		double par3 = 0;
		
		// parse and error check command
		try
		{
			parse_command(command, filename, cmd, new_type, par1, par2, par3);

			// valid command was entered (no exception yet thrown)
			switch (cmd)
			{
				case 'n': // "new", format: n TYPE ID x y
				{
					do_new_command(model, new_type, par1, par2, par3);

					// update view after each new object is added
					model.display(view);
					break;
				}
				case 'm': // "move", format: m ID x y

					do_move_command(model, par1, par2, par3);
					break;

				case 'w': // "work", format: w ID1 ID2 ID3
										
					do_work_command(model, par1, int(par2), int(par3));
					break;
							
				case 's': // "stop", format: s ID

					do_stop_command(model, par1);
					break;

				case 'a': // "attack", format a ID1 ID2
				
					do_attack_command(model, par1, int(par2));
					break;

				case 'i': // "inspect", format i ID

					do_inspect_command(model, par1);
					break;
				
				case 'l': // "list" - show status of all game objects

					do_list_command(model);
					break;

				case 'g': // "go" - one time step

					do_go_command(model, view);
					break;

				case 'r': // "run" - NUM_RUN_STEPS (5) time steps

					do_run_command(model, view);
					break;

				case 'S':

					do_save_command(model, save_stream, filename);
					break;

				case 'R':

					do_restore_command(model, restore_stream, filename);

					// show status of objects and display game view after restore
					model.show_status();
					model.display(view);
					break;

				case 'q': // "quit"

					do_quit_command(progRunning);
					break;
			}	
		}
		catch (Invalid_Input &e)
		{
			cout << "Invalid input - " << e.msg_ptr << endl;
			continue;
		}
	
	} // END MAIN PROGRAM LOOP	
	return 0;
}