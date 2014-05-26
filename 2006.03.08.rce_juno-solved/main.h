#define WIN32_LEAN_AND_MEAN

#define NOSOUND           Sound APIs and definitions
#define NOCOMM            Comm driver APIs and definitions
#define NODRIVERS         Installable driver APIs and definitions
#define OEMRESOURCE       OEM Resource values
#define NONLS             All NLS defines and routines
#define NOSERVICE         All Service Controller routines, SERVICE_ equates, etc.
#define NOKANJI           Kanji support stuff.
#define NOMINMAX          min() and max() macros
#define NOLOGERROR        LogError() and related definitions
#define NOPROFILER        Profiler APIs
#define NOMEMMGR          Local and global memory management
#define NOLFILEIO         _l* file I/O routines
#define NOOPENFILE        OpenFile and related definitions
#define NORESOURCE        Resource management
#define NOATOM            Atom management
#define NOLANGUAGE        Character test routines
#define NOLSTRING         lstr* string management routines
#define NODBCS            Double-byte character set routines
#define NOKEYBOARDINFO    Keyboard driver routines
#define NOGDICAPMASKS     GDI device capability constants
#define NOCOLOR           COLOR_* color values
#define NOGDIOBJ          GDI pens, brushes, fonts
#define NODRAWTEXT        DrawText() and related definitions
#define NOTEXTMETRIC      TEXTMETRIC and related APIs
#define NOSCALABLEFONT    Truetype scalable font support
#define NOBITMAP          Bitmap support
#define NORASTEROPS       GDI Raster operation definitions
#define NOMETAFILE        Metafile support
#define NOSYSMETRICS      GetSystemMetrics() and related SM_* definitions
#define NOSYSTEMPARAMSINFO SystemParametersInfo() and SPI_* definitions
#define NOMSG             APIs and definitions that use MSG structure
#define NOWINSTYLES       Window style definitions
#define NOWINOFFSETS      Get/SetWindowWord/Long offset definitions
#define NOSHOWWINDOW      ShowWindow and related definitions
#define NODEFERWINDOWPOS  DeferWindowPos and related definitions
#define NOVIRTUALKEYCODES VK_* virtual key codes
#define NOKEYSTATES       MK_* message key state flags
#define NOWH              SetWindowsHook and related WH_* definitions
#define NOMENUS           Menu APIs
#define NOSCROLL          Scrolling APIs and scroll bar control
#define NOCLIPBOARD       Clipboard APIs and definitions
#define NOICONS           IDI_* icon IDs
#define NOSYSCOMMANDS     WM_SYSCOMMAND SC_* definitions
#define NOMDI             MDI support
#define NOCTLMGR          Control management and controls
#define NOWINMESSAGES     WM_* window messages
#define NOHELP            Help support


#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "include/m_apm.h"
#include "include/prty.c"
#include "include/md5.h"
#include "include/tway.h"
#include "include/resource.h"

char szName[32]; 
char szCompany[32];
char szUserID[32]; 
char szUserKey[32]; 
char szSerial[128]; 

unsigned int kiHash[17]={0};
unsigned int nmHash[17]={0}; 
unsigned int cpHash[17]={0};  
unsigned int serialHash[17]={0};
unsigned int encryptedHash[17]={0};

char staticFloat[] = "\x2E\x29\x21\x2F\x36\x2D\x2E\x2C\x2A\x2F\x20\x29\x28\x2D\x21\x2E\x29\x2D\x2E";
char serialFormat[] = "\x3D\x28\x20\x74\x60\x35\x3D\x28\x20\x74\x60\x35\x3D\x28\x20\x74\x60";
char nameEr[] = "\x56\x79\x75\x7D\x38\x75\x6D\x6B\x6C\x38\x7A\x7D\x38\x7F\x6A\x7D\x79\x6C\x7D\x6A\x38\x6C\x70\x79\x76\x38\x2B\x38\x7B\x70\x79\x6A\x6B"; 
char compEr[] = "\x5B\x77\x75\x68\x79\x76\x61\x38\x75\x6D\x6B\x6C\x38\x7A\x7D\x38\x7F\x6A\x7D\x79\x6C\x7D\x6A\x38\x6C\x70\x79\x76\x38\x2B\x38\x7B\x70\x79\x6A\x6B";
char wellDone[] = "\x4C\x70\x79\x6C\x38\x6B\x7D\x6A\x71\x79\x74\x38\x71\x6B\x38\x7B\x77\x6A\x6A\x7D\x7B\x6C\x34\x38\x6F\x7D\x74\x74\x38\x7C\x77\x76\x7D\x21";

 typedef struct {
    float mB;
    float mD;
    float mT;
 } VECTOR;
 
 char dumbCrypt(char *in);
 void aTransform(float totalVector);
 int bTransform();
 float cTransform(VECTOR *v1);
 float hNameComp();
 void hUid();
