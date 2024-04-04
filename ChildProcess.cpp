#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 2) {
        cout << "Usage: ChildProcess.exe pipeHandle" << endl;
        return 1;
    }

    cout << "Tien trinh 2: Da san sang!\n";

    // Chuyển đổi chuỗi thành handle pipe
    stringstream ss(argv[1]);
    HANDLE hReadPipe;
    ss >> hReadPipe;

    cout << "Tien trinh 2: Da nhan duoc du lieu\n";
    cout << "Tien trinh 2: Bat dau xu ly du lieu...\n";
 
    // Đọc số từ pipe
    int number;
    DWORD dwBytesRead;
    if (!ReadFile(hReadPipe, &number, sizeof(number), &dwBytesRead, NULL)) {
        cout << "ReadFile failed with error code: " << GetLastError() << endl;
        return 1;
    }
    cout << "Tien trinh 2: ";
    // Kiểm tra xem số đó có phải là số chẵn hay lẻ và in kết quả ra màn hình
    if(number < 0){
        cout << number << " is an unvalid number." << endl;
    } 
    else if(number % 2 == 0) {
        cout << number << " is an even number." << endl;
    } else {
        cout << number << " is an odd number." << endl;
    }   

    cout << "Tien trinh 2: Da hoan thanh! Tu dong ket thuc tien trinh 2...\n";

    // Đóng handle của pipe
    CloseHandle(hReadPipe);

    return 0;
}
