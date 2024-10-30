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
    case 57: actualNote = "A3"; break;
    case 58: actualNote = "A3s"; break;
    case 59: actualNote = "B3"; break;
    case 60: actualNote = "C4"; break;
    case 61: actualNote = "C4s"; break;
    case 62: actualNote = "D4"; break;
    case 63: actualNote = "D4s"; break;
    case 64: actualNote = "E4"; break;
    case 65: actualNote = "F4"; break;
    case 66: actualNote = "F4s"; break;
    case 67: actualNote = "G4"; break;
    case 68: actualNote = "G4s"; break;
    case 69: actualNote = "A4"; break;
    case 70: actualNote = "A4s"; break;
    case 71: actualNote = "B4"; break;
    case 72: actualNote = "C5"; break;
    case 73: actualNote = "C5s"; break;
    case 74: actualNote = "D5"; break;
    case 75: actualNote = "D5s"; break;
    case 76: actualNote = "E5"; break;
    case 77: actualNote = "F5"; break;
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
void GotoXY(int x, int y) {        //移动光标
    COORD pos;
    pos.X = x - 1;
    pos.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void HideCursor(void) {           //隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
const int middlePosition = 54;
const int topPosition = 6;

void SingleToneWithStandardNote() {
    system("cls");
    HMIDIOUT myMidi;
    midiOutOpen(&myMidi, 0, 0, 0, 0);
    int voice = 0x0;            // 声音参数
    int voiceType = 0x90;       // 音色，范围为0x90~0x9f,其中0x99为鼓，其余为钢琴
    int Volume = 0x42;          // 旋律音量
    int times = 1;
    int count = 0;
    GotoXY(middlePosition - 2, topPosition);
    cout << "单   音   听   辨" << endl;
    GotoXY(middlePosition - 10, topPosition + 2);
    cout << "请设置:每    个音符放一次标准音";
    GotoXY(middlePosition, topPosition + 2);
    scanf("%d", &times);
    GotoXY(middlePosition, topPosition + 4);
    cout << "●  准备好了";
    while (getch() != 32) {}
    do {
        system("cls");
        GotoXY(middlePosition - 2, topPosition);
        cout << "单   音   听   辨" << endl;
        GotoXY(middlePosition - 5, topPosition + 2);
        cout << "每 "<<times<<" 个音符放一次标准音";
        GotoXY(middlePosition, topPosition + 4);
        cout << "当前:" << count + 1;
        if (count == 0) {
            GotoXY(middlePosition, topPosition + 6);
            cout << "标 准 音 :";
            voice = (Volume << 16) + (69 << 8) + voiceType;
            midiOutShortMsg(myMidi, voice);
            PrintNote(69, 1);
            Sleep(2000);
        }
        srand((unsigned int)(time(NULL)));
        int currentNote = 57 + rand() % 20;
        string myNote = "";
        voice = (Volume << 16) + (currentNote << 8) + voiceType;
        midiOutShortMsg(myMidi, voice);
        GotoXY(middlePosition, topPosition + 8);
        cout << "当 前 音 :"; cin >> myNote;
        GotoXY(middlePosition, topPosition + 14);
        if (NoteCmp(myNote, currentNote))
            cout << " 正确！          ";
        else {
            cout << "错误！正确音:";
            PrintNote(currentNote, 1);
            voice = (Volume << 16) + (currentNote << 8) + voiceType;
            midiOutShortMsg(myMidi, voice);
            while (getch() != 32) { cout << "空格继续..."; }
        }
        count++; if (count == times) count = 0;
    } while (getch() != '9');
    midiOutClose(myMidi);
}

int SingleTone() {        //乐谱
    system("cls");
    GotoXY(middlePosition - 2, topPosition);
    cout << "单   音   听   辨" << endl;
    GotoXY(middlePosition, topPosition + 2);
    cout << "选 择 界 面";
    GotoXY(middlePosition, topPosition + 5);
    cout << "●  重复标准音";
    GotoXY(middlePosition, topPosition + 7);
    cout << "○  仅一次标准音";
    GotoXY(middlePosition, topPosition + 9);
    cout << "○  返回";
    HideCursor();
    char input;
    int i = 0;
    while (1) {
        input = getch();
        switch (input) {
        case 72://上
            GotoXY(middlePosition, i + topPosition + 5); cout << "○"; i -= 2; break;
        case 80://下
            GotoXY(middlePosition, i + topPosition + 5); cout << "○"; i += 2; break;
        case 32://空格
            switch (i/2+1)
            {
            case 1:SingleToneWithStandardNote(); return 1; break;
            default:return 0; break;
            }
            break;
        }
        if (i > 8) i = 0;
        if (i < -1) i = 8;
        GotoXY(middlePosition, i + topPosition + 5); cout << "●";
    }
}

int MainMenu() {
    system("cls");
    GotoXY(middlePosition - 12, topPosition);
    cout << "欢 迎 牛 总 进 行 今 天 的 视 唱 练 耳！" << endl;
    GotoXY(middlePosition, topPosition + 2);
    cout << "选 择 界 面";
    GotoXY(middlePosition, topPosition + 5);
    cout << "●  单音听辨";
    GotoXY(middlePosition, topPosition + 7);
    cout << "○  暂未开发";
    GotoXY(middlePosition, topPosition + 9);
    cout << "○  暂未开发";
    GotoXY(middlePosition, topPosition + 11);
    cout << "○  暂未开发";
    GotoXY(middlePosition, topPosition + 13);
    cout << "○  暂未开发";
    HideCursor();
    char input;                 
    int i = 0;                  
    while (1) {                  
        input = getch();
        switch (input) {
        case 72://上
            GotoXY(middlePosition, i + topPosition + 5); cout << "○"; i -= 2; break;
        case 80://下
            GotoXY(middlePosition, i + topPosition + 5); cout << "○"; i += 2; break;
        case 32://空格
            switch (i/2+1)
            {
            case 1:SingleTone(); return 1; break;
            default: return 0;
                break;
            }
            break;
        }
        if (i > 8) i = 0;
        if (i < -1) i = 8;
        GotoXY(middlePosition, i + topPosition + 5); cout << "●";
    }
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