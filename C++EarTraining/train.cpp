#include <iostream>
#include <cstring>
#include <Windows.h>
#include <conio.h>
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)
using namespace std;

enum Scale {
    C8 = 108, B7 = 107, A7s = 106, A7 = 105, G7s = 104, G7 = 103, F7s = 102, F7 = 101, E7 = 100,
    D7s = 99, D7 = 98, C7s = 97, C7 = 96, B6 = 95, A6s = 94, A6 = 93, G6s = 92, G6 = 91, F6s = 90, F6 = 89,
    E6 = 88, D6s = 87, D6 = 86, C6s = 85, C6 = 84, B5 = 83, A5s = 82, A5 = 81, G5s = 80, G5 = 79, F5s = 78,
    F5 = 77, E5 = 76, D5s = 75, D5 = 74, C5s = 73, C5 = 72, B4 = 71, A4s = 70, A4 = 69, G4s = 68, G4 = 67,
    F4s = 66, F4 = 65, E4 = 64, D4s = 63, D4 = 62, C4s = 61, C4 = 60, B3 = 59, A3s = 58, A3 = 57, G3s = 56,
    G3 = 55, F3s = 54, F3 = 53, E3 = 52, D3s = 51, D3 = 50, C3s = 49, C3 = 48, B2 = 47, A2s = 46, A2 = 45,
    G2s = 44, G2 = 43, F2s = 42, F2 = 41, E2 = 40, D2s = 39, D2 = 38, C2s = 37, C2 = 36, B1 = 35, A1s = 34,
    A1 = 33, G1s = 32, G1 = 31, F1s = 30, F1 = 29, E1 = 28, D1s = 27, D1 = 26, C1s = 25, C1 = 24, B0 = 23,
    A0s = 22, A0 = 21, _ = 0xFF, rest = 0xFF,
};

string PrintNote(int note, int flag) {
    string actualNote;
    switch (note) {
    case 45: actualNote = "A2"; break;
    case 46: actualNote = "A2s"; break;
    case 47: actualNote = "B2"; break;
    case 48: actualNote = "C3"; break;
    case 49: actualNote = "C3s"; break;
    case 50: actualNote = "D3"; break;
    case 51: actualNote = "D3s"; break;
    case 52: actualNote = "E3"; break;
    case 53: actualNote = "F3"; break;
    case 54: actualNote = "F3s"; break;
    case 55: actualNote = "G3"; break;
    case 56: actualNote = "G3s"; break;
    case 57: actualNote = "A3"; break;
    case 58: actualNote = "A3s"; break;
    case 59: actualNote = "B3"; break;
    case 60: actualNote = "C4"; break;
    case 61: actualNote = "C4s"; break;
    case 62: actualNote = "D4"; break;
    case 63: actualNote = "D4s"; break;
    case 64: actualNote = "E4"; break;
    case 65: actualNote = "F4"; break;
    default: break;
    }
    if (flag)
        cout << actualNote;
    return actualNote;
}
bool NoteCmp(string sn, int n) {
    if (sn == PrintNote(n, 0)) return true;
    else return false;
}
void GotoXY(int x, int y) {        //�ƶ����
    COORD pos;
    pos.X = x - 1;
    pos.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void HideCursor(void) {           //���ع��
    CONSOLE_CURSOR_INFO cursorInfo = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
const int middlePosition = 54;
const int topPosition = 6;
int MainMenu() {
    GotoXY(middlePosition - 12, topPosition);
    cout << "�� ӭ ţ �� �� �� �� �� �� �� �� �� ����" << endl;
    GotoXY(middlePosition, topPosition + 2);
    cout << "ѡ �� �� ��";
    GotoXY(middlePosition, topPosition + 5);
    cout << "��  ��������";
    GotoXY(middlePosition, topPosition + 7);
    cout << "��  ��δ����";
    GotoXY(middlePosition, topPosition + 9);
    cout << "��  ��δ����";
    GotoXY(middlePosition, topPosition + 11);
    cout << "��  ��δ����";
    GotoXY(middlePosition, topPosition + 13);
    cout << "��  ��δ����";
    HideCursor();
    char input;                 //��������
    int i = 0;                  //������
    while (1) {                  //��¼/ע��ѡ��
        input = getch();
        switch (input) {
        case 72://��
            GotoXY(middlePosition, i + topPosition + 5); cout << "��"; i -= 2; break;
        case 80://��
            GotoXY(middlePosition, i + topPosition + 5); cout << "��"; i += 2; break;
        case 32://�ո�
            return i / 2 + 1;
            break;
        }
        if (i > 8) i = 0;
        if (i < -1) i = 8;
        GotoXY(middlePosition, i + topPosition + 5); cout << "��";
    }
}

void SingleTone() {        //����
    system("cls");
    HMIDIOUT myMidi;
    midiOutOpen(&myMidi, 0, 0, 0, 0);
    int voice = 0x0;            // ��������
    int voiceType = 0x90;       // ��ɫ����ΧΪ0x90~0x9f,����0x99Ϊ�ģ�����Ϊ����
    int Volume = 0x42;          // ��������
    GotoXY(middlePosition - 2, topPosition);
    cout << "��   ��   ��   ��" << endl;
    GotoXY(middlePosition, topPosition + 2);
    cout << "��  ׼������";
    while (getch() != 32) {}
    do {
        system("cls");
        GotoXY(middlePosition, topPosition + 4);
        cout << "�� ׼ �� :";
        voice = (Volume << 16) + (57 << 8) + voiceType;
        midiOutShortMsg(myMidi, voice);
        cout << "A3";
        Sleep(3000);
        GotoXY(middlePosition, topPosition + 6);
        srand((unsigned int)(time(NULL)));
        int currentNote = 45 + rand() % 20;
        string myNote = "";
        voice = (Volume << 16) + (currentNote << 8) + voiceType;
        midiOutShortMsg(myMidi, voice);
        cout << "�� ǰ ��:";
        cin >> myNote;
        GotoXY(middlePosition, topPosition + 14);
        if (NoteCmp(myNote, currentNote))
            cout << " ��ȷ�� ";
        else {
            cout << "������ȷ��:";
            PrintNote(currentNote, 1);
            voice = (Volume << 16) + (currentNote << 8) + voiceType;
            midiOutShortMsg(myMidi, voice);
            Sleep(3000);
        }
    } while (getch() != 9);
    midiOutClose(myMidi);
}

int main() {
    int mode = 0;
    mode = MainMenu();
    switch (mode) {
    case 1: SingleTone(); break;
    default: break;
    }
    return 0;
}