Build Status : [![Build Status](http://52.221.202.229:8080/job/c++_build/badge/icon)](http://52.221.202.229:8080/job/c++_build/)

### Introduction

Integrated the build process with simple two python script, one script helps to check for building the locally and another python script helps for continuous integration(in this case have integrated with jenkins too).

### PREREQUISITES
- GIT (Version Control System)
- Python 
- Jenkins

### Build script
Implemented a build script which will build the c++ code and move the output to bin folder, stdout and stderr are produced respectively.
```
python build.py
```

By default we need to mention which build files need to be done.

### Build script result
#### Success scenario
In case of success it will create the binary folder and move the same.
```
calculator.c :  Compilation is sucess without any error
helloworld.c :  Compilation is sucess without any error

```
#### Failure scenario
In case of failure it will throw as below error.

```
calculator.c :  Compilation is sucess without any error
helloworld.c :  Compilation is failure, please find the error for your reference.
helloworld.c: In function ‘int main()’:
helloworld.c:9:4: error: expected ‘;’ before ‘return’
    return 0;
    ^
```

### CI Build script
Implemented a ci build script which will inturn invoke build.py and on successfull build it will push the binary back to repo and in case of failure it will create the zip with stdout,stderr and list of change in the files.
```
python ci_build.py
```


#### Success scenario
In case of success it will create the binary folder and move the same.
```
> python ci_build.py 
Git pull latest code was successfull
Build is successfull
git push is successfull
```
#### Failure scenario
In case of failure it will throw as below error.

```
> python ci_build.py
Git pull latest code was successfull
tared the log file for reference

> cat stdout_build.log 
calculator.c :  Compilation is sucess without any error
> cat stdout_error.log 
helloworld.c :  Compilation is failure, please find the error for your reference.
helloworld.c: In function ‘int main()’:
helloworld.c:9:4: error: expected ‘;’ before ‘return’
    return 0;
    ^
> cat list_of_changed_files.log 
helloworld.c
```

### Jenkins Integration

Installed Jenkins in AWS(Ubuntu 18.04)
URL: http://52.221.202.229:8080/job/c++_build/

Following are integrated as part of continuous script.
1. Integrated the github with jenkins with token.
2. Integrated the githubu-webhook with jenkins so whenever changes in repo it automatically triggers the build without manual intervention.
3. On succesfull build, it will push the bin back to github repo.

#### Note: On push to github the cyclic action will be triggered in jenkins to avoid those scenario the changes made inside binary are excluded in the jenkins.
4. On failure build, it will create the tar file as a artificats.

