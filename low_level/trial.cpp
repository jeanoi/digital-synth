#include <pulse/simple.h>
#include <pulse/error.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

int main() {

    // pa_sample_spec é uma struct, aqui passamos os valores da struct através de sample_spec
    pa_sample_spec sample_spec;
    sample_spec.format = PA_SAMPLE_S16LE;  // 16 bits little endian
    sample_spec.rate = 44100;              // Sample rate Hz
    sample_spec.channels = 2;             // Número dos canais de áudio

    // pa_simple também é uma struct, aqui passamos os valores que retornam de pa_simple_new 
    //para pa_Connection
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
        cerr << "Conexão com Pulse Audio não funcionou" << endl;
        return 1;
    }

    // Buffer para o audio de data, 1024 é um valor médio entre baixa latência e rápido processamento
    const int audioBufferSize = 1024;
    int16_t audioBuffer[audioBufferSize];

    while (true) {
        // Geração de white noise
        for (int i = 0; i < audioBufferSize; i++) {
            // Cria um valor aleatório na range da type short e joga o resultado em audioBuffer
            audioBuffer[i] = static_cast<int16_t>(rand() % (2 * SHRT_MAX) - SHRT_MAX);
        }


        //int pa_simple_write	(	pa_simple * 	s,
        //const void * 	data,
        //size_t 	bytes,
        //int * 	error 
        //)	
        int error;
        // pa_simple_write escreve os valores de audioBuffer na stream aberta
        // por paConnection e retorna um valor menor do que 0 se algum erro ocorreu 
        if (pa_simple_write(paConnection, audioBuffer, sizeof(audioBuffer), &error) < 0) {
            cerr << "pa_simple_write error: " << pa_strerror(error) << endl;
            break;
        }
    }

    // pa_simple_drain garante que o hardware reproduziu todas as informações enviadas
    // antes de enviar mais, e retorna um valor menor do que 0 se algum erro ocorreu 
    int error;
    if (pa_simple_drain(paConnection, &error) < 0) {
        cerr << "pa_simple_drain error: " << pa_strerror(error) << endl;
    }


    //pa_simple_free dá uma limpada na sujeira que o programa deixa no hardware/Kernel
    pa_simple_free(paConnection);

    return 0;
}