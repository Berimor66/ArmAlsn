/*-----------------------------------------------------------
  VERSION CONTROL BUILD SYSTEM                               
  This header file was created by VERBUILD v1.0.0            
  Copyright(c) 2005-2007 Yeamaec Communication.Co,.Ltd.      
  -----------------------------------------------------------
  You can modify below comments for own purpose!             

  version number is usually A.B.C.D format.                  
  A : major B : minor C : build number D : extend            
  VERBUILD supports two type automatic version number.       
  first is increasing normal digits and second is enhanced   
  increasing normal digits with by daily basis build number. 
  the option -d is for second type by set to digit part C.   
  part C in daily basis set maximum 5 digits build number,   
  For example: today¡¯s build number is 02302:               
  which you can decode as follows:                           
  02  => year: but it is not a direct mapping:               
         if the base year is 2005,¡®2¡¯ maps to 2007.        
  302 => daily index from 01/01                              
  it also could be described by -d2005 option.               
  for overflow,you can set minimum and maximum version bumber
  specified by given -b and -e option with -s option.        
  in normal digits mode,the overflow sequence is A>B>C>D.    
  in daily basis mode,the overflow sequence is A>B>D.        
  minimum version number set by -b option.                   
  For example, -b1.0.0.0                                     
  maximum version number set by -e option.                   
  For example, -e15.10.99999.90                              
  these minimum and maximum version number not effect part   
  C in daily basis mode.                                     
  For example,if part D overflow,skip C and jump to B.       
  The full version is based on VERSION_FULL commonly.        
  For each file version or product version increasing,       
  use -x option as -xf -xp.                                  
                                                             
  info : http://www.yeamaec.com                              
         krkim@yeamaec.com                                   
-----------------------------------------------------------*/
#ifndef VERSIONNO__H
#define VERSIONNO__H

#define VERSION_FULL           0.14.5148.30

#define VERSION_BASEYEAR       2010
#define VERSION_DATE           "2015-05-29"
#define VERSION_TIME           "15:52:38"

#define VERSION_MAJOR          0
#define VERSION_MINOR          14
#define VERSION_BUILDNO        5148
#define VERSION_EXTEND         30

#define VERSION_FILE           0,14,5148,30
#define VERSION_PRODUCT        0,14,5148,30
#define VERSION_FILESTR        "0,14,5148,30\0"
#define VERSION_PRODUCTSTR     "0,14,5148,30\0"

#ifndef DEBUG
#define VER_DEBUG                   0
#else
#define VER_DEBUG                   VS_FF_DEBUG
#endif

#endif
