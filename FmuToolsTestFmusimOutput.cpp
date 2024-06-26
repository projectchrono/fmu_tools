// =============================================================================
// fmu_tools
//
// Copyright (c) 2024 Project Chrono (projectchrono.org)
// Copyright (c) 2024 Digital Dynamics Lab, University of Parma, Italy
// Copyright (c) 2024 Simulation Based Engineering Lab, University of Wisconsin-Madison, USA
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution.
//
// =============================================================================
// Program for testing the output log from fmusim
// =============================================================================

#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    std::cout << "Opening fmusim log: " << FMUSIM_LOG << std::endl;
    std::cout << "-> status: ";
    std::ifstream file(FMUSIM_LOG);
    if (!file.is_open()) {
        std::cerr << "ERROR: cannot open file: " << FMUSIM_LOG << std::endl;
        return 1;
    }
    std::cout << " SUCCESS" << std::endl;

    //// RADU TODO ...

    std::regex errorRegex(R"(\[ERROR\](.*))");
    std::regex warningRegex(R"(\[WARNING\](.*))");
    std::string line;

    std::cout << "Parsing fmusim log..." << std::endl;
    unsigned int errorCount = 0;
    unsigned int warningCount = 0;
    while (std::getline(file, line)) {
        std::smatch match;
        if (std::regex_search(line, match, errorRegex)) {
            std::cout << "[Error]" << match[1] << std::endl;
            errorCount++;
        }
        else if (std::regex_search(line, match, warningRegex)) {
            std::cout << "[Warning]" << match[1] << std::endl;
            warningCount++;
        }
    }

    file.close();
    std::cout << "Parsing completed with:" << std::endl;
    std::cout << "- errors: " << errorCount << std::endl;
    std::cout << "- warnings: " << warningCount << std::endl;

    return errorCount > 0;
}