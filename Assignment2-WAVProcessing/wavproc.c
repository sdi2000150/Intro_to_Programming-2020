/* File: wavproc.c */
#include <stdio.h>
#include <math.h>
#define MODE 1

/* Comments are in Greeklish */
/* Ekana ta MODES: 1, 2, 3, 4, 5, 6, 7*/

/* Synarthsh pou pernei san orisma enan akeraio 4rwn bytes kai ton dinei stin eksodo san LittleEndian */
void put4bytes(int num) {
    int ch1, ch2, ch3, ch4;
    ch4 = num % 256;                                                                                                  /* Pare to 4o byte tou arithmou */
    ch3 = (num / 256) % 256;                                                                                          /* Pare to 3o byte tou arithmou */
    ch2 = ((num / 256) / 256) % 256;                                                                                  /* Pare to 2o byte tou arithmou */
    ch1 = (((num / 256) / 256) / 256) % 256;                                                                          /* Pare to 1o byte tou arithmou */
    putchar(ch4);                                                                                                 /* Ektypwse to 4o byte tou arithmou */
    putchar(ch3);                                                                                                 /* Ektypwse to 3o byte tou arithmou */
    putchar(ch2);                                                                                                 /* Ektypwse to 2o byte tou arithmou */
    putchar(ch1);                                                                                                 /* Ektypwse to 1o byte tou arithmou */
}

/* Synarthsh pou pernei san orisma enan akeraio 2 bytes kai ton dinei stin eksodo san LittleEndian */
void put2bytes(int num) {
    int ch1, ch2;
    ch2 = num % 256;                                                                                                  /* Pare to 2o byte tou arithmou */
    ch1 = (num / 256) % 256;                                                                                          /* Pare to 1o byte tou arithmou */
    putchar(ch2);                                                                                                 /* Ektypwse to 2o byte tou arithmou */
    putchar(ch1);                                                                                                 /* Ektypwse to 1o byte tou arithmou */
}

/* Synarthsh pou pernei 4 xarakthres kai tous dinei stin eksodo enan-enan */
void put4char(int ch1, int ch2, int ch3, int ch4) {
    putchar(ch1);
    putchar(ch2);
    putchar(ch3);
    putchar(ch4);
}

/* Synarthsh tou MODE 7 */
void mysound(int dur, int sr, double fm, double fc, double mi, double mv) {
    int f, stigmes, i;
    double t;
    stigmes = dur * sr;                                         /* xronikes stigmes=duration×SampleRate (diladi SizeOfData/2 efoson BitsPerSample=16) */
    for (i = 0 ; i < stigmes ; i++) {                                                                             /* Epanalabe gia SizeOfData/2 fores */
        t = i / (double)sr;                                                                              /* Xronos=dedomenh xronikh stigmh/SampleRate */
        f = mv * sin(2 * M_PI * fc * t - mi * sin(2 * M_PI * fm * t));  /*Dhmiourgia tou dedomenou hxou(twn 2 bytes)me bash auton ton mathimatiko typo*/
        putchar(f % 256);                                                                      /* Ektypwse to 2o byte tou f(diladi kata LittleEndian) */
        putchar(f >> 8);                                                                       /* Ektypwse to 1o byte tou f(diladi kata LittleEndian) */
        /* (xrhsimopoiw >> 8 gia to 1o byte anti gia /256%256 wste na metaferthoun swsta kai oi arnhtikoi) */
    }
}

