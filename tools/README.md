# Tools structure

## 1. include:
```
file list to include in the tools. need to compile before pulling down in new machine

compile:
    - cd tools/include
    - g++ -c ./*.cpp
```
## 2. unfolding: 
```
to unfold the context based on inputed functions

compile:
    - cd tools/unfolding/src
    - compile.sh
    - cd ../
    - compile.sh

run:
    - run.sh 
```
## 3. doxygen: 
```
to generate document from comments
```
