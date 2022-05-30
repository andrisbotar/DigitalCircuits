



#include <iostream>
#include <sstream>  
#include <fstream>
#include <string>
#include <array>
#include "drawing.h"
#include "circuit.h"
#include "utility.h"
using namespace digital_circuits;

namespace digital_circuits
{

	void circuit_to_diag(circuit circ)
	{
		if (check_blockdiag()) {
			write_diag_file(circ);
		}
	}

	bool check_blockdiag()
	{
		bool found_blockdiag = false;
		std::string command("blockdiag --version");

		//Call system call of blockdiag and check if it is installed
		//Code until "compare with.." copied from https://stackoverflow.com/questions/44610978/popen-writes-output-of-command-executed-to-cout
		std::array<char, 128> buffer;
		std::string result;
		FILE* pipe = _popen(command.c_str(), "r");
		if (!pipe)
		{
			std::wcout << "Could not conenct to system shell";
			found_blockdiag = false;
		}
		else {
			while (fgets(buffer.data(), 128, pipe) != NULL) {
				result += buffer.data();
			}
		}

		//copare with that blockdiag should produce
		if (result.rfind("blockdiag ", 0) == 0) {
			found_blockdiag = true;
			//std::wcout << L"Blockdiag found!";
			//std::cerr << "Blockdiag found!";
		}


		if (found_blockdiag) {
			std::wcout << L"Blockdiag installation not detected, unable to draw circuit diagram.\n" <<
				"Please isntall it using 'sudo dnf install Bloackdiag'. ";
			std::cerr << L"Blockdiag installation not detected, unable to draw circuit diagram.\n" <<
				"Please isntall it using 'sudo dnf install Bloackdiag'. ";
			return false;
		}
		return true;
	}

	//Writes a .diag fiel that blaockiag can udnerstand
	void write_diag_file(circuit circ, bool show_labels)
	{
		size_t count = circ.component_count();
		size_t size = circ.size();
		std::wstringstream ss;
		std::vector<std::wstring> gates(size, L"");
		std::wstring typ;
		//std::unique_ptr<component> comp;
		//std::wcout << count;

		//write down each gate and its label
		ss << "{\n";
		for (int i = 0; i < count; ++i) {
			//std::unique_ptr<component> comp(circ.get_component_copy(i));
			//defined nodes representing each compoennt
			typ = circ.get_component_type(i);
			ss << L"gate" << i << L" [";
			if (draw_names) { ss << "label=\"" << typ; }
			if (draw_labels) { ss << ": " << circ.get_component_label(i); }
			
			//ss << get_backgrdound(typ); //read access violation

			//draw symbols for each gate
			if (draw_symbols) {
				if (typ == L"AND Gate") { ss << L"\", background=\"images\\and.png"; }
				if (typ == L"OR Gate") { ss << L"\", background=\"images\\or.png"; }
				if (typ == L"XOR Gate") { ss << L"\", background=\"images\\xor.png"; }
				if (typ == L"Inverting AND Gate") { ss << L"\", background=\"images\\nand.png"; }
				if (typ == L"Inverting OR Gate") { ss << L"\", background=\"images\\nor.png"; }
				if (typ == L"Inverting XOR Gate") { ss << L"\", background=\"images\\nxor.png"; }
				if (typ == L"NOT Gate" || typ == L"Inverting Buffer") { ss << L"\", background=\"images\\not.png"; }
				if (typ == L"Constant True Input") { ss << L"\", background=\"images\\T.png"; }
				if (typ == L"Constant False Input") { ss << L"\", background=\"images\\F.png"; }
			}
			ss << "\"];\n";
			//keep track of where they output
			//std::wcout << i<<": "<< circ.get_component_output(i) <<"\n";
			gates[circ.get_component_output(i)] = (L"gate" + std::to_wstring(i));
		}

		//write down conenctiosn between gates
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < count; ++j) {
				//print_vector(circ.get_component_inputs(j));
				if (vector_contains(i, circ.get_component_inputs(j)) && gates[i] != L"") {
					ss << gates[i] << L" -> gate" << j << ";\n"; //<< " [label=\"" << i <<"\"];\n";
				}
			}
			std::wcout << "\n";
		}
		ss << "\n}";

		//try to write out to file
		try {
			std::wofstream outFile("diag_print.diag");
			outFile << ss.rdbuf();
			outFile.close();
		}
		catch (...) {
			std::wcout << "Unalbe to write .diag file";
		}

		//try to call external block_diag to convert .diag into image
		try {
			system("blockdiag diag_print.diag");
		}
		catch (...) {
			std::wcout << "Unable to call BlockDiag to create image";
		}

	}




}