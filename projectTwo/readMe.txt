Bernadette Kornberger

Linux

Steps to Compile:
To run the project it can be done so from the runMe

Bugs:
When there are too little passengers given the program will lock up and not all the passengers are acounted for. 

Also when you run the program if user does not give a number of passengers and trips then it will not run

Process:
I first created the threads and got one plane to work. Then got them all to work. After I figured that out i worked on getting the semaphore to work for the runway. I lastly figured out how to get the semaphore to work for the passengers.


Questions
1. yes and the program is in a deadlock. Not one plane can go and the planes are stuck frozen
2.The program runs pretty much the same as the last question. Because they are randomly boarded on all of the planes not one will take off even though we have 12 passengers.
3.The program was stck in deadlock. Not one plane left for a tour.
4.There was enough passengers that the airport was able to get all tours done. 
5. The minmum number to guarentee no deadlock is 89 passengers. This is because no matter what atleast one plane will have 12 passengers giving it enough to leave for a tour. 
