CRANE
=====

CRANE (Chemical ReAction NEtwork) is an open source software dedicated to modeling the time evolution of coupled rate equations. CRANE is part of the MOOSE framework: [http://mooseframework.org](http://mooseframework.org)

**Instructions for installing CRANE:**

**Step 1.** Install the [MOOSE](http://mooseframework.org/) development environment (click on 'Getting Started' at the following link and follow the instructions),

`http://mooseframework.org/`

After installing MOOSE, make sure you have the following folder on your local machine containing MOOSE

`~/projects`

**Step 2.** After installing the MOOSE environment, execute the following commands:

`cd ~/projects`

`git clone https://github.com/lcpp-org/crane`

`cd crane`

`make -jn` 

where `n` is the number of logical processors on your computer. 

**Step 3.**
Run tests to make sure CRANE is installed properly. 

`./run_tests`

If all the tests pass, CRANE has been successfully installed. 
