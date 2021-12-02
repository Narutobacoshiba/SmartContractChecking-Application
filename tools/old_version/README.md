# Tools structure

## 1. dcr2cpn: 
```
to transform from DCR to HCPN(xml -> .lna)

compile:
    - cd tools/dcr2cpn/src
    - g++ -c ./*.cpp
    - cd ../
    - g++  dcr2cpn.cpp ../include/*.o  ./src/*.o  -o dcr2cpn

run:
    - dcr2cpn --xml "xml_file_path" --out_file "out_file_path"
```
## 2. doxygen: 
```
to generate document from comments
```
## 3. ltl2prop: 
```
to convert from LTL formula to Helena (.lna file)

compile:
    - cd tools/ltl2prop/src
    - g++ -c ./*.cpp
    - cd ../
    - g++  ltl2prop.cpp ../include/*.o  ./src/*.o  -o ltl2prop

run:
    - ltl2prop --lna "lna_file_path" --json "json_file_path" --ltl "prop_file_path" --out_file "out_file_path"
```
## 4. solidity2cpn: 
```
to transform Solidity code to Helena (.lna file)
```
## 5. unfolding: 
```
to unfold the context based on inputed functions

compile:
    - cd tools/unfolding/src
    - g++ -c ./*.cpp
    - cd ../
    - g++  unfolding.cpp ../include/*.o  ./src/*.o  -o unfolding

run:
    - unfolding--lna "lna_file_path" --context "context_file_path" --param "function1/function2/..." --out_file "out_file_path"
```
## include:
```
file list to include in the tools. need to compile before pulling down in new machine

compile:
    - cd tools/include
    - g++ -c ./*.cpp
```
