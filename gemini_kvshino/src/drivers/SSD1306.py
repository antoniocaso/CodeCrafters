##################################################################
##                  DRIVER FOR SSD1306 OLED I2C                 ##
##################################################################
#                                                                #
#                       credit to group 10                       #
#                                                                #
#                       @antonio_d'angelo                        #
#                      @federica_capobianco                      #
#                    @giuseppe_maria_dell'orto                   #
#                         @edoardo_bavaro                        #
#                                                                #
##################################################################

"""
    ============================================
     DRIVER DISPLAY OLED I2C IIC SSD1306 128X64
    ============================================

    > HOW TO USE
     -->copy SSD1306.py file in "resources" zerynth project folfer

     - from resources import SSD1306
     - display=SSD1306.SSD1306(60)
     
     - display._display_Print_string(string)
"""


###################################################################################################
#######                                                                                     #######
##                             >>> VALUE ASSIGNMENT OF REGISTERS <<<                             ##
#######                                                                                     #######
###################################################################################################

SSD1306_LCDWIDTH                    = 128 
SSD1306_LCDHEIGHT                   = 64 
SSD1306_SETCONTRAST                 = 0x81 
SSD1306_DISPLAYALLON_RESUME         = 0xA4 
SSD1306_DISPLAYALLON                = 0xA5 
SSD1306_NORMALDISPLAY               = 0xA6 
SSD1306_INVERTDISPLAY               = 0xA7 
SSD1306_DISPLAYOFF                  = 0xAE 
SSD1306_DISPLAYON                   = 0xAF 
SSD1306_SETDISPLAYOFFSET            = 0xD3 
SSD1306_SETCOMPINS                  = 0xDA 
SSD1306_SETVCOMDETECT               = 0xDB 
SSD1306_SETDISPLAYCLOCKDIV          = 0xD5 
SSD1306_SETPRECHARGE                = 0xD9 
SSD1306_SETMULTIPLEX                = 0xA8 
SSD1306_SETLOWCOLUMN                = 0x00 
SSD1306_SETHIGHCOLUMN               = 0x10 
SSD1306_SETSTARTLINE                = 0x40 
SSD1306_MEMORYMODE                  = 0x20 
SSD1306_COLUMNADDR                  = 0x21 
SSD1306_PAGEADDR                    = 0x22 
SSD1306_COMSCANINC                  = 0xC0 
SSD1306_COMSCANDEC                  = 0xC8 
SSD1306_SEGREMAP                    = 0xA0 
SSD1306_CHARGEPUMP                  = 0x8D 
SSD1306_EXTERNALVCC                 = 0x1 
SSD1306_SWITCHCAPVCC                = 0x2


###################################################################################################
#######                                                                                     #######
##                                  >>> DATABASE CHARACTERS <<<                                   ##
#######                                                                                     #######
###################################################################################################

