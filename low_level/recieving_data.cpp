#include <pulse/simple.h>
#include <pulse/error.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cmath>
#include <ncurses.h>

using namespace std;

// Function to generate a sine wave of a specified frequency and amplitude
void generateSineWave(int16_t* buffer, int bufferSize, double frequency, int16_t amplitude) {
    double phase = 0.0;
    double phaseIncrement = 2 * M_PI * frequency / 44100; // Adjust for your sample rate

    for (int i = 0; i < bufferSize; i++) {
        buffer[i] = static_cast<int16_t>(amplitude * sin(phase));
        phase += phaseIncrement;

        if (phase >= 2 * M_PI) {
            phase -= 2 * M_PI;
        }
    }
}

int main() {
    // Initialize ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    // PulseAudio setup
    pa_sample_spec sample_spec;
    sample_spec.format = PA_SAMPLE_S16LE;
    sample_spec.rate = 44100;
    sample_spec.channels = 2;
    
    pa_simple* paConnection = pa_simple_new(
        NULL,                   // Nome do servidor, NULL como default
        "FAZ BARULHO AE",       // Nome do cliente
        PA_STREAM_PLAYBACK,     // Direção da stream, playback, record, upload
        NULL,                   // Sink name (or NULL for the default sink)
        "SHMOKING WEED DOING COKE DRINKING BEARS",       // Stream description
        &sample_spec,           // Referência ao local de memória de sample_spec
        NULL,                   // Mapa dos canais
        NULL,                   // Atributos do Buffer
        NULL                    // Log de erros
    );

    if (!paConnection) {
        cerr << "PulseAudio connection failed" << endl;
        return 1;
    }

    const int audioBufferSize = 1024;
    int16_t audioBuffer[audioBufferSize];

    int ch;
    const int button = 'a';
    const int button2 = 'b';
    const int button3 = 'x';
    int aux = 1;

    while (aux == 1) {
        ch = getch();

        switch (ch) {
            case button:
                generateSineWave(audioBuffer, audioBufferSize, 750.0, SHRT_MAX);
                break;

            case button2:
                generateSineWave(audioBuffer, audioBufferSize, 500.0, SHRT_MAX);
                break;

            case button3:
                aux = 0;
                break;
        }

        // Play audio with pa_simple_write
        int error;
        if (pa_simple_write(paConnection, audioBuffer, sizeof(audioBuffer), &error) < 0) {
            cerr << "pa_simple_write error: " << pa_strerror(error) << endl;
            break;
        }
    }

    // Cleanup and exit
    endwin();
    pa_simple_drain(paConnection, NULL);
    pa_simple_free(paConnection);

    return 0;
}