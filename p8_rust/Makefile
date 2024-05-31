#Build commands to copy:
#Java:
#	javac source_file.java
#Python:
#	echo "Nothing to compile."
#C#:
#	mcs -out:exec_name source_file.cs 
#C:
#	gcc -o exec_name source_file.c
#C++:
#	g++ -o exec_name source_file.cpp
#Rust:
#	rustc source_file.rs

build:
	rustc -C codegen-units=1 -C opt-level=3 -C target-cpu=native -o knapsack knapsack.rs

#Run commands to copy:
#Java:
#	java source_file
#Python 3:
#	python3 source_file.py
#C#:
#	mono exec_name
#C/C++:
#	./exec_name
#Rust:
#	./source_file

run:
	./knapsack