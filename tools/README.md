# Tools structure

## 2. doxygen: 
```
to generate document from comments
```
## 5. unfolding: 
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
## include:
```
file list to include in the tools. need to compile before pulling down in new machine

compile:
    - cd tools/include
    - g++ -c ./*.cpp
```
g++ unfolding.cpp ./src/*.o -o g++ unfolding.cpp ./src/*.o -o  ../include/*.ounfolding