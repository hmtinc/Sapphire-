//
//  swf_proccess.h
//  Sapphire
//
//  Created by Harsh Mistry  on 2016-01-21.
//  Copyright (c) 2016 Harsh Mistry . All rights reserved.
//

#ifndef __Sapphire__swf_proccess__
#define __Sapphire__swf_proccess__

#include <stdio.h>
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <fstream>
#include <list>

//Namespaces
using namespace std;

//Data Definitions
typedef int text_int;
typedef bool text_bool;
typedef string text_str;
typedef list<string> text_list;

//User Info Struct
struct user_Info{
    
    text_str download_dir;
    text_str csv_name;
    text_str png_dir;
    text_str swfrender_path;
    text_str har_path;
    text_str har_name;
    text_str convert_bin;
    text_str output_loc;
    
};

//Functions
void png_to_pdf(user_Info, text_list);
text_str url_return(const string& infix);
text_list get_url(user_Info);
text_list download_swf(text_list, user_Info);
text_list convert_png(text_list, user_Info);
user_Info get_info(void);
user_Info har_to_csv(user_Info);


#endif /* defined(__Sapphire__swf_proccess__) */
