//Digital circuits
//This is a program to represent, manipulate, simualate and display digital circuits
//Written by Andras Botar
//May 2022

//import dependencies
#include "digitalcircuits.h"

//setup function to collect some start-up actions
int setup() 
{
    //Set up output mode of windows console so we can output unicode characters
    //Using std::wcout and std::wstring
    int _ = _setmode(_fileno(stdout), _O_U16TEXT);
    //digital_circuits::verbose = false;
    //std::wcout << L"Testing unicode -- English -- Ελληνικά -- Español." << std::endl;
    
    return 0;
}

//function to create and eample circuit with one of each logic gate type
void example_circuit(circuit& circuit_1) 
{
    circuit_1.add_component(std::make_unique< constant_input>(true, 1));
    circuit_1.add_component(std::make_unique< constant_input>(true, 2));
    circuit_1.add_component(std::make_unique< and_gate>(1, 2, 3));
    circuit_1.add_component(std::make_unique< or_gate>(1, 2, 4));
    circuit_1.add_component(std::make_unique< xor_gate>(1, 2, 5));
    circuit_1.add_component(std::make_unique< not_gate>(1, 7));
    circuit_1.add_component(std::make_unique< buffer>(1, 8));
    circuit_1.add_component(std::make_unique< majority_function>(1, 2, 9));
}


