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
│   ├── in
│   │   └── 1.in
│   └── out
│       └── 1.out
├── parse
└── test1.cpp

```
Run
```
 ./parse -t 3000 -m 512000  -i 1 -l 2 test1.cpp  
```