CHARACTERS={
    #-> LETTERS
    'A':[0X7E,0X09,0X09,0X7E,0X00], 
    'B':[0X7F,0X49,0X49,0X36,0X00], 
    'C':[0X3E,0X41,0X41,0X22,0X00], 
    'D':[0X7F,0X41,0X41,0X3E,0X00], 
    'E':[0X7F,0X49,0X49,0X41,0X00], 
    'F':[0X7F,0X09,0X09,0X01,0X00], 
    'G':[0X3E,0X41,0X51,0X32,0X00], 
    'H':[0X7F,0X08,0X08,0X7F,0X00], 
    'I':[0X41,0X7F,0X41,0X00], 
    'J':[0X30,0X40,0X40,0X3F,0X00], 
    'K':[0X7F,0X08,0X14,0X63,0X00], 
    'L':[0X7F,0X40,0X40,0X40,0X00], 
    'M':[0X7F,0X02,0X04,0X02,0X7F,0X00], 
    'N':[0X7F,0X04,0X08,0X7F,0X00], 
    'O':[0X3E,0X41,0X41,0X3E,0X00], 
    'P':[0X7F,0X09,0X09,0X06,0X00], 
    'Q':[0X3E,0X41,0X21,0X5E,0X00], 
    'R':[0X7F,0X09,0X09,0X76,0X00], 
    'S':[0X26,0X49,0X49,0X32,0X00], 
    'T':[0X01,0X01,0X7F,0X01,0X01,0X00], 
    'U':[0X3F,0X40,0X40,0X3F,0X00], 
    'V':[0X1F,0X20,0X40,0X20,0X1F,0X00], 
    'W':[0X7F,0X20,0X18,0X20,0X7F,0X00], 
    'X':[0X77,0X08,0X08,0X77,0X00], 
    'Y':[0X2F,0X48,0X48,0X3F,0X00], 
    'Z':[0X71,0X49,0X49,0X47,0X00], 
    #-> NUMBERS
    '1':[0x42,0x7F,0x40,0x00], 
    '2':[0x62,0x51,0x49,0x46,0x00], 
    '3':[0x22,0x49,0x49,0x36,0x00], 
    '4':[0x0C,0x0A,0x09,0x7F,0x00], 
    '5':[0x47,0x45,0x45,0x39,0x00], 
    '6':[0x3C,0x4A,0x49,0x30,0x00], 
    '7':[0x01,0x71,0x09,0x07,0x00], 
    '8':[0x36,0x49,0x49,0x36,0x00], 
    '9':[0x06,0x49,0x29,0x1E,0x00], 
    '0':[0x3E,0x51,0x49,0x3E,0x00], 
    #-> PUNCTUATION
    '.':[0x40,0x00], 
    ',':[0x60,0x00], 
    ';':[0x64,0x00], 
    ':':[0x44,0x00], 
    '*':[0x05,0x02,0x05,0x00], 
    '+':[0x08,0x08,0x3E,0x08,0x08,0x00], 
    '-':[0x08,0x08,0x08,0x08,0x08,0x00], 
    '?':[0x02,0x51,0x09,0x06,0x00], 
    '!':[0x5F,0x00], 
    '&':[0x54,0x23,0x55,0x29,0x36,0x00], 
    '(':[0X1C,0x22,0x41,0x00], 
    ')':[0x41,0x22,0x1C,0X00], 
    '[':[0X7F,0x41,0x41,0x00], 
    ']':[0x41,0x41,0x7F,0X00], 
    '{':[0X08,0x77,0x41,0x41,0x00], 
    '}':[0x41,0x41,0x77,0x08,0X00], 
    ' ':[0X00,0x00],
    '=':[0X14,0X14,0X14,0X00],
    '>':[0x41,0x22,0x14,0x08,0x00],
    '<':[0x08,0x14,0x22,0x41,0x00],
    'à':[0x04,0x02,0x09,0x25,0x95,0x25,0x09,0x02,0x04,0x00], #wifi acceso
    'ò':[0x00,0x00,0x00,0x00,0xBF,0x00,0x00,0x00,0x00,0x00]  #wifi spento
    }

#DEFINITION OF GLOBAL VARIABLES BY COUNTING SPACES

cont=0
spaziodisponibile=128

import i2c

"""
import serial
serial.serial()
i2c_scan_buf = i2c.scan()

for addr in i2c_scan_buf:
    print("addr", addr, "present")

"""


