![logo](https://raw.githubusercontent.com/hmtinc/Sapphire-/master/Resources/logo.png?token=ABQMErifvbZ3_dqyVbQW4naGBSPNWiYqks5WrB0LwA%3D%3D)
# Sapphire ETEXT Backup Utility
Sapphire ETEXT Backup Utility is a C++ command line app which allows you to make legal offline 
backups of your Pearson ETEXT Books

# Why? 
Pearson's ETEXT viewer requires you to view your ebook online using thier flash based viewer.
This can be problematic for indviduals who do not have a online connection at all times or 
do not have a flash based device. 

# Extract Textbooks 
1. Obtain a HTTP Archive (HAR) containing all HTTP requests for your specific textbook
2. Launch Sapphire 
3. Enter the required directory paths
4. Wait (This can take some time around 1 - 2 seconds per page) 
5. Read Offline 

# Required Binaries 
Sapphire makes use of 3rd party binaries to convert the online etext to pdf format. These binaries are
not provided with Sapphire and will need to be downloaded separately (links provided below)
- HarTools (har2csv) - https://github.com/spcgh0st/HarTools
- Swftools (swfrender) - http://www.swftools.org
- Imagemagick (convert) - http://www.imagemagick.org/script/index.php

# Output 
Sapphire will output/save the textbook in 3 formats (.swf, .png, and .pdf).

# Windows Users
Currently only a unix executable is provided, but the source code is provided if you wish to build
your own Windows Binary.

# Goals
The long term goal for Sapphire is to provide a fully functional GUI based app that is
cross-platform

   
# Legal
Sapphire is meant to be used to back up LEGAL COPIES ONLY and does not contain any copyrighted 3rd party material/code.
Please review the textbook's terms of service before proceeding with this Utility as most pearson textbooks permit one legal backup.












