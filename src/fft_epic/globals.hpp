// Copyright Neil Maitland 1992
//
//
// Description:
//
// This file contains the global definitions for the project, including
// constants, typedefs, enum types, and structures.
// A conditional compile directive prevents redefinition during the same
// compilation.
//
//
//
// Functions contained are as follows:
//
//  None
//
//
//
// Modifications :
//
//  21-01-93 : Neil Maitland - added new options for DISTORTQUAD
//  26-01-93 : Neil Maitland - added SPACE to enum extrakeys
//  26-01-93 : Neil Maitland - added define for gamma corrected grey scales
//  29-01-93 : Neil Maitland - added NO8087 to fatalerror
//  12-03-93 : Neil Maitland - edited struct distortdetails to allow
//                             variable mark-space square waves
//  12-03-93 : Neil Maitland - added WRONGCPU to fatalerror
//  13-03-93 : Neil Maitland - added DOGAUSS filtertype and edited
//                             filterdetails
//  15-03-93 : Neil Maitland - added INVALIDINPUT to enum normerrors
//  24-03-93 : Neil Maitland - added NUMTOOLONG and BADSQUADNUM to enum
//                             normerrors and #define for STRINGTOOLONG
//  27-03-93 : Neil Maitland - added compiler directives to be included in
//                             every file
//  19-04-93 : Neil Maitland - changed version from "1.0 beta" to "1.0"
//  07-05-93 : Neil Maitland - changed version from "1.0" to "1.01" after
//                             editing MENUS.CPP
//



#ifndef __GLOBALS__

#define __GLOBALS__


#define VERSION " 1.01"    // version number of this compilation, as
                           // displayed above menus

// #define DEBUG       // used to display debug information at various points
                       // in the program

// when a picture is drawn on screen which is of lower resolution than the
// picture in memory the displayed pixel value may be calculated in one of
// three possible ways:
//
//     FIRSTBLOCKS - the value of the first pixel in the block is used
//     AVGEBLOCKS  - the average of a of the block of pixels is taken
//     MAXBLOCKS   - the highest valued pixel in the block is used
//
// the define BLOCKREDUCE should be set to the method required

#define FIRSTBLOCKS 0
#define AVGEBLOCKS 1
#define MAXBLOCKS 2

#define BLOCKREDUCE MAXBLOCKS


// #define EMULATEXMS  // this allows the use of disk files to emulate xms, so
                       // that the program can be debugged when there is
                       // little XMS available

// #define CBREAKABORT // if defined then control break will quit program
                       // any other value will mean break is ignored

#define GAMMA16        // if defined, these options force the palette
//#define GAMMA64      // initialisation routines to use gamma corrected
                       // grey scales instead of linear scales - one each
                       // for the 16 and 64 scale palettes

// define the palette values for some colours
#define MYBLACK      8
#define MYWHITE      15
#define MYBLUE       0
#define MYLBLUE      1
#define MYLGREEN     2
#define MYLCYAN      3
#define MYLRED       4
#define MYLMAGENTA   5
#define MYYELLOW     6
#define MYRED        7

// these define specific colours for specific types of display
#define INPUTCOL     MYLMAGENTA
#define REQUESTCOL   MYLCYAN
#define TITLECOL     MYYELLOW
#define BARCOLOUR    MYLBLUE

// these are screen co-ordinates for various parts of the graphical displays
#define MENUTOP      212
#define DIRTOP       318
#define ERRTOP       439
#define FIRSTWINX    16
#define WINXDIFF     160
#define WINTOP       35
#define WINBOTTOM    (WINTOP+127)
#define XOFFSET      96
#define YOFFSET      95
#define FRAMEXOFFSET (XOFFSET-1)
#define FRAMEYOFFSET (YOFFSET-1)
#define FILTERWIN    429
#define WIN1X        16
#define WIN2X        177


// some boolean defines
#define TRUE         1
#define FALSE        0
#define ERROR        -1
#define YES          1
#define NO           0

// value for an invalid quadrant number
#define BADQUAD      -1

// return value for when user input is too long
#define STRINGTOOLONG -2

// some useful typedefs
typedef unsigned char byte;
typedef unsigned char flag;
typedef unsigned int word;

// a typedef for the vga colour palette
typedef unsigned char dacpalette256[256][3];

// the menu system requires the following enum type, where NUMMENUS will be
// assigned the value corresponding to the total number of menus, so must be
// last.
enum menus {TOP,
            FILING,
            PROCESS,
            FILTTYPE,
            AREAFILTS,
            POINTFUNCS,
            DISTORTQUAD,
            NUMMENUS
           };

// MENUSIZE is one bigger than the maximum number of options to accomodate
// the menu title.
#define MAXMENUOPTIONS 5
#define MENUSIZE (MAXMENUOPTIONS + 1)


// the following are straightforward enumerated types

enum graphmodes {HIGHRES=18,
                 HICOLOUR=19,
                 NOTINIT=-1
                };

