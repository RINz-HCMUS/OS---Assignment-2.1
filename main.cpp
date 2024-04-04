#include <windows.h>
#include <iostream>
#include <sstream>

using namespace std;
void createPipe(){
    cout << "Tien trinh 1: Tao pipe\n";
     // Tạo pipe
    HANDLE hReadPipe, hWritePipe;
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        cout << "CreatePipe failed with error code: " << GetLastError() << endl;
        return;
    }
    cout << "Dang tao Tien trinh 2\n";

    // Tạo tiến trình 2
    STARTUPINFOA si;  
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    // Chuyển đổi handle pipe thành chuỗi
    stringstream ss;
    ss << hReadPipe;
    string pipeHandle = ss.str();

    // Tạo một command line để truyền pipe handle cho tiến trình 2
    string commandLine = "ChildProcess.exe " + pipeHandle;

    // Tạo tiến trình 2
    if (!CreateProcessA(NULL, const_cast<char*>(commandLine.c_str()), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        cout << "CreateProcess failed with error code: " << GetLastError() << endl;
        return;
    }

    Sleep(1000);
    
    cout << "Tien trinh 1: nhan gia tri tu nguoi dung:\n";
        int number;
        cout << "Enter a number: ";
        cin >> number;
        
    cout << "Tien trinh 1: Nhan gia tri thanh cong!\n";
    Sleep(200);

    cout << "Tien trinh 1: tao pipe va gui gia tri vua nhan...\n";
    Sleep(200);

    // Gửi số nhập từ người dùng tới tiến trình 2
    DWORD dwBytesWritten;
    WriteFile(hWritePipe, &number, sizeof(number), &dwBytesWritten, NULL);
    CloseHandle(hWritePipe);

    // Đợi tiến trình 2 kết thúc
    WaitForSingleObject(pi.hProcess, INFINITE);
    Sleep(1000);

    // Đóng handle của pipe và tiến trình 2
    CloseHandle(hReadPipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


int main() {
    cout << "Chuong trinh kiem tra so chan va so le\n";
    cout << "------------------------------------------\n";
    cout << "Tien trinh 1: Da san sang!\n";

    while(true){
        createPipe();

        cout << "Tien trinh 1: Tiep tuc? (1: Co / 0: Khong)\n";
        cout << "Nhap lua chon: ";
        int i; cin >> i;
        if(i == 0)
            break;;
    }

    cout << "Tien trinh 1: Ket thuc chuong trinh!\n";

    system("pause");
    return 0;
}
