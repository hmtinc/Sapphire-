//
//  main.cpp
//  Sapphire
//
//  Created by Harsh Mistry  on 2016-01-21.
//  Copyright (c) 2016 Harsh Mistry . All rights reserved.
//

#include "swf_proccess.h"



size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}


void DownloadFile(const char* url, const char* fname) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl){
        fp = fopen(fname, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

int main(int argc, const char * argv[]) {
    
    user_Info h_info = get_info();
    user_Info u_info = har_to_csv(h_info);
    text_list p;
    text_list u_list = get_url(u_info);
    text_list swf_list = download_swf(u_list, u_info);
    text_list png_list = convert_png(swf_list, u_info);
    png_to_pdf(u_info, png_list);

    
}

void png_to_pdf(user_Info u_info, text_list png_list){
    
    text_str bin_str = u_info.convert_bin;
    text_str png_path_str = u_info.png_dir;
    text_str file_str = ".png";
    text_str command_str = bin_str + " " + "-quality 50 ";
    text_int length = png_list.size();
    text_str output_str = u_info.output_loc;
    
    cout << "Preparing to Convert to PDF - Please Wait" << endl;
    
    for (int x = length - 1; x > -1; x = x -1) {
        
        command_str = command_str + png_path_str + "/" + to_string(x) + file_str + " ";
        //png_list.pop_back();
        
    }
    
    command_str = command_str + output_str;
    cout << "Converting ...." << endl;
    system(command_str.c_str());
    cout << "Conversion Complete" << endl;
    
    
    
}

text_str url_return(const string& infix)
{
    //Temp Variables
    text_str build_url_str = "";
    
    for (auto c = infix.begin(); c!=infix.end(); ++c)
    {
        //Break loop if char is a space
        if (isspace(*c)){
        
            break;
        }
    
        //Append Character to the build str
        build_url_str.push_back(*c);
    }
    
    return build_url_str;
    

}

text_list get_url(user_Info u_info){
    
    text_list url_list;
    
    text_str url_str;
    text_str cell_str;
    
    fstream infile(u_info.csv_name);
    
    for( std::string line; getline( infile, line ); )
    {
        url_str = url_return(line);
        
        if(url_str.substr( url_str.length() - 3 ) == "swf")
        {
        
            url_list.push_back(url_str);
            
        }
        
    }
    
    return url_list;


}

text_list download_swf(text_list url_list, user_Info u_info) {
    
    text_list new_file_list;
    text_int length = url_list.size();
    text_str dir_str = u_info.download_dir;
    text_str file_str = ".swf";
    text_str message_str = " and saved as ";
    text_str final_str;

    
    for( int x = 0; x < length; x++) {
        
        final_str = dir_str + "/" + to_string(x) + file_str;
        new_file_list.push_front(final_str); // Add new location to new file list
        DownloadFile(url_list.front().c_str(), final_str.c_str());
        cout << "Downloaded " + url_list.front().substr(url_list.front().length() - 36) + message_str + to_string(x) + file_str << endl;
        url_list.pop_front();
        
    }
    
    return new_file_list;

}

text_list convert_png(text_list swf_list, user_Info u_info){
    
    text_list new_file_list;
    text_int length = swf_list.size();
    text_str dir_str = u_info.png_dir ;
    text_str swf_str = u_info.swfrender_path;
    text_str file_str = ".png";
    text_str message_str = " and saved as ";
    text_str res_str = "-X 1836 -Y 2376 ";
    text_str final_str;
    text_str loc_str;
    
    
    text_str q = "/Users/harshmistry/Downloads/q/swfrender1 /Users/harshmistry/Downloads/q/5.swf -o /Users/harshmistry/Downloads/q/5.png";
    
    for( int x = 0; x < length; x++) {
        
        loc_str = dir_str + "/" + to_string(x) + file_str;
        final_str = swf_str + " " + res_str + swf_list.front() + " -o " + loc_str;
        swf_list.pop_front();
        new_file_list.push_front(loc_str); // Add new location to new file list
        system(final_str.c_str());
        cout << "Converted " + to_string(x) + ".swf to png" << endl;
    
        
    }
    

    return new_file_list;
}


user_Info get_info (){
    
    user_Info u_info;
    
    cout << "Enter SWF Dir Path : " << endl;
    cin >> u_info.download_dir;
    
    cout << "Enter HAR Dir Path : " << endl;
    cin >> u_info.csv_name;
    
    cout << "Enter HAR Name (enter without .har extension) : " << endl;
    cin >> u_info.har_name;
    
    cout << "Enter PNG Dir Path : " << endl;
    cin >> u_info.png_dir;
    
    cout << "Enter Swftools Path : " << endl;
    cin >> u_info.swfrender_path;
    
    cout << "Enter Har Tools Path : " << endl;
    cin >> u_info.har_path;
    
    cout << "Enter ImageMagicK Path : " << endl;
    cin >> u_info.convert_bin;
    
    cout << "Enter Output Path with pdf name (Ensure to include .pdf) : " << endl;
    cin >> u_info.output_loc;
    
    return u_info;
    

}

user_Info har_to_csv( user_Info u_info){
    
    text_str file_str = ".har";
    text_str path_str = u_info.csv_name;
    text_str name_str = u_info.har_name;
    text_str tool_str = u_info.har_path;
    text_str dest_str = path_str + "/1.csv";
    u_info.csv_name = dest_str;
    text_str out_str = tool_str + " --in " + path_str + "/" + name_str + file_str + " --out " + dest_str;
    
    system(out_str.c_str());
    cout << "Har Converted to CSV" << endl;
    
    return u_info;
}






