#!/usr/bin/env python
__author__   = "Ahamed Yaser Arafath"
__version__  = "1.0.0"
__email__    = "ahamedyaserarafath@gmail.com"

import sys
import os
import subprocess

list_of_c_files=["calculator.c",
                 "helloworld.c"]

class buildCommon:

    def __init__(self):
        self.bin_directory = "./bin/"
        if not os.path.exists(self.bin_directory):
            os.makedirs(self.bin_directory)

    def DoError (self,Error) :
        sys.stderr.write(Error)
        sys.exit(1)

    def execute_command(self,cmd_to_execute):
        '''
        Execute the bash command
        '''
        try:
            check_state = subprocess.Popen(cmd_to_execute, shell=True,
                                            stdout=subprocess.PIPE,
                                            stderr=subprocess.PIPE)
            output, error = check_state.communicate()
            return check_state.returncode, output, error
        except Exception as e:
            self.DoError(str(e))

    def cplusplus_build(self):
        '''
        Build the c++ build using g++ command
        ex: g++ helloworld.c -o bin/helloworld
        '''
        try:
            compilation_command = "g++ "
            for temp_file in list_of_c_files:
                if os.path.exists(temp_file):
                    frame_command = compilation_command + temp_file \
                                    + " -o " + self.bin_directory \
                                    + temp_file.split(".")[0]
                    returncode,output,error = self.execute_command(frame_command)
                    if returncode == 0:
                        sys.stdout.write(temp_file + " :  Compilation is sucess without any error\n")
                    else:
                        self.DoError(temp_file + " :  Compilation is failure, please find the error for your reference.\n"
                        		+str(error))
                else:
                    self.DoError(temp_file + " :  File doesnt exists")
        except Exception as e:
            self.DoError(str(e))

if __name__ == '__main__':
    ob = buildCommon()
    ob.cplusplus_build()