void tutorial() {
    std::wstring response;

    std::wcout << "Welcome to the digital circuits tutorial!\n";
    std::wcout << "The attached Readme file and the project report the functionality and background of this program,\n";
    std::wcout << "This tutorial will be an active demonstarion. Press enter to move along and input values. \n";
    std::wcout << "Following along in the code may be insightful, just search for \"Tutorial " << "Code\". \n";
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcin >> response;
    //std::cin.ignore();
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::wcout << "First, the two main classes in this program are components and circuits made of components.\n";
    std::wcout << "Let us create a circuit, and add some components to it: \n";
    std::wcout << "circuit circuit_1(10)\n";// example_circuit(circuit_1);\n";
    std::wcout << "\n";
    std::wcout << "\n";

    //create a circuit and add gate
    circuit circuit_1(5);
    circuit_1.add_component(std::make_unique< constant_input>(true, 1));
    circuit_1.add_component(std::make_unique< constant_input>(true, 2));

    //example_circuit(circuit_1);
    std::wcin >> response;

    std::wcout << "Here the \"5\" indicates the number of wires in the circuit (minus one). \n";
    std::wcout << "Wires mke up the state of a circuit. Each can be in a true or false state, and can be connected to multiple components.\n";
    std::wcout << "\n";
    std::wcin >> response;

    std::wcout << "Using circuit_1.print_state() we can see that all the wires are initialized to 0. \n";
    //print current state of circuit
    std::wcout << "Intitial state: ";
    circuit_1.print_state();
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcin >> response;

    std::wcout << "We have added some components to the circuit, so by calling circuit_1++ we can see those components act on the circuit state. \n";
    //simulate one time step and print new state
    circuit_1++; //equivalent to circuit_1.update();
    std::wcout << "New state:      ";
    circuit_1.print_state();
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcin >> response;

    std::wcout << "Updates are carried out in discrete timesteps. Using component circuit_1.get_component_type()\n";
    std::wcout << "First component: " << circuit_1.get_component_type(0) << "\n";
    std::wcout << "Second component: " <<  circuit_1.get_component_type(1) << "\n";
    std::wcout << "We can see that these are cosntant inputs, which have set their respective wires to true, and will keep them so.\n";
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcin >> response;

    std::wcout << "We now add an AND gate and an OR gate \n";
    //std::wcout << ", using:\n";
    circuit_1.add_component(std::make_unique< and_gate>(1, 2, 3));
    circuit_1.add_component(std::make_unique< or_gate>(1, 2, 4));
    std::wcout << "And if we do an additional update: \n";
    circuit_1++; 
    std::wcout << "New state:      ";
    circuit_1.print_state();
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcin >> response;

    std::wcout << "And we can now add more wires and components to the circuit: \n";
    std::wcout << "circuit_1.add_wires(3) adds 3 wires to the circuit;\n";
    std::wcout << "And we use circuit_1.add_component(std::make_unique< xor_gate>(3, 4, 5));\n";
    std::wcout << "To add a XOR gate taking inputs 3,4 and outputtign to wire 5.\n";
    std::wcout << "\n";
    circuit_1.add_wires(3);
    circuit_1.add_component(std::make_unique< xor_gate>(3, 4, 5));
    circuit_1.add_component(std::make_unique< not_gate>(1, 6));
    circuit_1.add_component(std::make_unique< buffer>(1, 7));
    circuit_1.print_state();
    std::wcout << "And we can even invert an existing gate, for example the first AND gate we added! \n";
    circuit_1.set_invert(2, true);
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcin >> response;

    std::wcout << "If we run forward another timestep: \n";
    circuit_1++;
    std::wcout << "New state:      ";
    circuit_1.print_state();
    //std::wcout << "\n";
    std::wcout << "We see all the gates took their effect.\n";
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcin >> response;


    std::wcout << "We can reset the state of the circuit using circuit_1.reset_state(); \n";
    std::wcout << "And we can run forward some given number of timesteps.\n";
    std::wcout << "(Please enter a positive integer (default 10)):\n";
    std::wcin >> response;
    int timesteps = 10;
    try {
        timesteps = std::stoi(response);
    }
    catch (...) {  }
    //reset circuit and run proper simulation
    std::wcout << "Simulation over "<< timesteps<<" timesteps: \n";
    circuit_1.reset_state();
    circuit_1.simulate_cli(timesteps);
    std::wcout << "\n\n";
    std::wcin >> response;

    std::wcout << "We can print detailed information on any component: circuit_1.component_info(2);\n";
    //Print info for a specific component
    std::wcout << "Detailed information of component 3: \n";
    circuit_1.component_info(3);
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcin >> response;

    std::wcout << "Or for the entire circuit: circuit_1.print_info();\n";
    std::wcin >> response;
    circuit_1.print_info();
    std::wcout << "\n";
    std::wcout << "\n";
    std::wcin >> response;


    std::wcout << "We can print the truth table for any logic gate\n";
    std::wcout << "Truth table for a XOR gate: \n";
    xor_gate gate_1(0, 1, 0);
    print_truth_table(gate_1, 2, 2);
    std::wcout << "\n";

    /*std::wcout << "Truth table for a bigger XOR gate: \n";
    xor_gate gate_2(0, 2, 0);
    std::vector<bool> trutht_2 = truth_table(gate_2, 3);
    print_state(trutht_2);
    std::wcout << "\n";*/




    std::wcout << "\n";
    std::wcout << "\n";
    std::wcout << "And we can even get the truth table for an entire circuit,\n";
    std::wcout << "because we can turn any arbitrary circuit into a logic gate!\n";
    std::wcout << "Just select which wire you would like to treat as an \"output\":\n";
    std::wcout << "(Please enter a positive integer (default 4)):\n";
    std::wcin >> response;
    int output_port = 4;
    try {
        output_port = std::stoi(response);
    }
    catch (...) {}

    //copy-create two more circuits
    circuit circuit_2(circuit_1); //copy constructor
    circuit circuit_3; //copy assignment operator
    circuit_3 = circuit_1;
    circuit_1.add_wires(1);
    circuit_1.add_component(circuit_2.to_logic_gate(1, 2, 8, output_port));
    std::wcout << "Old circuit_1 added as logic gate in slot 8!\n";
    std::wcout << "\n";

    std::wcout << "Truth table of wire "<< output_port<<" is: \n";
    sub_circuit_component gate_3;
    gate_3 = *circuit_2.to_logic_gate(1, 2, 0, output_port);
    print_truth_table(gate_3, 2, 2);
    std::wcout << "\n";
    std::wcout << "\n";



    std::wcout << "Visualizing the cirtcuit this way may be difficult.\n";
    std::wcout << "So a method is provided to display a circuit diagram.\n";
    std::wcout << "\n";
    try {
        write_diag_file(circuit_1);
        std::wcout << "A circuit diagram has now been created named circuit_diagram, in the program folder.\n";
        std::wcout << "\n";
    }
    catch(...) {
        std::wcout << "The program was unable to create a circuit diagram.\n";
    }
    std::wcout << "\n";
    std::wcout << "\n";

    std::wcout << "\n";
    std::wcout << "That is the end of the tutorial.\n";
    std::wcout << "Thank you for viewing!\n";
    std::wcout << "\n";


    //create a circuit and fill it with example data
    /*std::wcout << "Delete wires and re-run simulation.\n";
    circuit_1.reset_state();
    circuit_1.delete_wires(std::vector<int>{3, 8});
    //circuit_1.delete_wires(std::vector<int>{5, 8});
    circuit_1.simulate_cli(5);
    std::wcout << "\n\n";*/

    //std::wcin >> response;
    //if (response == L"1") {}
    //else if (response == L"2") { state = 98; }
    
    //circuit_1.debug();
}

