#include <iostream>
#include <string>
#include <Windows.h>



//BOOL WINAPI ReadProcessMemory(
//	_In_  HANDLE  hProcess,
//	_In_  LPCVOID lpBaseAddress,
//	_Out_ LPVOID  lpBuffer,
//	_In_  SIZE_T  nSize,
//	_Out_ SIZE_T  *lpNumberOfBytesRead
//);
//
//HANDLE WINAPI OpenProcess(
//	_In_ DWORD dwDesiredAccess,
//	_In_ BOOL  bInheritHandle,
//	_In_ DWORD dwProcessId
//);

//BOOL WriteProcessMemory(
//	HANDLE  hProcess,
//	LPVOID  lpBaseAddress,
//	LPCVOID lpBuffer,
//	SIZE_T  nSize,
//	SIZE_T  *lpNumberOfBytesWritten
//);



void clean() {
	std::cout << std::string(100, '\n');
}

int main() {
	
		std::string selectedOP;
		std::string position;

		DWORD pid = 0;
		std::cout << "Enter PID: ";
		std::cin >> pid;
		std::cout << "PID: " << pid << " is valid" <<'\n';

		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		std::cout << "Opening process: " << pid << '\n';
			if (hProcess == NULL) {
				std::cout << "OpenProcess failed, reason: " << GetLastError() << '\n';
				system("pause");
				return EXIT_FAILURE;
			}

		std::string ops[5] = { "Please select what do you want to overwrite:", "1. Integer", "2. Char", "3. Exit" };

		std::cout << ops[0] << '\n';
		std::cout << ops[1] << '\n';
		std::cout << ops[2] << '\n';
		std::cout << ops[3] << '\n';
		std::cout << ops[4] << '\n';
		std::cout << "Waiting for input: ";

		int opSelected = 0;
		std::cin >> opSelected;
		selectedOP = ops[opSelected];
		std::cout << "You selected: " << selectedOP << '\n';
		int rInput = 0;
	
			while (opSelected != 3){
		
				clean();
			

				if (opSelected == 1) {



					clean();


					std::cout << selectedOP << " overwriting" << '\n';

					uintptr_t memoryaddress = 0x0;
					std::cout << "Which memory address are you overwriting? (in hexadecimal): 0x";
					std::cin >> std::hex >> memoryaddress;
					std::cout << "Overwriting memory at address: " << std::hex << std::uppercase << memoryaddress << " ..." << '\n';

					int intToWrite = 0;
					std::cout << "Enter a integer that will overwrite current one: ";
					std::cin >> std::dec >> intToWrite;
					bool wpmReturn = WriteProcessMemory(hProcess, (LPVOID)memoryaddress, &intToWrite, sizeof(int), NULL);
					if (wpmReturn == FALSE) {
						std::cout << "writeProcessMem failed, reason: " << std::dec << GetLastError() << '\n';
						system("pause");
						return EXIT_FAILURE;
					}

					std::cout << "Successfully rewritten to: " << std::dec << intToWrite << '\n';
					std::cout << "Press 1 to write again\n";
					std::cin >> rInput;

				}

				else if (opSelected == 2){

					clean();
					

						std::cout << selectedOP << " overwriting" << '\n';

					uintptr_t memoryaddress = 0x0;
						std::cout << "Which memory address are you overwriting? (in hexadecimal): 0x";
						std::cin >> std::hex >> memoryaddress;
						std::cout << "Overwriting memory at address: " << std::hex << std::uppercase << memoryaddress << " ..." << '\n';

					char arrToWrite[128] = "''";
						std::cout << "Enter a char (or array of chars) that will overwrite current one: ";
						std::cin >> std::dec >> arrToWrite;
					bool wpmReturn = WriteProcessMemory(hProcess, (LPVOID)memoryaddress, &arrToWrite, sizeof(char[128]), NULL);
						if (wpmReturn == FALSE) {
							std::cout << "writeProcessMem failed, reason: " << std::dec << GetLastError() << '\n';
							system("pause");
							return EXIT_FAILURE;
						}

						std::cout << "Successfully rewritten to: " << std::dec << arrToWrite << '\n';
						std::cout << "Press 1 to write again\n";
						std::cin >> rInput;


					}
				}
			


		BOOL close = CloseHandle(hProcess);
			if (close == TRUE)
			{
			std::cout << "We done, closed handle";
			}




	return 0;

}	