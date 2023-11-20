# This is kata's social media helper v0.3 

This is not finalized build

-------------------------------------------------------------------------
Run the installScript.bat from the src folder to install the software 
You can make a shortcut to parent folder afterwards.                  
The executable is named "mediaHelper.exe"                             

## FILE NAMING
- To correctly use the filters, name your picture files using the template [number].[name].jpg
    - For example 001.dazai.jpg

## Description / Plan
A program that uses user assigned folders depending on the mood and the cosplay of the picture (User puts photos into corresponding folders).

The program asks the user for the mood and cosplay they want to post and selects a picture randomly from specific category depending on the user input and moves it to a output folder.

## NOTE!
- For the random mood to properly work, there shouldn't be any empty mood folders.
The program might crash otherwise!

- Before using the software, delete the files named DELETE ME from pictures and toPost folders..

## How to use
- You can create folders into the pictures folder, wich acts as the first filter. (moods)
- Put the photos into corresponding folders.

- TO USE THE SECOND FILTER (cosplay/(can be used as a person or whatever filter you desire))
 - name your file using the naming convention (001.name.jpg)


## Prequisites:
- Up to date vc redist packages
- Up to date g++ (c++ compiler)


## Changelog:
- Added possibility to randomize mood selection