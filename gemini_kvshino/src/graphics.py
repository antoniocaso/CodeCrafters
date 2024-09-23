import fs
 
def from_string_to_int(string):
    return int(string,16)

def bpm(n=3):
    """n=1,2 : Heart graphic animation
       n=3 : Results page"""

    bpm=[]
    directory="/zerynth/bpm "+str(n)+".txt"
    fd=fs.open(directory, 'r')
    for i in range(0,1024):
        line=fd.readline()
        bpm.append(from_string_to_int(line))
    fd.close()
    return bpm

def braccialetto2(n=5):
    """n=1,2,3,4 : Heart's graphic animation
       n=5 : Results page"""
    
    braccialetto2=[]
    directory="/zerynth/braccialetto2 "+str(n)+".txt"
    fd=fs.open(directory, 'r')
    for i in range(0,1024):
        line=fd.readline()
        braccialetto2.append(from_string_to_int(line))
    fd.close()
    return braccialetto2

def gemini(n=5):
    """n=1,2,3,4,5 : Startup graphic animation"""
    
    gemini=[]
    directory="/zerynth/gemini "+str(n)+".txt"
    fd=fs.open(directory, 'r')
    for i in range(0,1024):
        line=fd.readline()
        gemini.append(from_string_to_int(line))
    fd.close()
    return gemini

def menu(n=1):
    """n=1 : Principal menu function
       n=2 : Trillo menu selected
       n=3 : BPM menu selected
       n=4 : Braccialetto2 menu selected"""
    
    menu=[]
    directory="/zerynth/menu "+str(n)+".txt"
    fd=fs.open(directory, 'r')
    for i in range(0,1024):
        line=fd.readline()
        menu.append(from_string_to_int(line))
    fd.close()
    return menu

def trillo(n=1):
    """n=1,2 : Trillo animation"""
    
    trillo=[]
    directory="/zerynth/trillo "+str(n)+".txt"
    fd=fs.open(directory, 'r')
    for i in range(0,1024):
        line=fd.readline()
        trillo.append(from_string_to_int(line))
    fd.close()
    return trillo