int main(void) {
    int n, i, SizeOfFile, format, Wtypef, MonoStereo, SampleRate, BytesPerSec, BlockAlign,                               /* Metablhtes olwn twn MODES */
        ginomeno, BitsPerSample, ginomeno2, SizeOfData, SODbytes, SizeOfExtra;                                           /* Metablhtes olwn twn MODES */
    int SampleRate2, BytesPerSec2, SizeOfFile2, MonoStereo2, BlockAlign2, SizeOfData2, z, z2, dur = 3; /* Metablhtes twn allwn MODES ektos tou MODE 1 */
    double fm = 2.0, fc = 1500.0, mi = 100.0, mv = 30000.0;                                                                  /* Metablhtes tou MODE 7 */
    short tempdata6;                                                                                                          /* Metablhth tou MODE 6 */
    if (MODE != 7) {                                                                                  /* An to MODE einai ena apo ta 1, 2, 3, 4, 5, 6 */
        SizeOfData = 0;
        SODbytes = 0;
        SizeOfExtra = 0;
        z = 45;                                                                                                     /* Tha xrhsimopoihthei sto MODE 4 */
        z2 = 47;                                                                                                    /* Tha xrhsimopoihthei sto MODE 5 */
        i = 1;                                                                                       /* Metrhths twn bytes pou diavazontai me getchar */
        n = getchar();                                                                                                            /* Diavase ena byte */
        while (n != EOF) {                                                       /* Oso auto pou diavazeis me getchar einai diaforo tou EOF epanalabe */
            if (i == 1) {        /* 1o byte pou diavasthke me getchar,(omoiws gia ta else if pou akolouthoun an diavasthke to 2o, 3o, 4o,...klp byte) */
                if (n !='R') {
                    fprintf(stderr, "Error! \"RIFF\" not found\n");
                    return -1;                           /* Termatismos programmatos efoson brethike lathos,(omoiws gia ta return -1 pou akolouthoun) */
                }
                /* Efoson den brethike lathos kai eimaste sto MODE pou theloume ektypwse to antistoixo byte(omoiws sth synexeia) */
                else if (MODE == 2 || MODE == 3 || MODE == 4 || MODE == 5 || MODE == 6) { 
                    putchar('R');
                }
            }
            else if (i == 2) {
                if (n !='I') {
                    fprintf(stderr, "Error! \"RIFF\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 4 || MODE == 5 || MODE == 6) {
                    putchar('I');
                }
            }
            else if (i == 3) {
                if (n !='F') {
                    fprintf(stderr, "Error! \"RIFF\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 4 || MODE == 5 || MODE == 6) {
                    putchar('F');
                }
            }
            else if (i == 4) {
                if (n !='F') {
                    fprintf(stderr, "Error! \"RIFF\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 4 || MODE == 5 || MODE == 6) {
                    putchar('F');
                }                
            }
            else if (i == 5) {
                SizeOfFile = n;                                                         /* Dwse to 1o byte tou SizeOfFile se mia metablhth SizeOfFile */
                if (MODE == 2 || MODE == 3 || MODE == 6) {     /* Gia MODE 4 kai 5 stamatame na ektypwnoume bytes efoson theloume prwta to SizeOfData */
                    putchar(n);
                }
            }
            else if (i == 6) {
                SizeOfFile = SizeOfFile + n*256;                                /* Ananewse to SizeOfFile me to 2o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 7) {
                SizeOfFile = SizeOfFile + n*256*256;                            /* Ananewse to SizeOfFile me to 3o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 8) {
                SizeOfFile = SizeOfFile + n*256*256*256;                        /* Ananewse to SizeOfFile me to 4o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            } 
            else if (i == 9) {
                fprintf (stderr, "size of file: %d\n",SizeOfFile);                               /* Ektypwse to SizeOfFile efoson diavasthke oloklhro */
                if (n != 'W') {
                    fprintf(stderr, "Error! \"WAVE\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('W');
                }
            }
            else if (i == 10) {
                if (n !='A') {
                    fprintf(stderr, "Error! \"WAVE\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('A');
                }
            }
            else if (i == 11) {
                if (n !='V') {
                    fprintf(stderr, "Error! \"WAVE\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('V');
                }
            }
            else if (i == 12) {
                if (n !='E') {
                    fprintf(stderr, "Error! \"WAVE\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('E');
                }
            }
            else if (i == 13) {
                if (n !='f') {
                    fprintf(stderr, "Error! \"fmt \" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('f');
                }
            }
            else if (i == 14) {
                if (n !='m') {
                    fprintf(stderr, "Error! \"fmt \" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('m');
                }
            }
            else if (i == 15) {
                if (n !='t') {
                    fprintf(stderr, "Error! \"fmt \" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('t');
                }
            }
            else if (i == 16) {
                if (n !=' ') {
                    fprintf(stderr, "Error! \"fmt \" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(' ');
                }
            }
            else if (i == 17 ) {
                format = n;                                                         /* Dwse to 1o byte tou SizeOfFormatChunck se mia metablhth format */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 18 ) {
                format = format + n*256;                                            /* Ananewse to format me to 2o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 19 ) {
                format = format + n*256*256;                                        /* Ananewse to format me to 3o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 20 ) {
                format = format + n*256*256*256;                                    /* Ananewse to format me to 4o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            } 
            else if (i == 21 ) {
                fprintf(stderr, "size of format chunck: %d\n",format);                               /* Ektypwse to format efoson diavasthke oloklhro */
                if (format != 16) {
                    fprintf(stderr, "Error! size of format chunck should be 16\n");
                    return -1;
                }
                Wtypef = n;                                                             /* Dwse to 1o byte tou WAVETypeFormat se mia metablhth Wtypef */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 22 ) {
                Wtypef = Wtypef + n*256;                                            /* Ananewse to Wtypef me to 1o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 23 ) {
                fprintf(stderr, "WAVE type format: %d\n",Wtypef);                                    /* Ektypwse to Wtypef efoson diavasthke oloklhro */
                if (Wtypef != 1) {
                    fprintf(stderr, "Error! WAVE type format should be 1\n");
                    return -1;
                }
                MonoStereo = n;                                                        /* Dwse to 1o byte tou Mono/Stereo se mia metablhth MonoStereo */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 24 ) {
                MonoStereo = MonoStereo + n*256;                                /* Ananewse to MonoStereo me to 2o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 25 ) {
                fprintf(stderr, "mono/stereo: %d\n",MonoStereo);                                 /* Ektypwse to MonoStereo efoson diavasthke oloklhro */
                if ((MonoStereo != 1) && (MonoStereo != 2)) {
                    fprintf(stderr, "Error! mono/stereo should be 1 or 2\n");
                    return -1;
                }
                SampleRate = n;                                                         /* Dwse to 1o byte tou SampleRate se mia metablhth SampleRate */
                if (MODE == 6) {                   /* Gia MODE 2 kai 3 stamatame na ektypwnoume bytes efoson theloume prwta na allaksei to SampleRate */
                    putchar(n);
                }
            }
            else if (i == 26 ) {
                SampleRate = SampleRate + n*256;                                /* Ananewse to SampleRate me to 2o byte metatrepontas to se BigEndian */
                if (MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 27 ) {
                SampleRate = SampleRate + n*256*256;                            /* Ananewse to SampleRate me to 3o byte metatrepontas to se BigEndian */
                if (MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 28 ) {
                SampleRate = SampleRate + n*256*256*256;                        /* Ananewse to SampleRate me to 4o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3) {
                    if (MODE == 2) {
                        SampleRate2 = SampleRate / 2;                                                 /* An to MODE=2, to SampleRate ypodiplasiazetai */
                    }
                    else {
                        SampleRate2 = SampleRate * 2;                                                    /* An to MODE=3, to SampleRate diplasiazetai */
                    }
                    put4bytes(SampleRate2);           /* Kalese tin synarthsh put4bytes wste na ektypwthei to ananewmeno SampleRate2 san LittleEndian */
                }
                else if (MODE == 6) {
                    putchar(n);
                }
            } 
            else if (i == 29 ) {
                fprintf(stderr, "sample rate: %d\n",SampleRate);
                BytesPerSec = n;                                                        /* Dwse to 1o byte tou Bytes/Sec se mia metablhth BytesPerSec */
                if (MODE == 6) {                  /* Gia MODE 2 kai 3 stamatame na ektypwnoume bytes efoson theloume prwta na allaksei to BytesPerSec */
                    putchar(n);
                }
            }
            else if (i == 30 ) {
                BytesPerSec = BytesPerSec + n*256;                             /* Ananewse to BytesPerSec me to 2o byte metatrepontas to se BigEndian */
                if (MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 31 ) {
                BytesPerSec = BytesPerSec + n*256*256;                         /* Ananewse to BytesPerSec me to 3o byte metatrepontas to se BigEndian */
                if (MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 32 ) {
                BytesPerSec = BytesPerSec + n*256*256*256;                     /* Ananewse to BytesPerSec me to 4o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3) {
                    if (MODE == 2) {
                        BytesPerSec2 = BytesPerSec / 2;                                              /* An to MODE=2, to BytesPerSec ypodiplasiazetai */
                    }
                    else {
                        BytesPerSec2 = BytesPerSec * 2;                                                 /* An to MODE=3, to BytesPerSec diplasiazetai */
                    }
                    put4bytes(BytesPerSec2);         /* Kalese tin synarthsh put4bytes wste na ektypwthei to ananewmeno BytesPerSec2 san LittleEndian */
                }
                else if (MODE == 6) {
                    putchar(n);
                }
            } 
            else if (i == 33 ) {
                fprintf(stderr, "bytes/sec: %d\n",BytesPerSec);                                 /* Ektypwse to BytesPerSec efoson diavasthke oloklhro */
                BlockAlign = n;                                                     /* Dwse to 1o byte tou BlockAlignment se mia metablhth BlockAlign */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 34 ) {
                BlockAlign = BlockAlign + n*256;                                /* Ananewse to BlockAlign me to 2o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 35 ) {
                fprintf(stderr, "block alignment: %d\n",BlockAlign);                             /* Ektypwse to BlockAlign efoson diavasthke oloklhro */
                ginomeno = SampleRate * BlockAlign;                                                   /* Elegxos an BytesPerSec=SampleRate×BlockAlign */
                if (ginomeno != BytesPerSec) {
                    fprintf(stderr, "Error! bytes/second should be sample rate x block alignment\n");
                    return -1;
                }
                BitsPerSample = n;                                                  /* Dwse to 1o byte tou Bits/Sample se mia metablhth BitsPerSample */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 36 ) {
                BitsPerSample = BitsPerSample + n*256;                       /* Ananewse to BitsPerSample me to 2o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 37) {
                fprintf(stderr, "bits/sample: %d\n",BitsPerSample);                           /* Ektypwse to BitsPerSample efoson diavasthke oloklhro */
                if ((BitsPerSample != 8) && (BitsPerSample != 16)) {                                 /* Elegxos an BitsPerSample isoutai me 8 h me 16 */
                    fprintf(stderr, "Error! bits/sample should be 8 or 16\n");
                    return -1;
                }
                ginomeno2 = (BitsPerSample/8) * MonoStereo;                                       /* Elegxos an BlockAlign=BitsPerSample/8×MonoStereo */
                if (ginomeno2 != BlockAlign) {
                    fprintf(stderr, "Error! block alignment should be bits per sample / 8 x mono/stereo\n");
                    return -1;
                }
                if (n != 'd') {
                    fprintf(stderr, "Error! \"data\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('d');
                }
            }
            else if (i == 38) {
                if (n !='a') {
                    fprintf(stderr, "Error! \"data\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('a');
                }
            }
            else if (i == 39) {
                if (n !='t') {
                    fprintf(stderr, "Error! \"data\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('t');
                }
            }
            else if (i == 40) {
                if (n !='a') {
                    fprintf(stderr, "Error! \"data\" not found\n");
                    return -1;
                }
                else if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar('a');
                }
            }
            else if (i == 41 ) {
                SizeOfData = n;                                                    /* Dwse to 1o byte tou SizeOfDataChunk se mia metablhth SizeOfData */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 42 ) {
                SizeOfData = SizeOfData + n*256;                                /* Ananewse to SizeOfData me to 2o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 43 ) {
                SizeOfData = SizeOfData + n*256*256;                            /* Ananewse to SizeOfData me to 3o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
            }
            else if (i == 44 ) {
                SizeOfData = SizeOfData + n*256*256*256;                        /* Ananewse to SizeOfData me to 4o byte metatrepontas to se BigEndian */
                if (MODE == 2 || MODE == 3 || MODE == 6) {
                    putchar(n);
                }
                else if (MODE == 4 || MODE == 5) {        /* Efoson diavasthke kai to SizeOfData synexizoume na ektypwnoume bytes gia ta MODE 4 kai 5 */
                    if (MonoStereo == 2) {        /* An o hxos einai stereofwnikos tote to megethos tou arxeiou meiwnetai kata to miso tou SizeOfData */
                        SizeOfFile2 = SizeOfFile - (SizeOfData / 2);
                    }
                    else {                                           /* An o hxos einai monofwnikos tote to megethos tou arxeiou paramenei opws einai */
                        SizeOfFile2 = SizeOfFile;
                    }
                    put4bytes(SizeOfFile2);           /* Kalese tin synarthsh put4bytes wste na ektypwthei to ananewmeno SizeOfFile2 san LittleEndian */
                    put4char('W','A','V','E');                      /* Kalese tin synarthsh put4char wste na ektypwthei to 'WAVE' xarakthra-xarakthra */
                    put4char('f','m','t',' ');                      /* Kalese tin synarthsh put4char wste na ektypwthei to 'fmt ' xarakthra-xarakthra */
                    put4bytes(format);                                /* Kalese tin synarthsh put4bytes wste na ektypwthei to format san LittleEndian */
                    put2bytes(Wtypef);                                /* Kalese tin synarthsh put2bytes wste na ektypwthei to Wtypef san LittleEndian */
                    MonoStereo2 = 1;                     /* To MonoStereo2=1 efoson o hxos einai pleon monofwnikos(eite apo metatroph eite eks'arxhs) */
                    put2bytes(MonoStereo2);           /* Kalese tin synarthsh put2bytes wste na ektypwthei to ananewmeno MonoStereo2 san LittleEndian */
                    put4bytes(SampleRate);                        /* Kalese tin synarthsh put4bytes wste na ektypwthei to SampleRate san LittleEndian */
                    if (MonoStereo == 2) {                                      /* An o hxos einai stereofwnikos tote to BytesPerSec ypodiplasiazetai */                          
                        BytesPerSec2 = BytesPerSec / 2;
                    }
                    else {                                                    /* An o hxos einai monofwnikos tote to BytesPerSec paramenei opws einai */
                        BytesPerSec2 = BytesPerSec;
                    }
                    put4bytes(BytesPerSec2);         /* Kalese tin synarthsh put4bytes wste na ektypwthei to ananewmeno BytesPerSec2 san LittleEndian */
                    if (MonoStereo == 2) {                                       /* An o hxos einai stereofwnikos tote to BlockAlign ypodiplasiazetai */
                        BlockAlign2 = BlockAlign / 2;
                    }
                    else {                                                     /* An o hxos einai monofwnikos tote to BlockAlign paramenei opws einai */
                        BlockAlign2 = BlockAlign;
                    }
                    put2bytes(BlockAlign2);           /* Kalese tin synarthsh put2bytes wste na ektypwthei to ananewmeno BlockAlign2 san LittleEndian */
                    put2bytes(BitsPerSample);                  /* Kalese tin synarthsh put2bytes wste na ektypwthei to BitsPerSample san LittleEndian */
                    put4char('d','a','t','a');                      /* Kalese tin synarthsh put4char wste na ektypwthei to 'data' xarakthra-xarakthra */
                    if (MonoStereo == 2) {                                       /* An o hxos einai stereofwnikos tote to SizeOfData ypodiplasiazetai */
                        SizeOfData2 = SizeOfData / 2;
                    }
                    else {                                                     /* An o hxos einai monofwnikos tote to SizeOfData paramenei opws einai */
                        SizeOfData2 = SizeOfData;
                    }
                    put4bytes(SizeOfData2);            /* Kalese tin synarthsh put4bytes wste na ektypwthei to ananewmenoSizeOfData2 san LittleEndian */
                }
            }
            else if (i == 45) {                                                                        /* An to i brisketai sto 1o "data" tou arxeiou */
                fprintf(stderr, "size of data chunk: %d\n", SizeOfData);                         /* Ektypwse to SizeOfData efoson diavasthke oloklhro */
                if (MODE == 2 || MODE == 3 || MODE == 4) {  
                    putchar(n);
                }
                else if (MODE == 6) {                                                                                                    /* An MODE=6 */
                    if (BitsPerSample == 8) {          /* An BitsPerSample=8 tote ektypwse ton hxo(1 byte) me meiwmenh tin entash sto 1/8 tis arxikhs */
                        putchar((1.0 / 8.0 ) * n);
                    }
                    else {                                      /* An BitsPerSample=16 tote dwse to 1o(byte) dedomeno hxou se mia metablhth tempdata6 */
                        tempdata6 = n;
                    }
                }
            }
            else if ((i >= 46) && (i <= SizeOfData + 44)) {                                          /* An to i brisketai mesa sta "data" tou arxeiou */
                if (MODE == 2 || MODE == 3) {
                    putchar(n);
                }
                else if (MODE == 4) {                                                                                                    /* An MODE=4 */
                    if (MonoStereo == 2) {        /* An o hxos einai stereofwnikos tote prepei na ektypwthoun ta dedomena mono tou aristerou kanaliou */
                        if (i % 2 == 1) {
                            z = z + 2;                                              /* To z ksekinaei apo 45 kai auksanetai kata 2 ana 2 epanalipseis */
                        }
                        /* An BitsPerSample=8 tote ektypwse (to 1o exei ektypwthei hdh gia i=45),to 3o,to 5o,to 7o,...klp byte tou "data"(diladi mono to aristero kanali) */
                        if (BitsPerSample == 8) {
                            if (i % 2 == 1) {
                                putchar(n);
                            }
                        }
                        /* An BitsPerSample=16 tote ektypwse (to 1o exei ektypwthei hdh gia i=45),to 2o,to 5o,to 6o,to 9o,to 10o,...klp byte tou "data"(diladi mono to aristero kanali) */
                        else {
                            if (z % 4 == 1) {
                                putchar(n);
                            }
                        }
                    }
                    else {                                                         /* An o hxos einai monofwnikos tote ektypwnetai to monadiko kanali */
                        putchar(n);
                    }
                }
                else if (MODE == 5) {                                                                                                    /* An MODE=5 */
                    if (MonoStereo == 2) {          /* An o hxos einai stereofwnikos tote prepei na ektypwthoun ta dedomena mono tou deksiou kanaliou */
                        if (i % 2 == 1) {
                            z2 = z2 + 2;                                           /* To z2 ksekinaei apo 47 kai auksanetai kata 2 ana 2 epanalipseis */
                        }
                        /* An BitsPerSample=8 tote ektypwse to 2o,to 4o,to 6o,...klp byte tou "data"(diladi mono to deksi kanali) */
                        if (BitsPerSample == 8) {
                            if (i % 2 == 0) {
                                putchar(n);
                            }
                        }
                        /* An BitsPerSample=16 tote ektypwse to 3o,to 4o,to 7o,to 8o,...klp byte tou "data"(diladi mono to deksi kanali) */
                        else {
                            if (z2 % 4 == 1) {
                                putchar(n);
                            }
                        }
                    }
                    else {                                                         /* An o hxos einai monofwnikos tote ektypwnetai to monadiko kanali */
                        putchar(n);
                    }
                }
                else if (MODE == 6) {                                                                                                    /* An MODE=6 */
                    if (BitsPerSample == 8) {          /* An BitsPerSample=8 tote ektypwse ton hxo(1 byte) me meiwmenh tin entash sto 1/8 tis arxikhs */
                        putchar((1.0 / 8.0 ) * n);
                    }
                    else {                                                                                                     /* An BitsPerSample=16 */
                        if (i % 2 == 0) {                                                                                              /* An i artios */
                            tempdata6 = tempdata6 + n*256;                       /* Ananewse to tempdata6 me to 2o byte metatrepontas to se BigEndian */
                            tempdata6 = (1.0 / 8.0) * tempdata6;                                            /* Ananewse to tempdata6 meiwmeno sto 1/8 */
                            putchar(tempdata6 % 256);                                  /* Ektypwse to 2o byte tou tempdata6(diladi kata LittleEndian) */
                            putchar(tempdata6 >> 8);                                   /* Ektypwse to 1o byte tou tempdata6(diladi kata LittleEndian) */
                            /* (xrhsimopoiw >> 8 gia to 1o byte anti gia /256%256 wste na metaferthoun swsta kai oi arnhtikoi) */
                        }
                        else if (i % 2 == 1) {                                                                                       /* An i perittos */
                            tempdata6 = n;                                               /* Dwse to 1o(byte) dedomeno tou epomenou hxou sto tempdata6 */
                        }
                    }
                }
            }
            else {                                                                /* An i>SizeOfData+44 (diladi an to i brisketai mesa sta ExtraBytes */
                SizeOfExtra++;                                                                         /* To plhthos twn ExtraBytes auksanetai kata 1 */
                if (MODE == 2 || MODE == 3 || MODE == 4 || MODE == 5 || MODE == 6) {
                    putchar(n);
                }
            }
            
            if (i > 44) {                                                                            /* An to i brisketai mesa sta "data" tou arxeiou */
                SODbytes++;                                                                          /* Ta minimum SizeOfDatabytes auksanontai kata 1 */
            }
            i++;                                                                 /* Auksanetai kata 1 o metrhths twn bytes pou diavazontai me getchar */
            n = getchar();                                                                                                 /* Diavase to epomeno byte */
        }
        if (SODbytes < SizeOfData) {                     /* An ta minimum SizeOfDatabytes einai ligotera apo to SizeOfData exoume "insufficient data" */
            fprintf(stderr, "Error! insufficient data\n");
            return -1;
        }
        if (SizeOfFile != 36 + SizeOfData + SizeOfExtra) {
            fprintf(stderr, "Error! bad file size\n");
            return -1;
        }
    }
    else if (MODE == 7) {                                                                                                       /* An to MODE einai 7 */
        SampleRate = 44100;
        MonoStereo = 1;
        BitsPerSample = 16;
        SizeOfFile = dur * SampleRate * 2 + 36;                             /* SizeOfFile=duration×SampleRate×(BitsPerSample/8)(=2)+ta prwta 36 bytes */
        format = 16;                                                                                       /* To size of format chunck panta einai 16 */
        Wtypef = 1;                                                                                              /* To WAVE type format panta einai 1 */
        BlockAlign = 2 * MonoStereo;                                                                   /* BlockAlign=(BitsPerSample/8)(=2)×MonoStereo */
        BytesPerSec = SampleRate * BlockAlign;                                                                   /* BytesPerSec=SampleRate×BlockAlign */
        SizeOfData = dur * SampleRate * 2;                                                    /* SizeOfData=duration×SampleRate×(BitsPerSample/8)(=2) */
        put4char('R','I','F','F');                                  /* Kalese tin synarthsh put4char wste na ektypwthei to 'RIFF' xarakthra-xarakthra */
        put4bytes(SizeOfFile);                                    /* Kalese tin synarthsh put4bytes wste na ektypwthei to SizeOfFile san LittleEndian */
        put4char('W','A','V','E');                                  /* Kalese tin synarthsh put4char wste na ektypwthei to 'WAVE' xarakthra-xarakthra */
        put4char('f','m','t',' ');                                  /* Kalese tin synarthsh put4char wste na ektypwthei to 'fmt ' xarakthra-xarakthra */
        put4bytes(format);                                            /* Kalese tin synarthsh put4bytes wste na ektypwthei to format san LittleEndian */
        put2bytes(Wtypef);                                            /* Kalese tin synarthsh put2bytes wste na ektypwthei to Wtypef san LittleEndian */
        put2bytes(MonoStereo);                                    /* Kalese tin synarthsh put2bytes wste na ektypwthei to MonoStereo san LittleEndian */
        put4bytes(SampleRate);                                    /* Kalese tin synarthsh put4bytes wste na ektypwthei to SampleRate san LittleEndian */
        put4bytes(BytesPerSec);                                  /* Kalese tin synarthsh put4bytes wste na ektypwthei to BytesPerSec san LittleEndian */
        put2bytes(BlockAlign);                                    /* Kalese tin synarthsh put2bytes wste na ektypwthei to BlockAlign san LittleEndian */
        put2bytes(BitsPerSample);                              /* Kalese tin synarthsh put2bytes wste na ektypwthei to BitsPerSample san LittleEndian */
        put4char('d','a','t','a');                                  /* Kalese tin synarthsh put4char wste na ektypwthei to 'data' xarakthra-xarakthra */
        put4bytes(SizeOfData);                                    /* Kalese tin synarthsh put4bytes wste na ektypwthei to SizeOfData san LittleEndian */
        mysound(dur, SampleRate, fm, fc, mi, mv);                           /* Kalese tin synarthsh mysound wste na ektypwthoun ta "data" tou arxeiou */
    }
    return 0;
}
