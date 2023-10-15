from soud_creation.create_chord import ChordGenerator
from scipy.io.wavfile import write
import numpy as np

def generate_chord(key, samplerate, wave_type, duration, chord_type):

    ############################### Informações ###############################
    #Frequência da nota central do acorde:
    #key = 293.66
    #Taxa de amostragem
    #samplerate = 44000
    #Tipo da onda = sine, sawtooth, square, triangle
    #wave_type = "triangle"
    #Duração em segundos
    #duration = 3
    #Tipo do acorde = minor, major
    #chord_type = "minor"

    #Gera o acorde
    x = ChordGenerator(key=key, samplerate=samplerate, wave_type = wave_type, duration = duration, chord_type = chord_type).create_chord()
    return x

def write_to_wav(key, wave_type, duration, chord_type):

    # Chama a função para gerar o acorde
    samplerate = 44000
    x = generate_chord(key = key, samplerate = samplerate, wave_type = wave_type, duration = duration, chord_type = chord_type)
    # Escreve o acorde gerado no warquivo wav
    wav_path = "/home/jean/Desktop/Ferias/vacation/scripts/starting.wav"
    write(wav_path, samplerate, x.astype(np.int16))

write_to_wav(key = 293, wave_type = "square", duration = 3, chord_type = "minor")