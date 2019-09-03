#!/usr/bin/env python
__author__   = "Ahamed Yaser Arafath"
__version__  = "1.0.0"
__email__    = "ahamedyaserarafath@gmail.com"

import sys
import os
import subprocess
import datetime

class ciBuild:

    def __init__(self):
        self.list_of_changed_files = ""
        self.build_stdout_log_filename = "stdout_build.log"
        self.build_stderr_log_filename = "stderr_build.log"
        self.list_of_changed_files_filename = "list_of_changed_files.log"
        self.time_format = datetime.datetime.now().strftime("%d_%m_%y_%H_%M_%S")

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

    def push_binary_back_to_vcs(self):
        '''
        Push the binary to github repo itself
        '''
        try:
            git_binary_add = "git add -f bin/*"
            git_binary_commit = "git commit -m 'binary auto push during successfull build '"
            git_binary_push = "git push"
            git_binary_add_returncode,_,error = self.execute_command(git_binary_add)
            if git_binary_add_returncode == 0:
                git_binary_commit_returncode,_,error = self.execute_command(git_binary_commit)
                if git_binary_commit_returncode == 0:
                    git_binary_push_returncode,_,error = self.execute_command(git_binary_push)
                    if git_binary_push_returncode == 0:
                        sys.stdout.write("git push is successfull\n")
                    else:
                        self.DoError("Error in git push" + str(error))
                else:
                    self.DoError("Error in git commit" + str(error))
            else:
                self.DoError("Error in git add" + str(error))
        except Exception as e:
            self.DoError(str(e))

    def get_latest_files_with_pull(self):
        '''
        pull the latest code from git repo
        '''
        try:
            git_fetch = "git fetch"
            git_diff = "git diff ..origin"
            git_pull_latest_code = "git pull"
            git_fetch_returncode,_,error = self.execute_command(git_fetch)
            if git_fetch_returncode == 0:
                git_diff_returncode,output,error = self.execute_command(git_diff)
                if git_diff_returncode == 0:
                    self.list_of_changed_files = output
                    git_pull_latest_code_returncode,output,error = self.execute_command(git_pull_latest_code)
                    if git_pull_latest_code_returncode == 0:
                        sys.stdout.write("Git pull latest code was successfull\n")
                    else:
                        self.DoError("Error in git push" + str(error))
                else:
                    self.DoError("Error in git push" + str(error))

            else:
                self.DoError("Error in git push" + str(error))

        except Exception as e:
            self.DoError(str(e))

    def create_error_log_tar(self,build_ouput,build_error):
        '''
        In case of build failure creating the create a error log tar file
        '''
        try:
            file_stdout_write = open(self.build_stdout_log_filename, "w")
            file_stderr_write = open(self.build_stderr_log_filename, "w")
            file_diff = open(self.list_of_changed_files_filename, "w")
            file_stdout_write.write(str(build_ouput))
            file_stderr_write.write(str(build_error))
            file_diff.write(str(self.list_of_changed_files))
            file_stdout_write.close()
            file_stderr_write.close()
            file_diff.close()
            tar_command = "tar cvzf logs_" + self.time_format + ".tar.gz " + \
                            self.build_stdout_log_filename + " " + \
                            self.build_stderr_log_filename + " " + \
                            self.list_of_changed_files_filename
            tar_command_returncode,output,error = self.execute_command(tar_command)
            if tar_command_returncode == 0:
                sys.stdout.write("tared the log file for reference\n")
                deleting_the_log_files = "rm " + self.build_stdout_log_filename + " " + \
                                self.build_stderr_log_filename + " " + \
                                self.list_of_changed_files_filename
                deleting_the_log_files_returncode,_,_ = self.execute_command(deleting_the_log_files)
            else:
                self.DoError("Error in complaition")
        except Exception as e:
            self.DoError(str(e))

    def run_build_script(self):
        '''
        Executing the build script and take decision on the output
        ex: python build.py
        '''
        try:
            build_command = "python build.py"
            returncode,output,error = self.execute_command(build_command)
            if returncode == 0:
                sys.stdout.write("Build is successfull\n")
                self.push_binary_back_to_vcs()
            else:
                self.create_error_log_tar(output,error)
                self.DoError("Error in complaition")
        except Exception as e:
            self.DoError(str(e))

if __name__ == '__main__':
    ob = ciBuild()
    ob.get_latest_files_with_pull()
    ob.run_build_script()
