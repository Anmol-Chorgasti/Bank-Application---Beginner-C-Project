This project is a basic Banking Application that allows the user to 
1) Create an account
2) Login to an existing account
3) Add/remove money from account
4) change login password
5) delete account
6) request to view details of their own account

The code utilizes a text file as its backend source. The overall flow of the program is as follows:
1) Main function is executed and a Bank type object is made
2) A text file is opened in the backend and all the data in it is read into a map (or dictionary) data structure. The details for each account are stored in key value pairs
3) The Account IDs which are assigned automatically to each new account are treated as keys, and all the details of the corresponding account are treated as the value
4) Based on the user's choices, all the changes and actions are then performed on the data within the map
5) Finally, just before the end of the program, the data in the text file is wiped out and the data from the map (including the new changes) is written back into the text file

This approach was selected to reduce the total number of reads and writes to the backend file. In this approach, the file is read from and written to only once. If I had opted to work directly with the file data and not use maps, the number of reads and writes to the files would have grown exponentially with each user action