void UI()
{
    //Then, some sort of UI is needed, so
        //a menu sysem is created as a state machine
    int state = 1; //Use int to represent states, since unfortunately string cannto be used for switch

    //declare variables
    std::wstring response; //user response
    std::wstring response2;
    std::wifstream f("README.txt");

    while (state != 0) {
        //cin.clear();
        switch (state)
        {
        default:
            //break;
        case 0:
            break;
        case 1: //Main menu
            std::wcout << "Welcome to the digital circuit simualtor!\n";
            std::wcout << "Please select what you would like to do: \n";
            std::wcout << "(press the associated number on you keyboard, then enter to cinfirm your choice)";

            std::wcout << "1-See tutorial\n";
            std::wcout << "2-Load existing circuit\n";
            std::wcout << "3-Create new circuit\n";
            std::wcout << "4-Settings\n";
            std::wcout << "5-Help\n";
            std::wcout << "6-Exit\n";
            std::wcout << "";
            //crete component

            std::wcout << "\n";
            std::wcout << "-made by AND(ras, Botar)\n";

            std::wcin >> response;
            //std::wcout << (response==L"3") << L"\n";
            if (response == L"1") { state = 10; }
            else if (response == L"2") { state = 20; }
            else if (response == L"3") { state = 30; }
            else if (response == L"4") { state = 40; }
            else if (response == L"5") { state = 50; }
            else if (response == L"6") { state = 60; } //Exit
            else if (response == L"9") { state = 99; } //Debug
            break;

        case 10: // Tutorial Code
            try {
                tutorial();
            }
            catch (...) {
                std::wcout << "There was an error while running the tutorial.";
            }
            //std::wcout << "Would you like to continue to ...\n";

            //return to main menu
            state = 1;
            break;

        case 20:
            std::wcout << "Please select which circuit you would like to load: \n";
            std::wcout << "1- Example tutorial circuit. \n";

            std::wcin >> response;


            break;

        case 30: //Create new circuit

            break;

        case 40: //Settings
            std::wcout << "Please select which settings you would like to change: \n";
            std::wcout << "1- verbosity: Useful for debugging: " << verbose << " \n";
            std::wcout << "2- draw symbols in circuit diagram: " << draw_symbols << "\n";
            std::wcout << "3- draw names in circuit diagram: " << draw_names << "\n";
            std::wcout << "4- draw labels in circuit diagram: " << draw_labels << "\n";
            std::wcout << "5- file format to export circuti diagram. Must be one of: png, svg or pdf. \n";
            std::wcout << "6- for truth tables print column and row indecies: " << print_indecies << " \n";
            std::wcout << "7- whether to print a frame around truth table: " << print_frame << "  \n";
            //std::wcout << "8- ";
            std::wcout << "8- return to main menu.\n";
            std::wcout << "\n";



            std::wcin >> response;
            if (response == L"1") { verbose = !verbose; }
            else if (response == L"2") { draw_symbols = !draw_symbols; }
            else if (response == L"3") { draw_names = !draw_names; }
            else if (response == L"4") { draw_labels = !draw_labels; }
            else if (response == L"5") {
                std::wcout << "PLease select which format you would like to use: ";
                std::wcout << "1-png\n";
                std::wcout << "2-svg\n";
                std::wcout << "3-pdf\n";
                std::wcin >> response2;
                if (response2 == L"1") { diagram_format = "png"; }
                else if (response2 == L"2") { diagram_format = "svg"; }
                else if (response2 == L"3") { diagram_format = "pdf"; }
            }
            else if (response == L"6") { print_indecies = !print_indecies; }
            else if (response == L"7") { print_frame = !print_frame; }
            else if (response == L"8") { state = 1; }
            break;

        case 50:
            if (f.is_open())
                while (!f.fail() && !f.eof() && !f.peek() != EOF)
                {
                    std::wcout << f.rdbuf();
                }
            std::wcin >> response;
            break;
        case 60:
            state = 0; //Exit program
            break;

        case 99: // Debug
            std::wcout << "Text \n";
            std::wcout << "\n";

            std::wcin >> response;
            if (response == L"1") {}
            else if (response == L"2") { state = 98; }
            break;

        }
        //restart while loop
    }
}

void clean_up()
{
    //Cleanup memory
    if (verbose) { std::wcout << "Cleaning up: \n"; }
    //delete circuit_1; //destructors take care of cleanups

    //Exit program
    std::wcout << "\n";
    std::wcout << "Goodbye!\n";
}





//Main function of program
//ENTRY POINT HERE
int main()
{   
    //First, do some basic setup so everything will work fine
    setup();

    //Then use UI to allow user itneraction
    UI();

    //and close program
    clean_up();
    return 0;
}





