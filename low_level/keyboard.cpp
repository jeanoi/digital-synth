#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

void choose_values(int (&info)[2]);

class Keyboard{
    private:
    int info_mem[2];
    int (&info)[2] = info_mem;
    int State;
    std::string Note;

    public:
    Keyboard(std::string note, int state):Note(note), State(state){}

    void set_state(){
            info[1] = State;
            if (Note == "q"){
                info[0] = 0;
            }
            else if(Note == "w"){
                info[0] = 1; // C#
            }
            else if(Note == "e"){
                info[0] = 2; // D
            }
            else if(Note == "r"){
                info[0] = 3; // D#
            }
            else if(Note == "f"){
                info[0] = 4; // E
            }
            else if(Note == "v"){
                info[0] = 5; // F
            }
            else if(Note == "b"){
                info[0] = 6; // F#
            }
            else if(Note == "h"){
                info[0] = 7; // G
            }
            else if(Note == "u"){
                info[0] = 8; // G#
            }
            else if(Note == "i"){
                info[0] = 9; // A
            }
            else if(Note == "o"){
                info[0] = 10; // A#
            }
            else if(Note == "p"){
                info[0] = 11; // B
            }
            else{
                info[0] = 77;
            }
    }
    int (&get_values())[2] {
        return info;
    }
};

int main ()
{
    Display* d = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(d);
    Window curFocus;
    char buf[17];
    KeySym ks;
    XComposeStatus comp;
    int len;
    int revert;
    XGetInputFocus (d, &curFocus, &revert);
    XAutoRepeatOff(d);
    XSelectInput(d, curFocus, KeyPressMask|KeyReleaseMask);

    // variáveis de controle pq o programa tava pulando pra KeyRelease quando devia ir pra KeyPress
    bool keyPressed = false;
    bool keyReleased = false;

    while (1)
    {
        XEvent ev;
        XNextEvent(d, &ev);
    
        switch (ev.type)
        {
            case KeyPress:

                len = XLookupString(&ev.xkey, buf, 16, &ks, &comp);

                if (len > 0 && isprint(buf[0]) )
                {
                    buf[len]=0;
                    Keyboard mykey(buf,1);
                    mykey.set_state();
                    keyPressed = true;
                    keyReleased = false;
                    choose_values(mykey.get_values());
                    while(XPending(d) == 0){
                    }

                }break;

            case KeyRelease:
            if (keyPressed && !keyReleased) {
            Keyboard mykey("0",0);
            mykey.set_state();
            choose_values(mykey.get_values());
            keyReleased = true;
            while(XPending(d) == 0){
                    }}break;
        }
        }
}

void choose_values(int (&info)[2]){
    int wtf = 1;

    if (info[1] == 1){
        switch (info[0])
        {
        case 0:
            std::cout << "C ligado" << std::endl;
            
            break;
        case 1:
            std::cout << "C# ligado" << std::endl;
            break;
        case 2:
            std::cout << "D ligado" << std::endl;
            break;
        case 3:
            std::cout << "D# ligado" << std::endl;
            break;
        case 4:
            std::cout << "E ligado" << std::endl;
            break;
        case 5:
            std::cout << "F ligado" << std::endl;
            break;
        case 6:
            std::cout << "F# ligado" << std::endl;
            break;
        case 7:
            std::cout << "G ligado" << std::endl;
            break;
        case 8:
            std::cout << "G# ligado" << std::endl;
            break;
        case 9:
            std::cout << "A ligado" << std::endl;
            break;
        case 10:
            std::cout << "A# ligado" << std::endl;
            break;
        case 11:
            std::cout << "B ligado" << std::endl;
            break;
        default:
            std::cout << "nada" << std::endl;
            break;
        }
    }
    else{
        std::cout << "Nada ligado" << std::endl;
    }
}