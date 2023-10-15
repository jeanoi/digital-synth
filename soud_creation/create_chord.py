import numpy as np
from scipy import signal

class ChordGenerator:

    def __init__(self, key = float, samplerate = int, wave_type = str, duration = int, chord_type = str):
        self.key = key
        self.samplerate = samplerate
        self.wave_type = wave_type
        self.duration = duration
        self.chord_type = chord_type

    def create_chord(self):
        #Samplerate e frequência

        if(self.chord_type == "major"):
            root = self.key
            third = 1.2599*root
            fifth = 1.4983*root
        elif(self.chord_type == "minor"):
            root = self.key
            third = 1.189207*root
            fifth = 1.4983*root


        #Geração dos valores no tempo
        time_values = np.linspace(0., self.duration, self.samplerate*self.duration)
        amplitude = (np.iinfo(np.int16).max)

        #Criação dos acordes
        if(self.wave_type == "square"):
            wave1 = signal.square(2. * np.pi * root * time_values)
            wave2 = signal.square(2. * np.pi * third * time_values)
            wave3 = signal.square(2. * np.pi * fifth * time_values)

        elif(self.wave_type == "triangle"):
            wave1 = signal.sawtooth(2. * np.pi * root * time_values, 0.5)
            wave2 = signal.sawtooth(2. * np.pi * third * time_values, 0.5)
            wave3 = signal.sawtooth(2. * np.pi * fifth * time_values, 0.5)

        elif(self.wave_type == "sawtooth"):
            wave1 = signal.sawtooth(2. * np.pi * root * time_values)
            wave2 = signal.sawtooth(2. * np.pi * third * time_values)
            wave3 = signal.sawtooth(2. * np.pi * fifth * time_values)
        
        elif(self.wave_type == "sine"):
            wave1 = np.sin(2. * np.pi * root * time_values)
            wave2 = np.sin(2. * np.pi * third * time_values)
            wave3 = np.sin(2. * np.pi * fifth * time_values)

        #Concatena as ondas
        chord = amplitude * (wave1+wave2+wave3)

        #Normaliza o acorde para a amplitude máxima de 16 bits do arquivo wav
        max_amplitude = np.max(np.abs(chord))
        if max_amplitude > amplitude:
            chord = chord * amplitude / max_amplitude
        
        return chord