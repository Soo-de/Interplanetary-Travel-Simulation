/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 11.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/


#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "setjmp.h"                     // for jumper

jmp_buf jumper;

#define try do{if(!setjmp(jumper)){     // try block
#define catch }else{                    // catch block
#define throw longjmp(jumper, -1);      // return when there is an exception
#define tryEnd }}while(0)               // end of try-catch block

#endif