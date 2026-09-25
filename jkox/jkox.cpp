// Created by Yuri Alexander Pagel Krüger

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

void setCol(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

std::string GetOEMProductKey() {
    const DWORD acpiSignature = 'IPCA';
    const DWORD msdmSignature = 'MDSM';

    DWORD bufSize = GetSystemFirmwareTable(acpiSignature, msdmSignature, nullptr, 0);
    if (bufSize == 0) return "";

    std::vector<char> buffer(bufSize);
    if (GetSystemFirmwareTable(acpiSignature, msdmSignature, buffer.data(), bufSize) == 0) {
        return "";
    }

    if (bufSize >= 29) {
        std::string key(buffer.end() - 29, buffer.end());
        if (key[5] == '-' && key[11] == '-' && key[17] == '-' && key[23] == '-') {
            return key;
        }
    }
    return "";
}

std::string SanitizeKey(const std::string& input) {
    std::string clean = "";
    for (char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            clean += static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        }
    }

    if (clean.length() != 25) {
        return "";
    }

    std::string formatted = "";
    for (size_t i = 0; i < 25; ++i) {
        formatted += clean[i];
        if ((i + 1) % 5 == 0 && i < 24) {
            formatted += '-';
        }
    }
    return formatted;
}

void RenderMenu() {
    system("cls");
    std::cout << "\n";

    setCol(14); std::cout << "  (*)  ";
    setCol(11); std::cout << "   ██╗██╗  ██╗ ██████╗ ██╗  ██╗";
    setCol(14); std::cout << "   (*)\n";

    setCol(14); std::cout << "   │   ";
    setCol(11); std::cout << "   ██║██║ ██╔╝██╔═══██╗╚██╗██╔╝";
    setCol(14); std::cout << "    │\n";

    setCol(15); std::cout << "  ███  ";
    setCol(11); std::cout << "   ██║█████╔╝ ██║   ██║ ╚███╔╝ ";
    setCol(15); std::cout << "   ███\n";

    setCol(15); std::cout << "  ███  ";
    setCol(11); std::cout << "██╗██║██╔═██╗ ██║   ██║ ██╔██╗ ";
    setCol(15); std::cout << "   ███\n";

    setCol(15); std::cout << "  ███  ";
    setCol(11); std::cout << "╚████║██║  ██╗╚██████╔╝██╔╝ ██╗";
    setCol(15); std::cout << "   ███\n";

    setCol(15); std::cout << "  ███  ";
    setCol(3);  std::cout << " ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝";
    setCol(15); std::cout << "   ███\n";

    setCol(11);
    std::cout << "\n                :: CORE OEM ACTIVATION TOOLKIT ::\n";
    setCol(8);
    std::cout << " ────────────────────────────────────────────────────────────────────────\n";
    setCol(15);
    std::cout << "  [1] Auto OEM Activation (Extract from BIOS & Activate)\n";
    std::cout << "  [2] Display Embedded OEM Key Only\n";
    std::cout << "  [3] Manual Key Input & Activation\n";
    std::cout << "  [4] Check Current Activation Status\n";
    std::cout << "  [5] Exit\n";
    setCol(8);
    std::cout << " ────────────────────────────────────────────────────────────────────────\n";
    setCol(11);
    std::cout << " > Select an option [1-5]: ";
    setCol(15);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitleA("JKOX - OEM & Retail Activation Engine");

    std::string opt;
    while (true) {
        RenderMenu();
        std::getline(std::cin, opt);

        if (opt == "1") {
            system("cls");
            setCol(11);
            std::cout << "\n [+] JKOX // AUTOMATED OEM ACTIVATION\n";
            setCol(8);
            std::cout << " ────────────────────────────────────────────────────────────────\n";
            setCol(7);
            std::cout << " This procedure extracts the original factory license embedded in the\n"
                << " motherboard ACPI MSDM table and applies it to this Windows installation.\n\n";

            setCol(14);
            std::cout << " [*] Querying firmware table...\n";
            std::string oemKey = GetOEMProductKey();

            if (oemKey.empty()) {
                setCol(12);
                std::cout << "\n [-] ERROR: No embedded OEM license found in BIOS/UEFI.\n"
                    << "     Possible causes:\n"
                    << "     - Custom assembled desktop motherboard.\n"
                    << "     - Laptop shipped without an OS (FreeDOS / Linux).\n\n";
            }
            else {
                setCol(10);
                std::cout << " [+] Embedded OEM Key detected: " << oemKey << "\n\n";
                setCol(15);

                std::cout << " [*] Step 1/3: Registering key into Software Licensing Service (slmgr /ipk)...\n";
                std::string cmdIpk = "cscript //nologo %windir%\\system32\\slmgr.vbs /ipk " + oemKey;
                system(cmdIpk.c_str());

                std::cout << "\n [*] Step 2/3: Contacting Microsoft KMS/Activation servers (slmgr /ato)...\n";
                system("cscript //nologo %windir%\\system32\\slmgr.vbs /ato");

                std::cout << "\n [*] Step 3/3: Validating license state...\n";
                setCol(8);
                std::cout << " ----------------------------------------------------------------\n";
                setCol(15);
                system("cscript //nologo %windir%\\system32\\slmgr.vbs /xpr");
                setCol(8);
                std::cout << " ----------------------------------------------------------------\n";

                setCol(10);
                std::cout << "\n [+] Activation sequence finished.\n";
            }
            setCol(8);
            system("pause");
        }
        else if (opt == "2") {
            system("cls");
            setCol(11);
            std::cout << "\n [+] JKOX // FIRMWARE KEY VIEWER\n";
            setCol(8);
            std::cout << " ────────────────────────────────────────────────────────────────\n";
            setCol(7);
            std::cout << " Reads the hardware license without modifying system licensing settings.\n\n";

            setCol(14);
            std::cout << " [*] Inspecting ACPI MSDM table...\n\n";
            std::string oemKey = GetOEMProductKey();

            if (oemKey.empty()) {
                setCol(12);
                std::cout << " [-] No OEM key present in firmware.\n\n";
            }
            else {
                setCol(10);
                std::cout << " [=] Motherboard Embedded Key: " << oemKey << "\n\n";
            }
            setCol(8);
            system("pause");
        }
        else if (opt == "3") {
            system("cls");
            setCol(11);
            std::cout << "\n [+] JKOX // MANUAL KEY ACTIVATION\n";
            setCol(8);
            std::cout << " ────────────────────────────────────────────────────────────────\n";
            setCol(7);
            std::cout << " Enter a 25-character Windows Retail, OEM, or Volume license key.\n"
                << " Dashes are optional and case does not matter.\n\n";

            setCol(14);
            std::cout << " > Enter product key: ";
            setCol(15);

            std::string userRawKey;
            std::getline(std::cin, userRawKey);

            std::string formattedKey = SanitizeKey(userRawKey);

            if (formattedKey.empty()) {
                setCol(12);
                std::cout << "\n [-] ERROR: Invalid key format. Expected 25 alphanumeric characters.\n\n";
            }
            else {
                setCol(10);
                std::cout << "\n [+] Key formatted: " << formattedKey << "\n\n";
                setCol(15);

                std::cout << " [*] Step 1/3: Installing product key (slmgr /ipk)...\n";
                std::string cmdIpk = "cscript //nologo %windir%\\system32\\slmgr.vbs /ipk " + formattedKey;
                system(cmdIpk.c_str());

                std::cout << "\n [*] Step 2/3: Authenticating with Microsoft servers (slmgr /ato)...\n";
                system("cscript //nologo %windir%\\system32\\slmgr.vbs /ato");

                std::cout << "\n [*] Step 3/3: Verifying expiration status...\n";
                setCol(8);
                std::cout << " ----------------------------------------------------------------\n";
                setCol(15);
                system("cscript //nologo %windir%\\system32\\slmgr.vbs /xpr");
                setCol(8);
                std::cout << " ----------------------------------------------------------------\n";

                setCol(10);
                std::cout << "\n [+] Procedure finished.\n";
            }
            setCol(8);
            system("pause");
        }
        else if (opt == "4") {
            system("cls");
            setCol(11);
            std::cout << "\n [+] JKOX // SYSTEM ACTIVATION STATUS\n";
            setCol(8);
            std::cout << " ────────────────────────────────────────────────────────────────\n\n";
            setCol(15);
            system("cscript //nologo %windir%\\system32\\slmgr.vbs /dli");
            std::cout << "\n";
            system("cscript //nologo %windir%\\system32\\slmgr.vbs /xpr");
            std::cout << "\n";
            setCol(8);
            system("pause");
        }
        else if (opt == "5") {
            break;
        }
    }

    return 0;
}