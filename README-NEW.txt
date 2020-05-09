This is a disk scheduling program written in C.

It has implemented three common disk scheduling algorithms:
	1. First Come First Serve (FCFS)
	2. SCAN
	3. C-SCAN

How to Run this Program?
	1. Use the make file command "make"
	2. A new file called "run" will appear in the current directory
	3. You can run the program using the command "./run", which will run the program with a default head
		position of 33
	3a. You can specifiy the inital head position by running the program with this command "./run [head_pos]
		where 'head_pos' is an integer value of where you would like the head position of the 
		algorithm to start at. 
	4. Once you have runned the program the file "output.txt" will be created with the results to the program
	NOTE: The program will only run the algorithms with a file name "input.txt", also the output file will
		always be named "output.txt"
	5. (Optional) You may use the make commane "make clean" which will remove the "run" file
Example Run:
	1. The current "input.txt" file can be runned and will output a file "output.txt"
	2. You may use that the compare with "output_ans.txt" which is the answer to the program provided
		by the professor. You can see that they match and therefore I have successfully created a
		program that runs the three specified disk scheduling algorithm.

Edward Leung
Student Number: 215484611