class SSD1306(i2c.I2c):
    
    #Initialization of registers and configuration
    def __init__(self, addr=0x3C,drvname=I2C0, clock=1000000):
        i2c.I2c.__init__(self, addr, drvname, clock)
        #print("init")
        self._display_Setup()
        self._display_Clean()

    def _display_Off(self):
        """I turn off the display"""
        self.write(bytearray([0x00,SSD1306_DISPLAYOFF]))  

    def _display_On(self):  
        """I turn on the display"""
        self.write(bytearray([0x00,SSD1306_DISPLAYON]))               
    
    def _display_Setup(self):
        """I initialize all the registers and set them properly"""
        self._display_Off()

        self.write(bytearray([0x00,SSD1306_SETDISPLAYCLOCKDIV]))          
        self.write(bytearray([0x00,0x80]))             
            
        self.write(bytearray([0x00,SSD1306_SETMULTIPLEX]))               
        self.write(bytearray([0x00,0x3F]))
            
        self.write(bytearray([0x00,SSD1306_SETDISPLAYOFFSET]))           
        self.write(bytearray([0x00,0x0]))                              
            
        self.write(bytearray([0x00,SSD1306_SETSTARTLINE]))
            
        self.write(bytearray([0x00,SSD1306_CHARGEPUMP]))                  
        self.write(bytearray([0x00,0x14]))

        self.write(bytearray([0x00,SSD1306_MEMORYMODE]))                 
        self.write(bytearray([0x00,0x00]))        
            
        self.write(bytearray([0x00,SSD1306_SEGREMAP]))
        self.write(bytearray([0x00,SSD1306_COMSCANDEC]))
            
        self.write(bytearray([0x00,SSD1306_SETCOMPINS]))                 
        self.write(bytearray([0x00,0x12]))
            
        self.write(bytearray([0x00,SSD1306_SETCONTRAST]))                 
        self.write(bytearray([0x00,0xCF]))
            
        self.write(bytearray([0x00,SSD1306_SETPRECHARGE]))                
        self.write(bytearray([0x00,0xF1]))
            
        self.write(bytearray([0x00,SSD1306_SETVCOMDETECT]))               
        self.write(bytearray([0x00,0x40]))

        self.write(bytearray([0x00,SSD1306_DISPLAYALLON_RESUME]))         
            
        self.write(bytearray([0x00,SSD1306_NORMALDISPLAY]))        
        self.write(bytearray([0x00,0XC0]))  #REVERSE   

                        

        self._display_On()

        self.write(bytearray([0x00,SSD1306_COLUMNADDR]))           
        self.write(bytearray([0x00,0]))      
        self.write(bytearray([0x00,127]))    

        self.write(bytearray([0x00,SSD1306_PAGEADDR]))           
        self.write(bytearray([0x00,0]))      
        self.write(bytearray([0x00,7]))    


    def _display_Clean(self):
        """I erase everything on the display"""
        for i in range(1024):
            self.write(bytearray([0x40,0]))


    #_display_Setup()
    #_display_Clean()




    ###################################################################################################
    #######                                                                                     #######
    ##                               >>> DEFINITION OF FUNCTIONS <<<                                 ##
    #######                                                                                     #######
    ###################################################################################################

    # LOW-LEVEL FUNCTIONS

    def _display_get_character(self, character):
        """Getter function that searches the dictionary and returns the list with 8bit arrays """
        return CHARACTERS.get(character.upper(),[0X00,0x00])


    def _display_Print(self, arrayPixel):
        """Function Prints an 8bit vertical array"""
        self.write(bytearray([0x40,arrayPixel]))


    def _display_conta_character(self,car):
        """I count the spaces horizontally that the CHARACTERS occupy
             takes as input a character (key)"""
        character=self._display_get_character(car)
        lenght=len(character)
        return lenght

    # MID-LEVEL FUNCTIONS

    def _display_Print_character(self,c):
        """Function that prints CHARACTERS"""
        character=self._display_get_character(c)
        global cont
        cont=cont+self._display_conta_character(c)
        for y in range(0,len(character)):
            self._display_Print(character[y])
            

    # ->GO TO HEAD
    def _display_go_to_head(self, free_space):
        """If the character exceeds the display resolution, I wrap"""
        for i in range(free_space):
            self._display_Print(0x00) 


    # HIGH-LEVEL FUNCTIONS

    # ->PRINT string
    def _display_Print_string(self, stringA):
        """I print the string on the display"""
        global cont
        global spaziodisponibile
        cont=0
        spaziodisponibile=128
        
        for character in stringA:
            if(spaziodisponibile>self._display_conta_character(character)):
                self._display_Print_character(character)
            else:
                self._display_go_to_head(spaziodisponibile)
                cont=0
                spaziodisponibile=128
                self._display_Print_character(character)
            spaziodisponibile=128-cont
        self._display_go_to_head(spaziodisponibile)

    # ->PRINT BITMAP
    def _display_Print_Bitmap(self, bitmap):
        """This function takes an input list as a parameter and prints its entire content"""
        self.control_bitmap_size(bitmap)
        for i in range(0,1024):
            self._display_Print(bitmap[i])
        

    # ->MERGE 2 BITMAP
    def _display_Merge_Bitmap(self, bitmap1, bitmap2):
        """Function takes 2 bitmap lists as input and merges them into a single bitmap list"""
        self.control_bitmap_size(bitmap1)
        self.control_bitmap_size(bitmap2)
        bitmap_final=[]
        for i in range(0,1024):
            val=bitmap1[i] | bitmap2[i]
            bitmap_final.append(val)
        return bitmap_final
        

    def _display_add_Row_Bitmap(self, n):
        """Add a row in a bitmap list"""
        bitmap=[]
        for x in range(0,n):
            for y in range(0,128):
                bitmap.append(0x00)
        return bitmap

    # ->CONVERTER string TO BITMAP LIST
    def _display_String_to_Bitmap(self, stringA, row, orientation=0, mode=0):
        """Function converts string of CHARACTERS returning a bitmap list
            ->row= 0,1,2,3,4,5,6,7
            ->orientation= 0(Sx), 1(Central), 2(Dx)
            ->mode =0 return 128 x 64, =1 return 128x16
        """
        bitmap=[] #this is the single string
        bitmapFinal=[] #128x64 bitmap list whith string or 128x16
        if(mode==0):
            #add a row
            if((row>0) and (row<8)):
                bitmapFinal=self._display_add_Row_Bitmap(row)
        else:
            if((row>0)and(row<3)):
                bitmapFinal=self._display_add_Row_Bitmap(row)

        
        #add a string in bitmap list
        for character in stringA:
            car=self._display_get_character(character)
            #print("car: ",car)
            lenghtCar=len(car)
            #print("lenghtCar: ",lenghtCar)
            if(lenghtCar>1):
                for x in range(0,lenghtCar):
                    bitmap.append(car[x])

        lenghtBitmap=len(bitmap)
        
        #control the orientation of the string
        if(orientation==1):
            if(lenghtBitmap<=128):    
                for i in range(0, 64-int(lenghtBitmap/2)):
                    bitmapFinal.append(0x00)
                for x in range(0,lenghtBitmap):
                    bitmapFinal.append(bitmap[x])
                    
        
        elif(orientation==2):
            if(lenghtBitmap<=128):
                for i in range(0,128-lenghtBitmap):
                    bitmapFinal.append(0x00)
                for x in range(0,lenghtBitmap):
                        bitmapFinal.append(bitmap[x])
        
        else: #orientation=0
            for x in range(lenghtBitmap):
                bitmapFinal.append(bitmap[x])
        
        lenghtBitmapFinal=len(bitmapFinal)

        if(lenghtBitmapFinal<1024):
            for y in range(lenghtBitmap,1024):
                bitmapFinal.append(0x00)

        return bitmapFinal


    def control_bitmap_size(self,bitmap,mode=0):
        """RETURN LIST>Control the lenght of the bitmap list, if is <1024(mode=0) or <768(mode=1) or <256(mode=2), append the list with 0x00"""
        lenght=len(bitmap)
        
        if(mode==0):
            if(lenght<1024):
                for y in range(lenght,1024):
                    bitmap.append(0x00)
        if(mode==1):
            if(lenght<768):
                
                for y in range(lenght,768):
                    bitmap.append(0x00)
        if(mode==2):
            if(lenght<256):
                for y in range(lenght,256):
                    bitmap.append(0x00)
        #print(bitmap)
        return bitmap


    def _display_Merge_6x2_Row_Bitmap(self, bitmap1, bitmap2):
        """Return a bitmap list with the first 6 row is for the list Bitmap1, and the last 2 row is from the list bitmap2"""
        bitmap_final=[]
        self.control_bitmap_size(bitmap1,1)
        self.control_bitmap_size(bitmap2,2)
        for i in range(0,768):
            bitmap_final.append(bitmap1[i])
        for i in range(0,256):
            bitmap_final.append(bitmap2[i])
        return bitmap_final



        
