// All Copyright belongs to Konstantin Passig


#include "ExecuteShellCommand.h"
#include "..\Public\ExecuteShellCommand.h"
#include "iostream"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>


#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

/*void UExecuteShellCommand::ExecuteCommand(FString Command) {
	std::ostringstream;
	std::cout << "";
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, FString(Command));


}*/

FString UExecuteShellCommand::ExecuteCommand(FString cmd_raw) {
    char* cmd = TCHAR_TO_ANSI(*cmd_raw);
    std::array<char, 128> buffer;
    FString result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void UExecuteShellCommand::CloseConsole() {

}
