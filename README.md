### 版本

Linux x86_64
g++  gcc : 10.2.0

### QuickStart
```
git clone https://github.com/gerayking/Cjudger.git
cd Cjudger
cmake Cmakelist
make
./parse -h
```
运行环境目录
```
.
├── config.txt
├── dev
│   └── 1
│       ├── in
│       │   ├── 1.in
│       │   └── 2.in
│       └── out
│           ├── 1.out
│           └── 2.out
├── parse
└── test1.cpp


```
Run
```
 ./parse -t 3000 -m 512000  -p 1 -l 2 test1.cpp
```
### config.txt
```
TEMPPATH = /dev
```