enum fatalerrs {GRAPHINIT,
                NOTVGA,
                WRONGSEGX,
                WRONGSEGY,
                NUMQUADRANTS,
                NOXMS,
                NOTENOUGHXMS,
                BADXMS,
                NORAM,
                NO8087,
                WRONGCPU
               };

enum normerrors {BADKEY,
                 NOTTRANS,
                 ALREADYTRANS,
                 READINGFILE,
                 INVALIDFILE,
                 FILENOTFOUND,
                 FILENAMETOOLONG,
                 PATHTOOLONG,
                 INVALIDPATH,
                 GENERALFILE,
                 WRITINGFILE,
                 CREATINGFILE,
                 FILEEXISTS,
                 BADDRIVE,
                 AOI,
                 AVGEAOI,
                 REDUCEDMODE,
                 ICANOTEPIC,
                 TAKELOGS,
                 NOTIMPLEMENTED,
                 EXITOP,
                 INVALIDINPUT,
                 NUMTOOLONG,
                 BADQUADNUM
                };

enum picsizemodes {STANDARD,
                   REDUCED,
                   XMSNOTAVAIL
                  };

enum extrakeys {ESC=0x001b,
                F1=0x3b00,
                F2=0x3c00,
                F3=0x3d00,
                F4=0x3e00,
                F5=0x3f00,
                F6=0x4000,
                SF1=0x5400,
                SF2=0x5500,
                SF3=0x5600,
                SF4=0x5700,
                CF1=0x5e00,
                CF2=0x5f00,
                CF3=0x6000,
                CF4=0x6100,
                AF1=0x6800,
                AF2=0x6900,
                AF3=0x6a00,
                AF4=0x6b00,
                LEFT=0x4b00,
                RIGHT=0x4d00,
                UP=0x4800,
                DOWN=0x5000,
                PGUP=0x4900,
                PGDN=0x5100,
                BACKSP=0x0008,
                SPACE=0x0020,
                BADOPTION=0
               };

enum transformstates {NONE,
                      FOURIER,
                      HOMOMORPHIC
                     };

enum directions {FORWARD,
                 INVERSE
                };

enum trantype {DIVIDE,
               NODIVIDE
              };

enum filters {STEP,
              BUTTER,
              USER,
              DOGAUSS,
              COEFFSCALE,
              COEFFROOT,
              CEPSTRUM,
              NOTDEFINED
             };

enum filing {READ,
             WRITE
            };

enum aoitypes {AVERAGE,
               AREA
              };

enum distorttypes {SINE,
                   SQUARE
                  };

enum ways {HORIZONTAL,
           VERTICAL
          };

// this is the structure to contain details of a filter.  The type is a fixed
// field, while all of the others are a union, as it may only contain one
// type of filter.
struct filterdetails {
   enum filters type;
   union {
      struct {
         float radius;
         float maxgain, mingain;
         int order;
         flag highpass;
      } area;
      struct {
         float mag1, mag2;
         float sigma1, sigma2;
      } gauss;
      struct {
         flag polar;
         float mul1;
         float mul2;
      } scale;
      struct {
         float magp;
         float mul;
      } root;
      struct {
         float k;
         float a;
         float b;
      } cepstrum;
   };
};

// this is the structure to contain details of a distortion function.
struct distortdetails {
   enum distorttypes type;
   enum ways dirn;
   float amp;
   union {
      struct {
         float wavelength;
      } sine;
      struct {
         float high, low;
      } square;
   };
};


#endif

// now include standard compiler directives in file

// #pragma option -2   // use 80286p instructions
// #pragma option -a   // align data on even addresses
// #pragma option -K   // use unsigned chars
// #pragma option -v   // include debug info in OBJs
// #pragma option -Z   // optimise register usage
// #pragma option -d   // merge duplicate strings


#ifdef DEBUG // then don't optimise

// #pragma option -Od  // turn off all optimisations


#else // optimise for maximum speed

// #pragma option -vi  // expand C++ inline functions
// #pragma option -G   // optimise code for speed
// #pragma option -O   // jump optimisation
// #pragma option -Og  // global common subexpression optimisation
// #pragma option -Oe  // global register allocation and live range testing
// #pragma option -Om  // move invariant code outside loops
// #pragma option -Ov  // make loop induction variables
// #pragma option -Ol  // use CPUs string instructions for loops
// #pragma option -Ob  // remove dead code during compilation
// #pragma option -Op  // enable copy propogation optimisation
// #pragma option -Oi  // compile instrinsic functions inline
// #pragma option -po  // localise C++ object members with SI register
// #pragma option -k-  // do not use a standard stack frame

#endif

// enable compiler warnings that default to off
// #pragma option -wbbf
// #pragma option -wpin
// #pragma option -wamb
// #pragma option -wamp
// #pragma option -wasm
// #pragma option -wpro
// #pragma option -wcln
// #pragma option -wdef
// #pragma option -wsig
// #pragma option -wnod
// #pragma option -wstv
// #pragma option -wucp
// #pragma option -wuse
// #pragma option -weas
// #pragma option -wpre
